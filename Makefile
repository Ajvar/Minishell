NAME = Minishell

SRCS_PATH = ./srcs
FT_PRINTF_PATH = ${SRCS_PATH}/ft_printf
LIBFT_PATH = ${SRCS_PATH}/libft
GNL_PATH = ${SRCS_PATH}/Get_next_line

CFLAGS = -Wall -Wextra  -g -fsanitize=address
SRCS =	${SRCS_PATH}/main.c \
		${SRCS_PATH}/prompt.c \
		${GNL_PATH}/get_next_line.c \
		${GNL_PATH}/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}
CC = gcc

$(NAME): ${OBJS}  ${LIBFT_PATH}/libft.a 
	 ${CC} ${CFLAGS} ${SRCS} ${LIBFT_PATH}/libft.a  -o ${NAME}
all: ${NAME}

${LIBFT_PATH}/libft.a:
	make -C ${LIBFT_PATH}

#${FT_PRINTF_PATH}/libftprintf.a:
#	make -C ${FT_PRINTF_PATH}

clean:
	rm -rf ${OBJS}
	make clean -C ${LIBFT_PATH}
	#make clean -C ${FT_PRINTF_PATH}

fclean: clean
	rm -rf ${NAME}


re: fclean all

work: all clean

.PHONY: all clean fclean re