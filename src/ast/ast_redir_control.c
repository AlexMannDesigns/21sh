/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:42:07 by amann             #+#    #+#             */
/*   Updated: 2022/12/05 16:17:18 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	add_redir_struct(t_ast_redir ***redirs, t_ast_redir *new)
{
	size_t	len;

	if (!*redirs)
	{
		*redirs = (t_ast_redir **) ft_memalloc(sizeof(t_ast_redir *) * 2);
		if (!*redirs)
			return (print_error_bool(false, ERR_MALLOC_FAIL));
	}
	len = ft_null_array_len((void **)*redirs);
	if (len == 0)
	{
		(*redirs)[0] = new;
		return (true);
	}
	if (!ft_resize_null_array((void ***)redirs, len + 1))
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	(*redirs)[len] = new;
	return (true);
}

static bool	add_redir_in(t_ast *node, t_token **cursor)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!ft_strequ((*cursor)->value, "<") && !ft_strequ((*cursor)->value, "<<"))
		return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
	res->in_type = ft_strdup((*cursor)->value);
	if (!res->in_type)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!((*cursor)->next) || (*cursor)->next->type != TOKEN_WORD)
		return (print_bool_syntax_error(ERR_SYNTAX, *cursor, false));
	*cursor = (*cursor)->next;
	res->in_file = ft_strdup((*cursor)->value);
	if (!res->in_file)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	*cursor = (*cursor)->next;
	return (add_redir_struct(&(node->redirs), res));
}

static bool	add_redir_out(t_ast *node, t_token **cursor)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!ft_strequ((*cursor)->value, ">") && !ft_strequ((*cursor)->value, ">>")
		&& !ft_strequ((*cursor)->value, ">&"))
		return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
	res->out_type = ft_strdup((*cursor)->value);
	if (!res->out_type)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!((*cursor)->next) || (*cursor)->next->type != TOKEN_WORD)
		return (print_bool_syntax_error(ERR_SYNTAX, *cursor, false));
	*cursor = (*cursor)->next;
	res->out_file = ft_strdup((*cursor)->value);
	if (!res->out_file)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	*cursor = (*cursor)->next;
	return (add_redir_struct(&(node->redirs), res));
}

/*
 * First, we must filter out separators or null, as we will call this function
 * if these are detected in ast_add_args.
 *
 * We then loop through the tokens, checking for fd aggregation or redirects,
 * and handling them accordingly, until we hit a sequence of tokens not matching
 * the syntax.
 *
 * Bad syntax, for example no file to redirect into or ">>>>>",  will be managed
 * by the respective handler functions; to keep this loop as clean and minimal
 * as possible.
 */

bool	ast_redirect_control(t_ast *node, t_token **cursor)
{
	if (!(*cursor) || (!((*cursor)->type & (TOKEN_LT | TOKEN_GT))
			&& !ast_fd_agg_format_check(cursor)))
		return (true);
	while (*cursor)
	{
		if (ast_fd_agg_format_check(cursor))
		{
			if (!ast_add_fd_agg(node, cursor))
				return (false);
		}
		else if ((*cursor)->type == TOKEN_GT)
		{
			if (!add_redir_out(node, cursor))
				return (false);
		}
		else if ((*cursor)->type == TOKEN_LT)
		{
			if (!add_redir_in(node, cursor))
				return (false);
		}
		else
			return (true);
	}
	return (true);
}
