/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:23:51 by mbentahi          #+#    #+#             */
/*   Updated: 2024/03/05 00:55:00 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(int nbr, char c)
{
	unsigned long	i;
	unsigned long	nb;
	int				counter;
	char			*base;

	counter = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	nb = (unsigned long)nbr;
	i = ft_strlen(base);
	if (nb >= i)
	{
		counter += ft_putnbr_base((unsigned int)nb / i, c);
		counter += ft_putnbr_base((unsigned int)nb % i, c);
	}
	else
	{
		ft_putchar(base[nb]);
		counter++;
	}
	return (counter);
}
