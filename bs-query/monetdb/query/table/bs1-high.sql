SELECT *
FROM bs_udf_tbl((select * from blackscholes))
WHERE sptprice < 50 OR sptprice > 100
LIMIT 10;
