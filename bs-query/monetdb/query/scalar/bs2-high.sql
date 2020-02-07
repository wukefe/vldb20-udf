SELECT sptprice, optiontype
FROM (
	SELECT sptprice, optiontype, bs_udf_scalar(sptprice, strike, rate, volatility, time, optiontype) as optionprice
	FROM blackscholes
) AS table_bs0
WHERE sptprice < 50 OR sptprice > 100
LIMIT 10;
