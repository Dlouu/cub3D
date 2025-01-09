# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 14:57:46 by mbaumgar          #+#    #+#              #
#    Updated: 2025/01/09 13:22:20 by mbaumgar         ###   ########.fr        #
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
LFT			= ./lib/libft.a
LMLX		= ./lib/libmlx42.a
LIBFT		= ./lib/libft
LIBMLX		= ./lib/MLX42
MAKE_LIBFT	= ${MAKE} --no-print-directory -C ${LIBFT}
MAKE_LIBMLX	= @cmake $(LIBMLX) -B $(LIBMLX)/build && make -s -C $(LIBMLX)/build -j4

ifeq ($(shell uname), Linux)
CFLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I ./includes -I $(LIBMLX)/include
LIBS		= ${LFT} ${LMLX} -ldl -lglfw -pthread -lm
else
CFLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I ./includes -I/opt/X11/include -Imlx
LIBS		= ./lib/libft.a ./lib/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
endif

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

SRC_DIR		= ./src/
OUT_DIR		= ./objects/

SRC			= cub3d.c parsing.c start_game.c

OBJ			= $(SRC:%.c=$(OUT_DIR)%.o)

# ╦═╗╦ ╦╦  ╔═╗╔═╗
# ╠╦╝║ ║║  ║╣ ╚═╗
# ╩╚═╚═╝╩═╝╚═╝╚═╝

all: $(NAME)

$(LFT): 
	@$(MAKE_LIBFT)

$(LMLX):
	@$(MAKE_LIBMLX) --no-print-directory
	@mv $(LIBMLX)/build/libmlx42.a ./lib/

$(NAME): $(LFT) $(LMLX) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS) $(INCLUDES)

$(OUT_DIR)%.o: ${SRC_DIR}%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I./inc -g3 -c $< -o $@ 

clean:
	@$(MAKE_LIBFT) clean
	@$(RM) $(OUT_DIR)
	@echo "🧹 $(RED)removed:$(END) objects"
	@$(RM) $(LIBMLX)/build/

fclean: clean
	$(RM) $(NAME)
	@$(MAKE_LIBFT) fclean
	$(RM) $(LMLX)
	@echo "🧹 $(RED)removed:$(END) cub3D\n"

re: fclean all

uwu: re
	@${MAKE} --no-print-directory clean

norminette:
	@echo "\n"
	norminette lib/libft/inc/*
	@echo "\n"
	norminette lib/libft/src/*
	@echo "\n"
	norminette src/*

leak: re
	$(CC) $(CFLAGS) $(DBG_LEAK) -o $(NAME) $(OBJ) $(LIBS) $(INCLUDES)

address: re
	$(CC) $(CFLAGS) $(DBG_ADDRESS) -o $(NAME) $(OBJ) $(LIBS) $(INCLUDES)

thread: re
	$(CC) $(CFLAGS) $(DBG_THREAD) -o $(NAME) $(OBJ) $(LIBS) $(INCLUDES)

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
