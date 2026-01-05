SRCS = src/main.c\
	
OBJS_DIR = obj

OBJS = $(SRCS:src/%.c=$(OBJS_DIR)/%.o)

NAME = philo

HEADER = includes/philo.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3


all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: src/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all