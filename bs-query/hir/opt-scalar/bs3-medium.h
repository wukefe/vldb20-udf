static I horse_main(V *h_rtn);
//#define myfabs(x) ((x)>=0?(x):-(x))
// exp, fabs, sqrt

static I horse_CNDF_opt(V *rtn, V *args){
    V InputX   = args[0];
    V invs2xPI = args[1];
    V OutputX = incV();
    L r0 = vn(InputX);
    initV(OutputX, H_E, r0);
    DOP(r0, {
            E xK2 = 1.0 / (1.0 + 0.2316419 * fabs(vE(InputX,i)));
            E xK2_2 = xK2 * xK2;
            E xK2_3 = xK2 * xK2_2;
            E xK2_4 = xK2 * xK2_3;
            E xLocal=1.0-ve(invs2xPI)*myexp(-0.5*vE(InputX,i)*vE(InputX,i))*((xK2_2 * -0.356563782) + (xK2_3 * 1.781477937) + (xK2_4 * -1.821255978) + xK2 * xK2_4 * 1.330274429 + xK2 * 0.319381530);
            vE(OutputX,i)=(vE(InputX,i)<0?(1.0-xLocal):xLocal);
            })
    rtn[0] = OutputX;
}

static I horse_BlkSchls_opt(V *rtn, V *args){
	V sptprice   = args[0];
	V strike     = args[1];
	V rate       = args[2];
	V divq       = args[3];
	V volatility = args[4];
	V time       = args[5];
	V otype      = args[6];
	V divs       = args[7];
	V dfrefval   = args[8];
    L r0 = vn(sptprice);
    V xD1        = incV();
    V xD2        = incV();
    V NofXd1     = incV();
    V NofXd2     = incV();
    V invs2xPI   = incV();
    V OptionPrice= incV();
    V tempV[10]; // temporary return vars
    initV(xD1, H_E, r0);
    initV(xD2, H_E, r0);
    DOP(r0, { E xDen = vE(volatility,i) * sqrt(vE(time,i));
            vE(xD1,i)=((vE(rate,i)+vE(volatility,i)*vE(volatility,i)*0.5)*vE(time,i) + mylog(vE(sptprice,i)/vE(strike,i)))/xDen;
            vE(xD2,i)=vE(xD1,i)-xDen; })
    PROFILE(15, copyV(invs2xPI, LiteralF64(0.39894228040143270286)));
    tic();
    horse_CNDF_opt(tempV, (V []){xD1, invs2xPI}); NofXd1 = tempV[0];
    horse_CNDF_opt(tempV, (V []){xD2, invs2xPI}); NofXd2 = tempV[0];
    initV(OptionPrice, H_E, r0);
    DOP(r0, {
            E FutureValueX = vE(strike,i) * myexp(-1*vE(rate,i)*vE(time,i));
            vE(OptionPrice,i)=vB(otype,i)?(FutureValueX * (1.0-vE(NofXd2,i))-vE(sptprice,i) * (1.0-vE(NofXd1,i))):(vE(sptprice,i)*vE(NofXd1,i) - FutureValueX * vE(NofXd2,i)); })
    //WP("option price: %lld\n", vn(OptionPrice));
    //printV2(OptionPrice, 20); getchar();
    rtn[0] = OptionPrice;
}


static I horse_CNDF(V *rtn, V *args){
    V InputX   = args[0];
    V invs2xPI = args[1];
    V t0 = incV(); V t1 = incV(); V t2 = incV(); V t3 = incV();
    V t4 = incV(); V t5 = incV(); V t6 = incV(); V t7 = incV();
    V t8 = incV(); V t9 = incV(); V t10= incV(); V t11= incV();
    V t12= incV(); V t13= incV(); V t14= incV(); V t15= incV();
    V t16= incV();
    V sign       = incV();
    V xNPrimeofX = incV();
    V expValues  = incV();
    V xInput     = incV();
    V xK2        = incV();
    V xK2_2      = incV();
    V xK2_3      = incV();
    V xK2_4      = incV();
    V xK2_5      = incV();
    V xLocal     = incV();
    V xLocal_1   = incV();
    V xLocal_2   = incV();
    V OutputX    = incV();
    PROFILE(1, pfnLt(sign, InputX, LiteralF64(0)));
    PROFILE(2, pfnAbs(xInput, InputX));
    PROFILE(3, pfnMul(t1, InputX, InputX));
    PROFILE(4, pfnMul(t2, LiteralF64(-0.5), t1));
    PROFILE(5, pfnExp(expValues, t2));
    PROFILE(6, pfnMul(xNPrimeofX, invs2xPI, expValues));
    PROFILE(7, pfnMul(t3, LiteralF64(0.2316419), xInput));
    PROFILE(8, pfnPlus(t4, LiteralF64(1), t3));
    PROFILE(9, pfnDiv(xK2, LiteralF64(1), t4));
    PROFILE(10, pfnMul(xK2_2, xK2, xK2));
    PROFILE(11, pfnMul(xK2_3, xK2, xK2_2));
    PROFILE(12, pfnMul(xK2_4, xK2, xK2_3));
    PROFILE(13, pfnMul(xK2_5, xK2, xK2_4));
    PROFILE(14, pfnMul(xLocal_1, xK2, LiteralF64(0.319381530)));
    PROFILE(15, pfnMul(t5, xK2_2, LiteralF64(-0.356563782)));
    PROFILE(16, pfnMul(t6, xK2_3, LiteralF64(1.781477937)));
    PROFILE(17, pfnMul(t7, xK2_4, LiteralF64(-1.821255978)));
    PROFILE(18, pfnMul(t8, xK2_5, LiteralF64(1.330274429)));
    PROFILE(19, pfnPlus(t9, t5, t6));
    PROFILE(20, pfnPlus(t10, t9, t7));
    PROFILE(99, pfnPlus(xLocal_2, t10, t8));
    PROFILE(21, pfnPlus(t11, xLocal_2, xLocal_1));
    PROFILE(22, pfnMul(t12, xNPrimeofX, t11));
    PROFILE(23, pfnMinus(xLocal, LiteralF64(1.0), t12));
    PROFILE(24, pfnNot(t13, sign));
    PROFILE(25, pfnMul(t14, t13, xLocal));
    PROFILE(26, pfnMinus(t15, LiteralF64(1.0), xLocal));
    PROFILE(27, pfnMul(t16, sign, t15));
    PROFILE(28, pfnPlus(OutputX, t16, t14));
    //WP("2. %lld\n", vn(OutputX)); printV2(OutputX, 10); getchar();
    rtn[0] = OutputX;
}


static I horse_BlkSchls(V *rtn, V *args){
	V sptprice   = args[0];
	V strike     = args[1];
	V rate       = args[2];
	V divq       = args[3];
	V volatility = args[4];
	V time       = args[5];
	V otype      = args[6];
	V divs       = args[7];
	V dfrefval   = args[8];
    V t0 = incV();  V t1 = incV(); V t2 = incV();  V t3 = incV();
    V t4 = incV();  V t5 = incV(); V t6 = incV();  V t7 = incV();
    V t8 = incV();  V t9 = incV(); V t10= incV();  V t11= incV();
    V t12= incV();  V t13= incV(); V t14= incV();  V t15= incV();
    V t16= incV();  V t17= incV(); V t18= incV();
    V xSqrtTime     = incV();
    V xLogTerm      = incV();
    V xRiskFreeRate = incV();
    V xDen          = incV();
    V xPowerTerm    = incV();
    V xD1           = incV();
    V xD2           = incV();
    V NofXd1        = incV();
    V NofXd2        = incV();
    V invs2xPI      = incV();
    V FutureValueX  = incV();
    V OptionPrice   = incV();
    V tempV[10]; // temporary return vars
    //WP("time = %lld\n", vn(time)); getchar();
    PROFILE(1, pfnSqrt(xSqrtTime, time));
    PROFILE(2, pfnDiv(t0, sptprice, strike));
    PROFILE(3, pfnLog(xLogTerm, t0));
    PROFILE(4, copyV(xRiskFreeRate, rate));
    PROFILE(5, pfnMul(xDen, volatility, xSqrtTime));
    PROFILE(6, pfnMul(t1  , volatility, LiteralF64(0.5)));
    PROFILE(7, pfnMul(xPowerTerm, volatility, t1));
    PROFILE(8, pfnPlus(t2 , xRiskFreeRate, xPowerTerm));
    PROFILE(9, pfnMul(t3 , time, t2));
    PROFILE(10, pfnPlus(t4 , xLogTerm, t3));
    PROFILE(11, pfnDiv(xD1 , t4, xDen));
    PROFILE(13, pfnMinus(xD2, xD1, xDen));
    PROFILE(15, copyV(invs2xPI, LiteralF64(0.39894228040143270286)));
    horse_CNDF(tempV, (V []){xD1, invs2xPI}); NofXd1 = tempV[0];
    horse_CNDF(tempV, (V []){xD2, invs2xPI}); NofXd2 = tempV[0];
    PROFILE(18, pfnMul(t5 , rate, time));
    PROFILE(19, pfnNeg(t6 , t5));
    PROFILE(20, pfnExp(t7 , t6));
    PROFILE(21, pfnMul(FutureValueX, strike, t7));
    PROFILE(22, pfnMinus(t8, LiteralF64(1.0), NofXd1));
    PROFILE(23, pfnMul(t9, sptprice, t8));
    PROFILE(24, pfnMinus(t10, LiteralF64(1.0), NofXd2));
    PROFILE(25, pfnMul(t11, FutureValueX, t10));
    PROFILE(26, pfnMinus(t12, t11, t9));
    PROFILE(27, pfnMul(OptionPrice, otype, t12));
    PROFILE(28, pfnMul(t13, FutureValueX, NofXd2));
    PROFILE(29, pfnMul(t14, sptprice, NofXd1));
    PROFILE(30, pfnMinus(t15, t14, t13));
    PROFILE(31, pfnNot(t16, otype));
    PROFILE(32, pfnMul(t17, t16, t15));
    PROFILE(33, pfnPlus(OptionPrice, OptionPrice, t17));
    //WP("option price: %lld\n", vn(OptionPrice));
    //printV2(OptionPrice, 20); getchar();
    rtn[0] = OptionPrice;
}

static V horse_bs3_high(V t0){
    V optiontype = incV(); V optiontype1 = incV();
    V sptprice   = incV(); V sptprice1   = incV();
    V optionprice= incV(); V optionprice1= incV();
    PROFILE(1 , pfnColumnValue(optiontype , t0, LiteralSymbol("optiontype")));
    PROFILE(2 , pfnColumnValue(sptprice   , t0, LiteralSymbol("sptprice")));
    PROFILE(3 , pfnColumnValue(optionprice, t0, LiteralSymbol("optionprice")));
    // step 1: apply filter
    V filter = incV();
    L r0=vn(optionprice);
    initV(filter, H_B, r0);
    DOP(r0, vB(filter,i)=vE(optionprice,i)>6)
    // step 2: parallelism for boolean selection
    L lenZ = 0, parZ[H_CORE], offset[H_CORE];
    memset(parZ  , 0, sizeof(L)*H_CORE);
    memset(offset, 0, sizeof(L)*H_CORE);
    getNumOfNonZero(filter,parZ);
    DOI(H_CORE, lenZ += parZ[i])
    DOIa(H_CORE, offset[i]=parZ[i-1]+offset[i-1])
    //P("lenZ = %lld\n", lenZ); getchar();
    initV(optiontype1 , H_C, lenZ);
    initV(sptprice1   , H_E, lenZ);
    DOT(vn(sptprice), if(vB(filter,i)){ L k=offset[tid]++;
            vE(sptprice1   ,k)=vE(sptprice   ,i); 
            vC(optiontype1 ,k)=vC(optiontype ,i); })
    V columnname = incV();
    V columnvalue= incV();
    V result     = incV();
    PROFILE(3, copyV(columnname, LiteralVectorSymbol(2, (S []){"optiontype", "sptprice"})));
    PROFILE(4, pfnList(columnvalue, 2, (V []){optiontype1,sptprice1}));
    PROFILE(5, pfnTable(result, columnname, columnvalue));
    return result;
}

static I horse_main(V *h_rtn){
    V t0 = incV();
    V sptprice   = incV();
    V strike     = incV();
    V rate       = incV();
    V divq       = incV();
    V volatility = incV();
    V time       = incV();
    V optiontype = incV();
    V divs       = incV();
    V dgrefval   = incV();
    V columnname = incV();
    V columnvalue= incV();
    V optionprice= incV();
    V otype      = incV();
    V result     = incV();
    V tempV[10]; // temporary return vars
    PROFILE(1 , pfnLoadTable(t0, LiteralSymbol("blackscholes")));
    PROFILE(2 , pfnColumnValue(sptprice  , t0, LiteralSymbol("sptprice")));
    PROFILE(3 , pfnColumnValue(strike    , t0, LiteralSymbol("strike")));
    PROFILE(4 , pfnColumnValue(rate      , t0, LiteralSymbol("rate")));
    PROFILE(5 , pfnColumnValue(divq      , t0, LiteralSymbol("divq")));
    PROFILE(6 , pfnColumnValue(volatility, t0, LiteralSymbol("volatility")));
    PROFILE(7 , pfnColumnValue(time      , t0, LiteralSymbol("time")));
    PROFILE(8 , pfnColumnValue(optiontype, t0, LiteralSymbol("optiontype")));
    PROFILE(9 , pfnColumnValue(divs      , t0, LiteralSymbol("divs")));
    PROFILE(10, pfnColumnValue(dgrefval  , t0, LiteralSymbol("dgrefval")));
    PROFILE(11, pfnEq(otype, optiontype, LiteralChar('P')));
    horse_BlkSchls_opt(tempV, (V []){sptprice,strike,rate,divq,volatility,time,otype,divs,dgrefval}); optionprice = tempV[0];
    PROFILE(11, copyV(columnname, LiteralVectorSymbol(3, (S []){"optiontype", "sptprice", "optionprice"})));
    PROFILE(12, pfnList(columnvalue, 3, (V []){optiontype,sptprice,optionprice}));
    PROFILE(13, pfnTable(result, columnname, columnvalue));
    h_rtn[0] = horse_bs3_high(result);
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
