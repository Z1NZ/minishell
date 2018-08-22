#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srabah <srabah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/04 01:35:37 by srabah            #+#    #+#              #
#    Updated: 2015/02/27 19:36:30 by srabah           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

DEBUG	= no
ifeq ($(DEBUG),no)
	FLAGS=-Wall -Wextra -Werror
else
	FLAGS= -g
endif
NAME	= ft_minishell1
LDFLAGS	= -I./includes/ -I./libft/includes
SRC		= ft_cd.c ft_env.c \
		ft_process.c\
		ft_sh_tools.c\
		main.c\
		sh_splite.c\
		suite_env.c
OBJ		= $(SRC:.c=.o)
SRCDIR	= ./srcs/
OBJDIR	= ./obj/
INCDIR	= ./includes/
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(OBJ))
INCS	= $(addprefix $(INCDIR), $(INC))

all: $(NAME)

.SILENT:

$(NAME): $(OBJS) $(INCS)
	gcc $(FLAGS) -o $@ $^ -L./libft/ -lft
	echo "\\033[1;32mSuccess.\\033[0;39m"

$(OBJS): $(SRCS)
ifeq ($(DEBUG),yes)
	echo "\\033[1;31mDEBUG COMPILATION.. (no flags except -g)\\033[0;39m"
else
	echo "\\033[1;31mCompilation with -Wall -Wextra -Werror...\\033[0;39m"
endif
	make -C libft/
	echo "\\033[1;34mGenerating objects... Please wait.\\033[0;39m"
	gcc $(FLAGS) -c $(SRCS) $(LDFLAGS)
	mkdir -p $(OBJDIR)
	mv $(OBJ) $(OBJDIR)

.PHONY: clean fclean re

clean:
	echo "\\033[1;34mDeleting objects...\\033[0;39m"
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft/
	echo "\\033[1;34mDeleting $(NAME)\\033[0;39m"
	rm -f $(NAME)

re: fclean all