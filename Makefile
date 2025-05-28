# Colors
DEF_COLOR = \033[0;39m
YELLOW = \033[0;93m
CYAN = \033[0;96m
GREEN = \033[0;92m
BLUE = \033[0;94m
RED = \033[0;91m

NAME = minishell
CC = cc
# FLAGS = -Werror -Wall -Wextra -g -fsanitize=address -Wno-deprecated-declarations
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
		src/executor/handlers.c \
		src/executor/redirections.c \
		src/signals.c \
		src/heredoc.c \

OBJS = $(SRCS:.c=.o)

# UNAME_S := $(shell uname -s)
# ifeq ($(UNAME_S),Darwin)
# 	READLINE_INCLUDE = -I$(shell brew --prefix readline)/include
# 	READLINE_LIB = -L$(shell brew --prefix readline)/lib
# else
# 	READLINE_INCLUDE =
# 	READLINE_LIB =
# endif

all: make_libft $(NAME)

%.o: %.c Makefile $(HEADER)
	$(CC) $(FLAGS) $(READLINE_INCLUDE) -Ilib -c $< -o $@
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"

$(NAME): $(LIBFT_LIB) $(OBJS)
	@echo "$(GREEN)Compiling minishell!$(DEF_COLOR)"
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) $(READLINE_LIB) -lreadline -o $(NAME)
	@echo "$(GREEN)Minishell compiled!$(DEF_COLOR)"

make_libft:
	@make -C $(LIBFTDIR)

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
