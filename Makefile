NAME = philo

SRCS = srcs/*.c

FLAGS = -Wall -Werror -Wextra



all: $(NAME)

$(NAME):
	@echo "Création de l'executable..."
	@gcc $(FLAGS) $(SRCS) -o $(NAME) -lpthread
	@echo "Compilation terminée !"


clean:
	@echo "Clean..."
	@rm -rf $(NAME)
	@echo "Clean !"

fclean:
	@echo "Full clean..."
	@rm  -rf $(NAME)
	@echo "Fclean !"

re:	clean all