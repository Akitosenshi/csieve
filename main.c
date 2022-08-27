#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PRIMES_1000000 78498

int main(int argc, char** argv) {
	int MAX = 1000000;
	int sqr = (int)sqrt(MAX);
	char* sieve = malloc(MAX);
	sieve[0] = 0;
	for(int i = 1; i < MAX; ++i) {
		sieve[i] = 1;
	}
	struct timespec start, stop, start_format, stop_format;

	clock_gettime(CLOCK_REALTIME, &start);
	for(int i = 1; i < sqr; ++i) {
		if(sieve[i]) {
			for(int j = (i + 1) * (i + 1) - 1; j < MAX; j += i + 1) {
				sieve[j] = 0;
			}
		}
	}
	clock_gettime(CLOCK_REALTIME, &stop);

	int counted = 0, res_len = 0;
	char* res = malloc(1024 * 1024 * 32);

	clock_gettime(CLOCK_REALTIME, &start_format);
	for(int i = 0; i < MAX; ++i) {
		if(sieve[i]) {
			res_len += sprintf(res + res_len, "%d %s\n", i + 1, "is prime");
			++counted;
		} else {
			res_len += sprintf(res + res_len, "%d %s\n", i + 1, "is not prime");
		}
	}
	clock_gettime(CLOCK_REALTIME, &stop_format);

	double t = (double)(stop.tv_nsec - start.tv_nsec) / 1000, t_format = (double)(stop_format.tv_nsec - start_format.tv_nsec) / 1000;
	char *usec = "µs", *msec = "ms";
	char *t_unit = usec, *t_format_unit = usec;
	int t_p = 3, t_format_p = 3;
	if(t > 1000) {
		t /= 1000;
		t_p = 6;
		t_unit = msec;
	}
	if(t_format > 1000) {
		t_format /= 1000;
		t_format_p = 6;
		t_format_unit = msec;
	}
	printf("%scounted: %d\nactual:  %d\n\ncalculated in %.*lf%s\nformatting this output took %.*lf%s\n", res, counted, NUM_PRIMES_1000000, t_p, t, t_unit, t_format_p, t_format, t_format_unit);
	free(sieve);
	free(res);
	return 0;
}
