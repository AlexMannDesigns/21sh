# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:02:44 by jumanner          #+#    #+#              #
#    Updated: 2022/11/03 13:52:43 by jumanner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

INCLUDE_DIR = ./include

LIB_DIR = ./libft
LIB_INCLUDE_DIR = ./libft/include
LIB_PATH = ./libft/libft.a

SRC_DIR = ./src

AST_DIR = ast
AST_FILES = ast_add_args.c ast_pipe_sequence.c ast_parse_expansions.c \
				ast_redir_control.c ast_retokenize.c ast_free.c \
				ast_cleanse_ws.c ast_fd_agg_format_check.c grammar.c

AUTOCOMPLETE_DIR = autocomplete
AUTOCOMPLETE_FILES = autocomplete.c

BUILT_INS_DIR = built-ins
BUILT_INS_FILES = built_ins.c cmd_cd.c cmd_echo.c cmd_env.c cmd_setenv.c \
				cmd_unsetenv.c cmd_exit.c

CURSOR_DIR = cursor
CURSOR_FILES = cursor.c cursor_utils.c

DEBUG_DIR = debug
DEBUG_FILES = ast_print_debug.c print_tokens.c

DISPLAY_DIR = display
DISPLAY_FILES = display.c

ENVIRONMENT_DIR = environment
ENVIRONMENT_FILES = environment.c environment_getters.c shlvl.c

EXECUTION_DIR = execution
EXECUTION_FILES = bin.c executor.c fork.c pipes.c redirects.c \
					tokenize_and_execute.c execute_fd_aggregation.c

EXPANSION_DIR = expansion
EXPANSION_FILES = expand_tilde.c expand_variables.c

HISTORY_DIR = history
HISTORY_FILES = history.c

INPUT_DIR = input
INPUT_FILES = clipboard.c ctrl_d.c input.c input_handlers.c input_context.c \
				movement.c movement_alt.c

PARSING_DIR = parsing
PARSING_FILES = eat_read_token.c get_token_type.c lexer.c literals.c \
				token.c token_list.c add_to_result.c

SIGNALS_DIR = signals
SIGNALS_FILES = signal.c

TERMINAL_DIR = terminal
TERMINAL_FILES = terminal_configuration.c

UTILS_DIR = utils
UTILS_FILES = error.c utils.c utils_input.c return_value.c

SRC_FILES = main.c \
			$(patsubst %, $(AST_DIR)/%, $(AST_FILES)) \
			$(patsubst %, $(AUTOCOMPLETE_DIR)/%, $(AUTOCOMPLETE_FILES)) \
			$(patsubst %, $(BUILT_INS_DIR)/%, $(BUILT_INS_FILES)) \
			$(patsubst %, $(CURSOR_DIR)/%, $(CURSOR_FILES)) \
			$(patsubst %, $(DEBUG_DIR)/%, $(DEBUG_FILES)) \
			$(patsubst %, $(DISPLAY_DIR)/%, $(DISPLAY_FILES)) \
			$(patsubst %, $(ENVIRONMENT_DIR)/%, $(ENVIRONMENT_FILES)) \
			$(patsubst %, $(EXECUTION_DIR)/%, $(EXECUTION_FILES)) \
			$(patsubst %, $(EXPANSION_DIR)/%, $(EXPANSION_FILES)) \
			$(patsubst %, $(HISTORY_DIR)/%, $(HISTORY_FILES)) \
			$(patsubst %, $(INPUT_DIR)/%, $(INPUT_FILES)) \
			$(patsubst %, $(PARSING_DIR)/%, $(PARSING_FILES)) \
			$(patsubst %, $(SIGNALS_DIR)/%, $(SIGNALS_FILES)) \
			$(patsubst %, $(TERMINAL_DIR)/%, $(TERMINAL_FILES)) \
			$(patsubst %, $(UTILS_DIR)/%, $(UTILS_FILES))

SRCS := $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES))

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

GCC_FLAGS = -g -Wall -Wextra -Werror

$(NAME): $(LIB_PATH) $(OBJS)
	$(CC) $(GCC_FLAGS) $(OBJS) -o $(NAME) -ltermcap -L $(LIB_DIR) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(GCC_FLAGS) -I $(INCLUDE_DIR) -I $(LIB_INCLUDE_DIR) -c $< -o $@

.PHONY: all clean fclean re run

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(LIB_PATH):
	make -C $(LIB_DIR)

run: $(NAME)
	./$(NAME)
