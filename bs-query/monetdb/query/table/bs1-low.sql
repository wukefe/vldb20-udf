SELECT *
FROM bs_udf_tbl((select * from blackscholes))
WHERE sptprice BETWEEN 50 AND 100
LIMIT 10;
