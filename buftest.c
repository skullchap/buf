#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "buf.h"

int
buftest(void)
{
	Buf *b, *cb, *insb, *sb;	/* buf, copybuf, insertbuf, slicebuf */
	void *p; long n;
	int r, i;
	char s[] = "sneed and seed";
	char ins[] = "feed ";

	b = newbuf(1024);
	assert(b);
	assert(bufcap(b) == 1024);
	assert(buflen(b) == 0);
	assert(bufmem(b) == bufcursor(b));
	
	cb = copybuf(b);
	assert(cb);
	assert(bufcap(cb) == 1024);
	assert(buflen(cb) == 0);
	assert(bufmem(cb) == bufcursor(cb));
	assert(bufmem(cb) != bufcursor(b));
	freebuf(cb);

	n = 768;
	p = malloc(n);
	assert(p);
	r = appendbuf(b, p, n);
	assert(r == 0);
	assert(bufcap(b) == 1024);
	assert(buflen(b) == n);
	assert(((unsigned char*)bufmem(b)) + n == bufcursor(b));
	assert(bufmem(b) != p);

	r = appendbuf(b, p, n);
	assert(r == 0);
	assert(bufcap(b) == 1024 * 2);
	assert(buflen(b) == n*2);
	assert(((unsigned char*)bufmem(b)) + n*2 == bufcursor(b));
	assert(bufmem(b) != p);
	free(p);
	freebuf(b);

	b = newbuf(64);
	assert(b);
	r = insertbuf(b, 0, s, sizeof(s));
	assert(r == 0);
	assert(strncmp((char*)bufmem(b), s, sizeof(s)) == 0);
	insb = newbuf(sizeof(ins));
	r = insertbuf(insb, 0, ins, sizeof(ins));
	assert(r == 0);
	assert(strncmp((char*)bufmem(insb), ins, sizeof(ins)) == 0);
	assert(insb);
	r = insertbuf(b, 6, bufmem(insb), buflen(insb)-1);
	assert(r == 0);
	printf("|%s|\n", (char*)bufmem(b));
	assert(buflen(b) == 20);
	freebuf(insb);

	sb = slicebuf(b, 15, 19);
	assert(sb);
	assert(bufcap(sb) == 4);
	assert(buflen(sb) == 4);
	r = appendbuf(sb, "", 1);
	assert(r == 0);
	assert(bufcap(sb) == 4*2);
	assert(buflen(sb) == 5);
	printf("slice [15:19]: |%s|\n", (char*)bufmem(sb));

	r = cutbuf(sb, 1, 3);
	assert(r == 0);
	assert(bufcap(sb) == 4*2);
	assert(buflen(sb) == 3);
	printf("after [1:3] cut on slice: |%s|\n", (char*)bufmem(sb));
	freebuf(sb);

	r = cutbuf(b, 5, buflen(b)-1); /* '\0' */
	assert(r == 0);
	assert(buflen(b) == 6);
	printf("after [5:-1] cut on original: |%s|\n", (char*)bufmem(b));
	freebuf(b);

	b = newbuf(1024);
	assert(b);
	setbuflen(b, 512);
	assert(buflen(b) == 512);
	r = fillbuf(b, 42, 0, -1);
	assert(r == 0);
	for(i = 0; i < buflen(b); ++i){
		char c = *(char*)bufoff(b, i);
		assert(c == 42);
	}
	freebuf(b);

	puts("buftest Success.");
	return 0;
}


int
main(void)
{
	return buftest();
}
