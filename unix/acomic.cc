#include <iostream>
#include <stdint.h>
#include <fstream>

static inline int64_t atomic_swap64(volatile void *lockword, int64_t value)
{
    asm volatile(
            "lock xchg %0, (%1);"
            : "=a"(value)
            : "r"(lockword), "a"(value)
            : "memory"
    );
    return value;
}

static inline int64_t atomic_add64(volatile int64_t* mem, int64_t add)
{
    asm volatile(
            "lock xaddq %0, (%1)"
            : "=a" (add)
            : "r" (mem), "a" (add)
            : "memory"
    );
    return add;
}

class Counter {
public:
    Counter() : val_(0) {}
    int64_t Add(int64_t v) {
        return atomic_add64(&val_, v) + v;
    }
    int64_t Sub(int64_t v) {
        return atomic_add64(&val_, -v) - v;
    }
    int64_t Inc() {
        return atomic_add64(&val_, 1) + 1;
    }
    int64_t Dec() {
        return atomic_add64(&val_, -1) - 1;
    }
    int64_t Get() {
        return val_;
    }
    int64_t Set(int64_t v) {
        return atomic_swap64(&val_, v);
    }
    int64_t Clear() {
        return atomic_swap64(&val_, 0);
    }

private:
    volatile int64_t val_;
};



int64_t get_micros() { // get us before machine reboot
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<int64_t>(ts.tv_sec) * 1000000 + static_cast<int64_t>(ts.tv_nsec) / 1000;
}

uint64_t NowMicros() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return static_cast<int64_t>(ts.tv_sec) * 1000000 + static_cast<int64_t>(ts.tv_nsec) / 1000;
}

Counter a;

void test(){
    a.Inc();
}

int main(int argc, char *argv[])
{
    FILE *f;
    /*
    f = fopen("/proc/26411/statm", "r");
    if (f == NULL) {
        return 0;
    }
    int64_t tets;
    int64_t mem; 
    fscanf(f, "%*d %ld", &tets,&mem);
    std::cout << tets << " " ;
    std::cout << mem << " " ;
    mem = mem * 4 * 1024;
    std::cout << mem << std::endl;
    fclose(f);
    */
    
    f = fopen("/proc/1266/net/dev", "r");
    FILE *f1;
    f1 = fopen("/proc/net/dev", "r");
    int64_t net_rx, net_tx; 
    int ret = fseek(f, 327, SEEK_SET);
    int ret1 = fseek(f1, 327, SEEK_SET);
    for (int i = 0; i < 10; i++) {
        while (':' != fgetc(f));
        ret = fscanf(f, "%ld%*d%*d%*d%*d%*d%*d%*d%ld", &net_rx, &net_tx);
        if (ret >= 2 && net_rx > 0 && net_tx > 0) {
            break;
        }
    }
    std::cout << net_rx << "  " << net_tx << std::endl;
    for (int i = 0; i < 10; i++) {
        while (':' != fgetc(f1));
        ret = fscanf(f1, "%ld%*d%*d%*d%*d%*d%*d%*d%ld", &net_rx, &net_tx);
        if (ret >= 2 && net_rx > 0 && net_tx > 0) {
            break;
        }
    }

    std::cout << net_rx << "  " << net_tx << std::endl;
    fclose(f);
    fclose(f1);

    /*
    int64_t val;
    val = 19;
    
    std::cout << val << "  "
    << atomic_swap64(&val, 12)
    << val << std::endl;
    std::cout << a.Get() << " ";
    a.Inc();
    a.Get();
    std::cout << a.Get() << " ";
    Counter a;
    std::cout << a.Get() << " ";
    */
    return 0;
}
