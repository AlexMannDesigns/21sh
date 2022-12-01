/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:52:47 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/01 15:27:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies the null terminated array from src to dst. dst needs to have
 * enough space for the copy.
 * 
 * If the cpy function is NULL, the each pointer in the array is copied.
 * 
 * One will be returned on a successful copy. Zero otherwise.
 */
int	ft_copy_null_array(void **dst, void **src, void *(*cpy)(void *))
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (cpy)
		{
			dst[i] = cpy(src[i]);
			if (!((src[i] && dst[i]) || (!(src[i]) && !(dst[i]))))
				return (0);
		}
		else
			dst[i] = src[i];
		i++;
	}
	return (1);
}

/*
 * Duplicates the null terminated array src, and puts the result to the
 * address that result points to.
 * 
 * If the cpy function is NULL, the each pointer in the array is copied.
 * 
 * One will be returned on success. Zero otherwise.
 */
int	ft_dup_null_array(void **src, void ***result, void *(*cpy)(void *))
{
	size_t	size;

	size = ft_null_array_len(src);
	*result = (void **)ft_memalloc(sizeof(void *) * (size + 1));
	if (!(*result))
		return (0);
	return (ft_copy_null_array(*result, src, cpy));
}

/*
 * Resizes the given null terminated array to the given size and frees the
 * original array pointer.
 *
 * One will be returned on success. Zero otherwise.
 */
int	ft_resize_null_array(void ***array, size_t size)
{
	void	**result;

	result = (void **)ft_memalloc(sizeof(void *) * (size + 1));
	if (!result)
		return (0);
	if (!ft_copy_null_array(result, *array, NULL))
		return (0);
	free(*array);
	*array = result;
	return (1);
}
