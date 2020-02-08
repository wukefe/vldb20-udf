#!/bin/bash

usage(){
    printf '%s\n\n' \
        "Usage: $0 <options>" \
        "  1) exp sf1               ## run all tests and save to sf1/" \
        "  2) service <cmd>         ## turn monetdb [cmd:on/off]" \
        "  3) mserver <n_thread>    ## generate cmd for entering mserver mode"
    exit 1
}

localname=`hostname`
if [ ${localname} = "tigger" ]; then
    dbfarm=/mnt/local/hanfeng/datafarm/2019/TPCHDB
elif [ ${localname} = "sableintel" ]; then
    dbfarm=/mnt/local/datafarm/2019/TPCHDB
else
    echo "Unknown hostname: ${localname}"
    exit 2
fi


testsql(){
    echo "-- Testing query $1"
    for i in {1..5}
    do
        cat "q$1/q$1.pyfunc"
    done
    echo "call sys.querylog_empty();"
    echo "call sys.querylog_enable();"
    for i in {1..15}
    do
        cat "q$1/q$1.pyfunc"
    done
    echo "call sys.querylog_disable();"
    echo "select * from sys.querylog_history;"
    echo "select run/1000 as query_time from sys.querylog_history where query like '%select%';"
    echo "select avg(run)/1000 as avg_query$1 from sys.querylog_history where query like '%select%';"
}

run_exp(){
    #query=(1 4 6 12 14 16 19 22)
    query=(6)
    #query=(1 6 7 9 14 19)
    for id in ${query[@]}  ## {1..22}
    do
        testsql $id
    done
}

run_mserver(){
    echo "mserver5 --set embedded_py=true \\"
    echo "    --dbpath=${dbfarm}/tpch1 \\"
    echo "    --set monet_vault_key=${dbfarm}/tpch1/.vaultkey \\"
    echo "    --set gdk_nr_threads=$1"
    echo ""
    echo "Please copy the upon code and run it in your terminal."
}

if [ $# -eq 2 ]; then
    if [ $1 = "exp" ]; then
        if [ $2 = "sf1" ]; then
            (time run_exp | mclient -d tpch1) &> "sf1/log_thread_1.log"
        else
            usage
        fi
    elif [ $1 = "service" ]; then
        if [ $2 = "on" ]; then
            (set -x && monetdbd start ${dbfarm})
        elif [ $2 = "off" ]; then
            (set -x && monetdbd stop  ${dbfarm})
        else
            usage
        fi
    elif [ $1 = "mserver" ]; then
        run_mserver $2
    else
        usage
    fi
else
    usage
fi


