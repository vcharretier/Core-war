#include <ncurses.h>
#include <stdlib.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{	

	initscr();			/* Start curses mode 		*/
	WINDOW *my_win = newwin(0,0,0,0) ;
	char* titre = "CORE WAR !!!";
  	addstr(titre);
	curs_set(0);
	noecho();
	keypad(stdscr,TRUE);
	refresh();

	while(1);
	endwin();			/* End curses mode		  */
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	
}
