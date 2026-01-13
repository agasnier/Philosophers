NAME = philo

CC = cc
CFLAGS = -Werror -Wall -Wextra -g

MANDA_DIR = src/mandatory
BONUS_DIR = src/bonus
OBJ_DIR = obj

INC_MANDA_DIR = include/mandatory
INC_BONUS_DIR = include/bonus

SRCS =	$(MANDA_DIR)/main.c \
		$(MANDA_DIR)/utils.c \
		$(MANDA_DIR)/init.c

SRCS_BONUS =	

OBJS = $(SRCS:$(MANDA_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:$(BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS = $(INC_MANDA_DIR)/philo.h
HEADERS_BONUS =	

all: $(NAME)

$(NAME): .manda $(OBJS) 
	@echo "Compilation philo..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation philo OK."

.manda:
	@if [ -f .bonus ]; then \
		echo "Switch to manda..."; \
		$(MAKE) fclean > /dev/null 2>&1; \
	fi
	@touch .manda

bonus: .bonus $(OBJS_BONUS)
	@echo "Compilation philo_bonus..."
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)
	@echo "Compilation philo_bonus OK."

.bonus: 
	@if [ -f .manda ]; then \
		echo "Switch to bonus..."; \
		$(MAKE) fclean > /dev/null 2>&1; \
	fi
	@touch .bonus

$(OBJ_DIR)/%.o: $(MANDA_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_MANDA_DIR) -c $< -o $@
	
$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c $(HEADERS_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_BONUS_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f .bonus .manda

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

