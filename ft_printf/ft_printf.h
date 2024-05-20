/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:33:57 by mbentahi          #+#    #+#             */
/*   Updated: 2024/03/05 00:54:58 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

// size_t	ft_strlen(const char *str);
int	ft_putstr(char *s);
int	ft_printf(const char *str, ...);
int	ft_putnbr(int n);
int	ft_putchar(char c);
int	ft_putnbr_base(int nbr, char c);
int	ft_printadd(void *s);
int	ft_putlong(unsigned int nb);

#endif