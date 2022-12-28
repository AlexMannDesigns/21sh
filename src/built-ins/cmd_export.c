/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:48:06 by amann             #+#    #+#             */
/*   Updated: 2022/12/28 17:06:14 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	print_exported(char *const *args, t_state *state)
{
	if (!args[1] || (ft_strequ(args[1], "-p") && !args[2]))
	{
		env_print_all(state->exported);
		return (true);
	}
	return (false);
}

static bool	export_new_variable(char *var, t_state *state)
{
	size_t	len;
	char	*name;
	char	*value;

	len = valid_env_name_length(var);
	name = ft_strndup(var, len);
	if (!name)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	value = ft_strchr(var, '=');
	value += 1;
	if (!env_set(name, value, &(state->env))
		|| !env_set(name, value, &(state->intern))
		|| !env_set(name, value, &(state->exported)))
		return (false);
	ft_strdel(&name);
	return (true);
}

bool	export_existing_variable(char *name, t_state *state)
{
	char	**var;
	char	*value;
	char	**dest_ptr;
	size_t	len;

	var = env_get_pointer(name, state->intern);
	if (var)
	{
		value = ft_strchr(*var, '=');
		if (!env_set(name, value + 1, &(state->env))
			|| !env_set(name, value + 1, &(state->exported))
			|| !env_set(name, value + 1, &(state->intern)))
			return (false);
		return (true);
	}
	if (name[valid_env_name_length(name)]) //if this resolves to the null byte, the name is valid
		return (print_error_bool(false, ERRTEMPLATE_DOUBLE_NAMED_QUOTED, "export", name, ERR_NOT_VALID_ID));
	len = ft_null_array_len((void **)state->exported);
	dest_ptr = (char **)&((state->exported)[len]);
	*dest_ptr = ft_strdup(name);
	if (!((state->exported)[len]))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	return (true);
}


/*
 * export works similarly to setenv; ostensibly it allows the user to declare
 * variables that will be permanently added to the environment of future
 * commands.
 *
 * With the format:
 *
 * export <name>=<value>
 *
 * The variable is created added to the internal shell variables and
 * the environment. If <name> already exists, it is updated with the new value.
 *
 * With the format:
 *
 * export <name>
 *
 * If <name> exists in the internal shell variables, it will be exported to
 * the environment.
 *
 * If it does not exist, it will not go into the env, but will go into the list
 * of exported variables (assuming the syntax is ok) UNLESS that variable
 * already exists.
 *
 * When the -p flag is specified, all of the names of exported variables are
 * written to the stdout.
 */

int	cmd_export(char *const *args, t_state *state)
{
	int	i;
	int	ret;

	if (print_exported(args, state))
		return (1);
	ret = 0;
	i = 1;
	if (ft_strequ(args[1], "-p"))
		i = 2;
	while (args[i])
	{
		if (ft_strchr(args[i], '=')) //add new variable
		{
			if (!check_var_syntax(args[i]))
				ret = print_error(1, ERRTEMPLATE_DOUBLE_NAMED_QUOTED, "export", args[i], ERR_NOT_VALID_ID);
			else if (!export_new_variable(args[i], state))
				ret = 1;
		}
		else if (!export_existing_variable(args[i], state))//check if intern var exists already
				ret = 1;
		i++;
	}
	return (ret);
}
