#!/bin/bash

if [ -z $sf ]; then
    sf=8
fi

cmd="mclient -d tpch${sf} -t performance"
query_tpch=${HORSE_BASE}/tpch/query
queries=(1 4 6 12 14 16 19 22)

usage(){
    printf '%s\n\n' \
        "Usage: $0 <cmd>" \
        "  1) $0 tpch  <qid>    ## Execute a TPC-H query in MonetDB" \
        "  2) $0 mal   <qid>    ## Get MAL code size" \
        "  3) $0 turn on/off    ## Enable server on/off" \
        "  4) $0 batch mal      ## Get all MAL code sizes" \
        "  5) $0 fetch log      ## Fetch all log information" \
        "System variables:" \
        "- enable_result=yes $0 <cmd>   ## Enable output, default: no" \
        "- sf=1 $0 tpch 16              ## Enable sf, default: 8" \
        "Additional:" \
        "- Query path: ${query_tpch}"
    exit 1
}

if [ -z $enable_result ] || [ $enable_result = "no" ]; then
    show_result="no"   ## default
elif [ $enable_result = "yes" ]; then
    show_result="yes"
fi

run_tpch(){
    if [ $show_result = "no" ]; then  ## default
        (set -x && $cmd ${query_tpch}/$1.sql 1>/dev/null)
    else
        (set -x && $cmd ${query_tpch}/$1.sql)
    fi
}

get_mal(){
    (echo "EXPLAIN `cat ${query_tpch}/$1.sql`" | $cmd -f raw) 2> /dev/null
}

get_mal_all(){
    for qid in ${queries[@]}
    do
        size=`get_mal $qid | python count_mal.py`
        echo "Query $qid has lines of MAL code: $size"
    done
}

fetch_log_info(){
    threads=(1 2 4 8 16 32 64)
    for th in ${threads[@]}
    do
        echo "// Thread: ${th}"
        grep -A 3 avg_query log/sf8-paper/log_thread_${th}.log | python cut.py
        echo ""
    done
}


if [ $# -eq 2 ]; then
    opt=$1; qid=$2
    if [ $opt = "tpch" ]; then
        run_tpch $qid
    elif [ $opt = "mal" ]; then
        get_mal $qid
    elif [ $opt = "turn" ]; then
        server_path="/mnt/local/hanfeng/datafarm/2019"
        if [ $2 = "on" ]; then
            (set -x && monetdbd start $server_path && monetdb status)
        elif [ $2 = "off" ]; then
            (set -x && monetdbd stop  $server_path)
        else
            usage
        fi
    elif [ $opt = "batch" -a $2 = "mal" ]; then
        get_mal_all
    elif [ $opt = "fetch" -a $2 = "log" ]; then
        fetch_log_info
    else
        usage
    fi
else
    usage
fi



