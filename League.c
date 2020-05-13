#include <stdio.h>
#include "League.h"
#include "sort_league.h"
#include <stdlib.h>
#include <string.h>
// Created by tuli on 01/05/2020.
//

//create league object given two files, teams and matches
League* LeagueCreate(char* league_name, char* teamfile, char* matchfile){
    char* name;

    League* league_p = (League*)malloc(sizeof(League));
    if (!league_p){
        LOG_ERR(memory allocation failed )
        exit(1);
    }
    league_p->name= league_name;
    read_teams(teamfile, league_p);
    read_matches(matchfile, league_p);
    return league_p;
}

//free allocated memory for league object and all sub allocated memory
void  LeagueDestroy(League* league){
    int i;
    for (i=0; i<league->num_teams; i++){
        TeamDestroy(league->teams[i]);
    }
    for (i=0; i<league->num_matches; i++){
        MatchDestroy(league->matches[i]);
    }
    free(league);
}

//function reads teams from file, we assume known input configuration, delimiter = \n
//46 using getline to read from file, reallicating memory for each team line by line
void read_teams(char* filename, League* league) {

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        LOG_ERR(FILE NOT FOUND)
        exit(1);
    }
    char *buf = NULL;
    size_t buf_size = 0;

    league->teams = NULL;
    league->num_teams = 0;

    while (getline(&buf, &buf_size, fp) != EOF) {
        buf[strchr(buf, '\n') - buf] = '\0';
        league->teams = ((Team **) realloc(league->teams, sizeof(Team) * (league->num_teams + 1)));
        if(!league->teams){
            LOG_ERR(MEMORY ALLOCATION FAILED )
            exit(1);
        }
        league->teams[league->num_teams] = TeamCreate(buf);
        league->num_teams++;


    }
    free(buf);
    fclose(fp);
}
//function reads matches from  file, we assume a known input configuration, delimiter = tab
//83 using getline to read from file, reallicating memory for each match line by line
//90 parsing line and updating league matches respectibly
void read_matches(char *filename, League *league) {
    char* team1;
    char* team2;
    int goals1;
    int goals2;
    const char* s = "\t";

    FILE *fp =  fopen(filename, "r");
    if (!fp) {
        LOG_ERR(FILE NOT FOUND)
        exit(1);
    }
    char *buf = NULL;
    size_t buf_size = 0;

    league->matches = NULL;
    league->num_matches = 0;

    while (getline(&buf, &buf_size, fp) != EOF) {
        buf[strchr(buf, '\n') - buf] = '\0';
        league->matches = ((Match **) realloc(league->matches, sizeof(Match) * (league->num_matches + 1)));
        if(!league->matches){
            LOG_ERR(MEMORY ALLOCATION FAILED )
            exit(1);
        }
        team1=strtok(buf, s);
        team2=strtok(NULL, s);
        goals1 = atoi(strtok(NULL,s));
        goals2 = atoi(strtok(NULL, s));
        league->matches[league->num_matches] = MatchCreate(find_team(team1,league), find_team(team2,league), goals1, goals2);
        league->num_matches++;

    }
    free(buf);
    fclose(fp);

}
//function compares given string to all team names in league and returns the respective team object
Team* find_team(char* team, League* league){
    int i;
        for (i=0; i<league->num_teams; i++){
            if (!strcmp((team),league->teams[i]->team_name)){
                return league->teams[i];
            }

        }
    LOG_ERR(TEAM DOES NOT EXIST)
    exit(1);
}
int num_wins(League* league, Team* team){
    int wins = 0;
    int i;
    for (i=0; i< league->num_matches; i++){
        if (team_participated(team,league->matches[i])){
            if (team_won(team,league->matches[i])){
            wins++;
            }
        }
    }
    return wins;

}
int num_draws(League* league, Team* team) {
    int draws = 0;
    int i;
    for (i=0; i< league->num_matches; i++){
        if (team_participated(team,league->matches[i])){
        if (match_tied(team,league->matches[i])) {
            draws++;
            }
        }
    }
    return draws;


}
int num_losses(League* league, Team* team) {
    int losses = 0;
    int i;
    for (i=0; i< league->num_matches; i++){
        if (team_participated(team,league->matches[i])){
            if (team_won(team,league->matches[i])) {
                losses++;
            }
        }
    }
    return losses;

}
int num_GF(League* league, Team* team) {
    int GF = 0;
    int i;
    for (i=0; i< league->num_matches; i++){
        if (team_participated(team,league->matches[i])){
            if (league->matches[i]->team1==team) {
                GF+=league->matches[i]->goals1;

            }
            else{GF+=league->matches[i]->goals2;
            }
        }
    }
    return GF;

}
int num_GA(League* league, Team* team) {
    int GF = 0;
    int i;
    for (i=0; i< league->num_matches; i++){
        if (team_participated(team,league->matches[i])){
            if (league->matches[i]->team1==team) {
                GF+=league->matches[i]->goals2;

            }
            else{GF+=league->matches[i]->goals1;
            }
        }
    }
    return GF;

}

int num_games(League* league, Team* team) {
    int games = 0;
    int i;
    for (i=0; i< league->num_matches; i++){
        if (team_participated(team,league->matches[i])){
           games++;
        }
    }
    return games;

}

int num_points(League* league, Team* team){
    int points=0;
    int i;
    for (i=0; i< league->num_matches; i++){
        if (team_participated(team,league->matches[i])){
            if (team_won(team,league->matches[i])) {
                points+=PTS_FOR_WIN;

            }
            else if (match_tied(team,league->matches[i])){
                points+=PTS_FOR_DRAW;
            }
        }
    }
    return points;

}
        void print_table(League* liga){
    int i;
    printf("%s", liga->name);
    printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t \n", "Teams", "Games", "Wins", "Ties", "Losses", "GF", "GA", "Points");
    for (i=0; i<liga->num_teams;i++){
        printf("%-10s\t%-10d\t%-10d\t%-10d\t%-10d\t%-10d\t%-10d\t%-10d\t \n", liga->teams[i]->team_name, num_games(liga,liga->teams[i]), num_wins(liga,liga->teams[i]), num_draws(liga,liga->teams[i]), num_losses(liga,liga->teams[i]), num_GF(liga,liga->teams[i]), num_GA(liga,liga->teams[i]), num_points(liga,liga->teams[i]));
    }



}