
## Environment

Add current path to Python's environment path

    export PYTHONPATH=$PWD:${PYTHONPATH}


## Commands

See /home/sable/hanfeng.c/github/honey/froid

    update later

Run server (on sableintel)

    mserver5 --set embedded_py=true \
        --dbpath=/mnt/local/datafarm/2019/TPCHDB/tpch1 \
        --set monet_vault_key=/mnt/local/datafarm/2019/TPCHDB/tpch1/.vaultkey \
        --set gdk_nr_threads=1

Run server (on tigger)

    mserver5 --set embedded_py=true \
        --dbpath=/mnt/local/hanfeng/datafarm/2019/TPCHDB/tpch1 \
        --set monet_vault_key=/mnt/local/hanfeng/datafarm/2019/TPCHDB/tpch1/.vaultkey \
        --set gdk_nr_threads=1

Run client

    (time ./runtest | mclient -d tpch1)  &> "sf1/log_thread_1.log"

## Documents

Froid queries (~/github/honey/froid)

     Query | Notes
    ------------------------
       1   | ready
       3   | ...
       6   | ready
       7   | ready
       9   | ready
       14  | ready
       19  | ready
    ------------------------
       5   | date
       10  | date
       12  | date
    ------------------------


### Notes

general

    flag `-t performance` (11.750 ms) returns a different run time
    compared with querylog_history (8.783 ms)

q6

    tigger> errors when # of threads >= 37
            - runtime error when # of threads >= 38
            - no results when # of therads == 37
    tigger> reproduce the error
            - # of threads == 37
            - input 1: "select sum(l_extendedprice) from lineitem;"  // ok
            - input 2: "call sys.querylog_enable();"
            - input 1: "select sum(l_extendedprice) from lineitem;"  // error
            - error message: "GDK reported error: BATproject: does not match always"



