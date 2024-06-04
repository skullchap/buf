/*
	Author:		skullchap	(skullchap@proton.me)
	Date Started:	2024.06.04
	License:	Non-Commercial	(full text in LICENSE file)
*/

#define vecprotos(type, alias) \
\
typedef Buf Vec##alias; \
\
Vec##alias * newvec##alias(long nelem); \
type*	vec##alias##p(Vec##alias *v, long idx); \
type	vec##alias(Vec##alias *v, long idx); \
long	nvec##alias(Vec##alias *v); \
long	vec##alias##cap(Vec##alias *v); \
Vec##alias * copyvec##alias(Vec##alias *v); \
int	pushvec##alias(Vec##alias *v, type val); \
int	pushpvec##alias(Vec##alias *v, type *p); \
int	pusharrvec##alias(Vec##alias *v, type arr[], long n); \
int	popvec##alias(Vec##alias *v); \
int	insvec##alias(Vec##alias *v, long idx, type val); \
int	inspvec##alias(Vec##alias *v, long idx, type *p); \
int	insarrvec##alias(Vec##alias *v, long idx, type arr[], long n); \
Vec##alias * slicevec##alias(Vec##alias *v, long from, long till); \
int	cutvec##alias(Vec##alias *v, long from, long till); \
void	freevec##alias(Vec##alias *v); \
void	fprintvec##alias(FILE *f, char *fmt, Vec##alias *v);

#define vecfuncs(type, alias) \
\
typedef Buf Vec##alias; \
\
Vec##alias * \
newvec##alias(long nelem) \
{ \
	long cap; \
	cap = nelem * sizeof(type); \
	return newbuf(cap); \
} \
\
type* \
vec##alias##p(Vec##alias *v, long idx) \
{ \
      	long off; \
	off = idx * sizeof(type); \
	return bufoff(v, off); \
} \
\
type \
vec##alias(Vec##alias *v, long idx) \
{ \
	return *(type*)vec##alias##p(v, idx); \
} \
\
long \
nvec##alias(Vec##alias *v) \
{ \
	return buflen(v) / sizeof(type); \
} \
\
long \
vec##alias##cap(Vec##alias *v) \
{ \
	return bufcap(v) / sizeof(type); \
} \
\
Vec##alias * \
copyvec##alias(Vec##alias *v) \
{ \
	return copybuf(v); \
} \
\
int \
pushvec##alias(Vec##alias *v, type val) \
{ \
	return appendbuf(v, &val, sizeof(type)); \
} \
\
int \
pushpvec##alias(Vec##alias *v, type *p) \
{ \
	return appendbuf(v, p, sizeof(type)); \
} \
\
int \
pusharrvec##alias(Vec##alias *v, type arr[], long n) \
{ \
	return appendbuf(v, arr, sizeof(type) * n); \
} \
\
int \
popvec##alias(Vec##alias *v) \
{ \
	int r; \
	r = fillbuf(v, 0, buflen(v)-1-sizeof(type), buflen(v)); \
	if(r < 0) \
		return r; \
	setbuflen(v, buflen(v)-sizeof(type)); \
	return 0; \
} \
\
int \
insvec##alias(Vec##alias *v, long idx, type val) \
{ \
	long off; \
	off = idx * sizeof(type); \
	return insertbuf(v, off, &val, sizeof(type)); \
} \
\
int \
inspvec##alias(Vec##alias *v, long idx, type *p) \
{ \
	long off; \
	off = idx * sizeof(type); \
	return insertbuf(v, off, p, sizeof(type)); \
} \
\
int \
insarrvec##alias(Vec##alias *v, long idx, type arr[], long n) \
{ \
	long off; \
	off = idx * sizeof(type); \
	return insertbuf(v, off, arr, sizeof(type) * n); \
} \
\
Vec##alias * \
slicevec##alias(Vec##alias *v, long from, long till) \
{ \
	long foff, toff; \
	foff = from * sizeof(type); \
	toff = till * sizeof(type); \
	return slicebuf(v, foff, toff); \
} \
\
int \
cutvec##alias(Vec##alias *v, long from, long till) \
{ \
	long foff, toff; \
	foff = from * sizeof(type); \
	toff = till * sizeof(type); \
	return cutbuf(v, foff, toff); \
} \
\
void \
freevec##alias(Vec##alias *v) \
{ \
	freebuf(v); \
} \
\
void \
fprintvec##alias(FILE *f, char *fmt, Vec##alias *v) \
{ \
	int i; \
	fprintf(f, "[ "); \
	for(i = 0; i < nvec##alias(v); ++i){ \
		fprintf(f, fmt, vec##alias(v, i)); \
		if(i != nvec##alias(v)-1) \
			fprintf(f, ", "); \
	} \
	fprintf(f, " ]"); \
}
