/*
	Author:		skullchap	(skullchap@proton.me)
	Date Started:	2024.06.03
	License:	Non-Commercial	(full text in LICENSE file)
*/

#include "buf.h"
#include <limits.h>

typedef unsigned char uchar;

#define NULL	((void*)0)

extern void*	malloc(ulong n);
extern void*	realloc(void *p, ulong n);
extern void	free(void *p);
extern void*	memcpy(void *dst, const void *src, ulong n);
extern void*	memmove(void *dst, const void *src, ulong n);
extern void*	memset(void *s, int c, ulong n);

static ulong	bufneedsgrow(Buf*, ulong n);

static AllocFunc   alloc     = malloc;
static DeallocFunc dealloc   = free;
static ReallocFunc reallocfn = realloc;

struct Buf
{
	ulong	len;
	ulong	cap;
	uchar	*mem;
};

Buf*
newbuf(ulong cap)
{
	Buf *b = alloc(sizeof(Buf));
	b->mem = alloc(cap);
	b->len = 0;
	b->cap = cap;
	return b;
}

void
freebuf(Buf *b)
{
	if(b == NULL)
		return;
	dealloc(b->mem);
	dealloc(b);
}

ulong	buflen(Buf *b)			{return b->len;}
ulong	bufcap(Buf *b)			{return b->cap;}
void*	bufmem(Buf *b)			{return b->mem;}
void*	bufcursor(Buf *b)		{return b->mem+b->len;}
void*	bufoff(Buf *b, ulong off)	{return b->mem+off;}
void	setbuflen(Buf *b, ulong len) 	{b->len = len;}
void
setbufcap(Buf *b, ulong cap)
{
	b->mem = reallocfn(b->mem, cap);
	b->cap = cap;
}
void	setbufalloc(AllocFunc afn)	{alloc=afn;}
void	setbufdealloc(DeallocFunc dfn)	{dealloc=dfn;}
void	setbufrealloc(ReallocFunc rfn)	{reallocfn=rfn;}

Buf*
copybuf(Buf *b)
{
	Buf *nb = newbuf(b->cap);
	memcpy(nb->mem, b->mem, b->len);
	nb->len = b->len;
	return nb;
}

Buf* 
copybufn(Buf *b, ulong from, ulong till)
{
	ulong n = till - from;
	Buf *sb = newbuf(n);
	memcpy(sb->mem, b->mem + from, n);
	sb->len = n;
	return sb;
}

void
appendbuf(Buf *b, void *p, ulong n)
{
	ulong r = bufneedsgrow(b, n);
	if (r > 0) 
		setbufcap(b, r);
	memcpy(bufcursor(b), p, n);
	b->len += n;
}

void
insertbuf(Buf *b, ulong off, void *p, ulong n)
{
	ulong r = bufneedsgrow(b, n);
	if (r > 0) 
		setbufcap(b, r);
	memmove(b->mem + off + n, b->mem + off, b->len - off);
	memcpy(b->mem + off, p, n);
	b->len += n;
}

/* fixme: copynbuf used to be slicebuf. new slice impl returns "view" to original buffer, 
   but this has a potential problem of double free on original buf and sliced one.
   Potential fix to this could be made by marking Buf as slice internally either by adding 
   member like isslice inside Buf, or by setting cap to symbolic const like ULONG_MAX or something like that.
   ¯\_(ツ)_/¯
*/
/*
Buf* 
slicebuf(Buf *b, ulong from, ulong till)
{
	ulong n = till - from;
	Buf *sb = alloc(sizeof(Buf));
	sb->mem = b->mem + from;
	sb->len = n;
	sb->cap = 0;
	return sb;
}
*/

void
cutbuf(Buf *b, ulong from, ulong till)
{
	ulong n = till - from;
	memmove(b->mem + from, b->mem + till, n);
	b->len -= n;
}

void
fillbuf(Buf *b, int c, ulong from, ulong till)
{
	ulong n = till - from;
	memset(b->mem + from, c, n);
}

static 
ulong
next_power_of_two(ulong v)
{
    if (v == 0) return 1;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    #if ULONG_MAX > 0xFFFFFFFF
    v |= v >> 32;
    #endif
    return v + 1;
}

static
ulong
bufneedsgrow(Buf *b, ulong n)		/* returns new cap size if buf needs it */
{
	ulong cap = b->cap;
	ulong leftover = b->len + n;

	if (leftover <= cap)
		return 0;

 	return next_power_of_two(leftover);
 
/* 	if (cap == 0)
		cap = 1;
	while (cap < leftover)
		cap *= 2;
	return cap; */
}
