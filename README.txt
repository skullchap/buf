ANSI C89 compatible, dynamic buffer lib.

Buf*	newbuf(ulong cap);
void	freebuf(Buf*);
ulong	buflen(Buf*);
ulong	bufcap(Buf*);
void	setbuflen(Buf*, ulong len);
void	setbufcap(Buf*, ulong cap);
void*	bufmem(Buf*);
void*	bufcursor(Buf*);
void*	bufoff(Buf*, ulong off);
Buf*	copybuf(Buf*);
Buf*	copybufn(Buf *b, ulong from, ulong till);
void	appendbuf(Buf*, void*, ulong);
void	insertbuf(Buf*, ulong off, void*, ulong);
void	cutbuf(Buf *b, ulong from, ulong till);
void	fillbuf(Buf*, int c, ulong from, ulong till);
void	setbufalloc(AllocFunc afn);
void	setbufdealloc(DeallocFunc dfn);
void	setbufrealloc(ReallocFunc rfn);

Most functions assumed to be error proof by default, they don't check for NULL from malloc, realloc.
This means that by default they expect alloc/realloc to never fail.
To have some sort of check for NULL, provide own alloc/realloc functions, that have a check for it.

example/veci.c contains how type vector wrappers could be made.

vecdef.h is a set of code generator macros to help build type vector wrappers
similar to ones found in example/veci.c. It has vecprotos and vecfuncs macros,
that generate vector prototypes and functions for a given type.
example/vecgen contains how vecdef.h could be used.
