#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h> // usleep
#include <string.h> // strlen
#include <signal.h>

#define CHAD_FRAMES 7
#define CHAD_ROWS   24

#define TRUE 1
#define FALSE 0

#define DEFAULT_SIZE 1

int STAY = FALSE, LOOP = FALSE, SIZE = DEFAULT_SIZE, NOFUCKS = FALSE;
long SLEEP_TIMER = 150000;

/* Chad frames */

const char* chad_frames[CHAD_FRAMES][CHAD_ROWS] = {
    {
        "                          %",
        "                     .(....",
        "                  %......(",
        "              ,*........&",
        "           .#,.,,,,. .(",
        "         *.,.*,,,,&@/,%",
        "        /,,,,,,,,,,,,,,*",
        "        &,,((%.,,,,,,.#(*",
        "        &.,@.%,,,,,.(.*",
        "        .,..,.#*,,,,./.",
        "       /,,.@@/* ..,,,,/",
        "      @@@**@@@@@",
        "     @@@*@@...@@@",
        "   @@.@@***@@@......@@@",
        " @@...@@*********@@@...@@",
        " @@...@@@********@@ @@@",
        "@....@@@***@@@**@",
        " @@@@ @@******@@@",
        "     @******@@***@@",
        "     @...@@@  @@....@@*@@",
        " @@@@...@       @..@***@@",
        "@**@@@           @@***@",
        "@**@@              @@@",
        "@****@",
    },
    {
        "                         & /",
        "                     & ...%",
        "                 % ......%",
        "              (.........%",
        "           @.,,,,.%@@&",
        "         @,,,@.,,@(/@.&",
        "        /,,,..,,,,,,,,,.@",
        "        &,,*..*.,,,,.((.",
        "        &*, ,&,,,,,*@%@",
        "       ..,..,,./,,,,,.@",
        "       %,,,..*%@&#.,.*,",
        "      @@*****@@@",
        "     @********@@@",
        "     @*******@...@@",
        "   @@@********@@...@",
        "   @@.@@@*******@...@@",
        "     @@@*@@@@@**@.....@@",
        "     @********@@   @@@",
        "@@@  @@@***@@*@@@",
        "@@*@@.@@@@@@@@..@",
        "@@***@...@@@@...@",
        "@@*@@ @@@  @@.@@",
        "@@@      @@*****@",
        "         @@,,,,,,@@"
    },
    {
        "                       %...",
        "                   #...../",
        "               /........@",
        "            /,%######&%@",
        "          .,#,,,...(@%",
        "        %,,,,,,,,..,,,.",
        "        ,,,&./,,,,,,.#,,&",
        "        *,#*%%,,,,,,.#&",
        "       ...*../,,,,,.%@",
        "       %,,@,,,,,,,,,,,..",
        "     @@.,,,,,,,@ @&%",
        "  @*************@...@@",
        "  @@@@**********@@@.@@",
        "  @...@@******@@",
        "  @...@@******@@",
        "  @...@@******@@",
        "@@...@*****@@*@@",
        "@@...@**@****@@@",
        "  @@@@@@******@@",
        "   @@....@@@@@",
        "  @**@..@@@",
        "   @@***@",
        "   @@****@@",
        "     @*****@@"
    },
    {
        "                         (../",
        "                     /.....@",
        "                 %........(",
        "              //%#####%&/(",
        "           ,.,/,,,,..#%&",
        "          &,,,,.,,.,..,,,",
        "          .,.(,.,,,,,,.#.,#",
        "          .,@/*@,,,,,,,#(",
        "         #.,&,(,,,,,,,#@",
        "         .,,%,,,,,,,,,,,,",
        "      @@@,,,,,,,.@@ %,",
        "   @@.@@*********@@.@@",
        " @@.....@********@@.@@",
        "@.....@@@********@@...@",
        " @@...@@********@  @...@@",
        " @@.....@*******@  @...@@",
        "   @@....@@***@@",
        "     @@@@***@@@@",
        "      @@****@@@@",
        "     @..@@@@.....@@@***@@",
        "     @...@@@@@...@@***@",
        "   @@...@       @**@",
        " @@**@@@         @@",
        "   @@****@@"
    },
    {
        "                           /*%",
        "                       &....*",
        "                   (.......",
        "                %.........",
        "             /(.,,,,.../",
        "           ,,,@,,,.%@#@#",
        "          ,,,,,,,,,,,,,,.#",
        "          ,,(@(,.,,,,,%(/%",
        "          #,%#..,,,,,%.*&",
        "         %,,&,,*&,,,,,./",
        "        %.,,*@#/....,,,.#",
        "   @@.@@*@@@@@@@@",
        " @@.....@********@@",
        "@.....@@*********@@@",
        "@....@**********@...@@",
        " @@...@@********@@@.@@",
        " @@.....@@@***@@ @@.@@",
        "   @@@@@***@@@@@@...@@",
        "     @*****@**@@ @@@",
        "     @@@***@@@",
        "   @@.@@@@@.@@",
        " @@...@@ @@...@@",
        "@**@@@     @....@@@@",
        "@****@      @@*****@"
    },
    {
        "                       %..&",
        "                   %.....(",
        "               ,,........",
        "            #..**,/*, .",
        "         *.,,,,,%#/(,",
        "        *,,, .,,&@#.,,*",
        "       #,,.%#,,,,,,,,/,(",
        "       @,..%.&,,,,,,..",
        "       (@,%,#,,,,,/,.@",
        "      ,,,,.,,,.,,,,,,.#",
        "     @@,,,,,,.,  &,#*",
        "    @..@**@@@@@",
        "  @@...@*******@",
        "@@.....@*******@",
        "  @@....@@@****@",
        "     @@....@@@@@",
        "     @@@@@@****@",
        "     @@******@@.@@",
        "     @@***@@@@@.@@",
        "    @**@@@...@@@",
        "     @@@...@@",
        "       @...@@",
        "       @*****@@",
        "        @@@@@"
    },
    {
        "                     &..&",
        "                 (...../",
        "             /.........",
        "          (.*(((##/,.",
        "       ( ,,,,,&**(",
        "      ,,,, .,,#&/.,,(",
        "     #,, @&,,,,,,,,#,/",
        "     @,..&.%,,,,,,.*",
        "     /&,&,#,,,,,*..&",
        "    ,,,,.,,,.,,,,,,.%",
        "    &,,,,,,.,  &/&.",
        "  @@@*@@...@@*@@...@",
        "  @**@.....@@@.....@",
        "  @***@@........@@@",
        "@@.@@****@@@@@",
        "  @@@********@",
        "  @********@@",
        "  @**********@",
        "  @***@@***@@@",
        "  @...@@@....@",
        "  @...@@*@@@@",
        "@@...@  @****@",
        "@@@@@@  @****@",
        "@@******@"
    }
};

void usage(const int exit_code) {
    printf("./chad_stride -[flags]\n"
            "-s: Chad stays still and doesn't move forever\n"
            "-l: Chad walks infinitely\n"
            "-b SIZE: Big Chad (each b increases chad)\n"
            "-f: Chad gives no fucks (ignores signals)\n"
            "-a SLEEP_TIME: Adjust sleep timer for chad\n"
            "-h: This message\n");
    exit(exit_code);
}

int main(int argc, char *argv[]) {
    char c;

    /* Handle Arguments */
    while ((c = getopt (argc, argv, "slfhb:a:")) != -1) {
        switch (c) {
            case 's':
                STAY = TRUE;
                break;
            case 'l':
                LOOP = TRUE;
                break;
            case 'b': {
                char* p_end;
                long modifier = strtol(optarg, &p_end, 10);
                if (p_end == optarg) {
                    fprintf(stderr, "Invalid digits for flag -b\n");
                    usage(1);
                }
                if (modifier < 0) {
                    fprintf(stderr, "Error: invalid argument for b flag. Must be positive!\n");
                } 
                SIZE += modifier; 
                break;
            }
            case 'f':
                NOFUCKS = TRUE;
                break;
            case 'a': {
                char* p_end;
                long modifier = strtol(optarg, &p_end, 10);
                if (p_end == optarg) {
                    fprintf(stderr, "Invalid digits for flag -b\n");
                    usage(1);
                }
                if (modifier < 0) {
                    fprintf(stderr, "Error: Access isn't positive!\n");
                }
                SLEEP_TIMER = modifier; 
                break;
            }
            case 'h':
                usage(0);
            default:
                usage(1);
        }
    }

    if (NOFUCKS) {
        signal(SIGHUP , SIG_IGN);
        signal(SIGINT , SIG_IGN);
        signal(SIGPIPE, SIG_IGN);
        signal(SIGTERM, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
    }

    /* ncurses stuff */
    int col, row;
    int x_pos = 0, i = 0;
    initscr();
    getmaxyx(stdscr, row, col); // stdscr is default screen
    noecho();
    curs_set(0);
    nodelay(stdscr, 1);
    leaveok(stdscr, 1);
    scrollok(stdscr, 0);

    /* loop until done */
    while(x_pos < col || LOOP) {
        clear();

        // check for wrap on loop
        if (x_pos >= col) x_pos = 0;

        for (int j = 0; j < CHAD_ROWS; j++) {
            // find position of furthest character to the right
            int right_pos = x_pos + strlen(chad_frames[i % CHAD_FRAMES][j]);
            // draw row, checking it doesn't go off screen if not looping
            mvaddnstr(j * SIZE, x_pos, chad_frames[i % CHAD_FRAMES][j],
                    (right_pos > col && !LOOP) ? col - x_pos : right_pos);
        }

        i++; // increment animation counter
        if (!STAY) x_pos++; // move across screen

        /* Ncurses stuff */
        getch();
        refresh();

        /* animation wait */
        usleep(SLEEP_TIMER);
    }

    /* Clean up */
    delwin(stdscr);
    endwin();
    refresh();

    return 0;
}
