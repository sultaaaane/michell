/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:13:43 by mbentahi          #+#    #+#             */
/*   Updated: 2024/03/05 10:15:22 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	length(long nb, int *i)
{
	if (nb < 0)
	{
		(*i)++;
		nb *= -1;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		(*i)++;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	long	nb;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	nb = n;
	i = 1;
	length(nb, &i);
	result = malloc((i + 1) * sizeof(char));
	if (!result)
		return (0);
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	result[i--] = '\0';
	while (nb)
	{
		result[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	return (result);
}
