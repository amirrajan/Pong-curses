#include <ncurses.h>

#ifndef HOST
#define HOST localhost
#endif

int main(int argc, char **argv){	
	object scr; int i,cont=0; bool fin=false;
	initscr();					
	start_color();
	init_pair(1,COLOR_BLUE,COLOR_BLACK);	
	keypad(stdscr,true);
	noecho();
	curs_set(0);						
	getmaxyx(stdscr,scr.y,scr.x);

	for (nodelay(stdscr,1); !fin; usleep(4000)) {

		switch (getch()) {
			case KEY_DOWN:	b1.y++; break;
			case KEY_UP: 		b1.y--; break;
			case 'q':				b2.y--; break;
			case 'a':				b2.y++; break;
			case 'p':				getchar(); break;
			case 27: 				endwin(); fin++; break;
		}
		send( Keyboard)
			recv( all cordenates);
		erase();
		mvprintw(2,scr.x/2-2,"%i | %i",b1.c,b2.c);
		mvvline(0,scr.x/2,ACS_VLINE,scr.y);
		attron(COLOR_PAIR(1));
		mvprintw(b.y,b.x,"o");
		for(i=-1;i<2;i++){
			mvprintw(b1.y+i,b1.x,"|");
			mvprintw(b2.y+i,b2.x,"|");}
			attroff(COLOR_PAIR(1));
	}
}
