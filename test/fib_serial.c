 /* Example 1: fib in C++
 * ---------------------
 *
 #include <internal/cilk_fake.h>
   
   int fib(int n)
   {
       CILK_FAKE_PROLOG();
   
       if (n < 2)
           return n;
   
       int a, b;
       CILK_FAKE_SPAWN_R(a, fib(n - 1));
       b = fib(n - 2);
       CILK_FAKE_SYNC();
   
       return a + b;
   }
 */ 
 /* Example 2: fib in C
 * -------------------
 */
#include <time.h>
#include <sys/time.h>
#include <stdio.h> 
unsigned long long read_timer_ms() {
        struct timeval t;
        gettimeofday(&t, 0); 
        return t.tv_sec * 1000ULL + t.tv_usec / 1000ULL;
}

double read_timer() {
        return read_timer_ms() * 1.0e-3;
}

  
 int fib(int n);
  
   int fib(int n)
   {
       if (n < 2)
           return n;
   
       int a, b;
       a = fib(n - 1);
       b = fib(n - 2);
       return a + b;
   }

int main(int argc, char *argv[])
{
     int n, result;

     if (argc != 2) {
	  fprintf(stderr, "Usage: fib <n>\n");
	  exit(1);
     }
     n = atoi(argv[1]);
     int num_runs = 10;
     int i;
     double times = read_timer();
     for (i=0; i<num_runs; i++) {
        result = fib(n);
     }
     times = read_timer() - times;

     printf("Result (serial): fib(%d)=%d for %fs\n", n, result, times/num_runs);
     return 0;
}


