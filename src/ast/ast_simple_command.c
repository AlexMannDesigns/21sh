/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:39:33 by amann             #+#    #+#             */
/*   Updated: 2022/12/01 15:54:03 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	redirects_node(t_token **cursor, t_ast **node)
{
	if (!*cursor)
		return (true);
	if (!*node)
		*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!*node)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!(*node)->node_type)
		(*node)->node_type = AST_REDIRECTIONS;
	return (ast_redirect_control(*node, cursor));
}

static bool	args_node(t_token **cursor, t_ast **node)
{
	if (!*cursor)
		return (true);
	if (!*node)
		*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!*node)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!((*node)->node_type))
		(*node)->node_type = AST_COMMAND_ARGS;
	if (!((*node)->arg_list))
		(*node)->arg_list = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2));
	if (!((*node)->var_list))
		(*node)->var_list = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2));
	if (!((*node)->arg_list) || !((*node)->var_list))
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!(allocate_args_array(node, cursor)))
		return (false);
	return (true);
}

static bool	check_args_end(t_token **cursor)
{
	if (!*cursor || ast_is_separator(*cursor)
		|| ((*cursor)->type == TOKEN_PIPE && ft_strlen((*cursor)->value) == 1))
		return (true);
	return (false);
}

bool	ast_simple_command(t_token **cursor, t_ast **node)
{
	*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!(*node))
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	(*node)->node_type = AST_SIMPLE_COMMAND;
	while (cursor && *cursor)
	{
		if (check_args_end(cursor))
			break ;
		if (!check_separator_syntax(*cursor))
			return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
		if (!args_node(cursor, &((*node)->left))
			|| !redirects_node(cursor, &((*node)->right)))
			return (false);
	}
	if ((*node)->left)
	{
		ft_resize_null_array((void ***)&((*node)->left->arg_list),
			ft_null_array_len((void **)(*node)->left->arg_list));
	}
	return (true);
}
