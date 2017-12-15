//
// Created by Yonghong Yan on 12/21/15.
//

#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <cilk/cilkrts_api.h>

double read_timer_ms() {
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec * 1000ULL + t.tv_usec / 1000ULL;
}

double read_timer() {
    return read_timer_ms() * 1.0e-3;
}

int fib(int n);

void fib_spawn_helper(void * parent_frame, int* a, int n)
{
    REX_SPAWN_HELPER_PROLOG(parent_frame);
    *a = fib(n - 1);
    REX_SPAWN_HELPER_EPILOG();
}

int fib(int n) {

    //__cilkrts_worker * w = __cilkrts_get_tls_worker();
    //trace_printf("fib(%d) entry by %p(W%d)\n", n, __cilkrts_get_tls_worker(), w, w != NULL? w->self:99);
    if (n < 2)
        return n;

    REX_FUNCTION_PROLOG();
    int a, b;

    REX_SPAWN_WITH_HELP(fib_spawn_helper, &a, n);
    b = fib(n - 2);
    REX_SYNC();

    REX_FUNCTION_EPILOG();
    return a + b;
}

int main(int argc, char *argv[])
{
    int n, result;

    if (argc < 2) {
        fprintf(stderr, "Usage: fib <n> [<#nworkers>]\n");
        exit(1);
    }
    n = atoi(argv[1]);
    if (argc > 2) __cilkrts_set_param("nworkers", argv[2]);

    int i;
    int num_runs = 10;
    double times = read_timer();
    for (i=0; i<num_runs; i++) {
        result = fib(n);
    }
    times = read_timer() - times;
    int nw = __cilkrts_get_nworkers();

    printf("Result (%d workers): fib(%d)=%d for %fs\n", nw, n,
           result, times/num_runs);
    return 0;
}

