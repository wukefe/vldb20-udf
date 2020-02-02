function OptionPrice = BlkSchls(sptprice,strike,rate,volatility,time,otype)
% DOUBLE&1*?&REAL DOUBLE&1*?&REAL DOUBLE&1*?&REAL DOUBLE&1*?&REAL DOUBLE&1*?&REAL DOUBLE&1*?&REAL
    xSqrtTime = sqrt(time);
    xLogTerm   = log( sptprice ./ strike );
    xRiskFreeRate = rate;
    xDen = volatility .* xSqrtTime;
    xPowerTerm = volatility .* volatility .* 0.5;

    xD1  = ((xRiskFreeRate + xPowerTerm) .* time + xLogTerm) ./ xDen;
    xD2  = xD1 -  xDen;

    invs2xPI = 0.39894228040143270286;
    NofXd1 = CNDF( xD1, invs2xPI );
    NofXd2 = CNDF( xD2, invs2xPI );

    FutureValueX = strike .* ( exp( -(rate).*(time) ) );
    OptionPrice   = otype .* ((FutureValueX .* (1.0 - NofXd2)) - (sptprice .* (1.0 - NofXd1)));
    OptionPrice   = OptionPrice + (~otype) .* ((sptprice .* NofXd1) - (FutureValueX .* NofXd2));
end

