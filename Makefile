##
## EPITECH PROJECT, 2018
## make
## File description:
## makefile
##

CC	=	gcc -g3

NAME	=	octocat

SRC	=	./src/main.c					\
		./src/str_to_word_array.c		\

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I./inc/ -Wall -Wextra

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		@rm -f $(OBJ)

fclean:		clean
		@rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
