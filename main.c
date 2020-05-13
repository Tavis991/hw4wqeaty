#include <stdio.h>
#include <string.h>
#include "sort_league.h"
#include "League.h"
int main(int argc, char* argv[]) {
    if (argc != 2){printf("program requires two filename parameters; teams, matches");
    }

    League* liga = LeagueCreate("ligaA", argv[0], argv[1]);
    sort_league(liga);
    print_table(liga);
    LeagueDestroy(liga);

    return 0;
}
