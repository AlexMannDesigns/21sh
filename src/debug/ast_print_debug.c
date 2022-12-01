/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:07:12 by amann             #+#    #+#             */
/*   Updated: 2022/12/01 16:05:33 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	print_redirs(t_ast *node, int fd)
{
	int	i;

	if (!node->redirs)
		return ;
	i = 0;
	while (node->redirs[i])
	{
		if (node->redirs[i]->aggregation)
			ft_dprintf(fd, " aggregation (from: %d to: %d close: %d)",
				node->redirs[i]->agg_from, node->redirs[i]->agg_to,
				node->redirs[i]->agg_close);
		if (node->redirs[i]->in_type)
			ft_dprintf(fd, " input (type: %s file: %s)",
				node->redirs[i]->in_type, node->redirs[i]->in_file);
		if (node->redirs[i]->out_type)
			ft_dprintf(fd, " output (type: %s file: %s)",
				node->redirs[i]->out_type, node->redirs[i]->out_file);
		i++;
	}
	ft_dprintf(fd, "\n");
}

static void	print_spaces(int space, int count, int fd)
{
	int	i;

	i = count;
	while (i < space)
	{
		ft_dprintf(fd, " ");
		i++;
	}
}

static void	print_ast_node(t_ast *node, int space, int count, int fd)
{
	int	i;

	ft_dprintf(fd, "\n");
	print_spaces(space, count, fd);
	if (node->node_type == AST_PIPE_SEQUENCE)
		ft_dprintf(fd, "PIPE_SEQUENCE\n");
	else if (node->node_type == AST_SIMPLE_COMMAND)
		ft_dprintf(fd, "SIMPLE_COMMAND\n");
	else if (node->node_type == AST_COMMAND_ARGS)
	{
		i = 0;
		while ((node->arg_list)[i])
			ft_dprintf(fd, "%s ", (char *)(node->arg_list)[i++]);
		ft_dprintf(fd, "\n");
		print_spaces(space, count, fd);
		i = 0;
		while ((node->var_list)[i])
			ft_dprintf(fd, "%s ", (char *)(node->var_list)[i++]);
		ft_dprintf(fd, "\n");
	}
	else if (node->node_type == AST_REDIRECTIONS)
		print_redirs(node, fd);
}

static void	ast_iterate(t_ast *root, int space, int fd)
{
	int	count;

	count = 20;
	if (root)
	{
		space += count;
		ast_iterate(root->right, space, fd);
		print_ast_node(root, space, count, fd);
		ast_iterate(root->left, space, fd);
	}
	else
		return ;
}

void	print_ast(t_ast **ast, int fd)
{
	size_t	idx;
	t_ast	*root;

	ft_dprintf(fd, "########## AST ##########\n");
	if (!ast || !(ast[0]))
	{
		ft_dprintf(fd, "something terrible happened");
		return ;
	}
	idx = 0;
	while (ast[idx])
	{
		ft_dprintf(fd, "AST number %zu:\n", idx + 1);
		root = ast[idx];
		ast_iterate(root, 0, fd);
		idx++;
	}
}
