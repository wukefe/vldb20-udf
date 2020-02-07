SELECT optiontype, sptprice
FROM bs_udf_tbl((select * from blackscholes))
WHERE optionprice > 6
LIMIT 10;
