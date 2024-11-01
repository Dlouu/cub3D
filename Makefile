# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 14:57:46 by mbaumgar          #+#    #+#              #
#    Updated: 2024/10/22 21:01:10 by mbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

# ╔═╗╦  ╔═╗╔═╗╔═╗
# ╠╣ ║  ╠═╣║ ╦╚═╗
# ╚  ╩═╝╩ ╩╚═╝╚═╝

CC			= cc
ARFLAGS 	= -crs
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
DBG_LEAK	= -fsanitize=address -fsanitize=leak -g3
DBG_ADDRESS	= -fsanitize=address -g3
DBG_THREAD	= -fsanitize=thread -g3

LFT			= ./libft/libft.a
LIBS		= 
LIBFT		= ./libft
MAKE_LIBFT	= $(MAKE) --no-print-directory -C ${LIBFT}

# ╔═╗╔═╗╦  ╔═╗╦═╗╔═╗
# ║  ║ ║║  ║ ║╠╦╝╚═╗
# ╚═╝╚═╝╩═╝╚═╝╩╚═╚═╝
 
DUCK		= \033[38;2;8;195;187m
FLUO		= \033[38;2;223;255;0m
BLU			= \033[0;34m
RED			= \033[0;31m
END			= \033[m

# ╔═╗╔═╗╦ ╦╦═╗╔═╗╔═╗╔═╗
# ╚═╗║ ║║ ║╠╦╝║  ║╣ ╚═╗
# ╚═╝╚═╝╚═╝╩╚═╚═╝╚═╝╚═╝

OUT_DIR		= ./objects/

SRC			= ./src/cub3d.c

OBJ			= $(SRC:%.c=$(OUT_DIR)%.o)

# ╦═╗╦ ╦╦  ╔═╗╔═╗
# ╠╦╝║ ║║  ║╣ ╚═╗
# ╩╚═╚═╝╩═╝╚═╝╚═╝

all: $(NAME)

$(LFT): 
	@$(MAKE_LIBFT)

$(NAME): $(LFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFT) $(LIBS)

$(OUT_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I./inc -g3 -c $< -o $@ 

clean:
	@$(MAKE_LIBFT) clean
	$(RM) $(OUT_DIR)
	@echo "🧹 $(RED)removed:$(END) objects"

fclean: clean
	$(RM) $(NAME)
	@$(MAKE_LIBFT) fclean
	@echo "🧹 $(RED)removed:$(END) cub3D\n"

re: fclean all

uwu: re
	@${MAKE} --no-print-directory clean

norminette:
	@echo "\n"
	norminette libft/inc/*
	@echo "\n"
	norminette libft/src/*
	@echo "\n"
	norminette parsing/*
	@echo "\n"
	norminette utils/
	@echo "\n"
	norminette cub3d.c

leak: re
	$(CC) $(CFLAGS) $(DBG_LEAK) -o $(NAME) $(OBJ) $(LFT)

address: re
	$(CC) $(CFLAGS) $(DBG_ADDRESS) -o $(NAME) $(OBJ) $(LFT)

thread: re
	$(CC) $(CFLAGS) $(DBG_THREAD) -o $(NAME) $(OBJ) $(LFT)

main: fclean
	cd ..
	git add .
	git commit -m "$(m)"
	git push origin main

nils: fclean
	cd ..
	git add .
	git commit -m "Nils : $(m)"
	git push origin nils

dlou: fclean
	cd ..
	git add .
	git commit -m "Dlou : $(m)"
	git push origin dlou

.PHONY: all clean fclean re uwu norminette leak address thread main nils dlou
