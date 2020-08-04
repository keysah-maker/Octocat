/*
** EPITECH PROJECT, 2019
** str_to_word_array.c
** File description:
** str_to_word_array.c
*/

#include "octocat.h"

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    if (s1[i] > s2[i])
        return (1);
    if (s1[i] < s2[i])
        return (1);
    return (0);
}

int my_strlen(char *str)
{
    int i = 0;

    for (; str[i]; i++);
    return i;
}

char **str_to_word_array(char *str)
{
    char **array = 0;
    int j = 0;
    int k = 0;

    array = malloc(sizeof(char *) * my_strlen(str));
    for (int i = 0; i < my_strlen(str); i++)
        array[i] = malloc(sizeof(char) * my_strlen(str));
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            array[j][k] = '\0';
            j++;
            k = 0;
        }
        if (str[i] != ':' && str[i] != '\n') {
            array[j][k] = str[i];
            k++;
        }
    }
    array[j] = NULL;
    return (array);
}
