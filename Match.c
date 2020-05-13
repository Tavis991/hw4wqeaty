#include "Match.h"
#include <stdlib.h>
#include <stdio.h>

Match* MatchCreate(Team* team1, Team* team2, int goals1, int goals2){
    Match* match_p = (Match*)malloc(sizeof(Match));
    if (!match_p){
        LOG_ERR(memory allocation failed )
        exit(1);
    }
    match_p->team1=team1;
    match_p->team2=team2;
    match_p->goals1=goals1;
    match_p->goals2=goals2;
    return match_p;
}
void MatchDestroy(Match* match_p){
    free(match_p);
}
bool team_participated(Team* team, Match* match){
    if (team->team_name == match->team1->team_name) {
        return true ;
    }
    else if (team->team_name == match->team2->team_name){
        return true;
    }
    return false;

}
bool match_tied(Team* team, Match* match){
    if (!team_participated(team, match)){
        LOG_ERR(illegal action team not participated in match)
        exit(1);
    }
    if (match->goals1==match->goals2){
        return true;
    }
    return false;
}
bool team_won(Team* team, Match* match){
    if (!team_participated(team, match)) {
        LOG_ERR(illegal action team not participated in match)
        exit(1);
    }
    if (team->team_name==match->team1->team_name){
        return (match->goals1>match->goals2);
    }
    return (match->goals1<match->goals2);

}
bool team_lost(Team* team, Match* match){
    if (!team_participated(team, match)) {
        LOG_ERR(illegal action team not participated in match)
        exit(1);
    }
    if (team->team_name==match->team1->team_name){
        return (match->goals1<match->goals2);
    }
    return (match->goals1>match->goals2);

}
int GF(Team* team, Match* match){
    if (!team_participated(team, match)){
        LOG_ERR(illegal action team not participated in match)
        exit(1);

    }
    if (team->team_name==match->team1->team_name){
        return (match->goals1);
    }
    return (match->goals2);

}
int GA(Team* team, Match* match){
    if (!team_participated(team, match)) {
        LOG_ERR(illegal action team not participated in match)
        exit(1);
    }
    if (team->team_name==match->team1->team_name){
        return (match->goals2);
    }
    return (match->goals1);
}