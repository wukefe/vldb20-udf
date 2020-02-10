#!/bin/bash
TOOL_DIR=${HORSE_BASE}/src/horseir/v3
CODE_DIR=$PWD
query=(1 4 6 12 14 16 19 22)
threads=(1 2 4 8 16 32 64)

cc20_compile(){
    kind=$1
    # compiling
    for id in ${query[@]}
    do
        c_file=${CODE_DIR}/${kind}/q${id}.h
        echo ">> Compiling query $id (save to ${c_file})"
        if [ ${kind} = "naive" ]; then
            (cd ${TOOL_DIR} && ./run.sh compile q $id 1> ${c_file}) &> /dev/null
        elif [ ${kind} = "opt1" ]; then
            (cd ${TOOL_DIR} && opt=opt1 ./run.sh opt q $id 1> ${c_file}) &> /dev/null
        elif [ ${kind} = "opt2" ]; then
            (cd ${TOOL_DIR} && opt=opt2 ./run.sh opt q $id 1> ${c_file}) &> /dev/null
        fi
    done
}

cc20_run(){
    kind=$1
    # running
    log_folder=${CODE_DIR}/log/${kind}
    mkdir -p ${log_folder}
    for id in ${query[@]}
    do
        log_file=${log_folder}/log_q${id}.txt
        rm -f ${log_file}
        echo "** Executing query ${id} (log to ${log_file})"
        for th in ${threads[@]}
        do
            (cd ${CODE_DIR} && thread=${th} ./run.sh ${kind} ${id} 15 &>> ${log_file})
        done
    done
}

compile_and_run(){
    #cc20_compile $1
    #echo ""
    cc20_run $1
}

## echo "Step 1: generate tool from source code"
## (cd ${TOOL_DIR} && rm -rf build && ./make.sh debug)

# echo "Step 2: generate library from source code"
# (cd ${TOOL_DIR} && ./make.sh lib)

echo "Step 3: use the tool to generate C code"
# compile_and_run "naive" && \
#  compile_and_run "opt1" && \
#  compile_and_run "opt2"

compile_and_run "opt"

