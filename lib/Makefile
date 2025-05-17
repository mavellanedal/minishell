# Source files
SRCS_LIBFT = libft/ft_isalpha.c \
			 libft/ft_arrlen.c \
			 libft/ft_isdigit.c \
			 libft/ft_isdigit_str.c \
			 libft/ft_is_echo_n_flag.c \
			 libft/ft_is_numeric.c \
			 libft/ft_is_too_long_numeric.c \
			 libft/ft_isalnum.c \
			 libft/ft_isprint.c \
			 libft/ft_isascii.c \
			 libft/ft_strlen.c \
			 libft/ft_toupper.c \
			 libft/ft_tolower.c \
			 libft/ft_memset.c \
			 libft/ft_bzero.c \
			 libft/ft_memcpy.c \
			 libft/ft_memmove.c \
			 libft/ft_strlcpy.c \
			 libft/ft_strlcat.c \
			 libft/ft_strchr.c \
			 libft/ft_strcmp.c \
			 libft/ft_strrchr.c \
			 libft/ft_strncmp.c \
			 libft/ft_memchr.c \
			 libft/ft_memcmp.c \
			 libft/ft_strnstr.c \
			 libft/ft_strndup.c \
			 libft/ft_atoi.c \
			 libft/ft_strdup.c \
			 libft/ft_calloc.c \
			 libft/ft_substr.c \
			 libft/ft_strjoin.c \
			 libft/ft_strtrim.c \
			 libft/ft_split.c \
			 libft/ft_itoa.c \
			 libft/ft_strmapi.c \
			 libft/ft_striteri.c \
			 libft/ft_putchar_fd.c \
			 libft/ft_putstr_fd.c \
			 libft/ft_putendl_fd.c \
			 libft/ft_putnbr_fd.c \
			 libft/ft_free.c \
			 libft/ft_strcat.c \
			 libft/ft_strcpy.c \

SRCS_BONUS = libft/ft_lstnew_bonus.c \
			 libft/ft_lstadd_front_bonus.c \
			 libft/ft_lstsize_bonus.c \
			 libft/ft_lstlast_bonus.c \
			 libft/ft_lstadd_back_bonus.c \
			 libft/ft_lstdelone_bonus.c \
			 libft/ft_lstclear_bonus.c \
			 libft/ft_lstiter_bonus.c \
			 libft/ft_lstmap_bonus.c

SRCS_PRINTF = printf/ft_printf.c \
			  printf/ft_printf_functions.c

SRCS_GNL = gnl/get_next_line.c \
		   gnl/get_next_line_utils.c

# Object files
OBJS_LIBFT = ${SRCS_LIBFT:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
OBJS_PRINTF = ${SRCS_PRINTF:.c=.o}
OBJS_GNL = ${SRCS_GNL:.c=.o}

# Target settings
NAME = ultimate_libft.a
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

# Default target
all: ${NAME}

# Create static library
${NAME}: ${OBJS_LIBFT} $(OBJS_BONUS) ${OBJS_PRINTF} ${OBJS_GNL}
	@ar rc ${NAME} ${OBJS_LIBFT} ${OBJS_BONUS} ${OBJS_PRINTF} ${OBJS_GNL}
	@echo "$(GREEN)Project compiled!$(DEF_COLOR)"
	ranlib ${NAME}

# Bonus target
# bonus: ${NAME} ${OBJS_BONUS}
# 	ar rc ${NAME} ${OBJS_BONUS}
# 	ranlib ${NAME}

# Compile .c to .o
.c.o:
	${CC} ${CFLAGS} -c $< -o $@

# Clean up object files
clean:
	${RM} ${OBJS_LIBFT} ${OBJS_BONUS} ${OBJS_PRINTF} $(OBJS_GNL)
	@echo "$(RED)Cleaned object files$(DEF_COLOR)"

# Clean and remove the library
fclean: clean
	${RM} ${NAME}
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"

# Rebuild the project
re: fclean all

.PHONY: all bonus clean fclean re
