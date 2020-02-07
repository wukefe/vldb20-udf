SELECT optiontype, sptprice
FROM bs_udf_tbl((select * from blackscholes))
WHERE sptprice BETWEEN 51 AND 100
LIMIT 10;
