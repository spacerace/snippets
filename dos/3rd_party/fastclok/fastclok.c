/*
 *	This file contains the implementation of a more precise time
 * than that provided by DOS.  Routines are provided to increase the
 * clock rate to around 1165 interrupts per second, for a granularity
 * of close to 858 microseconds between clock pulses, rather than the
 * 55 milliseconds between normal PC clock pulses (18.2 times/second).
 *	The gettimeofday() routine acts like the Unix version, with
 * the exception that time zone does not matter.  The time will be returned
 * in timeval structures that match thier Unix counterparts.
 *	Note that the start_fasttimer() routine must be called before
 * the gettimeofday() routines will work, and that the stop_fasttimer()
 * routine MUST be called before the program terminates, or the machine
 * will be toasted.  For this reason, start_fasttimer() installs the
 * stop_fasttimer() routine to be called at program exit.
 */

#include	<stdlib.h>
#include	<dos.h>
#include	<time.h>
#include	<sys/nfs_time.h>
#include	"fastclok.h"

#define	CLOCK_INT	(0x08)
#define	USEC_INC	(858)

#pragma	option	-N-			// Do not check for stack overflow


static	int	fastclock_on = 0;	// Is the clock speed set higher?
static	struct	timeval	nowtime;	// Current time
static	void	interrupt (*oldfunc)(void);	// interrupt function pointer



/*	This routine will handle the clock interrupt at its higher rate.
 * It will call the DOS handler every 64 times it is called, to maintain
 * the 18.2 times per second that DOS needs to be called.  Each time through,
 * it adds to the nowtime value.
 *	When it is not calling the DOS handler, this routine must reset
 * the 8259A interrupt controller before returning. */

static	void	interrupt handle_clock(void) {
	static	int	callmod = 0;

	/* Increment the time */
	nowtime.tv_usec += USEC_INC;
	if (nowtime.tv_usec > 1000000L) {
		nowtime.tv_sec++;
		nowtime.tv_usec -= 1000000L;
	}

	/* Increment the callmod */
	callmod = (callmod+1)%64;

	/* If this is the 64th call, then call handler */
	if (callmod == 0) {
		oldfunc();

	/* Otherwise, clear the interrupt controller */
	} else {
		outp(0x20,0x20);	// End of interrupt
	}
}


/*	This routine will stop the fast clock if it is going.  It
 * has void return value so that it can be an exit procedure. */

void	stop_fastclock(void) {

	/* See if the clock is on - exit if not */
	if (!fastclock_on) {
		return;
	}

	/* Disable interrupts */
	asm {cli};

	/* Reinstate the old interrupt handler */
	setvect(CLOCK_INT, oldfunc);

	/* Reinstate the clock rate to 18.2 Hz */
	outp(0x43, 0x36);	// Set up for count to be sent
	outp(0x40, 0x00);	// LSB = 00  \_together make 65536 (0)
	outp(0x40, 0x00);	// MSB = 00  /

	/* Enable interrupts */
	asm {sti};

	/* Mark clock is not fast */
	fastclock_on = 0;
}


/*	This routine will start the fast clock rate by installing the
 * handle_clock routine as the interrupt service routine for the clock
 * interrupt and then setting the interrupt rate up to its higher speed
 * by programming the 8253 timer chip.
 *	This routine does nothing if the clock rate is already set to
 * its higher rate, but then it returns -1 to indicate the error.
 */

int	start_fastclock(void) {

	/* Make sure the clock is not already set faster */
	if (fastclock_on) {
		return(-1);
	}

	/* Disable interrupts */
	asm {cli};

	/* Store the old interrupt handler */
	oldfunc = getvect(CLOCK_INT);

	/* Install the new interrupt handler */
	setvect(CLOCK_INT,handle_clock);

	/* Increase the clock rate */
	outp(0x43, 0x36);	// Set up for count to be sent
	outp(0x40, 0x00);	// LSB = 00  \_together make 2^10 = 1024
	outp(0x40, 0x04);	// MSB = 04  /

	/* Set the time to seconds since GMT whatever time/date */
	nowtime.tv_sec = time(NULL);
	nowtime.tv_usec = 0;

	/* Install the stop_fastclock() routine to be called at exit */
	atexit(stop_fastclock);

	/* Enable interrupts */
	asm {sti};

	/* Mark the clock as faster */
	fastclock_on = 1;
	return(0);
}


/*	This routine will return the present value of the time, which is
 * read from the nowtime structure.  Interrupts are disabled during this
 * time to prevent the clock from changing while it is being read.
 */

void	getfasttime(struct timeval *time) {

	/* Disable interrupts */
	asm {cli};

	/* Read the time */
	*time = nowtime;

	/* Enable interrupts */
	asm {sti};
}

