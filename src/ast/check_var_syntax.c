/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:38:38 by amann             #+#    #+#             */
/*   Updated: 2022/12/21 15:41:31 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	check_var_syntax(char *str)
{
	size_t	i;

	if (!str || !ft_strchr(str, '=') || str[0] == '=' || ft_isdigit(str[0]))
		return (false);
	i = 0;
	while (str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
