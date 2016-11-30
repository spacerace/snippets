#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "mcurses.h"

void win_mmc_browser();
void win_mmc_browser_update_titlebar(char *s);
void win_mmc_browser_update_drive(unsigned int n);
void win_mmc_browser_update_path(char *s);
void win_mmc_browser_draw_key_assignments();
void win_mmc_browser_update_date_time();
void win_mmc_browser_info_win();

int main() {
	initscr();

	curs_set(FALSE);
	nodelay(TRUE);

	win_mmc_browser();
	win_mmc_browser_update_titlebar(" MMC/SD-TOOL  v0.0 ");
	win_mmc_browser_update_drive(0);
	win_mmc_browser_update_path("/PATH/ON/DISK//");
	win_mmc_browser_update_date_time();	
	win_mmc_browser_info_win();
	unsigned char c;

	for(;;) {
		c = getch();
		if(c != ERR) {
			switch(c) {
				case KEY_DOWN:
					break;
				case KEY_UP:
					break;
				case KEY_F(1):	
					break;
				case KEY_F(2):
					break;
				case 'q':
					goto fucked;
					break;
			}
		} 
		else {
			usleep(10000);	// 10mS
			win_mmc_browser_update_date_time();
		}	
	}

fucked:	
	endwin();

	return 0;
}

void win_mmc_browser_info_win() {
	attrset(F_WHITE | B_BLUE | A_BOLD);
	mvaddstr(4,51, " filesystem:");
	mvaddstr(5,51, "volume name: ");
	mvaddstr(6,51, "  volume ID:");
	mvaddstr(7,51, "volume size:");
	mvaddstr(8,51, " used/avail:");
}

void win_mmc_browser_draw_key_assignments() {
	attrset(B_BLUE | F_WHITE);
	mvaddstr(19,51, "F1 bench F5 copy   F9 drive");
	mvaddstr(20,51, "F2 fdisk F6 rename F10 view");
	mvaddstr(21,51, "F3 mkfs  F7 mkdir   q  quit");
	mvaddstr(22,51, "F4 fsck  F8 del     l label");

	attrset(F_YELLOW | B_BLUE | A_BOLD);
	mvaddstr(19,51, "F1");
	mvaddstr(20,51, "F2");
	mvaddstr(21,51, "F3");
	mvaddstr(22,51, "F4");
	mvaddstr(19,60, "F5");
	mvaddstr(20,60, "F6");
	mvaddstr(21,60, "F7");
	mvaddstr(22,60, "F8");
	mvaddstr(19,70, "F9");
	mvaddstr(20,70, "F10");
	mvaddstr(21,71, "q");
	mvaddstr(22,71, "l");
	
	attrset(B_BLUE  | F_WHITE);
}

void win_mmc_browser_update_date_time() {
	time_t t;
	attrset(F_CYAN | B_YELLOW | A_BOLD);
	t = time(NULL);
	mvaddstr(1,54, ctime(&t));
}

void win_mmc_browser_update_path(char *s) {
	attrset(F_RED | B_BLUE | A_BOLD);
	mvaddstr(22,7, s);	
}

void win_mmc_browser_update_drive(unsigned int n) {
	attrset(F_RED | B_BLUE | A_BOLD);
	char buf[3];
	if(n > 9) n = 9;
	move(22,2);
	sprintf(buf, "%u:", n);
	addstr(buf);
}

void win_mmc_browser_update_titlebar(char *s) {
	attrset(F_CYAN | B_YELLOW | A_BOLD );
	mvaddstr(1,2, s);
}
void win_mmc_browser() {
	int y, x;

	move(0,0);	// y,x	somewhat strange, as it is x/y usually. 
			// to be fair, afair all curses implementations 
			// are using y/x format

	attrset(B_BLUE | F_WHITE);

	// fill screen
	move(0,0);
	for(y = 0; y <= 23; y++) {
		for(x = 0; x <= 79; x++) {
			move(y,x);
			addch(' ');		
		}
	}
	

	// outer borderline around the whole window
	// top
	move(0,0);
	addch(ACS_ULCORNER);
	for(x = 1; x < 79; x++) addch(ACS_HLINE);
	addch(ACS_URCORNER);
	// left+right
	for(y = 1; y < 23; y++) {
		move(y,0);	// left
		addch(ACS_VLINE);
		move(y,79);	// right
		addch(ACS_VLINE);
	}
	// bottom
	y = 23;
	move(y, 0);
	addch(ACS_LLCORNER);
	for(x = 1; x < 79; x++) addch(ACS_HLINE);
	addch(ACS_LRCORNER);


	// draw border for header line	(date/time)
	move(0,49);
	addch(ACS_TTEE);
	move(1,49);
	addch(ACS_VLINE);
	move(2,49);
	addch(ACS_LTEE);
	for(x = 50; x <= 78; x++) addch(ACS_HLINE);
	addch(ACS_RTEE);

	// draw border for info window
	x = 49;
	for(y = 3; y <= 22; y++) {	// also covers left border of key assignments frame
		move(y,x);
		addch(ACS_VLINE);
	}
	y = 18;
	move(y,50);
	for(x = 50; x <= 78; x++) addch(ACS_HLINE);
	move(y,49);
	addch(ACS_LTEE);
	move(y,79);
	addch(ACS_RTEE);
	// draw border for key assignments
	move(23,49);
	addch(ACS_BTEE);
	// draw key assignments
	win_mmc_browser_draw_key_assignments();


	// draw border for drive and path
	move(21,0);
	addch(ACS_LTEE);
	move(21,49);
	addch(ACS_RTEE);
	move(21, 1);
	for(x = 1; x <= 48; x++) addch(ACS_HLINE);
	move(21,5);
	addch(ACS_TTEE);
	move(22,5);
	addch(ACS_VLINE);
	move(23,5);
	addch(ACS_BTEE);


	// draw titlebar
	move(2,0);
	addch(ACS_LTEE);
	for(x = 1; x <= 22; x++) addch(ACS_HLINE);
	move(2,22);
	addch(ACS_LRCORNER);
	move(1,22);
	addch(ACS_VLINE);
	move(0,22);
	addch(ACS_TTEE);


	attrset(B_BLUE | F_WHITE);
		
}

