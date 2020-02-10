#ifndef __H_C_LIB__
#define __H_C_LIB__

#include <float.h>  // DBL_MAX

//#define NO_PROFILE_INFO

//#define PROFILE(c, n, stmt) P("Line: %d\n",c); V n = allocNode(); stmt
#ifdef NO_PROFILE_INFO
    #define PROFILE(c, stmt) stmt
#else
    #define PROFILE(c,stmt) { my_tic(); \
        I e=stmt; if(e) printErrMsg(e); \
        E t0=my_toc(0); \
        if(t0>=0.1) P("[Profiling] Line %d: %g ms\n", c,t0); \
        else P("[Profiling] Line %d:\n", c); }
#endif

#define DOP_ACC(n, x, ...) {L i2=n; \
    _Pragma(STRINGIFY(acc parallel __VA_ARGS__)) \
    for(L i=0;i<i2;i++) x;}


static V incV(){
    if(buffS < MAX_V) return buffV[buffS++];
    else EP("Buff not available: %d\n", buffS);
}

static B isParOuter(V x){
    if(vn(x) > 0){
        L nums = vn(x)<100?vn(x):100;
        L max_size = -1;
        DOI(nums, if(max_size<vn(vV(x,i))) max_size=vn(vV(x,i)))
        R max_size < 10*vn(x);
    }
    R true;
}

static B MEMBER_CONST(S s, V x){
    DOI(xn, if(s[0]==vS(x,i)[0] && !strcmp(s,vS(x,i)))R 1) R 0;
}

static B MEMBER_CONST_Q(Q id, V x){
    DOI(xn, if(id == vQ(x,i))R 1) R 0;
}

//#define HORSE_UDF(x) do{L cur=buffS; x; buffS=cur;}while(0)
#define HORSE_UDF(c,stmt,cb) do{L cur=buffS; PROFILE(c,stmt); buffS=cur; cb}while(0)

#define LiteralSingle(T,t) {V z=incV(); initV(z, H_##T, 1); v##t(z)=x; R z;}
static V LiteralBool(B x) { LiteralSingle(B, b); }
static V LiteralI8  (J x) { LiteralSingle(J, j); }
static V LiteralI16 (H x) { LiteralSingle(H, h); }
static V LiteralI32 (I x) { LiteralSingle(I, i); }
static V LiteralI64 (L x) { LiteralSingle(L, l); }
static V LiteralF32 (F x) { LiteralSingle(F, f); }
static V LiteralF64 (E x) { LiteralSingle(E, e); }
static V LiteralDate(L x) { LiteralSingle(D, d); }
static V LiteralSymbol(S s) {Q x=getSymbol(s); LiteralSingle(Q, q);}

#define LiteralVector(T) {V z=incV(); initV(z, H_##T, n); DOI(n, v##T(z,i)=x[i]) R z;}
static V LiteralVectorBool(I n, B *x) { LiteralVector(B); }
static V LiteralVectorI8  (I n, J *x) { LiteralVector(J); }
static V LiteralVectorI16 (I n, H *x) { LiteralVector(H); }
static V LiteralVectorI32 (I n, I *x) { LiteralVector(I); }
static V LiteralVectorI64 (I n, L *x) { LiteralVector(L); }
static V LiteralVectorF32 (I n, F *x) { LiteralVector(F); }
static V LiteralVectorF64 (I n, E *x) { LiteralVector(E); }
static V LiteralVectorDate(I n, L *x) { LiteralVector(D); }
static V LiteralVectorString(I n, S *x) { LiteralVector(S); }

#define LiteralVectorDO(T,x) {V z=incV(); initV(z, H_##T, n); DOI(n, v##T(z,i)=x) R z;}
static V LiteralVectorSymbol(I n, S *s) { LiteralVectorDO(Q,getSymbol(s[i])); }

/* macros for fusion */

#ifdef LT
#undef LT
#endif

#ifdef EQ
#undef EQ
#endif

#define AND(x,y) (x)&&(y)
#define OR(x,y)  (x)||(y)
#define GEQ(x,y) (x)>=(y)
#define LEQ(x,y) (x)<=(y)
#define LT(x,y)  (x)<(y)
#define GT(x,y)  (x)>(y)
#define EQ(x,y)  (x)==(y)
#define NEQ(x,y) (x)!=(y)

#define MUL(x,y)   (x)*(y)
#define DIV(x,y)   (x)/(y)
#define MINUS(x,y) (x)-(y)
#define PLUS(x,y)  (x)+(y)
#define NOT(x)     !(x)

// copy from pfnLike
#define LIKEMATCH(src,slen,re,matchData) \
    pcre2_jit_match(re,\
       (PCRE2_SPTR)src,\
        slen,0,PCRE2_ANCHORED|PCRE2_NO_UTF_CHECK,matchData,NULL\
    )<0?0:1

// sequential version
//#define DOLIKE(n, x, ...){ L seg=(n)/H_CORE; \
    pcre2_match_context *mcontext = pcre2_match_context_create(NULL); \
    pcre2_jit_stack *jit_stack = pcre2_jit_stack_create(1024*1024, 4096*1024, NULL);\
    pcre2_jit_stack_assign(mcontext, NULL, jit_stack);\
    pcre2_match_data *match = pcre2_match_data_create_from_pattern(re, NULL);\
    DOI(n, x); \
    pcre2_match_data_free(match); \
    pcre2_match_context_free(mcontext); \
    pcre2_jit_stack_free(jit_stack); \
}

#define DOLIKE(n, x, ...){ L seg=(n)/H_CORE; \
    _Pragma(STRINGIFY(omp parallel __VA_ARGS__)) \
    { \
        pcre2_match_context *mcontext = pcre2_match_context_create(NULL); \
        pcre2_jit_stack *jit_stack = pcre2_jit_stack_create(1024*1024, 4096*1024, NULL);\
        pcre2_jit_stack_assign(mcontext, NULL, jit_stack);\
        pcre2_match_data *match = pcre2_match_data_create_from_pattern(re, NULL);\
        L tid = omp_get_thread_num(); \
        for(L i=tid*seg,i2=(tid!=H_CORE-1?(i+seg):(n));i<i2;i++) x; \
        pcre2_match_data_free(match); \
        pcre2_match_context_free(mcontext); \
        pcre2_jit_stack_free(jit_stack); \
    } \
}


#endif
