#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<ncurses.h>

void main()
{
    initscr();
    noecho();
    curs_set(0);
    
    int yMax,xMax;
    
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *win= newwin(yMax/2,xMax/2, yMax/4, xMax/4);
    
    box(win,0,0);
    mvwprintw(win, 1, 2, "Sort");
    mvwprintw(win, 2, 2, "Search");
    mvwprintw(win, 3, 2, "History");
    mvwprintw(win, 4, 2, "Exit");
    int i=-1,max=4;
    char op[4][15]={"Sort","Search","History","Exit"};
    int ch;
    while(ch=wgetch(win))
    {
        if(ch==66)
        {
            i=(i+1)%max;
            for(int j=0;j<max;j++)
            {
                if(i==j)
                {
                    wattron(win,A_STANDOUT);
                    mvwprintw(win, (j+1), 2, op[j]);
                    wattroff(win,A_STANDOUT);
                }
                else
                {
                    mvwprintw(win, (j+1), 2, op[j]);
                }
            }
            
        }
        else if(ch==65)
        {
            i=(i-1);
            if(i<0)
                i=max-1;
            for(int j=0;j<max;j++)
            {
                if(i==j)
                {
                        wattron(win,A_STANDOUT);
                        mvwprintw(win, (j+1), 2, op[j]);
                        wattroff(win,A_STANDOUT);
                }
                else
                {
                    mvwprintw(win, (j+1), 2, op[j]);
                }
            }
                
        }
        else if(ch==10)
        {
            switch(i)
            {
                case 0:mvwprintw(win,6,2,"You want to sort       ");
                       break;
                case 1:mvwprintw(win,6,2,"You want to search     ");
                       break;
                case 2:mvwprintw(win,6,2,"You want to see history");
                       break;
                case 3:mvwprintw(win,6,2,"You want to exit       ");
                       break;
            }
        }
    }
    endwin();
}
