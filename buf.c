/*
	Author:		skullchap	(skullchap@proton.me)
	Date Started:	2024.06.03
	License:	Non-Commercial	(full text in LICENSE file)
*/

#include "buf.h"
#include <limits.h>
#include <errno.h>

typedef unsigned char uchar;
typedef unsigned long ulong;

#define NULL	((void*)0)

extern void*	malloc(ulong n);
extern void*	realloc(void *p, ulong n);
extern void	free(void *p);
extern void*	memcpy(void *dst, const void *src, ulong n);
extern void*	memmove(void *dst, const void *src, ulong n);
extern void*	memset(void *s, int c, ulong n);

static long	bufneedsgrow(Buf*, long n);

struct Buf
{
	long	len;
	long	cap;
	uchar	*mem;
};

Buf*
newbuf(long cap)
{
	Buf *b;

	b = malloc(sizeof(Buf));
	if (b == NULL)
		return NULL;

	b->mem = malloc(cap);
	if (b->mem == NULL) {
		free(b);
		return NULL;
	}
	b->len = 0;
	b->cap = cap;
	return b;
}

void
freebuf(Buf *b)
{
	free(b->mem);
	free(b);
}

long
buflen(Buf *b)
{
	return b->len;
}

long
bufcap(Buf *b)
{
	return b->cap;
}

void*
bufmem(Buf *b)
{
	return b->mem;
}

void*
bufcursor(Buf *b)
{
	return b->mem + b->len;
}

void*
bufoff(Buf *b, long off)
{
	return b->mem + off;
}

Buf*
copybuf(Buf *b)
{
	Buf *nb;
	
	nb = newbuf(b->cap);
	if (nb == NULL)
		return NULL;
	memcpy(nb->mem, b->mem, b->len);
	nb->len = b->len;
	return nb;
}

int
appendbuf(Buf *b, void *p, long n)
{
	long r;

	r = bufneedsgrow(b, n);
	if (r > 0) {
		r = setbufcap(b, r);
		if (r < 0)
			return -1;
	}
	if (r < 0)
		return -1;
	memcpy(bufcursor(b), p, n);
	b->len += n;
	return 0;
}

int
insertbuf(Buf *b, long off, void *p, long n)
{
	long r;

	r = bufneedsgrow(b, n);
	if (r > 0) {
		r = setbufcap(b, r);
		if (r < 0)
			return -1;
	}
	if (r < 0)
		return -1;
	memmove(b->mem + off + n, b->mem + off, b->len - off);
	memcpy(b->mem + off, p, n);
	b->len += n;
	return 0;
}

Buf* 
slicebuf(Buf *b, long from, long till)
{
	Buf *sb;
	long n;

	if (from < 0)
		from = 0;
	if(till < 0 || till > b->len)
		till = b->len;

	if (from >= till) {
		errno = ERANGE;
		return NULL;
	}

	n = till - from;
	sb = newbuf(n);
	if (sb == NULL)
		return NULL;
	memcpy(sb->mem, b->mem + from, n);
	sb->len = n;
	return sb;
}

int 
fillbuf(Buf *b, int c, long from, long till)
{
	long n;

	if (from < 0)
		from = 0;
	if(till < 0 || till > b->len)
		till = b->len;

	if (from >= till) {
		errno = ERANGE;
		return -1;
	}

	n = till - from;
	memset(b->mem + from, c, n);
	return 0;
}

int
setbufcap(Buf *b, long cap)
{
	void *p;

	p = realloc(b->mem, cap);
	if (p == NULL)
		return -1;
	b->mem = p;
	b->cap = cap;
	return 0;
}

void
setbuflen(Buf *b, long len)
{
	b->len = len;
}

static
long
bufneedsgrow(Buf *b, long n)		/* returns new cap size if buf needs it */
{
	ulong cap, leftover;

	leftover = b->len + n;
	if (leftover > LONG_MAX) {
		errno = ERANGE;
		return -1;
	}
	cap = b->cap;
	while (cap < leftover) {
		cap *= 2;
		if (cap > LONG_MAX) {
			errno = ERANGE;
			return -1;
		}
	}

	if (cap == b->cap)
		return 0;

	return (long)cap;
}
