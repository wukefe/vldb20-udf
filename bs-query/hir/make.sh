#!/bin/bash
usage(){
    printf '%s\n\n' \
        "Usage: (default optimization: release)" \
        "  1) $0 <bs_id> <naive/opt> " \
        "  2) $0 <bs_id> <naive/opt> <debug/release/profile>"
    exit 1
}

check_src(){
    if [ $src = "opt-scalar" -o $src = "opt-table" ]; then
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

# assign compiler to cccc
setup_compiler(){
    if [ $sys = "tigger" ]; then
        cccc=gcc-8
    elif [ $sys = "sableintel" ]; then
        cccc=gcc-8
    else
        echo "Unknown host: $sys"
        exit 1
    fi
}

if [ $# -eq 2 ]; then
    bid=$1
    src=$2
    opt="release"
elif [ $# -eq 3 ]; then
    bid=$1
    src=$2
    opt=$3
else
    usage
fi

check_src
check_opt

sys=`hostname`
setup_compiler

src_path=${src}/bs${bid}.h
lib_header=${HORSE_BASE}/src/horseir/v3


(set -x && cp ${src_path} gencode.h)

cmd_line="make bs${bid} compiler=${cccc} opt=${opt} sys=${sys} lib_header=${lib_header}"

echo "run>> ${cmd_line}"
${cmd_line}

