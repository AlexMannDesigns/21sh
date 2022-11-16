/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:11 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 15:07:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/* Includes */

# include <fcntl.h>

# if __linux__
#  include <signal.h>
#  include <sys/wait.h>
# endif

# include "libft.h"
# include "general.h"
# include "utils.h"
# include "cursor.h"
# include "display.h"
# include "environment.h"
# include "built_ins.h"
# include "ast.h"
# include "history.h"
# include "terminal.h"
# include "debug.h"

/* Constants */
# define REDIR_APPEND ">>"
# define REDIR_HEREDOC "<<"

/* Types */

/* Files */

/* bin.c */
int		bin_env_find(const char *name, char *const *env, char **result);
pid_t	bin_execute(char *path, char **args, char *const *env, \
	t_ast_execution *ast);

/* executor.c */
pid_t	execute(char *const *args, t_state *state, t_ast_execution *ast);

/* execute_fd_aggregation.c */
int		execute_filedes_aggregation(t_ast *node, t_redir *r);

/* fork.c */
pid_t	start_fork(t_ast_execution *ast);

/* pipes.c */
void	pipe_reset(int pipe[2]);
void	pipe_close(int pipe[2]);
void	pipes_reset(int pipe1[2], int pipe2[2]);
int		pipes_connect(int read_pipe[2], int write_pipe[2]);
void	pipes_copy(int target[2], int source[2]);

/* heredocs.c */
int		heredoc_run(t_ast *redir_node, t_pipes *pipes);

/* redirects.c */
void	initialize_redir_struct(t_redir *r);
bool	handle_redirects(t_ast *redir_node, t_redir *r);

/* reset_io.c */
int		reset_io(t_redir *r);

/* tokenize_and_execute.c */
void	tokenize_and_execute(t_state *state);

#endif
