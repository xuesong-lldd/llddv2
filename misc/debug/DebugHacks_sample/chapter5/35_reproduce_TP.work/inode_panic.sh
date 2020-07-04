#!/bin/bash

echo 5000 > /proc/sys/vm/vfs_cache_pressure
echo "set /proc/sys/vm/vfs_cache_pressure to `cat /proc/sys/vm/vfs_cache_pressure`"

function force_kill_ps()
{
	killall vm_stress.sh
	killall stress
	killall inode_panic.sh rm
	echo "force kill all process"
}

### signal(Ctrl-c) handler
trap force_kill_ps INT 
### repeat the mount/umount
./mnt.sh &
### memory stress
./vm_stress.sh &

while [ 0 ] ; do
    cd /mnt/10 ; stress --hdd 5 --hdd-bytes 10M --hdd-noclean -t 5
    cd /mnt/11 ; stress --hdd 5 --hdd-bytes 10M --hdd-noclean -t 5 &
    cd /mnt/12 ; stress --hdd 5 --hdd-bytes 10M --hdd-noclean -t 5 &
    cd /mnt/13 ; stress --hdd 5 --hdd-bytes 10M --hdd-noclean -t 5 &

    mv /mnt/10/stress.* /mnt/11/ &
    mv /mnt/11/stress.* /mnt/12/ &
    mv /mnt/12/stress.* /mnt/13/ &
    mv /mnt/13/stress.* /mnt/10/ &

    rm -rfv /mnt/10/stress.* &
    rm -rfv /mnt/11/stress.* &
    rm -rfv /mnt/12/stress.* &
    rm -rfv /mnt/13/stress.* &

    sleep 5
done
