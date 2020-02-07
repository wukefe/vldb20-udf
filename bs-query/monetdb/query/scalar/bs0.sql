SELECT sptprice, optiontype, bs_udf_scalar(sptprice, strike, rate, volatility, time, optiontype) as optionprice
FROM blackscholes
LIMIT 10;
