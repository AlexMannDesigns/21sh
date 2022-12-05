/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:23:18 by amann             #+#    #+#             */
/*   Updated: 2022/12/05 19:30:46 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//TODO error handling, esp with mallocs

void	set_internal_variables(char **var_list, t_state *state)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**internal_var;
	char	*var_name;

	if (!(state->intern))
		state->intern = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2)); //protection needed
	j = ft_null_array_len((void **) state->intern);
	i = 0;
	while (var_list[i])
	{
		//if variable exists, replace it, otherwise, append to the intern array
		len = valid_env_name_length(var_list[i]);
		var_name = ft_strndup(var_list[i], len); //protect
		internal_var = env_get_pointer(var_name, state->intern);
		if (internal_var)
		{
			ft_strdel(internal_var);
			*internal_var = ft_strdup(var_list[i]); //protect
		}
		else
		{
			(state->intern)[j] = ft_strdup(var_list[i]); //protection needed
			j++;
		}
		ft_strdel(&var_name);
		i++;
	}
	for (i = 0 ; state->intern[i]; i++)
		ft_putendl(state->intern[i]);
}
