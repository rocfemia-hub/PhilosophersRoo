LIB = ar rcs
RM = rm -f

CC = cc

BLUE   = \033[34m
RESET  = \033[0m

CCFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address -fno-omit-frame-pointer -O1 -pthread

SRC_DIR = src

SRC = philo.c init_philo.c routines.c\

OBJS = ${SRC:%.c=objects/%.o}

INCLUDE = philo.h

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BLUE)        ||>>    $(BLUE)philo compiled!!    <<||$(RESET)"

objects/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CCFLAGS) -I/usr/include -c $< -o $@

clean:
	@$(RM) -rf objects

fclean:
	@$(RM) -rf objects
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re