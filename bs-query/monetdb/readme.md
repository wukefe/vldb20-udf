
## Setup MonetDB

Create data farm: UDFDB

    monetdbd create /mnt/local/hanfeng/datafarm/2019/
    monetdbd start  /mnt/local/hanfeng/datafarm/2019/

Create a database

    monetdb create  udfdb1
    monetdb release udfdb1
    monetdb set embedpy=true udfdb1
    monetdb start   udfdb1

Login

    mclient -d udfdb1

Define tables (after login)

    \<udf.ddl
    \d         -- check tables

Load data (`OFFSET 2`: ignore the first row)

    COPY OFFSET 2 INTO blackscholes FROM '/mnt/local/hanfeng/vldb20/in_1M.txt' USING DELIMITERS ' ';

Load a table udf (name: bs_udf_*)

    \<pyfunc/bs-table.pyfunc
    \<pyfunc/bs-scalar.pyfunc
    \df        -- view the defined function

Run server separately

    export PYTHONPATH=/home/sable/hanfeng.c/github/vldb20-udf/bs-query/monetdb/pyfunc
    mserver5 --set embedded_py=true \
        --dbpath=/mnt/local/hanfeng/datafarm/2019/udfdb1 --set monet_vault_key=/mnt/local/hanfeng/datafarm/2019/udfdb1/.vaultkey --set gdk_nr_threads=1


## Post Experiments

Run experiments
    
    ./run.sh exp

Fetch log information

    grep -A 3 avg_bs log/summary-scalar.log | python cut.py

    ... # bs0
    ... # bs1_high
    ... # bs1_medium
    ... # bs1_low
    ... # bs2_high
    ... # bs2_medium
    ... # bs2_low
    ... # bs3_high
    ... # bs3_medium
    ... # bs3_low


