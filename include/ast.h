/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:04 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/05 16:15:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/* Includes */

# include "libft.h"
# include "general.h"
# include "utils.h"
# include "parsing.h"
# include "expansion.h"

/* Constants */

# define FD_AGG_IN "<&"
# define FD_AGG_OUT ">&"

/* Types */

typedef struct s_token_dispatch
{
	char				symbol;
	t_token_type		token;
}	t_token_dispatch;

typedef int	t_parse_function(t_token **cursor, t_state *state, char **result);

/* Files */
bool	ft_isdigit_str(char *s);

/* ast_add_args.c */
bool	allocate_args_array(t_ast **node, t_token **cursor);

/* ast_add_fd_aggregation.c */
bool	ast_add_fd_agg(t_ast *node, t_token **cursor);

/* ast_cleanse_args.c */
void	ast_cleanse_ws(t_token *const *list);

/* ast_fd_agg_format_check.c */
bool	ast_fd_agg_format_check(t_token **cursor);

/* ast_free.c */
void	ast_free(t_ast ***tree_list);
void	ast_free_recursion(t_ast *node);

/* ast_is_separator.c */
bool	ast_is_separator(t_token *token);
int		ast_is_logic_op(t_token **cursor);
bool	check_separator_syntax(t_token *cursor);

/* ast_pipe_sequence.c */
bool	ast_pipe_sequence(t_token **cursor, t_ast **node, int x);

/* ast_redirect_control.c */
bool	ast_redirect_control(t_ast *node, t_token **cursor);
bool	add_redir_struct(t_ast_redir ***redirs, t_ast_redir *new);

/* ast_retokenize.c */
t_token	*ast_retokenize(char *line);

/* ast_simple_command.c */
bool	ast_simple_command(t_token **cursor, t_ast **node);

/* construct_ast_list.c */
t_ast	**construct_ast_list(t_token *cursor);

/* ast_end.c */
bool	check_end(t_token **cursor, t_token *reset, t_ast **node);
bool	recursion_end(t_token **cursor, t_token *reset, t_ast **node,
			int recurs_count);

#endif
