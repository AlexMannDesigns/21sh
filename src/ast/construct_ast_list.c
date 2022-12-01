/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_ast_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:27:35 by amann             #+#    #+#             */
/*   Updated: 2022/12/01 16:00:39 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"



#include "debug.h"

static size_t	ast_count(t_token *list)
{
	size_t	res;

	res = 1;
	while (list)
	{
		if ((list->type == TOKEN_SEMICOLON)
			|| ((list->type == TOKEN_AMPERSAND || list->type == TOKEN_PIPE)
				&& ft_strlen(list->value) == 2))
			res++;
		list = list->next;
	}
	return (res);
}

/*
 * In order to manage the semicolons effectively, we construct a separate tree
 * for each complete command, then pass that array of trees back to the parser
 *
 * The root node of each tree will be a pipe_sequence, with only one node if
 * nothing is being piped.
 */

static void	ast_list_loop(t_ast ***ast_list, t_token **cursor, size_t len)
{
	size_t	idx;
	int		ret;

	idx = 0;
	while (idx < len)
	{
		ret = ast_pipe_sequence(cursor, &((*ast_list)[idx]), 0);
		if (!ret)
		{
			ast_free(ast_list);
			return ;
		}
		if (!*cursor)
			return ;
		idx++;
	}
}

t_ast	**construct_ast_list(t_token *cursor)
{
	t_ast	**ast_list;
	size_t	len;
	t_token	*reset;

	if (!cursor)
		return (NULL);
	ast_cleanse_ws(&cursor);
	reset = cursor;
	len = ast_count(cursor);
	ast_list = (t_ast **) ft_memalloc(sizeof(t_ast *) * (len + 1));
	if (!ast_list)
		return (NULL);
	ast_list_loop(&ast_list, &cursor, len);
	cursor = reset;
	token_list_free(&cursor);
	return (ast_list);
}
