/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:23:18 by amann             #+#    #+#             */
/*   Updated: 2022/12/05 18:59:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//TODO error handling, esp with mallocs

void	set_internal_variables(char **var_list, t_state *state)
{
	size_t	i;
	size_t	j;

	if (!(state->intern))
		state->intern = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2));
	j = ft_null_array_len((void **) state->intern);
	i = 0;
	while (var_list[i])
	{
		(state->intern)[j] = ft_strdup(var_list[i]);
		j++;
		i++;
	}
	for (i = 0 ; state->intern[i]; i++)
		ft_putendl(state->intern[i]);
}
