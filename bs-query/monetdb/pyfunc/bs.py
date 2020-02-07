import numpy

def CNDF(InputX, invs2xPI):
    sign          = InputX < 0
    xInput        = numpy.abs(InputX)
    expValues     = numpy.exp(-0.5 * (InputX * InputX))
    xNPrimeofX    = invs2xPI * expValues
    xK2           = 1.0 / (1.0 + 0.2316419 * xInput)
    xK2_2         = xK2 * xK2
    xK2_3         = xK2 * xK2_2
    xK2_4         = xK2 * xK2_3
    xK2_5         = xK2 * xK2_4
    xLocal_1      = xK2 * 0.319381530
    xLocal_2      = (xK2_2 * -0.356563782) + (xK2_3 * 1.781477937) + (xK2_4 * -1.821255978) + xK2_5 * 1.330274429
    xLocal        = 1.0 - xNPrimeofX * (xLocal_2 + xLocal_1)
    OutputX       = (sign * (1.0 - xLocal)) + (~sign) * xLocal
    return OutputX

def BlkSchls(timet, sptprice, strike, rate, volatility, time, optiontype):
    xSqrtTime     = numpy.sqrt(time)
    xLogTerm      = logValues = numpy.log(sptprice * 1.0 / strike)
    xRiskFreeRate = rate
    otype         = optiontype=='P'
    xDen          = volatility * xSqrtTime
    xPowerTerm    = volatility * (volatility * 0.5)
    d1 = xD1      = (xLogTerm + time * (xRiskFreeRate + xPowerTerm)) / xDen
    d2 = xD2      = xD1 - xDen
    invs2xPI      = 0.39894228040143270286
    NofXd1        = CNDF( d1, invs2xPI )
    NofXd2        = CNDF( d2, invs2xPI )
    FutureValueX  = strike * numpy.exp(- rate * time)
    OptionPrice   = otype * ((FutureValueX * (1.0 - NofXd2)) - (sptprice * (1.0 - NofXd1)))
    OptionPrice   = OptionPrice + (~otype) * ((sptprice * NofXd1) - (FutureValueX * NofXd2))
    return OptionPrice


