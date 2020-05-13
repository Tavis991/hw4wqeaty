//
// Created by tuli on 01/05/2020.
//

#ifndef HW4_TEAM_H
#define HW4_TEAM_H
#define LOG_ERR(messege)  fprintf(stderr, "Big Error probelm help in file %s \n line %d",__FILE__, __LINE__);
typedef struct Team {
    char* team_name;
} Team;
Team* TeamCreate(char* team_name);
void  TeamDestroy(Team* team_p);

#endif //HW4_TEAM_H
