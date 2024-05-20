/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:10:42 by mbentahi          #+#    #+#             */
/*   Updated: 2024/03/05 00:54:56 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putlong_base(unsigned long nb)
{
	size_t	i;
	int		counter;
	char	*base;

	counter = 0;
	base = "0123456789abcdef";
	i = ft_strlen(base);
	if (nb >= i)
	{
		counter += ft_putlong_base(nb / i);
		counter += ft_putlong_base(nb % i);
	}
	else
		counter += ft_putchar(base[nb]);
	return (counter);
}

int	ft_printadd(void *s)
{
	unsigned long	n;

	if (s == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
		write(1, "0x", 2);
	n = (unsigned long)s;
	return (ft_putlong_base(n) + 2);
}
