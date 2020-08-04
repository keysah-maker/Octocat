/*
** EPITECH PROJECT, 2020
** Octocat
** File description:
** octocat
*/

#ifndef OCTOCAT_H_
#define OCTOCAT_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct octocat_s {
    char **map;
    int playerPosX;
    int playerPosY;
    int mapSize;
    bool isEnd;
    bool isHardcore;
    bool isCaught;
} octocat_t;

char **str_to_word_array(char *str);
int my_strlen(char *str);
int my_strcmp(char *s1, char *s2);

#endif /* !OCTOCAT_H_ */