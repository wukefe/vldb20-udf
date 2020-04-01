
Run server

    mserver5 --dbpath=/mnt/local/datafarm/2019/TPCHDB/tpch1 --set monet_vault_key=/mnt/local/datafarm/2019/TPCHDB/tpch1/.vaultkey --set gdk_nr_threads=1
    mserver5 --dbpath=/mnt/local/hanfeng/datafarm/2019/tpch8 --set monet_vault_key=/mnt/local/hanfeng/datafarm/2019/tpch8/.vaultkey --set gdk_nr_threads=1

Run client

    (time ./runtest | mclient -d tpch1)  &> "log/sf1/log_thread_1.log"
    (time ./runtest | mclient -d tpch8)  &> "log/sf8/log_thread_1.log"

Fetch result

    grep -A 3 avg_query log/sf1/log_thread_1.log | python cut.py
    grep -A 3 avg_query log/sf8/log_thread_1.log | python cut.py

Fetch all results over different number of threads (T1/2/4/8/16/32/64)

    ./run.sh fetch log

Fetch experiment results

    grep -A 3 avg_query log/sf8-paper/log_thread_1.log | python cut.py

Temporary experiments

    ./runtest | mclient -d tpch8 -t performance &> log/q14_sf8_t1.txt

Count lines of MAL code for a specific query (e.g. q6)

    ./run.sh mal 6 | python count_mal.py

Count lines of MAL code for all queries

    ./run.sh batch mal

