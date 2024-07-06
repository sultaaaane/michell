/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:58:22 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/06 17:21:59 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (nmemb && 18446744073709551615UL / nmemb < size)
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		ft_bzero(str, 1);
		return (str);
	}
	ft_bzero(str, nmemb * size);
	return (str);
}

void  **ft_realloc2d(void **ptr, size_t size)
{
	void	**new;
	size_t	i;

	new = ft_calloc(size + 1, sizeof(void *));
	if (!new)
		return (NULL);
	i = 0;
	while (ptr && ptr[i])
	{
		new[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	new = ft_calloc(size, 1);
	if (!new)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new, ptr, size);
		free(ptr);
	}
	return (new);
}
