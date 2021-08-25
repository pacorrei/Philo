NAME = philo

all: ${NAME}

CFLAGS = -Wall -Werror -Wextra
CC = gcc

RM = rm -rf

HEAD = -I srcs/


SRCS_PATH = srcs/

OBJS_PATH = objs/

SRCS_NAME = main.c utils.c thread_action.c thread_utils.c struct_and_mutex.c \

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	mkdir $(OBJS_PATH) 2> /dev/null || true
	gcc -c $(FLAGS) $(HEAD) -o $@ -c $<

$(NAME):  ${OBJS}
		${CC} ${CFLAGS} ${SRCS} ${HEAD} -o ${NAME} -lpthread

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re :	fclean all

.PHONY: all clean fclean re