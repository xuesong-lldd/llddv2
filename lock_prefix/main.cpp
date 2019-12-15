//#include <atomic>
//#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

//std::atomic_ulong my_atomic_ulong(0);
//unsigned long my_non_atomic_ulong = 0;
unsigned long my_arch_atomic_ulong = 0;
unsigned long my_arch_non_atomic_ulong = 0;
size_t niters;

void threadMain() {
    for (size_t i = 0; i < niters; ++i) {
        //my_atomic_ulong++;
        //my_non_atomic_ulong++;
        __asm__ __volatile__ (
            "incq %0;"
            : "+m" (my_arch_non_atomic_ulong)
            :
            : "memory"
        );
        __asm__ __volatile__ (
            "lock;"
            "incq %0;"
            : "+m" (my_arch_atomic_ulong)
            :
            : "memory"
        );
    }
}

int main(int argc, char **argv) {
    size_t nthreads;
    if (argc > 1) {
        nthreads = std::stoull(argv[1], NULL, 0);
    } else {
        nthreads = 2;
    }
    if (argc > 2) {
        niters = std::stoull(argv[2], NULL, 0);
    } else {
        niters = 10000;
    }
    std::vector<std::thread> threads(nthreads);
    for (size_t i = 0; i < nthreads; ++i)
        threads[i] = std::thread(threadMain);
    for (size_t i = 0; i < nthreads; ++i)
        threads[i].join();
    //assert(my_atomic_ulong.load() == nthreads * niters);
    //assert(my_atomic_ulong == my_atomic_ulong.load());
    std::cout << "my_arch_non_atomic_ulong " << my_arch_non_atomic_ulong << std::endl;
    //assert(my_arch_atomic_ulong == nthreads * niters);
    std::cout << "my_arch_atomic_ulong " << my_arch_atomic_ulong << std::endl;
}
