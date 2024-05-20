/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:10:18 by mbentahi          #+#    #+#             */
/*   Updated: 2024/04/01 22:00:22 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (*str1 && *str2 && *str1 == *str2 && i < n)
	{
		str1++;
		str2++;
		i++;
	}
	if (i == n)
		return (0);
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
