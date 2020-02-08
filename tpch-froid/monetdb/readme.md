
See /home/sable/hanfeng.c/github/honey/froid

    update later

Run server (on sableintel)

    mserver5 --set embedded_py=true \
        --dbpath=/mnt/local/datafarm/2019/TPCHDB/tpch1 \
        --set monet_vault_key=/mnt/local/datafarm/2019/TPCHDB/tpch1/.vaultkey \
        --set gdk_nr_threads=1

Run server (on tigger)

    mserver5 --set embedded_py=true \
        --dbpath=/mnt/local/hanfeng/datafarm/2019/TPCHDB/tpch1 \
        --set monet_vault_key=/mnt/local/hanfeng/datafarm/2019/TPCHDB/tpch1/.vaultkey \
        --set gdk_nr_threads=1

Run client

    (time ./runtest | mclient -d tpch1)  &> "sf1/log_thread_1.log"




