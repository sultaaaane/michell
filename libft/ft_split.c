/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:45:16 by mbentahi          #+#    #+#             */
/*   Updated: 2024/04/19 21:21:02 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_words(char const *str, char spacer)
{
	int	i;
	int	word_counter;

	word_counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != spacer && (str[i + 1] == spacer || str[i + 1] == '\0'))
		{
			word_counter++;
		}
		i++;
	}
	return (word_counter);
}

static int	get_word_length(char const *str, char spacer)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != spacer)
	{
		i++;
	}
	return (i);
}

static void	ft_free(char **str, int i)
{
	while (i--)
		free(str[i]);
	free(str);
}

static int	skip(char const *s, char **split, int flag, char c)
{
	int	i;

	i = 0;
	if (flag)
	{
		while (*s && *s == c)
		{
			i++;
			s++;
		}
		return (i);
	}
	if (!flag)
	{
		ft_strlcpy(*split, s, get_word_length(s, c) + 1);
		return (get_word_length(s, c));
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word_count;
	char	**str;

	if (!s)
		return (NULL);
	word_count = check_words(s, c);
	str = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		s += skip(s, str + i, 1, c);
		str[i] = (char *)malloc((get_word_length(s, c) + 1) * sizeof(char));
		if (!str)
		{
			ft_free(str, i);
			return (NULL);
		}
		s += skip(s, str + i, 0, c);
		i++;
	}
	str[word_count] = NULL;
	return (str);
}
