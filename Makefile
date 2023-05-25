##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## makefile
##

SRC	=	src/main.cpp


CFLAGS	=	-Wall -Werror -Wextra -g -I./include
CFLAGS +=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

NAME 	=	snake

all:	$(NAME)

$(NAME):
	g++ -o $(NAME) $(CFLAGS) $(SRC)

clean:
	@rm -rf *.o

fclean:	clean
	@rm -rf $(NAME)
	@echo Clean done

re:	fclean all

.PHONY:	re clean fclean all
