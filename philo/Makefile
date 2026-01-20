NAME = philo

CC = cc
CFLAGS = -Werror -Wall -Wextra -g

MANDA_DIR = src
BONUS_DIR = src
OBJ_DIR = obj

INC_MANDA_DIR = include

SRCS =	$(MANDA_DIR)/main.c \
		$(MANDA_DIR)/utils.c \
		$(MANDA_DIR)/init.c \
		$(MANDA_DIR)/routine.c \
		$(MANDA_DIR)/threads.c \
		$(MANDA_DIR)/mutex.c

OBJS = $(SRCS:$(MANDA_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS = $(INC_MANDA_DIR)/philo.h

all: $(NAME)

$(NAME): $(OBJS) 
	@echo "Compilation philo..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation philo OK."

bonus: $(OBJS_BONUS)
	@echo "Compilation philo_bonus..."
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)
	@echo "Compilation philo_bonus OK."

$(OBJ_DIR)/%.o: $(MANDA_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_MANDA_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

