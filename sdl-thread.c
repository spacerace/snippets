#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

int read_joystick(void *p) {
	printf("joystick-thread started...\n");
	while(1) {
		SDL_Delay (10);
	}
	return 0;
}

int thread2 (void *p) {
	printf("eeer\n");
	while(1) {
		SDL_Delay (10);
	}
	return 0;
}

int main (void) {
	SDL_Thread *t1, *t2;
	if(SDL_Init (0) == -1) {
		printf ("Kann SDL nicht initialisieren: %s\n", SDL_GetError ());
		exit (1);
	}
	t1 = SDL_CreateThread (read_joystick, NULL);
	t2 = SDL_CreateThread (thread2, NULL);
	SDL_Delay (2000);
	SDL_KillThread (t1);
	SDL_KillThread (t2);
	SDL_Quit ();
	return 0;
}
