/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir_recursion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:42:07 by amann             #+#    #+#             */
/*   Updated: 2022/10/28 15:05:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	add_redir_out(t_ast *node, t_token **cursor)
{
	if (node->out_type)
		ft_strdel(&(node->out_type));
	node->out_type = ft_strdup((*cursor)->value);
	if (!node->out_type)
		return (print_error(ERR_MALLOC_FAIL, 0));
	*cursor = (*cursor)->next;
	if (!(*cursor) || (*cursor)->type != TOKEN_WORD)
		return (print_error(ERR_SYNTAX, 0));
	if (node->out_file)
		ft_strdel(&(node->out_file));
	node->out_file = ft_strdup((*cursor)->value);
	if (!node->out_file)
		return (print_error(ERR_MALLOC_FAIL, 0));
	*cursor = (*cursor)->next;
	return (1);
}

static int	add_redir_in(t_ast *node, t_token **cursor)
{
	if (node->in_type)
		ft_strdel(&(node->in_type));
	node->in_type = ft_strdup((*cursor)->value);
	if (!node->in_type)
		return (print_error(ERR_MALLOC_FAIL, 0));
	*cursor = (*cursor)->next;
	if (!(*cursor) || (*cursor)->type != TOKEN_WORD)
		return (print_error(ERR_SYNTAX, 0));
	if (node->in_file)
		ft_strdel(&(node->in_file));
	node->in_file = ft_strdup((*cursor)->value);
	if (!node->in_file)
		return (print_error(ERR_MALLOC_FAIL, 0));
	*cursor = (*cursor)->next;
	return (1);
}

static int	add_fd_agg(t_ast *node, t_token **cursor)
{
	t_token	*reset;
	//word or gt/lt
	//if word, format is "from >& to"
	//if word following gt/lt is "-", we close the first word
	reset = *cursor;
	node->aggregation = TRUE;
	if (read_token(cursor, TOKEN_GT | TOKEN_LT, reset))
	{
		//print_tokens(*cursor);
		if ((*cursor)->value[0] == '>')
			node->agg_from = STDOUT_FILENO;
		if ((*cursor)->value[0] == '<')
			node->agg_from = STDIN_FILENO;
		eat_token(cursor, TOKEN_GT | TOKEN_LT, reset);
		if ((*cursor)->value[0] == '-')
			node->agg_close = TRUE;
		else
			node->agg_to = ft_atoi((*cursor)->value);
		eat_token(cursor, TOKEN_WORD, reset);
		return (TRUE);
	}
	node->agg_from = ft_atoi((*cursor)->value);
	eat_token(cursor, TOKEN_WORD, reset);
	eat_token(cursor, TOKEN_GT | TOKEN_LT, reset);
	if ((*cursor)->value[0] == '-')
		node->agg_close = TRUE;
	else
		node->agg_to = ft_atoi((*cursor)->value);
	eat_token(cursor, TOKEN_WORD, reset);
	return (TRUE);
}

int	ast_redirect_recursion(t_ast *node, t_token **cursor)
{
	if (*cursor && ast_fd_agg_format_check(cursor))
	{
		if (!add_fd_agg(node, cursor))
			return (0);
	}
	if (*cursor && (*cursor)->type == TOKEN_GT)
	{
		if (!add_redir_out(node, cursor))
			return (0);
	}
	if (*cursor && (*cursor)->type == TOKEN_LT)
	{
		if (!add_redir_in(node, cursor))
			return (0);
	}
	if (*cursor
		&& ((*cursor)->type == TOKEN_GT || (*cursor)->type == TOKEN_LT))
		ast_redirect_recursion(node, cursor);
	return (1);
}
