/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:07:35 by amann             #+#    #+#             */
/*   Updated: 2022/12/08 20:20:01 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*
 * The command set prints out the internal variables of the shell.
 *
 * The POSIX standard would require a number of flags to be handled:
 * https://pubs.opengroup.org/onlinepubs/009695399/utilities/set.html
 *
 * However, for the purposes of this project, printing the variables is
 * sufficient.
 */

int	cmd_set(char *const *args, t_state *state)
{
	size_t	i;

	(void) args;
	if (!(state->intern))
		return (0);
	i = 0;
	while ((state->intern)[i])
	{
		ft_putendl((state->intern)[i]);
		i++;
	}
	return (0);
}
