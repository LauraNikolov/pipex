NAME = pipex
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror

SRC_DIR = src
BONUS_DIR = bonus
OBJ_DIR = obj

SRC = $(SRC_DIR)/error.c \
      $(SRC_DIR)/execution.c \
      $(SRC_DIR)/execution2.c \
      $(SRC_DIR)/free.c \
      $(SRC_DIR)/lst_utils.c \
      $(SRC_DIR)/main.c \
      $(SRC_DIR)/split.c \
      $(SRC_DIR)/string_utils.c

BONUS_SRC = $(BONUS_DIR)/error_bonus.c \
            $(BONUS_DIR)/execution_bonus.c \
            $(BONUS_DIR)/execution2_bonus.c \
            $(BONUS_DIR)/free_bonus.c \
            $(BONUS_DIR)/heredoc.c \
            $(BONUS_DIR)/lst_utils_bonus.c \
            $(BONUS_DIR)/main_bonus.c \
            $(BONUS_DIR)/split_bonus.c \
            $(BONUS_DIR)/string_utils_bonus.c

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
BONUS_OBJ = $(patsubst $(BONUS_DIR)/%.c,$(OBJ_DIR)/%.o,$(BONUS_SRC))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

bonus: $(NAME)_bonus

$(LIBFT):
	@echo "$(GREEN)Compiling libft library$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compilation completed$(RESET)"

$(NAME): $(OBJ) | $(LIBFT)
	@echo "$(GREEN)Compiling source files$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
	@echo "$(GREEN)Compilation completed: $@$(RESET)"

$(NAME)_bonus: $(BONUS_OBJ) | $(LIBFT)
	@echo "$(GREEN)Compiling bonus files$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
	@echo "$(GREEN)Compilation completed: $@$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@printf "$(BLUE)Compiling source file $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r$(BLUE)Compiling source file $<... $(GREEN)done$(RESET)\n"

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(OBJ_DIR)
	@printf "$(BLUE)Compiling bonus file $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r$(BLUE)Compiling bonus file $<... $(GREEN)done$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(GREEN)Removing object files$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Object files removed$(RESET)"

fclean: clean
	@echo "$(GREEN)Removing executables$(RESET)"
	@rm -f $(NAME) $(NAME)_bonus
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Executables removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus