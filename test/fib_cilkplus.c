#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <sys/time.h>
#include <cilk/cilk_api.h>

unsigned long long read_timer_ms() {
     struct timeval t;
     gettimeofday(&t, 0);
     return t.tv_sec * 1000ULL + t.tv_usec / 1000ULL;
}

double read_timer() {
     return read_timer_ms() * 1.0e-3;
}


int fib(int n)
{
     if (n < 2) {
	  return n;
     } else {
	  int x, y;
	  x = _Cilk_spawn fib(n - 1);
	  y = fib(n - 2);
	  _Cilk_sync;
	  return (x + y);
     }
}

int main(int argc, char *argv[])
{
     int n, result;

     if (argc < 2) {
	  fprintf(stderr, "Usage: fib <n> [<nworkers>]\n");
	  exit(1);
     }
     n = atoi(argv[1]);
     int nw;
     if (argc > 2) __cilkrts_set_param("nworkers", argv[2]);

     nw = __cilkrts_get_nworkers();

//     __cilkrts_pedigree pedigree = __cilkrts_get_pedigree();
     int i;
     int num_runs = 10;
     double times = read_timer();
     for (i=0; i<num_runs; i++) result = fib(n);
     times = (read_timer() - times)/num_runs;

     printf("Result (%d workers): fib(%d)=%d for %f s\n", nw, n, result, times);
     return 0;
}
