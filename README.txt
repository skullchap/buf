ANSI C89 compatible, dynamic buffer lib.

Buf*	newbuf(long cap);
void	freebuf(Buf*);
long	buflen(Buf*);
void	setbuflen(Buf*, long len);
long	bufcap(Buf*);
int	setbufcap(Buf*, long cap);
void*	bufmem(Buf*);
void*	bufcursor(Buf*);
void*	bufoff(Buf*, long off);
Buf*	copybuf(Buf*);
int	appendbuf(Buf*, void*, long);
int	insertbuf(Buf*, long off, void*, long);
Buf*	slicebuf(Buf*, long from, long till);
int	cutbuf(Buf *b, long from, long till);
int	fillbuf(Buf*, int c, long from, long till);

Functions return either NULL or negative number on error.
appendbuf and insertbuf can set errno to ERANGE on long add overflow condition.
slicebuf, cutbuf and fillbuf can set errno to ERANGE on from >= till condition.

example/veci.c contains how type vector wrappers could be made.

vecdef.h is a set of code generator macros to help build type vector wrappers
similar to ones found in example/veci.c. It has vecprotos and vecfuncs macros,
that generate vector prototypes and functions for a given type.
example/vecgen contains how vecdef.h could be used.
