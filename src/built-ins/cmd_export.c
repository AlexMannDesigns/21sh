/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:31:22 by amann             #+#    #+#             */
/*   Updated: 2022/12/06 15:03:30 by amann            ###   ########.fr       */
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
 * When the -p flag is specified, all of the names of exported variables are
 * written to the stdout.
 */

int	cmd_export(char *const *args, t_state *state)
{
	size_t	i;

	if (!args[1] || (ft_strequ(args[1], "-p") && !args[2]))
		return (print_exported(state));
	i = 1;
	if (ft_strequ(args[1], "-p"))
		i = 2;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (!check_var_syntax(args[i]))
				print_export_error(args[i], 1);
		}
		else
			ft_putendl("var name search");
		i++;
	}
	return (0);
}
