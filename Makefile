# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 13:29:38 by mavellan          #+#    #+#              #
#    Updated: 2025/05/20 17:12:52 by ebalana-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR = \033[0;39m
YELLOW = \033[0;93m
CYAN = \033[0;96m
GREEN = \033[0;92m
BLUE = \033[0;94m
RED = \033[0;91m

NAME = minishell
CC = cc
FLAGS = -Werror -Wall -Wextra -g -fsanitize=address
LIBFTDIR = lib/
LIBFT_LIB = $(LIBFTDIR)/ultimate_libft.a
RM = rm -f
HEADER = include/minishell.h

SRCS = 	src/main.c \
		src/parser/tokenizer.c \
		src/parser/expand.c \
		src/parser/handle.c \
		src/built_ins/utils.c \
		src/built_ins/env_handler.c \
		src/built_ins/cd_handler.c \
		src/built_ins/export_handler.c \
		src/executor/executor.c \
		src/executor/utils.c \
		src/executor/child_process.c \
		src/executor/envp_handler.c \
		src/executor/command_path.c \

OBJS = $(SRCS:.c=.o)

all: make_libft $(NAME)

%.o: %.c Makefile pipex.h
	$(CC) $(FLAGS) -Ilib -c $< -o $@
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"

$(NAME): $(LIBFTDIR_LIB) $(OBJS)
	@echo "$(GREEN)Compiling minishell!$(DEF_COLOR)"
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) -lreadline
	@echo "$(GREEN)Minishell compiled!$(DEF_COLOR)"

make_libft:
	make -C $(LIBFTDIR)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJS)
	@echo "$(RED)Cleaned object files$(DEF_COLOR)"

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(NAME)
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re make_libft
