/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:38:28 by mbentahi          #+#    #+#             */
/*   Updated: 2024/03/05 00:54:59 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putlong(unsigned int nb)
{
	int	counter;

	counter = 0;
	if (nb >= 10)
	{
		counter += ft_putlong(nb / 10);
		counter += ft_putlong(nb % 10);
	}
	else
		counter += ft_putchar(nb + 48);
	return (counter);
}
