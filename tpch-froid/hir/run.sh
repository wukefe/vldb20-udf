#!/bin/bash

usage(){
    printf '%s\n\n' \
      "1) $0 naive <id> [runs]    ## ./make.sh <id> naive && ./run-query.sh <id> [runs]" \
      "2) $0 opt   <id> [runs]    ## ./make.sh <id> opt   && ./run-query.sh <id> [runs]" \
      "3) $0 compile <folder>     ## compile all code under <naive/opt>" \
      "4) $0 fetch log            ## fetch log information from <naive/opt>" 
    exit 1
}

cc20_query=( 1 4 6 12 14 16 19 22 )

if [ -z $thread ]; then
    thread=1
fi

if [ -z $scale ]; then
    scale=1
fi

report_compile_time(){
    folder=$1; id=$2
    src_dirs="-I${HORSE_BASE}/libs/include/ -I${HORSE_BASE}/src/horseir/v3"
    src_file="main.c"
    src_libs="${HORSE_BASE}/src/horseir/v3/libcore.a ${HORSE_BASE}/libs/lib/libpcre2-8.a"
    cc_flags="-std=c99 -fopenmp -lm -lstdc++ -march=native"
    # with -ftime-report
    (set -x && cp ${folder}/q${id}.h gencode.h && gcc-8 ${src_file} ${src_dirs} ${src_libs} ${cc_flags} -ftime-report -o compile-q${id})
}

prepare_exec(){
    folder=$1
    for id in ${cc20_query[@]}
    do
        report_compile_time $folder $id
    done
}

fetch_log(){
    folder=$1
    for id in ${cc20_query[@]}
    do
        cat log/naive/log_q${id}.txt | grep -i "times" | awk -F\| '{print $1}' | awk -F\: '{print $2}'
        cat log/opt/log_q${id}.txt   | grep -i "times" | awk -F\| '{print $1}' | awk -F\: '{print $2}'
    done
}


if [ "$#" -eq 2 ]; then
    mode=$1; qid=$2
    if [ ${mode} = "naive" ]; then
        (set -x && ./make.sh ${qid} naive && ./run-query.sh ${qid} 1 ${thread} ${scale})
    elif [ ${mode} = "opt" ]; then
        (set -x && ./make.sh ${qid} opt   && ./run-query.sh ${qid} 1 ${thread} ${scale})
    elif [ ${mode} = "compile" ]; then
        prepare_exec $2
    elif [ ${mode} = "fetch" ]; then
        fetch_log $2
    else
        usage
    fi
elif [ "$#" -eq 3 ]; then
    mode=$1; qid=$2; runs=$3
    if [ ${mode} = "naive" ]; then
        (set -x && ./make.sh ${qid} naive && ./run-query.sh ${qid} ${runs} ${thread} ${scale})
    elif [ ${mode} = "opt" ]; then
        (set -x && ./make.sh ${qid} opt   && ./run-query.sh ${qid} ${runs} ${thread} ${scale})
    else
        usage
    fi
else
    usage
fi

