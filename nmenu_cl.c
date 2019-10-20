/*
    A 'plug and play' menu system for ncurses with automatic sizing and centering
    Joe Standring <git@joestandring.com>
    GNU GPLv3

    This file is used to build an implementation of nmenu for the command line
*/

#include "nmenu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void printUsage()
{
    printf("USAGE\n\tnmenu Title Description\n\n\t-c Display the menu centered\n\t-v Display the menu vertically");
}

int main(int argc, char **argv)
{
    bool centered = false,
         vertical = false,
         hasTitle = false,
         hasDesc = false;
    char *title,
         *desc,
         *choices[3]; // I'll figure out resizing this dynamically at some point (promise!)

    if(argc < 3)
    {
        printUsage();
        exit(1);
    }
    
    for(int i = 1; i < argc; ++i)
    {
        if(strcmp(argv[i], "-c") == 0)
        {
            centered = true;
        }

        else if(strcmp(argv[i], "-v") == 0)
        {
            vertical = true;
        }

        else if(strcmp(argv[i], "-cv") == 0 || strcmp(argv[i], "-vc") == 0)
        {
            centered = true;
            vertical = true;
        }

        else if(hasTitle == false)
        {
            title = argv[i];
            hasTitle = true;
        }

        else if(hasDesc == false)
        {
            desc = argv[i];
            hasDesc = true;
        }

        else
        {
            choices[i - 3] = argv[i];
        }
    }

    //printf("%s %s %s %s", title, desc, choices[0], choices[1]);
    
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    printf("%d", menu(title, desc, choices, 3, true, true));

    endwin();

    return 0;
}
