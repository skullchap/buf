#include <stdio.h>
#include "buf.h"
#include "vecdef.h"
#include <time.h>

vecfuncs(ulong, _ulong)

int
main(void)
{
	Vec_ulong *vec;
	ulong i, iterations = 1000000000;
	clock_t start, end;
	double elapsed_time;

	vec = newvec_ulong(0);
	
	start = clock();
    	for(i = 0; i < iterations; ++i)
        	pushvec_ulong(vec, i);
	end = clock();

	elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    	printf("C array time: %.6f seconds\n", elapsed_time);

	freevec_ulong(vec);
   	return 0;
}

