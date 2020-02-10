#!/bin/bash
usage(){
    printf '%s\n\n' \
        "Usage: (default optimization: release)" \
        "  1) $0 <qid> <naive/opt> " \
        "  2) $0 <qid> <naive/opt> <debug/release/profile>"
    exit 1
}

check_src(){
    if [ $src = "naive" -o $src = "opt" ]; then
        :
    else
        usage
    fi
}

check_opt(){
    if [ $opt = "debug" -o $opt = "release" -o $opt = "profile" ]; then
        :
    else
        usage
    fi
}

if [ $# -eq 2 ]; then
    qid=$1
    src=$2
    opt="release"
elif [ $# -eq 3 ]; then
    qid=$1
    src=$2
    opt=$3
else
    usage
fi

check_src
check_opt

sys=`hostname`
src_path=${src}/q${qid}.h
lib_path=${HORSE_BASE}/src/horseir/v3

(set -x && cp ${src_path} gencode.h)

cmd_line="make q${qid} src=${src} opt=${opt} sys=${sys} lib_path=${lib_path}"

echo "run>> ${cmd_line}"
${cmd_line}

