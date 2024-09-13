/*
	Author:		skullchap	(skullchap@proton.me)
	Date Started:	2024.06.03
	License:	Non-Commercial	(full text in LICENSE file)
*/

typedef struct Buf 	Buf;
typedef unsigned long 	ulong;
typedef void* 		(*AllocFunc)(ulong);
typedef void  		(*DeallocFunc)(void*);
typedef void* 		(*ReallocFunc)(void*, ulong);

Buf*	newbuf(ulong cap);
void	freebuf(Buf*);
ulong	buflen(Buf*);					/* length of content */
ulong	bufcap(Buf*);					/* capacity */
void	setbuflen(Buf*, ulong len);
void	setbufcap(Buf*, ulong cap);			/* increase/decrease capacity. setbufcap(b, buflen(b)) can be used to shrink */
void*	bufmem(Buf*);					/* ptr to start of allocated mem */
void*	bufcursor(Buf*);				/* ptr to place where new mem will be appended */
void*	bufoff(Buf*, ulong off);			/* offset in memory */
Buf*	copybuf(Buf*);
Buf*	copybufn(Buf *b, ulong from, ulong till);	/* copy range */
void	appendbuf(Buf*, void*, ulong);
void	insertbuf(Buf*, ulong off, void*, ulong);	/* insert mem at given offset */
void	cutbuf(Buf *b, ulong from, ulong till);		/* cuts then welds provided range of buf */
void	fillbuf(Buf*, int c, ulong from, ulong till);	/* memset */
void	setbufalloc(AllocFunc);				/* replace malloc */
void	setbufdealloc(DeallocFunc);			/* replace realloc */
void	setbufrealloc(ReallocFunc); 			/* replace free */
/* Buf*	slicebuf(Buf*, ulong from, ulong till);		read fixme in c file */

/*
	Most functions assumed to be error proof by default, they don't check for NULL from malloc, realloc.
	This means that by default they expect alloc/realloc to never fail.
	To have some sort of check for NULL, provide own alloc/realloc functions, that have a check for it.
*/

#define BufLibVersion (2)	/* each update to lib should raise a version */

