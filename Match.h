//
// Created by tuli on 01/05/2020.
//

#ifndef HW4_MATCH_H
#define HW4_MATCH_H
#include "Team.h"
#include <stdbool.h>
#define LOG_ERR(messege)  fprintf(stderr, "Big Error probelm help in file %s \n line %d",__FILE__, __LINE__);


typedef struct Match{
    Team* team1;
    Team* team2;
    int goals1;
    int goals2;
} Match;
Match* MatchCreate(Team* team1, Team* team2, int goals1, int goals2);
void MatchDestroy(Match* match_p);
bool team_participated(Team* team, Match* match);
bool match_tied(Team* team, Match* match);
bool team_won(Team* team, Match* match);
bool team_lost(Team* team, Match* match);
int GF(Team* team, Match* match);
int GA(Team* team, Match* match);

#endif //HW4_MATCH_H
