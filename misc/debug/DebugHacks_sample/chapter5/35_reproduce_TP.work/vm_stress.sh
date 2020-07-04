#!/bin/bash

while [ 0 ] ; do
	./stress-1.0.0/src/stress --vm 8 --vm-bytes 500M --vm-keep --timeout 20
	sleep 5
done
