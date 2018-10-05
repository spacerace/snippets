/*
 *	This program will test the fastclok.c routines.  It starts the
 * fast clock and then goes printing the values of DOS current time and
 * gettimeofday() current time.  When a key is pressed, the program exits.
 */

#include	<stdio.h>
#include	<string.h>
#include	<conio.h>
#include	<time.h>
#include	"fastclok.h"
#include	<sys/nfs_time.h>

void	main(void) {
	time_t t;
	struct timeval	now_t;

	/* Start the clock going */
	if (start_fastclock()) {
		fprintf(stderr,"Could not start fastclock\n");
		return;
	}

	/* Make sure we can't start it twice */
	if (!start_fastclock()) {
		fprintf(stderr,"Restarted clock while started (error)\n");
		return;
	}

	/* Stop the clock */
	stop_fastclock();

	/* Restart the clock */
	if (start_fastclock()) {
		fprintf(stderr,"Could not restart fastclock\n");
		return;
	}

	/* Print time values until a key is pressed */
	clrscr();
	while (!kbhit()) {

		gotoxy(35,10);
		t = time(NULL);
		cprintf("DOS seconds:  %7ld",t);
		gotoxy(35,11);
		getfasttime(&now_t);
		cprintf("Fast seconds: %7ld %7ld",now_t.tv_sec,now_t.tv_usec);
	}

	/* We're out of here */
	(void)getch();
	return;
}