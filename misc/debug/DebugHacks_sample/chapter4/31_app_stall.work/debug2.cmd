set pagination off
set logging file debug2.log
set logging overwrite
set logging on
start
set $addr1 = pthread_mutex_lock
set $addr2 = pthread_mutex_unlock
b *$addr1
b *$addr2
while 1
    c
    if $pc != $addr1 && $pc != $addr2
        quit
    end
    printf "## addr: %08x\n", *(int*)($esp+4)
    bt
end
