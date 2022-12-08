# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:02:44 by jumanner          #+#    #+#              #
#    Updated: 2022/12/08 20:18:56 by amann            ###   ########.fr        #
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
AST_FILES = ast_add_args.c ast_pipe_sequence.c ast_redir_control.c \
				ast_retokenize.c ast_free.c ast_cleanse_ws.c \
				ast_fd_agg_format_check.c construct_ast_list.c \
				ast_simple_command.c ast_add_fd_aggregation.c \
				ast_is_separator.c ast_end.c

AUTOCOMPLETE_DIR = autocomplete
AUTOCOMPLETE_FILES = autocomplete.c

BUILT_INS_DIR = built-ins
BUILT_INS_FILES = built_ins.c built_ins_flags.c cmd_cd.c cmd_echo.c cmd_env.c \
				cmd_fc.c cmd_setenv.c cmd_unsetenv.c cmd_exit.c \
				cmd_execute_script.c cmd_export.c cmd_true_false.c cmd_type.c \
				cmd_set.c

CLEANUP_DIR = cleanup
CLEANUP_FILES = cleanup.c

CURSOR_DIR = cursor
CURSOR_FILES = cursor.c cursor_utils.c

DEBUG_DIR = debug
DEBUG_FILES = ast_print_debug.c print_tokens.c check_print_ast.c

DISPLAY_DIR = display
DISPLAY_FILES = display.c

ENVIRONMENT_DIR = environment
ENVIRONMENT_FILES = environment.c environment_getters.c shlvl.c

EXECUTION_DIR = execution
EXECUTION_FILES = bin.c executor.c executor_path_utils.c fork.c pipes.c \
					heredocs.c reset_io.c redirects.c tokenize_and_execute.c \
					execute_fd_aggregation.c handle_logical_ops.c \
					internal_variables.c

EXPANSION_DIR = expansion
EXPANSION_FILES = expand_tilde.c expand_variables.c expand_node.c \
				  	parse_expansions.c

HISTORY_DIR = history
HISTORY_FILES = history.c history_save.c history_load.c history_utils.c

INPUT_DIR = input
INPUT_FILES = clipboard_copy.c clipboard_cut.c clipboard_paste.c \
				clipboard_utils.c ctrl_d.c \
				input.c input_handlers.c input_context.c input_utils.c \
				movement.c movement_alt_horizontal.c movement_alt_vertical.c

PARSING_DIR = parsing
PARSING_FILES = eat_read_token.c get_token_type.c lexer.c literals.c \
				token.c token_list.c add_to_result.c

SETUP_DIR = setup
SETUP_FILES = setup.c

SIGNALS_DIR = signals
SIGNALS_FILES = signal.c

TERMINAL_DIR = terminal
TERMINAL_FILES = terminal_configuration.c

UTILS_DIR = utils
UTILS_FILES = error.c utils.c utils_input.c return_value.c syntax_error.c \
			  	debug_redir.c check_var_syntax.c

SRC_FILES = main.c \
			$(patsubst %, $(AST_DIR)/%, $(AST_FILES)) \
			$(patsubst %, $(AUTOCOMPLETE_DIR)/%, $(AUTOCOMPLETE_FILES)) \
			$(patsubst %, $(BUILT_INS_DIR)/%, $(BUILT_INS_FILES)) \
			$(patsubst %, $(CLEANUP_DIR)/%, $(CLEANUP_FILES)) \
			$(patsubst %, $(CURSOR_DIR)/%, $(CURSOR_FILES)) \
			$(patsubst %, $(DEBUG_DIR)/%, $(DEBUG_FILES)) \
			$(patsubst %, $(DISPLAY_DIR)/%, $(DISPLAY_FILES)) \
			$(patsubst %, $(ENVIRONMENT_DIR)/%, $(ENVIRONMENT_FILES)) \
			$(patsubst %, $(EXECUTION_DIR)/%, $(EXECUTION_FILES)) \
			$(patsubst %, $(EXPANSION_DIR)/%, $(EXPANSION_FILES)) \
			$(patsubst %, $(HISTORY_DIR)/%, $(HISTORY_FILES)) \
			$(patsubst %, $(INPUT_DIR)/%, $(INPUT_FILES)) \
			$(patsubst %, $(PARSING_DIR)/%, $(PARSING_FILES)) \
			$(patsubst %, $(SETUP_DIR)/%, $(SETUP_FILES)) \
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
