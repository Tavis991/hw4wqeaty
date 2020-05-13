#include <stdio.h>
#include "Team.h"
#include <stdlib.h>
#include <string.h>
// Created by tuli on 01/05/2020.
//

Team* TeamCreate(char* team_name){


    Team* team_p = (Team*)malloc(sizeof(Team));
    if (!team_p){
        LOG_ERR(memory allocation failed )
        exit(1);
    }
    team_p->team_name=strdup(team_name);
    return team_p;
}
void  TeamDestroy(Team* team_p){
    free(team_p);
}