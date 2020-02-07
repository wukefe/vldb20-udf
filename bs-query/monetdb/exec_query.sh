#!/usr/bin/env bash
## need to check args
echo "-- Testing query $1"
for i in {1..5}
do 
    cat $1
done
echo "call sys.querylog_empty();"
echo "call sys.querylog_enable();"
for i in {1..10}
do  
    cat $1
done
echo "call sys.querylog_disable();"
echo "select * from sys.querylog_history;"
echo "select run/1000 as query_time from sys.querylog_history where query like '%select%';"
echo "select avg(run)/1000 as \"avg_$2\" from sys.querylog_history where query like '%select%';"

