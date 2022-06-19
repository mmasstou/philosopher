
NAME = philo_bonus
HEADER = philo_bonus.h
CFLAGS	= -Wall -Wextra -Werror -pthread
CC		= cc
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

SRCS = main_bonus.c srcs/ft_parse_bonus.c srcs/philo_utils_bonus.c  srcs/lib.c  srcs/_starting_bonus.c srcs/init_semaphores_bonus.c srcs/error_bonus.c
LINKEDLIST_SRC = linkedList/add_back.c linkedList/add_front.c linkedList/lst_new.c linkedList/lst_size.c linkedList/lstLast.c
OBJS	= $(SRCS:.c=.o)
LINKEDLIST_OBJS	= $(LINKEDLIST_SRC:.c=.o)
all: $(NAME)

%.o:%.c  
	@${CC} ${CFLAGS}  -o $@ -c $<
	@echo "$(GREEN) $< $(RESET)"

$(NAME): $(OBJS) $(HEADER) $(LINKEDLIST_OBJS)
	@$(CC) $(CFLAGS) $(SRCS) $(LINKEDLIST_SRC) -o $(NAME) -g
	

push:fclean
	@git status
	@read -p "Files To Add:" files; git add "$$files" 
	@ read -p "Message:" message; \
	git commit -m "$$message"; \
	git push origin master

clean:
	@rm -rf $(OBJS) $(LINKEDLIST_OBJS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf philo.dSYM

re: fclean all

.PHONY: all $(NAME) clean fclean re