/* game of life */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define at2d(ptr, x, y, sx) (ptr)[(y) * (sx) + (x)]

void
wait_fraction(int fraction)
{
	clock_t nexttime = clock() + CLOCKS_PER_SEC / fraction;
	while(clock() < nexttime);
}


void
getsim(bool *simptr, size_t sx, size_t sy)
{
	for(int y=0; y<sy; y++) {
		for(int x=0; x<sx; x++) {
			if(getchar()=='#')
				at2d(simptr, x, y, sx)=true;
		}
		getchar();
	}
}

void
killsim(bool *simptr, size_t sx, size_t sy)
{
	for(int y=0; y<sy; y++)
		for(int x=0; x<sx; x++)
			at2d(simptr, x, y, sx)=false;
}

bool
getcell(bool *simptr, int x, int y, size_t sx, size_t sy)
{
	if(x<0)
		x=sx+x;
	else if(x>=sx)
		x=sx-x;
	if(y<0)
		y=sy+y;
	else if(y>=sy)
		y=sy-y;

	return at2d(simptr, x, y, sx);
}

void
matchboardtorules(bool *simptr, bool *nextgenptr, size_t sx, size_t sy)
{
	for(int x=0; x<sx; x++) {
		for(int y=0; y<sy; y++) {
			bool ccell = at2d(simptr, x, y, sx);
			bool nw, n, ne, w, e, sw, s, se;
			nw = getcell(simptr, x-1, y-1, sx, sy);
			n  = getcell(simptr, x  , y-1, sx, sy);
			ne = getcell(simptr, x+1, y-1, sx, sy);
			sw = getcell(simptr, x-1, y+1, sx, sy);
			s  = getcell(simptr, x  , y+1, sx, sy);
			se = getcell(simptr, x+1, y+1, sx, sy);
			w  = getcell(simptr, x-1, y  , sx, sy);
			e  = getcell(simptr, x+1, y  , sx, sy);

			int aliveneighbors = nw+n+ne+w+e+sw+s+se;

			if(ccell)
				if(aliveneighbors==2 || aliveneighbors==3)
					at2d(nextgenptr, x, y, sx)=true;
				else
					at2d(nextgenptr, x, y, sx)=false;
			else
				if(aliveneighbors==3)
					at2d(nextgenptr, x, y, sx)=true;
				else
					at2d(nextgenptr, x, y, sx)=false;
		}
	}
}

void
printboard(bool *simptr, size_t sx, size_t sy)
{
	for(int y=0; y<sy; y++) {
		for(int x=0; x<sx; x++) {
			bool ccell=at2d(simptr, x, y, sx);

			if(ccell)
				putchar('#');
			else
				putchar('.');
		}
		putchar('\n');
	}
}

int
main(int argc, char *argv[])
{
	bool simgrid[30 * 30];
	bool nextgengrid[30 * 30];
	int sx = 30;
	int sy = 30;
	int fractiontowait = 10;

	if(argc>1)
		fractiontowait=atoi(argv[1]);

	killsim(simgrid, sx, sy);
	getsim(simgrid, sx, sy);

	for(;;) {
		matchboardtorules(simgrid, nextgengrid, 30, 30);
		printboard(nextgengrid, 30, 30);

		memcpy(simgrid, nextgengrid, sizeof(nextgengrid));
		wait_fraction(fractiontowait);
	}

	return 0;
}

/* eof */
