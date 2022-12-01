/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:55:34 by amann             #+#    #+#             */
/*   Updated: 2022/12/01 17:10:38 by amann            ###   ########.fr       */
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

/*
 * malloc protection = if ft_strdup fails, the variable is just not added.
 * Not great, but wont break anything...
 */

bool	check_intern(t_ast **node, t_token *cursor, bool *var_flag)
{
	size_t	idx;

	if (ft_strchr(cursor->value, '=') && *var_flag)
	{
		idx = ft_null_array_len((void **) (*node)->var_list);
		((*node)->var_list)[idx] = ft_strdup(cursor->value);
		return (true);
	}
	*var_flag = false;
	return (false);
}
//TODO make this good

bool	allocate_args_array(t_ast **node, t_token **cursor)
{
	size_t	idx;
	bool	var_flag;

	var_flag = true;
	idx = ft_null_array_len((void **) (*node)->arg_list);
	while (*cursor && !check_cmd_end(cursor))
	{
		if ((*cursor)->type == TOKEN_WORD && !check_intern(node, *cursor, &var_flag))
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
