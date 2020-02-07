SELECT optiontype, sptprice
FROM bs_udf_tbl((select * from blackscholes))
WHERE optionprice > 15
LIMIT 10;
