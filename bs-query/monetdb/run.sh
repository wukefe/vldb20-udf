#!/usr/bin/env bash

usage(){
    printf '%s\n\n' \
        "$0 <options>" \
        "  1) exp                  ## run all experiments" \
        "  2) service <cmd>        ## restart (monetdbd) / reboot (monetdb) / exit" \
        "  3) mserver <n_threads>  ## run mserver with n threads" \
        "  4) init all             ## init all"
    exit 1
}

dbfarm_path=/mnt/local/hanfeng/datafarm/2019

run_exp(){
    export PYTHONPATH=$PWD/pyfunc

    LOG_T=log/summary-table.log
    LOG_S=log/summary-scalar.log

    echo ....
    mkdir -p log && rm -f $LOG_T

    udf=(bs0  bs1-high  bs1-medium  bs1-low  bs2-high  bs2-medium  bs2-low  bs3-high  bs3-medium  bs3-low)
    for id in ${udf[@]} 
    do
        echo "Processing table udf: $id"
        (time ./exec_query.sh "./query/table/$id.sql" "$id" | mclient -d udfdb1) >>$LOG_T
    done

    rm -f $LOG_S
    for id in ${udf[@]} 
    do
        echo "Processing scalar udf: $id"
        (time ./exec_query.sh "./query/scalar/$id.sql" "$id" | mclient -d udfdb1) >>$LOG_S
    done
}

service_restart(){
    monetdbd stop  ${dbfarm_path}
    monetdbd start ${dbfarm_path}
    echo "monetdb has been restarted!"
}

service_reboot(){
    monetdb stop  udfdb1
    monetdb start udfdb1
    echo "table udfdb1 has been rebooted!"
}

service_exit(){
    monetdb  stop  udfdb1
    monetdbd stop  ${dbfarm_path}
}

mserver_run(){
    echo "export PYTHONPATH=$PWD/pyfunc  ## optional"
    echo ""
    echo "mserver5 --set embedded_py=true \\"
    echo "   --dbpath=${dbfarm_path}/udfdb1 \\"
    echo "   --set monet_vault_key=${dbfarm_path}/udfdb1/.vaultkey \\"
    echo "   --set gdk_nr_threads=$1"
    echo ""
    echo "Please copy the upon code, and run it in your terminal"
}

init_all(){
    echo "Step 1: creating data farm"
    monetdbd create /mnt/local/hanfeng/datafarm/2019/
    monetdbd start  /mnt/local/hanfeng/datafarm/2019/
    echo "Step 2: creating database udfdb1"
    monetdb create  udfdb1
    monetdb release udfdb1
    monetdb set embedpy=true udfdb1
    monetdb start   udfdb1
    cat udf.ddl | mclient -d udfdb1
    echo "COPY OFFSET 2 INTO blackscholes FROM '/mnt/local/hanfeng/vldb20/in_1M.txt' USING DELIMITERS ' ';" | mclient -d udfdb1
    echo "Step 3: configuring functions"
    cat pyfunc/bs-table.pyfunc  | mclient -d udfdb1
    cat pyfunc/bs-scalar.pyfunc | mclient -d udfdb1
    service_restart
}


if [ $# -eq 1 ]; then
    if [  $1 = "exp" ]; then
        run_exp
    else
        usage
    fi
elif [ $# -eq 2 ]; then
    if [ $1 = "service" ]; then
        if [ $2 = "restart" ]; then
            service_restart
        elif [ $2 = "reboot" ]; then
            service_reboot
        elif [ $2 = "exit" ]; then
            service_exit
        else
            usage
        fi
    elif [ $1 = "mserver" ]; then
        mserver_run $2
    elif [ $1 = "init" ]; then
        if [ $2 = "all" ]; then
            init_all
        else
            usage
        fi
    else
        usage
    fi
else
    usage
fi


