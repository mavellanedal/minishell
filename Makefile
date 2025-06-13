# Colors
DEF_COLOR = \033[0;39m
YELLOW = \033[0;93m
CYAN = \033[0;96m
GREEN = \033[0;92m
BLUE = \033[0;94m
RED = \033[0;91m

NAME = minishell
CC = cc
MAC_FLAGS = -Werror -Wall -Wextra -g -fsanitize=address -Wno-deprecated-declarations
FLAGS = -Werror -Wall -Wextra -g -fsanitize=address
CFLAGS = $(FLAGS)

LIBFTDIR = lib
LIBFT_LIB = $(LIBFTDIR)/ultimate_libft.a
RM = rm -f
HEADER = include/minishell.h

SRCS = 	src/main.c \
		src/parser/check_pipes_redirecctions.c \
		src/parser/handle_expand_heredoc.c \
		src/parser/process_expand.c \
		src/parser/read_token.c \
		src/parser/tokenizer.c \
		src/parser/utils.c \
		src/built_ins/utils.c \
		src/built_ins/env_handler.c \
		src/built_ins/cd_handler.c \
		src/built_ins/export_handler.c \
		src/built_ins/envp_handler.c \
		src/built_ins/export_utils.c \
		src/built_ins/export_main_function_utils.c \
		src/executor/child_process.c \
		src/executor/command_path.c \
		src/executor/envp_handler.c \
		src/executor/executor.c \
		src/executor/free.c \
		src/executor/handle_child_process.c \
		src/executor/handlers.c \
		src/executor/pipeline.c \
		src/executor/redirections.c \
		src/executor/tokens_to_cmd.c \
		src/executor/utils.c \
		src/heredoc/clean.c \
		src/heredoc/heredoc.c \
		src/heredoc/utils.c \
		src/shlvl.c \
		src/free_env.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) $(READLINE_INCLUDE) -Ilib -c $< -o $@
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"

$(LIBFT_LIB):
	@make -C $(LIBFTDIR)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@echo "$(GREEN)Compiling minishell!$(DEF_COLOR)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(READLINE_LIB) -lreadline -o $(NAME)
	@echo "$(GREEN)Minishell compiled!$(DEF_COLOR)"

mac:
	@UNAME_S=$$(uname -s); \
	if [ $$UNAME_S = "Darwin" ]; then \
		READLINE_INCLUDE="-I$$(brew --prefix readline)/include"; \
		READLINE_LIB="-L$$(brew --prefix readline)/lib"; \
	else \
		READLINE_INCLUDE=""; \
		READLINE_LIB=""; \
	fi; \
	$(MAKE) CFLAGS="$(MAC_FLAGS)" READLINE_INCLUDE="$$READLINE_INCLUDE" READLINE_LIB="$$READLINE_LIB"

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJS)
	@echo "$(RED)Cleaned object files$(DEF_COLOR)"

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(NAME)
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re mac
