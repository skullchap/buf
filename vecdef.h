/*
	Author:		skullchap	(skullchap@proton.me)
	Date Started:	2024.06.04
	License:	Non-Commercial	(full text in LICENSE file)
*/

#define vecprotos(type, alias) \
\
typedef Buf Vec##alias; \
\
Vec##alias * newvec##alias(ulong nelem); \
type*	vec##alias##p(Vec##alias *v, ulong idx); \
type	vec##alias(Vec##alias *v, ulong idx); \
ulong	nvec##alias(Vec##alias *v); \
ulong	vec##alias##cap(Vec##alias *v); \
Vec##alias * copyvec##alias(Vec##alias *v); \
Vec##alias * copyvecn##alias(Vec##alias *v, ulong from, ulong till); \
void	pushvec##alias(Vec##alias *v, type val); \
void	pushpvec##alias(Vec##alias *v, type *p); \
void	pusharrvec##alias(Vec##alias *v, type arr[], ulong n); \
void	popvec##alias(Vec##alias *v); \
void	insvec##alias(Vec##alias *v, ulong idx, type val); \
void	inspvec##alias(Vec##alias *v, ulong idx, type *p); \
void	insarrvec##alias(Vec##alias *v, ulong idx, type arr[], ulong n); \
void	cutvec##alias(Vec##alias *v, ulong from, ulong till); \
void	freevec##alias(Vec##alias *v); \
void	fprintvec##alias(FILE *f, char *fmt, Vec##alias *v);

#define vecfuncs(type, alias) \
\
typedef Buf Vec##alias; \
\
Vec##alias * \
newvec##alias(ulong nelem) \
{ \
	ulong cap = nelem * sizeof(type); \
	return newbuf(cap); \
} \
\
type* \
vec##alias##p(Vec##alias *v, ulong idx) \
{ \
      	ulong off = idx * sizeof(type); \
	return bufoff(v, off); \
} \
\
type \
vec##alias(Vec##alias *v, ulong idx) \
{ \
	return *(type*)vec##alias##p(v, idx); \
} \
\
ulong \
nvec##alias(Vec##alias *v) \
{ \
	return buflen(v) / sizeof(type); \
} \
\
ulong \
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
Vec##alias * \
copyvecn##alias(Vec##alias *v, ulong from, ulong till) \
{ \
	ulong foff = from * sizeof(type); \
	ulong toff = till * sizeof(type); \
	return copybufn(v, foff, toff); \
} \
\
void \
pushvec##alias(Vec##alias *v, type val) \
{ \
	appendbuf(v, &val, sizeof(type)); \
} \
\
void \
pushpvec##alias(Vec##alias *v, type *p) \
{ \
	appendbuf(v, p, sizeof(type)); \
} \
\
void \
pusharrvec##alias(Vec##alias *v, type arr[], ulong n) \
{ \
	appendbuf(v, arr, sizeof(type) * n); \
} \
\
void \
popvec##alias(Vec##alias *v) \
{ \
	fillbuf(v, 0, buflen(v)-1-sizeof(type), buflen(v)); \
	setbuflen(v, buflen(v)-sizeof(type)); \
} \
\
void \
insvec##alias(Vec##alias *v, ulong idx, type val) \
{ \
	ulong off = idx * sizeof(type); \
	insertbuf(v, off, &val, sizeof(type)); \
} \
\
void \
inspvec##alias(Vec##alias *v, ulong idx, type *p) \
{ \
	ulong off = idx * sizeof(type); \
	insertbuf(v, off, p, sizeof(type)); \
} \
\
void \
insarrvec##alias(Vec##alias *v, ulong idx, type arr[], ulong n) \
{ \
	ulong off = idx * sizeof(type); \
	insertbuf(v, off, arr, sizeof(type) * n); \
} \
\
\
void \
cutvec##alias(Vec##alias *v, ulong from, ulong till) \
{ \
	ulong foff = from * sizeof(type); \
	ulong toff = till * sizeof(type); \
	cutbuf(v, foff, toff); \
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
