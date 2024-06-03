/*
	Author:		skullchap	(skullchap@proton.me)
	Date Started:	2024.06.03
	License:	Non-Commercial	(full text in LICENSE file)
*/

typedef struct Buf Buf;

Buf*	newbuf(long cap);
void	freebuf(Buf*);
long	buflen(Buf*);				/* length of content */
long	bufcap(Buf*);				/* capacity */
int	setbufcap(Buf*, long cap);		/* increase/decrease capacity. setbufcap(b, buflen(b)) can be used to shrink */
void*	bufmem(Buf*);				/* ptr to start of allocated mem */
void*	bufcursor(Buf*);			/* ptr to place where new mem will be appended */
Buf*	copybuf(Buf*);
int	appendbuf(Buf*, void*, long);
int	insertbuf(Buf*, long idx, void*, long);
Buf*	slicebuf(Buf*, long from, long till);	/* slicebuf(b, 1, 4) on "Hello" returns "ell". negative ranges clamp to 0 and buflen */

/*
	Functions return either NULL or negative number on error.
	appendbuf and insertbuf can set errno to ERANGE on long add overflow condition.
	slicebuf can set errno to ERANGE on from >= till condition.
*/
