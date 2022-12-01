/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:39:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/01 16:24:59 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
 * Returns the length of the portion of the given string that's considered a
 * valid environment variable name ([a-zA-Z_][a-zA-Z_0-9]*).
 *
 * Returns zero if the given string is null.
 */

size_t	valid_env_name_length(char *name)
{
	size_t	result;

	if (!name)
		return (0);
	if (ft_isdigit(name[0]))
		return (0);
	result = 0;
	while (name[result])
	{
		if (ft_isalnum(name[result]) || name[result] == '_')
			result++;
		else
			break ;
	}
	return (result);
}

/*
 * Sets an environment variable to the given value.
 *
 * If there is no existing variable with the same name, the variable is added
 * to the end of the list. If there already is a variable with the same name,
 * the value of it is updated.
 *
 * Returns one on success, zero otherwise.
 */

int	env_set(const char *name, const char *value, char *const **env)
{
	size_t	new_size;
	char	**destination_pointer;
	char	*new;

	if (ft_strisempty(name))
		return (1);
	destination_pointer = env_get_pointer(name, *env);
	if (!destination_pointer)
	{
		new_size = ft_null_array_len((void **)*env) + 1;
		if (!ft_resize_null_array((void ***)(env), new_size))
			return (print_error(
					0, ETEMPLATE_SHELL_SIMPLE, ERR_MALLOC_FAIL));
		destination_pointer = (char **)*env + new_size - 1;
	}
	new = ft_strnew(ft_strlen(name) + 1 + ft_strlen(value));
	if (!new)
		return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_MALLOC_FAIL));
	ft_strcpy(new, name);
	new[ft_strlen(name)] = '=';
	if (value && ft_strlen(value) != 0)
		ft_strcpy(new + ft_strlen(name) + 1, value);
	free(*destination_pointer);
	*destination_pointer = new;
	return (1);
}

/*
 * Removes an environment variable, if it is set. If the variable is not set,
 * nothing is done and one is returned.
 *
 * Returns one on success, zero otherwise.
 */

int	env_unset(const char *name, char *const **env)
{
	char	**removeable;

	removeable = env_get_pointer(name, *env);
	if (removeable)
	{
		if (!ft_remove_from_null_array((void ***)env, (void *)(*removeable)))
			return (print_error(
					0, ETEMPLATE_SHELL_SIMPLE, ERR_MALLOC_FAIL));
	}
	return (1);
}

/*
 * Prints all environment variables.
 */

void	env_print_all(char *const *env)
{
	size_t	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}
