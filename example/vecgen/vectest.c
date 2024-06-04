#include <stdio.h>
#include "buf.h"
#include "vecdef.h"

vecprotos(int, i)
vecprotos(unsigned long, ul)
vecprotos(double, d)

#define	nelem(x)	(sizeof(x)/sizeof((x)[0]))

int
main(void)
{
        Vecd *vd;
        double arr[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6};

        vd = newvecd(24);
        if(vd == NULL)
                return -1;

        pusharrvecd(vd, arr, nelem(arr));
        fprintvecd(stdout, "%.2f", vd);
        puts("");
        printf("n: %d, ncap: %d\n", nvecd(vd), vecdcap(vd));

        cutvecd(vd, 1, 5);
        printf("vecd after 1-5 cut: ");
        fprintvecd(stdout, "%.2f", vd);
        puts("");
        printf("n: %d, ncap: %d\n", nvecd(vd), vecdcap(vd));

        freevecd(vd);
}
