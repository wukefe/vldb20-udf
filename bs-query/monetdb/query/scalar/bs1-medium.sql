SELECT sptprice, optiontype, bs_udf_scalar(sptprice, strike, rate, volatility, time, optiontype) as optionprice
FROM blackscholes
WHERE sptprice BETWEEN 51 AND 100
LIMIT 10;

