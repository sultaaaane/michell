/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:38:46 by mbentahi          #+#    #+#             */
/*   Updated: 2024/03/05 00:55:01 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	long	nb;
	int		counter;

	counter = 0;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		counter += write(1, "-", 1);
	}
	if ((nb / 10) > 0)
		counter += ft_putnbr((nb / 10));
	counter += ft_putchar(nb % 10 + 48);
	return (counter);
}
