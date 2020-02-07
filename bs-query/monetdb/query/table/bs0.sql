SELECT *
FROM bs_udf_tbl((select * from blackscholes))
LIMIT 10;
