// Parsing time (ms): 0.19
 // - #: 24
 // - #: 4
 // - #: 2
// Total # of fused stmts: 30
static I horse_main(V *h_rtn);
static I q1_patterncompress_0(V *z, V x, V *y);
static I q1_autofusion_12(V z, V *x);
static I q1_autofusion_11(V z, V *x);
static I q1_patternindex_13(V *z, V *x, V y);
static I q1_autofusionlist_1(V *z, V *x);
static I q1_patternindex_14(V *z, V *x, V y);

static I q1_patterncompress_0(V *z, V x, V *y){
    V z0 = z[0]; // t23
    V z1 = z[1]; // t24
    V z2 = z[2]; // t25
    V z3 = z[3]; // t26
    V z4 = z[4]; // t27
    V z5 = z[5]; // t28
    V y0 = y[0]; // t6
    V y1 = y[1]; // t7
    V y2 = y[2]; // t8
    V y3 = y[3]; // t9
    V y4 = y[4]; // t10
    V y5 = y[5]; // t11
    L len = vn(x), k = 0;
    L lenZ = 0, parZ[H_CORE], offset[H_CORE];
    DOI(H_CORE, parZ[i]=offset[i]=0)
    CHECKE(getNumOfNonZero(x,parZ));
    DOI(H_CORE, lenZ += parZ[i])
    DOIa(H_CORE, offset[i]=parZ[i-1]+offset[i-1])
    initV(z0,H_E,lenZ);
    initV(z1,H_E,lenZ);
    initV(z2,H_E,lenZ);
    initV(z3,H_E,lenZ);
    initV(z4,H_C,lenZ);
    initV(z5,H_C,lenZ);
    DOT(len, if(vB(x,i)){L c=offset[tid]++;\
        vE(z0,c) = vE(y0,i);\
        vE(z1,c) = vE(y1,i);\
        vE(z2,c) = vE(y2,i);\
        vE(z3,c) = vE(y3,i);\
        vC(z4,c) = vC(y4,i);\
        vC(z5,c) = vC(y5,i);\
    })
    R 0;
}

static I q1_autofusion_12(V z, V *x){
    V x0=x[0]; // t24
    V x1=x[1]; // t25
    initV(z, H_E, vn(x0));
    DOP(vn(x0), vE(z,i)=MUL(vE(x0,i),MINUS(1,vE(x1,i)))) R 0;
}
static I q1_autofusion_11(V z, V *x){
    V x0=x[0]; // t24
    V x1=x[1]; // t25
    V x2=x[2]; // t26
    initV(z, H_E, vn(x0));
    DOP(vn(x0), vE(z,i)=MUL(MUL(vE(x0,i),MINUS(1,vE(x1,i))),PLUS(1,vE(x2,i)))) R 0;
}
static I q1_patternindex_13(V *z, V *x, V y){
    V z0 = z[0]; // t45
    V z1 = z[1]; // t46
    V x0 = x[0]; // t27
    V x1 = x[1]; // t28
    initV(z0, H_C, vn(y));
    initV(z1, H_C, vn(y));
    DOP(vn(z0), {
        vC(z0,i) = vC(x0, vL(y,i));
        vC(z1,i) = vC(x1, vL(y,i));
    })
    R 0;
}

static I q1_autofusionlist_1(V *z, V *x){
    V x0=x[0]; // t27
    V x1=x[1]; // t44
    V x2=x[2]; // t25
    V x3=x[3]; // t40
    V x4=x[4]; // t36
    V x5=x[5]; // t24
    V x6=x[6]; // t23
    V z0=z[0]; // t73
    V z1=z[1]; // t70
    V z2=z[2]; // t64
    V z3=z[3]; // t61
    V z4=z[4]; // t58
    V z5=z[5]; // t55
    V z6=z[6]; // t52
    V z7=z[7]; // t49
    initV(z0, H_L, vn(x1)); // t73
    initV(z1, H_E, vn(x1)); // t70
    initV(z2, H_E, vn(x1)); // t64
    initV(z3, H_E, vn(x1)); // t61
    initV(z4, H_E, vn(x1)); // t58
    initV(z5, H_E, vn(x1)); // t55
    initV(z6, H_E, vn(x1)); // t52
    initV(z7, H_E, vn(x1)); // t49
        DOJ(vn(x1), {V t=vV(x1,j); \
            E c1=0;E c2=0; E c3=0; E c4=0; E c5=0; E c6=0; E c7=0; E c8=0; \
            DOP(vn(t), {L k=vL(t,i);\
                c2+=vE(x2,k); \
                c3+=vE(x3,k); \
                c4+=vE(x4,k); \
                c5+=vE(x5,k); \
                c6+=vE(x5,k); \
                c7+=vE(x6,k); \
                c8+=vE(x6,k); \
            }, reduction(+:c1,c2,c3,c4,c5,c6,c7,c8)) \
            vL(z0,j)=vn(vV(x1,j)); \
            vE(z1,j)=c2/vn(t); \
            vE(z2,j)=c3; \
            vE(z3,j)=c4; \
            vE(z4,j)=c5/vn(t); \
            vE(z5,j)=c6; \
            vE(z6,j)=c7/vn(t); \
            vE(z7,j)=c8; \
        })
    R 0;
}

static I q1_patternindex_14(V *z, V *x, V y){
    V z0 = z[0]; // t76
    V z1 = z[1]; // t77
    V z2 = z[2]; // t78
    V z3 = z[3]; // t79
    V z4 = z[4]; // t80
    V z5 = z[5]; // t81
    V z6 = z[6]; // t82
    V z7 = z[7]; // t83
    V z8 = z[8]; // t84
    V z9 = z[9]; // t85
    V x0 = x[0]; // t45
    V x1 = x[1]; // t46
    V x2 = x[2]; // t49
    V x3 = x[3]; // t55
    V x4 = x[4]; // t61
    V x5 = x[5]; // t64
    V x6 = x[6]; // t52
    V x7 = x[7]; // t58
    V x8 = x[8]; // t70
    V x9 = x[9]; // t73
    initV(z0, H_C, vn(y));
    initV(z1, H_C, vn(y));
    initV(z2, H_E, vn(y));
    initV(z3, H_E, vn(y));
    initV(z4, H_E, vn(y));
    initV(z5, H_E, vn(y));
    initV(z6, H_E, vn(y));
    initV(z7, H_E, vn(y));
    initV(z8, H_E, vn(y));
    initV(z9, H_L, vn(y));
    DOP(vn(z0), {
        vC(z0,i) = vC(x0, vL(y,i));
        vC(z1,i) = vC(x1, vL(y,i));
        vE(z2,i) = vE(x2, vL(y,i));
        vE(z3,i) = vE(x3, vL(y,i));
        vE(z4,i) = vE(x4, vL(y,i));
        vE(z5,i) = vE(x5, vL(y,i));
        vE(z6,i) = vE(x6, vL(y,i));
        vE(z7,i) = vE(x7, vL(y,i));
        vE(z8,i) = vE(x8, vL(y,i));
        vL(z9,i) = vL(x9, vL(y,i));
    })
    R 0;
}


static I horse_main(V *h_rtn){
    V t0 = incV(); V t6 = incV(); V t7 = incV(); V t8 = incV(); 
    V t9 = incV(); V t10 = incV(); V t11 = incV(); V t12 = incV(); 
    V t23 = incV(); V t40 = incV(); V t24 = incV(); V t41 = incV(); 
    V t25 = incV(); V t50 = incV(); V t42 = incV(); V t26 = incV(); 
    V t18 = incV(); V t51 = incV(); V t43 = incV(); V t35 = incV(); 
    V t27 = incV(); V t60 = incV(); V t52 = incV(); V t44 = incV(); 
    V t36 = incV(); V t28 = incV(); V t61 = incV(); V t53 = incV(); 
    V t45 = incV(); V t37 = incV(); V t70 = incV(); V t62 = incV(); 
    V t54 = incV(); V t46 = incV(); V t38 = incV(); V t71 = incV(); 
    V t63 = incV(); V t55 = incV(); V t47 = incV(); V t39 = incV(); 
    V t80 = incV(); V t72 = incV(); V t64 = incV(); V t56 = incV(); 
    V t48 = incV(); V t81 = incV(); V t73 = incV(); V t57 = incV(); 
    V t49 = incV(); V t82 = incV(); V t74 = incV(); V t58 = incV(); 
    V t83 = incV(); V t75 = incV(); V t59 = incV(); V t84 = incV(); 
    V t76 = incV(); V t68 = incV(); V t85 = incV(); V t77 = incV(); 
    V t69 = incV(); V t86 = incV(); V t78 = incV(); V t87 = incV(); 
    V t79 = incV(); V t88 = incV(); 
    V tempV[10]; // temporary return vars
    PROFILE(4, pfnLoadTable(t0, LiteralSymbol("lineitem")));
    PROFILE(5, pfnColumnValue(t6, t0, LiteralSymbol("l_quantity")));
    PROFILE(6, pfnColumnValue(t7, t0, LiteralSymbol("l_extendedprice")));
    PROFILE(7, pfnColumnValue(t8, t0, LiteralSymbol("l_discount")));
    PROFILE(8, pfnColumnValue(t9, t0, LiteralSymbol("l_tax")));
    PROFILE(9, pfnColumnValue(t10, t0, LiteralSymbol("l_returnflag")));
    PROFILE(10, pfnColumnValue(t11, t0, LiteralSymbol("l_linestatus")));
    PROFILE(11, pfnColumnValue(t12, t0, LiteralSymbol("l_shipdate")));
    PROFILE(12, pfnLeq(t18, t12, LiteralDate(19980902)));
    PROFILE(13, q1_patterncompress_0((V []){t23, t24, t25, t26, t27, t28}, t18, (V []){t6, t7, t8, t9, t10, t11}));
    PROFILE(20, q1_autofusion_12(t36, (V[]){t24,t25}));
    PROFILE(24, q1_autofusion_11(t40, (V[]){t24,t25,t26}));
    PROFILE(25, pfnList(t41, 2, (V []){t27, t28}));
    PROFILE(26, pfnGroup(t42, t41));
    PROFILE(27, pfnKeys(t43, t42));
    PROFILE(28, pfnValues(t44, t42));
    PROFILE(29, q1_patternindex_13((V []){t45, t46}, (V []){t27, t28}, t43));
    PROFILE(54, q1_autofusionlist_1((V []){t73,t70,t64,t61,t58,t55,t52,t49}, (V []){t27,t44,t25,t40,t36,t24,t23}));
    PROFILE(55, pfnList(t74, 2, (V []){t45, t46}));
    PROFILE(56, pfnOrderBy(t75, t74, LiteralVectorBool(2, (B []){1, 1})));
    PROFILE(57, q1_patternindex_14((V []){t76, t77, t78, t79, t80, t81, t82, t83, t84, t85}, (V []){t45, t46, t49, t55, t61, t64, t52, t58, t70, t73}, t75));
    PROFILE(67, copyV(t86,LiteralVectorSymbol(10, (S []){"l_returnflag", "l_linestatus", "sum_qty", "sum_base_price", "sum_disc_price", "sum_charge", "avg_qty", "avg_price", "avg_disc", "count_order"})));
    PROFILE(68, pfnList(t87, 10, (V []){t76, t77, t78, t79, t80, t81, t82, t83, t84, t85}));
    PROFILE(69, pfnTable(t88, t86, t87));
    h_rtn[0] = t88;
    return 0;
}

E horse_entry(){
    V rtns[99];
    tic();
    HORSE_UDF(0, horse_main(rtns), {});
    E elapsed = calc_toc();
    P("The elapsed time (ms): %g\n", elapsed);
    P("Output:\n");
    DOI(1, printV2(rtns[i],20))
    return elapsed;
}

// Compiling time (ms): 0.529
