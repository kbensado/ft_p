# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/21 02:48:50 by kbensado          #+#    #+#              #
#    Updated: 2017/12/02 16:18:36 by kbensado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			gcc

CFLAG =			-Wall -Wextra -Werror -g

NAME_N =		serveur
NAME_O =		client

SRC_PATH_N =	./src/serveur/
SRC_PATH_O =	./src/client/

OBJ_PATH_N =	./obj/serveur/
OBJ_PATH_O =	./obj/client/

LIBFT_PATH =	./libft/

INC_PATH_N =	./inc/serveur/
INC_PATH_O =	./inc/client/

SRC_NAME_N =	main.c serv.c cmd.c cmd_serv.c cmd_serv2.c macro.c macro2.c send_get.c
SRC_NAME_O =	main.c client.c cmd.c macro.c macro2.c cmd2.c cmd3.c

OBJ_NAME_N =	$(SRC_NAME_N:.c=.o)
OBJ_NAME_O =	$(SRC_NAME_O:.c=.o)

LIBFT_NAME =	libft.a

INC_NAME_N =	serveur.h
INC_NAME_O =	client.h

SRC_N =			$(addprefix $(SRC_PATH_N),$(SRC_NAME_N))
SRC_O =			$(addprefix $(SRC_PATH_O),$(SRC_NAME_O))

OBJ_N =			$(addprefix $(OBJ_PATH_N),$(OBJ_NAME_N))
OBJ_O =			$(addprefix $(OBJ_PATH_O),$(OBJ_NAME_O))


INC_N =			$(addprefix $(INC_PATH_N),$(INC_NAME_N))
INC_O =			$(addprefix $(INC_PATH_O),$(INC_NAME_O))

LIBFT =			$(addprefix $(LIBFT_PATH),$(LIBFT_NAME))
INCLIBFT = 		$(LIBFT_PATH)inc


LIBFT_FLAG = 	-L$(LIBFT_PATH) -lft

all:			libft $(NAME_N) $(NAME_O)
				

$(NAME_N):		$(OBJ_N)
				$(CC) $(LIBFT_FLAG) -o $@ $^ -fsanitize=address
				@echo "Done"

$(OBJ_PATH_N)%.o: 	$(SRC_PATH_N)%.c $(INC_N)
					mkdir -p $(OBJ_PATH_N)
					$(CC) $(CFLAG) -I$(INC_PATH_N) -I$(INCLIBFT) -o $@ -c $< 

$(NAME_O):		$(OBJ_O)
				$(CC) $(LIBFT_FLAG) -o $@ $^ -fsanitize=address
				@echo "Done"

$(OBJ_PATH_O)%.o: 	$(SRC_PATH_O)%.c $(INC_O)
					mkdir -p $(OBJ_PATH_O)
					$(CC) $(CFLAG) -I$(INC_PATH_O) -I$(INCLIBFT) -o $@ -c $< 

libft:			$(LIBFT)

$(LIBFT):		$(LIBFT_PATH)
				@make -C $(LIBFT_PATH)

clean:
				@make clean -C $(LIBFT_PATH)
				@rm -f $(OBJ_O)
				@rm -f $(OBJ_N)

fclean:			
				@rm -f $(OBJ_O)
				@rm -f $(OBJ_N)
				@make fclean -C $(LIBFT_PATH)
				@rm -f $(NAME_O)
				@rm -f $(NAME_N)

re: 			fclean all

.PHONY:			all libft clean fclean re
