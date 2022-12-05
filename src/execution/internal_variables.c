/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:23:18 by amann             #+#    #+#             */
/*   Updated: 2022/12/05 18:33:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	set_internal_variables(char **var_list, t_state *state)
{
	(void) state;

	size_t	i;

	i = 0;
	while (var_list[i])
		ft_putendl(var_list[i++]);
}
