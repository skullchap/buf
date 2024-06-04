#include <stdio.h>
#include <assert.h>
#include "buf.h"

/* int vector wrapper example */

typedef Buf Veci;

Veci*
newveci(int nelem)              /* alloc underlying buf for n count of elements */
{
	long cap;

	cap = nelem * sizeof(int);
	return newbuf(cap);
}

int*
vecip(Veci *v, int idx)          /* return ptr to elem in dynamic array (&int v[idx]) */
{
	long off;

	off = idx * sizeof(int);
	return bufoff(v, off);
}

int
veci(Veci *v, int idx)          /* return elem from dynamic array (int v[idx]) */
{
	return *(int*)vecip(v, idx);
}

int
nveci(Veci *v)                   /* current n count of elements */
{
	return buflen(v) / sizeof(int);
}

int
vecicap(Veci *v)                /* current elem capacity in underlying buf */
{
	return bufcap(v) / sizeof(int);
}

int
pushveci(Veci *v, int val)
{
	return appendbuf(v, &val, sizeof(val));
}

int
popveci(Veci *v)                /* pop last element */
{
	int r;

	r = fillbuf(v, 0, buflen(v)-1-sizeof(int), buflen(v));
	if(r < 0)
		return r;
	setbuflen(v, buflen(v)-sizeof(int));
	return 0;
}

int
insveci(Veci *v, long idx, int val)     /* insert at given idx */
{
	long off;

	off = idx * sizeof(int);
	return insertbuf(v, off, &val, sizeof(int));
}

Veci*
sliceveci(Veci *v, long from, long till)     /* slice from idx till idx */
{
	long foff, toff;

	foff = from * sizeof(int);
	toff = till * sizeof(int);
	return slicebuf(v, foff, toff);
}

int
cutveci(Veci *v, long from, long till)     /* slice from idx till idx */
{
	long foff, toff;

	foff = from * sizeof(int);
	toff = till * sizeof(int);
	return cutbuf(v, foff, toff);
}

void
freeveci(Veci *v)
{
	freebuf(v);
}

void
printveci(Veci *v)
{
	int i;
	printf("[ ");
	for(i = 0; i < nveci(v); ++i){
		printf("%d", veci(v, i));
		if(i != nveci(v)-1)
			printf(", ");
	}
	puts(" ]");
}

int
main(void)
{
	Veci *v, *sv;

	v = newveci(6);
	assert(v);
	puts("new 6 elem capacity veci:");
	printf("v nelem: %d\n", nveci(v));
	printf("v elem cap: %d\n", vecicap(v));
	puts("");

	pushveci(v, 1);
	pushveci(v, 2);
	pushveci(v, 3);
	pushveci(v, 4);
	pushveci(v, 5);
	puts("after 5 elem addition:");
	printf("v nelem: %d\n", nveci(v));
	printf("v elem cap: %d\n", vecicap(v));

	pushveci(v, 6);
	pushveci(v, 7);
	puts("");
	puts("after 2 elem addition:");
	printf("v nelem: %d\n", nveci(v));
	printf("v elem cap: %d\n", vecicap(v));
	printf("veci elems: ");
	printveci(v);
	puts("");

	popveci(v);
	printf("veci elems after pop: ");
	printveci(v);
	printf("v nelem: %d\n", nveci(v));
	printf("v elem cap: %d\n", vecicap(v));
	puts("");

	insveci(v, 3, 7);
	printf("veci elems after insert of 7 at 3 idx: ");
	printveci(v);
	printf("v nelem: %d\n", nveci(v));
	printf("v elem cap: %d\n", vecicap(v));
	puts("");

	*vecip(v, 1) = 42;
	printf("veci elems after replacing elem at 1 idx with 42: ");
	printveci(v);
	printf("v nelem: %d\n", nveci(v));
	printf("v elem cap: %d\n", vecicap(v));
	puts("");

	sv = sliceveci(v, 1, 4);
	printf("new sliced sv veci 1-4: ");
	printveci(sv);
	printf("sv nelem: %d\n", nveci(sv));
	printf("sv elem cap: %d\n", vecicap(sv));
	freeveci(sv);
	puts("");

	cutveci(v, 1, 4);
	printf("veci elems after 1-4 cut: ");
	printveci(v);
	printf("sv nelem: %d\n", nveci(v));
	printf("sv elem cap: %d\n", vecicap(v));

	freeveci(v);
}
