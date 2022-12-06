/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:20 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/06 14:57:49 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* Includes */

# include <sys/ioctl.h>
# include <termcap.h>
# include <fcntl.h>

# include "libft.h"
# include "general.h"

/* Files */

/* debug_redir.c */
void	debug_redir(t_ast_redir *redir, t_redir *r);

/* check_var_syntax.c */
bool	check_var_syntax(char *str);

/* error.c */
int		print_error_valist(int return_value, char *format, va_list list);
int		print_error(int return_value, char *format, ...);
bool	print_error_bool(bool return_value, char *format, ...);

/* syntax_error.c */
bool	print_bool_syntax_error(char *message, t_token *token, bool ret);
bool	print_bool_sep_error(char *message, t_token *token, bool ret);

/* return_value.c */
int		get_return_value_from_status(int status);
void	set_return_value(int return_value, t_state *state);

/* utils.c */
void	update_window_size(t_input_context *context);
void	clear_input(t_input_context *context);
void	*var_copy(void *var);

/* utils_input.c */
size_t	input_get_row_count(t_input_context *context, size_t index);
void	input_get_line_properties(t_input_context *context, size_t index, \
		size_t *start, size_t *length);

#endif
