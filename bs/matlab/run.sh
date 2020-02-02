#!/bin/bash
log="log"
log_matlab="$log/log_matlab.txt"
log_horse="$log/log_horse.txt"
matlab19="/usr/local/pkgs/matlab/R2019a/bin/matlab -nodesktop"
runs=15

mkdir -p $log

echo "Running MATLAB (save to log/log_matlab.txt) ..."
scales=(1 2 4 8 16)
for sf in "${scales[@]}"
do
    ${matlab19} -batch "run('in_${sf}M.txt', $runs)" >> ${log_matlab}
done

echo "Running Horse (save to log/log_horse.txt) ..."

