static I horse_main(V *h_rtn);

static V horse_bs2_high(V t0){
    V optiontype = incV(); V optiontype1 = incV();
    V sptprice   = incV(); V sptprice1   = incV();
    PROFILE(1 , pfnColumnValue(optiontype, t0, LiteralSymbol("optiontype")));
    PROFILE(2 , pfnColumnValue(sptprice  , t0, LiteralSymbol("sptprice")));
    // step 1: apply filter
    V filter = incV();
    L r0 = vn(sptprice);
    initV(filter, H_B, r0);
    DOP(r0, vB(filter,i)=vE(sptprice,i)>=50&&vE(sptprice,i)<=100)
    // step 2: parallelism for boolean selection
    L lenZ = 0, parZ[H_CORE], offset[H_CORE];
    memset(parZ  , 0, sizeof(L)*H_CORE);
    memset(offset, 0, sizeof(L)*H_CORE);
    getNumOfNonZero(filter,parZ);
    DOI(H_CORE, lenZ += parZ[i])
    DOIa(H_CORE, offset[i]=parZ[i-1]+offset[i-1])
    //P("lenZ = %lld\n", lenZ); getchar();
    initV(optiontype1, H_C, lenZ);
    initV(sptprice1  , H_E, lenZ);
    DOT(r0, if(vB(filter,i)){ L k=offset[tid]++;
            vC(optiontype1,k)=vC(optiontype,i);
            vE(sptprice1  ,k)=vE(sptprice  ,i); })
    // step 3: partial results passing
    V columnname = incV();
    V columnvalue= incV();
    V result     = incV();
    PROFILE(11, copyV(columnname, LiteralVectorSymbol(2, (S []){"optiontype", "sptprice"})));
    PROFILE(12, pfnList(columnvalue, 2, (V []){optiontype1,sptprice1}));
    PROFILE(13, pfnTable(result, columnname, columnvalue));
    return result;
}

static I horse_main(V *h_rtn){
    V t0 = incV(); 
    PROFILE(1 , pfnLoadTable(t0, LiteralSymbol("blackscholes")));
    h_rtn[0] = horse_bs2_high(t0);
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
