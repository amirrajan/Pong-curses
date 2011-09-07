#include <ncurses.h>		
#include <stdlib.h>
#include <stdbool.h>
typedef struct{short int x; short int y; short int c; bool movhor; bool movver;}objeto;
bool cbool(bool a) {return a=(a==true) ? false : true;}
void engine(objeto *a, objeto *b1, objeto *b2, objeto *scr) {
	a->movver=((a->y==scr->y-1)||(a->y==1)) ? cbool(a->movver):a->movver;
	if ((a->x >= scr->x-2)||(a->x <= 2)){
		a->movhor=cbool(a->movhor);
		a->movver=((a->y==b1->y-1)||(a->y==b2->y-1)) ? false : cbool(a->movver);
		a->movver=((a->y==b1->y+1)||(a->y==b2->y+1)) ? true : a->movver;
		if (((a->y > b1->y+1)||(a->y < b1->y-1))&&(a->x>=scr->x-2)) {b1->c++; a->x=scr->x/2; a->y=scr->y/2;}
		if (((a->y > b2->y+1)||(a->y < b2->y-1))&&(a->x<=2)) {b2->c++; a->x=scr->x/2; a->y=scr->y/2;}
	}
	a->x=(a->movhor==true) ? a->x+1 : a->x-1;
	a->y=(a->movver==true) ? a->y+1 : a->y-1;
}
void main() {
	objeto b1,b2,b,s; int cont=0; bool fin=false;
	
	initscr();					
	start_color();	
	keypad(stdscr, true);
	noecho();
	curs_set(0);	
	init_pair(1,COLOR_RED,COLOR_BLACK);
	init_pair(2,COLOR_BLUE,COLOR_BLACK);
	init_pair(3,COLOR_WHITE,COLOR_BLACK);					
	getmaxyx(stdscr,s.y,s.x);
	b1.x=s.x-2; 	b2.x=1;		b.x=s.x/2;
	b1.y=s.y/2; 	b2.y=s.y/2; 	b.y=s.y/2;
	b1.c=0;		b2.c=0;
	mvprintw(4,5,"          oooooooooo                                   "); 
        mvprintw(5,5,"          888    888  ooooooo  oo oooooo     oooooooo8 ");
        mvprintw(6,5,"          888oooo88 888     888 888   888  888    88o  ");
        mvprintw(7,5,"          888       888     888 888   888   888oo888o  ");
        mvprintw(8,5,"         o888o        88ooo88  o888o o888o 888     888 ");
        mvprintw(9,5,"                                            888ooo888  ");
        mvprintw(11,5,"Any questions please send me at vicente.bolea@gmail.com");
	mvprintw(14,s.x/4,"Player 1 your controls are 'a' and 'q'");
	mvprintw(15,s.x/4,"Player 2 your controls are the arrows of the keyboard");
	mvprintw(17,s.x/4,"Push ANY key to start");
	getch();
			
	nodelay(stdscr,1);
	while (fin != true) {
		cont++;
		usleep(4000);
		if (cont%16==0) { engine(&b,&b1,&b2,&s);
		if (b1.y<=1) b1.y=s.y-2;
		if (b1.y>=s.y-1) b1.y=2;
		if (b2.y<=1) b2.y=s.y-2; 
		if (b2.y>=s.y-1) b2.y=2;
		}
		switch (getch()) {
			case KEY_DOWN:
				b1.y++;
				break;
			case KEY_UP:
				b1.y--;
				break;
			case 113:
				b2.y--;
				break;
			case 97:
				b2.y++;
				break;
			case 112:
				nodelay(stdscr,0);
				mvprintw(s.y/2,s.x/4,"The game is paused, push ANY key to resume");
				getch();
				nodelay(stdscr,1);
				break;
			case 27:
				fin=true;
				break;
		}
		erase();
		box(stdscr,0,0);
		attron(COLOR_PAIR(1));
		mvprintw(b.y,b.x,"o");
		attroff(COLOR_PAIR(1));	
		attron(COLOR_PAIR(2));
		mvprintw(s.y-4,s.x/2-4,"PINGPONG");
		attroff(COLOR_PAIR(2));		
		attron(COLOR_PAIR(3));
		mvprintw(b1.y-1,b1.x,"|");
		mvprintw(b1.y,b1.x,"|");
		mvprintw(b1.y+1,b1.x,"|");
		mvprintw(b2.y-1,b2.x,"|");
		mvprintw(b2.y,b2.x,"|");
		mvprintw(b2.y+1,b2.x,"|");
		attroff(COLOR_PAIR(3));
		mvprintw(2,s.x/11,"Player 1 : %i",b1.c);
		mvprintw(2,4*s.x/5,"%i : Player 2",b2.c);
		mvprintw(2,s.x/2-4,"time: %i",cont/8);
	}
	erase();
        endwin();
}
