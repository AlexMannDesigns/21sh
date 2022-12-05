/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2022/12/05 18:36:41 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	set_underscore(t_ast_context *ctx, t_state *state)
{
	if (ft_null_array_len((void **)ctx->node->left->arg_list) != 0)
		env_set("_",
			ctx->node->left->arg_list[
			ft_null_array_len((void **)ctx->node->left->arg_list) - 1],
			&(state->env));
	else
		env_set("_", NULL, &(state->env));
}

static int	is_at_end_check(t_ast *node)
{
	return (!node->right || node->right->node_type == AST_SIMPLE_COMMAND);
}

static pid_t	execute_simple_command(t_ast_context *ctx, t_state *state)
{
	pid_t	result;

	result = -1;
	if (!ctx->is_at_end)
	{
		if (pipe(ctx->pipes->write) == -1)
			print_error(1, ETEMPLATE_SHELL_SIMPLE, ERR_PIPE_FAIL);
	}
	if (ctx->node->right && !heredoc_run(ctx->node->right, ctx->pipes))
		return (print_error(1, ETEMPLATE_SHELL_SIMPLE, ERR_HEREDOC_FAIL));
	if (ctx->is_at_end)
		pipe_reset(ctx->pipes->write);
	if (ctx->node->left && ctx->node->left->arg_list)
	{
		result = execute(ctx->node->left->arg_list, state, ctx);
		if (result == -1)
			set_internal_variables(ctx->node->left->var_list, state);
		set_underscore(ctx, state);
	}
	pipe_close(ctx->pipes->read);
	pipes_copy(ctx->pipes->read, ctx->pipes->write);
	return (result);
}

static pid_t	execute_ast(t_ast_context *ctx, t_state *state)
{
	pid_t			result;

	result = -1;
	if (ctx->node->node_type == AST_SIMPLE_COMMAND)
	{
		result = execute_simple_command(ctx, state);
		if (ctx->node->right)
			reset_io(ctx->redirect);
	}
	else if (ctx->node->node_type == AST_PIPE_SEQUENCE)
	{
		result = execute_ast(
				&(t_ast_context){
				ctx->node->left, ctx->redirect, ctx->pipes, !ctx->node->right
			}, state);
		if (ctx->node->right)
			result = execute_ast(
					&(t_ast_context){ctx->node->right, ctx->redirect,
					ctx->pipes, is_at_end_check(ctx->node)}, state);
	}
	return (result);
}

static void	execute_ast_list(t_ast **ast, t_state *state)
{
	t_redir	*redir;
	t_pipes	pipes;
	pid_t	pid;
	int		ret;
	int		i;

	if (!ast)
		return ;
	check_print_ast(ast, state, false);
	redir = (t_redir *) ft_memalloc(sizeof(t_redir));
	pipes_reset(pipes.read, pipes.write);
	i = 0;
	while (ast[i] != NULL)
	{
		initialize_redir_struct(redir);
		parse_expansions(ast[i], state);
		pid = execute_ast(&(t_ast_context){ast[i], redir, &pipes, 0}, state);
		if (pid != -1 && waitpid(pid, &ret, 0) != -1)
			set_return_value(get_return_value_from_status(ret), state);
		handle_logical_ops(ast, state, &i);
	}
	pipe_close(pipes.read);
	check_print_ast(ast, state, true);
	ast_free(&ast);
	free(redir);
}

void	tokenize_and_execute(t_state *state)
{
	t_tokenizer	tokenizer;

	if (ft_strisempty(state->input_context.input))
	{
		ft_putchar('\n');
		clear_input(&(state->input_context));
		return ;
	}
	if (!terminal_apply_config(&(state->orig_conf)))
	{
		print_error(1, ETEMPLATE_SHELL_SIMPLE, ERR_TERMIOS_FAIL);
		return ;
	}
	state->input_context.cursor = ft_strlen(state->input_context.input);
	move_cursor_to_saved_position(&(state->input_context));
	ft_putchar('\n');
	execute_ast_list(construct_ast_list(
			tokenize(state->input_context.input, &tokenizer)), state);
	history_store(state->input_context.input, state, 0);
	clear_input(&(state->input_context));
	if (!terminal_apply_config(&(state->input_conf)))
		print_error(1, ETEMPLATE_SHELL_SIMPLE, ERR_TERMIOS_FAIL);
}
