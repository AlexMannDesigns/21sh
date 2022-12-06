/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:31:22 by amann             #+#    #+#             */
/*   Updated: 2022/12/06 16:58:35 by amann            ###   ########.fr       */
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

int	export_variable(char *var, t_state *state)
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
	//TODO add to internal vars list
	if (!env_set(name, value, &(state->env)) || !env_set(name, value, &(state->intern)))
		return (0);
/*	internal_var = env_get_pointer(name, state->intern);
	if (internal_var)
	{
		ft_strdel(internal_var);
		*internal_var = ft_strdup(var); //protect
	}
	else
		(state->intern)[ft_null_array_len((void **) state->intern)] = ft_strdup(var); //protection needed
*/	//add to env
	ft_strdel(&name);
	return (1);
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
				ret = print_export_error(args[i], 1);
			if (!export_variable(args[i], state))
				return (1);
		}
		else
			ft_putendl("var name search");
		i++;
	}
	return (ret);
}
