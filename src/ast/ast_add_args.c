/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:55:34 by amann             #+#    #+#             */
/*   Updated: 2022/12/08 16:18:29 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	check_cmd_end(t_token **cursor)
{
	t_token	*reset;

	reset = *cursor;
	if (eat_token(cursor, TOKEN_LT | TOKEN_GT, reset))
	{
		*cursor = reset;
		return (true);
	}
	if (ast_fd_agg_format_check(cursor))
		return (true);
	if (ast_is_separator(*cursor))
		return (true);
	if (!check_separator_syntax(*cursor))
		return (true);
	if ((*cursor)->type == TOKEN_PIPE && ft_strlen((*cursor)->value) == 1)
		return (true);
	return (false);
}

bool	allocate_args_array(t_ast **node, t_token **cursor)
{
	size_t	idx;

	idx = ft_null_array_len((void **)(*node)->arg_list);
	while (*cursor && !check_cmd_end(cursor))
	{
		if ((*cursor)->type == TOKEN_WORD)
		{
			((*node)->arg_list)[idx] = ft_strdup((*cursor)->value);
			if (!((*node)->arg_list)[idx])
				return (print_error_bool(false, ERR_MALLOC_FAIL));
			idx++;
		}
		else if ((*cursor)->type & (TOKEN_AMPERSAND | TOKEN_BACKSLASH))
			return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
		*cursor = (*cursor)->next;
	}
	return (true);
}
