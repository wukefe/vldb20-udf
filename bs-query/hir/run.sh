#!/bin/bash

usage(){
    printf '%s\n\n' \
      "Usage: $0 <cmd>" \
      "  1) $0 plans            ## generate execution plans from ../monetdb/query" \
      "  2) $0 <kind> <id>      ## ./run.sh <id> <kind> && ./run-query.sh <id>" \
      "Note:" \
      "  - variables: runs=1, thread=1, scale=1"
    exit 1
}

if [ -z ${runs} ]; then
    runs=1
fi

if [ -z ${thread} ]; then
    thread=1
fi

if [ -z ${scale} ]; then
    scale=1
fi

gen_plan(){
    FOLDER_PLAN=plans
    folder_scalar=${FOLDER_PLAN}/scalar
    folder_table=${FOLDER_PLAN}/table
    queries=(bs0  bs1-high  bs1-medium  bs1-low  bs2-high  bs2-medium  bs2-low  bs3-high  bs3-medium  bs3-low)
    cmd="mclient -d udfdb1 -f raw"
    for id in ${queries[@]}
    do
        echo "PLAN `cat ../monetdb/query/scalar/$id.sql`" | ${cmd} > ${folder_scalar}/${id}.plan
        echo "PLAN `cat ../monetdb/query/table/$id.sql`"  | ${cmd} > ${folder_table}/${id}.plan
    done
    echo "Done!  Run: tree ${FOLDER_PLAN}"
}

if [ $# -eq 1 ]; then
    if [ $1 = "plans" ]; then
        gen_plan
    else
        usage
    fi
elif [ $# -eq 2 ]; then
    if [ $1 = "opt-table" -o $1 = "opt-scalar" ]; then
        (set -x && ./make.sh $2 $1 && ./run-query.sh $2 $runs ${thread} ${scale})
    else
        usage
    fi
else
    usage
fi


