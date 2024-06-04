/*
	Author:		skullchap	(skullchap@proton.me)
	Date Started:	2024.06.03
	License:	Non-Commercial	(full text in LICENSE file)
*/

typedef struct Buf Buf;

Buf*	newbuf(long cap);
void	freebuf(Buf*);
long	buflen(Buf*);				/* length of content */
void	setbuflen(Buf*, long len);
long	bufcap(Buf*);				/* capacity */
int	setbufcap(Buf*, long cap);		/* increase/decrease capacity. setbufcap(b, buflen(b)) can be used to shrink */
void*	bufmem(Buf*);				/* ptr to start of allocated mem */
void*	bufcursor(Buf*);			/* ptr to place where new mem will be appended */
void*	bufoff(Buf*, long off);			/* offset in memory */
Buf*	copybuf(Buf*);
int	appendbuf(Buf*, void*, long);
int	insertbuf(Buf*, long off, void*, long);		/* insert mem at given offset */
Buf*	slicebuf(Buf*, long from, long till);		/* slicebuf(b, 1, 4) on "Hello" returns "ell" copy. negative ranges clamp to 0 and buflen */
int	cutbuf(Buf *b, long from, long till);		/* same semantics as slicebuf, except it cuts then welds provided range of buf */
int	fillbuf(Buf*, int c, long from, long till);	/* memset */

/*
	Functions return either NULL or negative number on error.
	appendbuf and insertbuf can set errno to ERANGE on long add overflow condition.
	slicebuf and fillbuf can set errno to ERANGE on from >= till condition.
*/
