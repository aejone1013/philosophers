# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 11:13:03 by jaoh              #+#    #+#              #
#    Updated: 2025/03/01 11:46:56 by jaoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL=  /bin/bash

FBlack			=   $(shell echo -e "\033[1;30m")
Black			=   $(shell echo -e "\033[0;30m")
FRed			=   $(shell echo -e "\033[1;31m")
Red				=   $(shell echo -e "\033[0;31m")
FGreen          =   $(shell echo -e "\033[1;32m")
Green           =   $(shell echo -e "\033[0;32m")
FBrown		    =   $(shell echo -e "\033[1;33m")
Brown           =   $(shell echo -e "\033[0;33m")
FYellow         =   $(shell echo -e "\033[1;33m")
Yellow          =   $(shell echo -e "\033[0;33m")
FBlue           =   $(shell echo -e "\033[1;34m")
Blue            =   $(shell echo -e "\033[0;34m")
FPurple         =   $(shell echo -e "\033[1;35m")
Purple          =   $(shell echo -e "\033[0;35m")
FCyan           =   $(shell echo -e "\033[1;36m")
Cyan            =   $(shell echo -e "\033[0;36m")
FWhite          =   $(shell echo -e "\033[1;37m")
White           =   $(shell echo -e "\033[0;37m")
RESET           =   $(shell echo -e "\033[0m")

NAME = philo

CC				= gcc

INCLUDES_DIR 	= includes

CFLAGS		 	= -Wall -Werror -Wextra -I${INCLUDES_DIR} # -pthread -fsanitize=thread -g

SRC_FILE 		= main \
				utils \
				init \
				philos \
				start \
				actions \
				log \
				forks

SRCS 			= $(addprefix srcs/, $(addsuffix .c, $(SRC_FILE)))

OBJS 			= ${SRCS:.c=.o}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo -e "${FBlue}${NAME}${Blue} compiled\n${RESET}"

all: ${NAME}

clean:
	rm -f ${OBJS}
	@echo -e "$(FPurple).o files $(Purple)cleaned\n${RESET}"


fclean: clean
	rm -f ${NAME}
	@echo -e "$(FRed)${NAME}$(Red) cleaned${RESET}\n"
	
re : fclean all

.PHONY: all clean fclean re
