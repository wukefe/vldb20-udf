#!/bin/bash

usage(){
    printf '%s\n\n' \
        "Usage: $0 <options>" \
        "  1) exp  sf1              ## run all tests and save to sf1/" \
        "  2) exp2 sf1              ## run with -t performance (cut2.py)" \
        "  3) service <cmd>         ## turn monetdb [cmd:on/off/reboot]" \
        "  4) mserver <n_thread>    ## generate cmd for entering mserver mode" \
        "  5) testsql  <qid>        ## generate query for tests with qid" \
        "  6) testsql2 <qid>        ## generate query2" \
        "Notes:" \
        "  - froid-example.log: logging information" \
        "  - cat q12/q12.pyfunc  | mclient -d tpch1 -t performance"
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

check_thread(){
    if [ -z ${thread} ]; then
        echo "thread=<Unknown> $0 $1 sf1  ## need to specify thread number"
        exit 2
    fi
}

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


testsql2(){
    id=$1
    echo "-- Testing query $id"
    for i in {1..15}
    do
        cat "q${id}/q${id}.pyfunc"
    done
}

run_exp2(){
    #query=(1 4 6 12 14 16 19 22)
    query=(1 6 7 14 19)  # q9 run time error
    #query=(1 6 7 9 14 19)
    for id in ${query[@]}  ## {1..22}
    do
        testsql2 $id
    done
}

run_mserver(){
    echo "export PYTHONPATH=$PWD:\${PYTHONPATH}  ## optional"
    echo ""
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
            check_thread $1
            log_file="sf1/log_thread_${thread}.txt"
            (time run_exp | mclient -d tpch1) &> ${log_file}
        else
            usage
        fi
    elif [ $1 = "exp2" ]; then
        if [ $2 = "sf1" ]; then
            check_thread $1
            log_file="sf1/perf_thread_${thread}.txt"
            echo "Saving to ... ${log_file}"
            (time run_exp2 | mclient -d tpch1 -t performance) &> ${log_file}
            echo "Please fetch log info: "
            echo "    cat sf1/perf_thread_12.txt | grep -A 1 \"tuple\" | python cut2.py"
        else
            usage
        fi
    elif [ $1 = "service" ]; then
        if [ $2 = "on" ]; then
            (set -x && monetdbd start ${dbfarm})
        elif [ $2 = "off" ]; then
            (set -x && monetdbd stop  ${dbfarm})
        elif [ $2 = "reboot" ]; then
            (set -x && monetdbd stop  ${dbfarm} && monetdbd start ${dbfarm})
        else
            usage
        fi
    elif [ $1 = "mserver" ]; then
        run_mserver $2
    elif [ $1 = "testsql" ]; then
        testsql $2
        echo "-- Run with:  ($0 testsql $2 | mclient -d tpch1 -t performance) &> sf1/log_thread_xx.txt"
    elif [ $1 = "testsql2" ]; then
        testsql2 $2
        echo "-- Run with:  ($0 testsql2 $2 | mclient -d tpch1 -t performance) &> sf1/perf_thread_xx.txt"
    else
        usage
    fi
else
    usage
fi


