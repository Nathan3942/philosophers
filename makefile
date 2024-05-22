# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 12:51:08 by nathan            #+#    #+#              #
#    Updated: 2024/02/15 15:58:51 by njeanbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

SRCS = $(wildcard src/*.c)

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lpthread

RM = rm -rf

#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

all: ${NAME}

${NAME}: ${OBJS}
	@printf "$(CURSIVE)$(GRAY)	- Compiling $(NAME)... $(RESET)\n"
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LDFLAGS}
	@printf "$(GREEN)	- Executable ready.\n$(RESET)"

clean:
	${RM} ${OBJS}
	@printf "$(YELLOW)	-Objects removed.$(RESET)\n"

fclean: clean
	${RM} ${NAME}
	@printf "$(YELLOW)	-Executable removed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re