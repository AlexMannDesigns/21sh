/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:31:22 by amann             #+#    #+#             */
/*   Updated: 2022/12/06 18:04:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	print_exported(t_state *state)
{
	ft_printf("uwu this is a list of the exported variables (except not right now lol):\n");
	env_print_all(state->intern);
	return (0);
}

int	print_export_error(char *var, int ret)
{
	ft_dprintf(
			STDERR_FILENO,
			"21sh: export: `%s': not a valid identifier\n",
			var
			);
	return (ret);
}

bool	print_bool_export_error(char *var, bool ret)
{
	ft_dprintf(
			STDERR_FILENO,
			"21sh: export: `%s': not a valid identifier\n",
			var
			);
	return (ret);
}

bool export_new_variable(char *var, t_state *state)
{
	size_t	len;
	char	*name;
	char	*value;


	if (!(state->intern))
		state->intern = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2)); //protection needed
	len = valid_env_name_length(var);
	name = ft_strndup(var, len); //protect
	value = ft_strchr(var, '=');
	value += 1;
	//TODO add to exported vars list
	if (!env_set(name, value, &(state->env)) || !env_set(name, value, &(state->intern)))
		return (false);
	ft_strdel(&name);
	return (true);
}

/*
 * Check the list of internal variables. If a match is found, this can be
 * copied into the environment.
 *
 * Otherwise, the syntax of the name can be checked for validity. If invalid
 * an error can be returned. Otherwise, it can be added to the list of exported
 * variables.
 */

bool	export_existing_variable(char *name, t_state *state)
{
	char	**var;
	char	*value;
	size_t	i;

	var = env_get_pointer(name, state->intern);
	if (var)
	{
		value = ft_strchr(*var, '=');
		value += 1;
		if (!env_set(name, value, &(state->env)))
			return (false);
		return (true);
	}
	if (ft_isdigit(name[0]))
		return (print_bool_export_error(name, false));
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (print_bool_export_error(name, false));
		i++;
	}
	//add to exported variables list if name syntax checks out
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
 *
 */

int	cmd_export(char *const *args, t_state *state)
{
	size_t	i;
	int		ret;

	if (!args[1] || (ft_strequ(args[1], "-p") && !args[2]))
		return (print_exported(state));
	ret = 0;
	i = 1;
	if (ft_strequ(args[1], "-p"))
		i = 2;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (!check_var_syntax(args[i]))
			{
				print_export_error(args[i], 1);
				if (ret == 0)
					ret = 1;
			}
			if (!export_new_variable(args[i], state) && ret == 0)
				ret = 1;
		}
		else if (!export_existing_variable(args[i], state) && ret == 0)
			ret = 1;
		i++;
	}
	return (ret);
}
