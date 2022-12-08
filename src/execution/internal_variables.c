/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:23:18 by amann             #+#    #+#             */
/*   Updated: 2022/12/08 20:04:59 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//TODO error handling, esp with mallocs

void	set_internal_variables(char **var_list, t_state *state)
{
	size_t	i;
	size_t	len;
	char	*name;
	char	*value;

	if (!(state->intern))
		state->intern = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2)); //protection needed
	i = 0;
	while (var_list[i])
	{
		len = valid_env_name_length(var_list[i]);
		name = ft_strndup(var_list[i], len); //protect
		value = ft_strchr(var_list[i], '=');
		value += 1;
		if (!env_set(name, value, &(state->intern))) //error handle
			return ;
		ft_strdel(&name);
		i++;
	}
}
