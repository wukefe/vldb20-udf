#!/bin/bash
runs=1 # number of runs
threads=1 # number of threads
scale=1
if [ "$#" -eq 1 ]; then
    :  # this is a null
elif [ "$#" -eq 2 ]; then
    runs=$2
elif [ "$#" -eq 3 ]; then
    runs=$2
    threads=$3
elif [ "$#" -eq 4 ]; then
    runs=$2
    threads=$3
    scale=$4
else
    printf '%s\n\n' \
        "Usage: (default runs=1, threads=1, scale=1)" \
        "  1) $0 <id> " \
        "  2) $0 <id> <runs>" \
        "  3) $0 <id> <runs> <threads>" \
        "  4) $0 <id> <runs> <threads> <scale>" \
        "Note: targ=compile-clang ./run-query.sh 6 10  # for compile-clang-q6"
    exit 1
fi

export OMP_PLACES=cores
export OMP_PROC_BIND=spread
export OMP_NUM_THREADS=$threads

id=$1   # query id
if [ -z $targ ]; then
    targ=compile  # executable
fi

echo "`hostname`> Q$id, T$threads, Run$runs, SF$scale"
(set -x && ./$targ-q$id $scale $runs)

