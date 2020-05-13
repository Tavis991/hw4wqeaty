//
// Created by tuli on 02/05/2020.
//

#ifndef HW4_LEAGUE_H
#define HW4_LEAGUE_H

#include "Team.h"
#include "Match.h"

typedef struct League{
    char* name;
    int num_teams;
    int num_matches;
    Team** teams;
    Match** matches;

}League;
League* LeagueCreate (char* league_name, char* teamfile, char* matchfile);
void LeagueDestroy(League* league);
void read_teams(char* filename, League* league);
void read_matches(char* filename, League* league);
int num_wins(League* league, Team* team);
int num_draws(League* league, Team* team);
int num_losses(League* league, Team* team);
int num_GF(League* league, Team* team);
int num_GA(League* league, Team* team);
int num_games(League* league, Team* team);
void print_table(League* liga);
int num_points(League* league, Team* team);
Team* find_team(char* team, League* league);
#endif //HW4_LEAGUE_H
