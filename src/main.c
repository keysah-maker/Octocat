/*
** EPITECH PROJECT, 2020
** Octocat
** File description:
** main
*/

#include "octocat.h"

void getPlayerPos(octocat_t *this)
{
    for (int i = 0; this->map[i]; i++) {
        for (int j = 0; this->map[i][j]; j++) {
            if (this->map[i][j] == 'P') {
                this->playerPosX = i;
                this->playerPosY = j;
            }
        }
    }
}

int movePlayer(char c, octocat_t *this)
{
    getPlayerPos(this);
    if (c == 'z' || c == 'Z') {
        if (this->playerPosX - 1 != -1 && this->map[this->playerPosX - 1][this->playerPosY] != '#') {
            if (this->map[this->playerPosX - 1][this->playerPosY] == 'X')
                this->isEnd = true;
            this->map[this->playerPosX - 1][this->playerPosY] = 'P';
            this->map[this->playerPosX][this->playerPosY] = ' ';
        } else if (this->playerPosX - 1 != -1 && this->map[this->playerPosX - 1][this->playerPosY] == '#')
            this->isCaught = true;
    }
    if (c == 's' || c == 'S') {
        if (this->playerPosX + 1 != this->mapSize && this->map[this->playerPosX + 1][this->playerPosY] != '#') {
            if (this->map[this->playerPosX + 1][this->playerPosY] == 'X')
                this->isEnd = true;
            this->map[this->playerPosX + 1][this->playerPosY] = 'P';
            this->map[this->playerPosX][this->playerPosY] = ' ';
        } else if (this->playerPosX + 1 != this->mapSize && this->map[this->playerPosX + 1][this->playerPosY] == '#')
            this->isCaught = true;
    }
    if (c == 'd' || c == 'D') {
        if (this->playerPosY + 1 != my_strlen(this->map[this->playerPosX]) && this->map[this->playerPosX][this->playerPosY + 1] != '#') {
            if (this->map[this->playerPosX][this->playerPosY + 1] == 'X')
                this->isEnd = true;
            this->map[this->playerPosX][this->playerPosY + 1] = 'P';
            this->map[this->playerPosX][this->playerPosY] = ' ';
        } else if (this->playerPosY + 1 != my_strlen(this->map[this->playerPosX]) && this->map[this->playerPosX][this->playerPosY + 1] == '#')
            this->isCaught = true;
    }
    if (c == 'q' || c == 'Q') {
        if (this->playerPosY - 1 != -1 && this->map[this->playerPosX][this->playerPosY - 1] != '#') {
            if (this->map[this->playerPosX][this->playerPosY - 1] == 'X')
                this->isEnd = true;
            this->map[this->playerPosX][this->playerPosY - 1] = 'P';
            this->map[this->playerPosX][this->playerPosY] = ' ';
        } else if (this->playerPosY - 1 != -1 && this->map[this->playerPosX][this->playerPosY - 1] == '#')
            this->isCaught = true;
    }
    return 0;
}

char askUserInput()
{
    int c = 0;
    int j = 0;

    write(1, "Input: ", 7);
    c = getchar();
    j = getchar();
    write(1, "\n\n", 2);
    return c;
}

int check_if_valid_map(char *map)
{
    int octocat = 0;
    int exit = 0;

    for (int i = 0; map[i]; i++) {
        if (map[i] == 'P')
            octocat++;
        if (map[i] == 'X')
            exit++;
    }
    if (exit == 0 || octocat != 1)
        return 1;
    return 0;
}

void display(octocat_t *this)
{
    for (int i = 0; this->map[i]; i++) {
        write(1, this->map[i], my_strlen(this->map[i]));
        write(1, "\n", 1);
    }
}

int read_map(char *notOpennedFile, octocat_t *this)
{
    int opennedFile = open(notOpennedFile, O_RDONLY);
    char *buffer = NULL;
    struct stat sb;

    if (stat(notOpennedFile, &sb) == -1) {
        write(1, "Error: stat failed!\n", 20);
        return 1;
    }
    if ((buffer = malloc(sizeof(char) * (sb.st_size + 1))) == NULL) {
        write(1, "Error: malloc failed!\n", 22);
        return 1;
    }
    if (read(opennedFile, buffer, sb.st_size) == -1) {
        write(1, "Error: read failed!\n", 20);
        return 1;
    }
    buffer[sb.st_size] = '\0';
    if (check_if_valid_map(buffer) == 1) {
        free(buffer);
        write(1, "Error: Invalid map!\n", 19);
        return 2;
    }
    this->map = str_to_word_array(buffer);
    free(buffer);
    for (; this->map[this->mapSize]; this->mapSize++);
    return 0;
}

void loop(octocat_t *this)
{
    char c;

    while (1) {
        display(this);
        if (this->isEnd == true) {
            write(1, "You won.\n", 9);
            break;
        }
        c = askUserInput();
        movePlayer(c, this);
    }
}

void init_struct(octocat_t *this)
{
    this->map = NULL;
    this->playerPosX = 0;
    this->playerPosY = 0;
    this->mapSize = 0;
    this->isEnd = false;
    this->isHardcore = false;
    this->isCaught = false;
}

void doHardcore(octocat_t *this)
{
    char c;

    display(this);
    write(1, "Input: ", 7);
    while ((c = getchar()) != '\n' && this->isCaught == false)
        movePlayer(c, this);
    if (this->isEnd == true)
        write(1, "\nYOU DID IT!! YOU'RE OUT \\o/\n", 28);
    else if (this->isEnd == false && this->isCaught == false)
        write(1, "\nYou got lost and you were eaten by Grievers\n", 45);
}

int main(int ac, char **av)
{
    octocat_t this;
    int ret = 0;

    init_struct(&this);
    if (ac != 2 && ac != 3)
        return 84;
    if ((ret = read_map(av[1], &this)) == 1)
        return 84;
    else if (ret == 2)
        return 1;
    if (ac == 3 && my_strcmp(av[2], "--hardcore") == 0) {
        doHardcore(&this);
        return 0;
    }
    loop(&this);
    return 0;
}