#!/bin/bash

for i in `seq 0 4`
do
./run_new.sh
cat countlog* | grep "Latency" >> "$1"_total_metrics_$i
cat "$1"_total_metrics_$i |  awk '{ if($2>=0) {print $2}}' >> "$1"_metrics_$i
tail -n 10000000 "$1"_metrics_$i >> "$1"_metrics_"$i"_small
done

tar -czf "$1"_5_metrics.tar.gz *metrics_* 
