SELECT sptprice, optiontype, bs_udf_scalar(sptprice, strike, rate, volatility, time, optiontype) as optionprice
FROM blackscholes
WHERE sptprice < 50 OR sptprice > 100
LIMIT 10;

