#!/bin/bash

ssh 192.168.10.2 "sh -c ./bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/cleanup.sh"
ssh 192.168.10.1 "sh -c ./bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/cleanup.sh"

scp kill.sh sgx@192.168.10.1:~/bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/
scp kill.sh sgx@192.168.10.2:~/bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/

ssh 192.168.10.2 "sh -c ./bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/kill.sh"
ssh 192.168.10.1 "sh -c ./bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/kill.sh"

scp spoutIP sgx@192.168.10.1:~/bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/
scp countIP sgx@192.168.10.1:~/bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/
scp spoutIP sgx@192.168.10.2:~/bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/
scp countIP sgx@192.168.10.2:~/bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/

for i in `seq 0 2 0`
do
ssh 192.168.10.1 "sh -c 'cd bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack; nohup ./app spout  $i 192.168.10.1 5000 > spoutlog$i 2>&1 &' " 
done

for i in `seq 1 2 1`
do
ssh 192.168.10.2 "sh -c 'cd bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack; nohup ./app spout $i 192.168.10.2 5000 > spoutlog$i 2>&1 &' "
done


for i in `seq 0 2 4`
do
ssh 192.168.10.1 "sh -c 'cd bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack; nohup ./app splitter  $i 2 192.168.10.1 6000 > splitterlog$i 2>&1 &' "
done
for i in `seq 1 2 5`
do
ssh 192.168.10.2 "sh -c 'cd bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack; nohup ./app splitter  $i 2 192.168.10.2 6000 > splitterlog$i 2>&1 &' "
done

for i in `seq 0 2 4`
do
ssh 192.168.10.1 "sh -c 'cd bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack; nohup ./app count  $i 192.168.10.1 6000 > countlog$i 2>&1 &' "
done
for i in `seq 1 2 5`
do
ssh 192.168.10.2 "sh -c 'cd bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack; nohup ./app count  $i 192.168.10.2 6000 > countlog$i 2>&1 &' "
done

sleep 100

ssh 192.168.10.2 "sh -c ./bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/kill.sh"
ssh 192.168.10.1 "sh -c ./bilal/Minotaur/Minotaur-SGX/WordCount-MsgPack/kill.sh"
