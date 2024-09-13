#include <stdio.h>
#include <assert.h>
#include "buf.h"

/* int vector wrapper example */

typedef Buf Veci;

Veci*
newveci(int nelem)              /* alloc underlying buf for n count of elements */
{
	ulong cap = nelem * sizeof(int);
	return newbuf(cap);
}

int*
vecip(Veci *v, int idx)          /* return ptr to elem in dynamic array (&int v[idx]) */
{
	ulong off = idx * sizeof(int);
	return bufoff(v, off);
}

int	veci(Veci *v, int idx)		{return *(int*)vecip(v, idx);}		/* return elem from dynamic array (int v[idx]) */
int	nveci(Veci *v)			{return buflen(v) / sizeof(int);}	/* current n count of elements */
int	vecicap(Veci *v)		{return bufcap(v) / sizeof(int);}	/* current elem capacity in underlying buf */
void	pushveci(Veci *v, int val)	{appendbuf(v, &val, sizeof(val));}

void
popveci(Veci *v)	/* pop last element */
{
	fillbuf(v, 0, buflen(v)-1-sizeof(int), buflen(v));
	setbuflen(v, buflen(v)-sizeof(int));
}

void
insveci(Veci *v, ulong idx, int val)	/* insert at given idx */
{
	ulong off = idx * sizeof(int);
	insertbuf(v, off, &val, sizeof(int));
}

Veci*
copynveci(Veci *v, ulong from, ulong till)	/* copy from idx till idx */
{
	ulong foff = from * sizeof(int);
	ulong toff = till * sizeof(int);
	return copybufn(v, foff, toff);
}

void
cutveci(Veci *v, ulong from, ulong till)	/* cut from idx till idx */
{
	ulong foff = from * sizeof(int);
	ulong toff = till * sizeof(int);
	cutbuf(v, foff, toff);
}

void	freeveci(Veci *v)	{freebuf(v);}

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

	sv = copynveci(v, 1, 4);
	printf("new copied range sv veci 1-4: ");
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
