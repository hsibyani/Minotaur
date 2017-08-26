#!/bin/bash

declare -a bgpids

cleanup() {
	for pid in ${bgpids[@]}; do
		kill -9 $pid
	done
}

trap "cleanup" SIGINT SIGTERM

./script.sh & 
bgpids+=("$!")
