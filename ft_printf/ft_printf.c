/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:42:39 by mbentahi          #+#    #+#             */
/*   Updated: 2024/03/05 00:54:57 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_placeholder(const char *str, int *i, va_list varg,
		int *counter)
{
	if (str[*i + 1] == '%')
		*counter += write(1, "%", 1);
	else if (str[*i + 1] == 's')
		*counter += ft_putstr(va_arg(varg, char *));
	else if (str[*i + 1] == 'd' || str[*i + 1] == 'i')
		*counter += ft_putnbr(va_arg(varg, int));
	else if (str[*i + 1] == 'x')
		*counter += ft_putnbr_base(va_arg(varg, unsigned int), 'x');
	else if (str[*i + 1] == 'X')
		*counter += ft_putnbr_base(va_arg(varg, unsigned int), 'X');
	else if (str[*i + 1] == 'p')
		*counter += ft_printadd(va_arg(varg, void *));
	else if (str[*i + 1] == 'c')
		*counter += ft_putchar(va_arg(varg, int));
	else if (str[*i + 1] == 'u')
		*counter += ft_putlong(va_arg(varg, unsigned int));
	else
	{
		*counter += write(1, &str[*i], 1);
		*counter += write(1, &str[*i + 1], 1);
	}
	(*i)++;
	return (1);
}

static int	handle_percent(const char *str, int *i, int *counter)
{
	if (str[*i] == '%' && !str[*i + 1])
		return (-1);
	*counter += write(1, &str[*i], 1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		counter;
	va_list	varg;

	va_start(varg, str);
	if (!str)
		return (-1);
	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
			handle_placeholder(str, &i, varg, &counter);
		else if (handle_percent(str, &i, &counter) == -1)
			return (-1);
		i++;
	}
	va_end(varg);
	return (counter);
}
