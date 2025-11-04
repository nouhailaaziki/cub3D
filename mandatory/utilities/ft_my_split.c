/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:06:38 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/10/05 18:30:23 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s && s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\r'))
			i++;
		if (s[i] && s[i] != c && s[i] != '\r')
		{
			word_count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (word_count);
}

static int	count_chars(char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c && s[len] != '\r')
		len++;
	return (len);
}

static void	fill_word(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
}

char	**ft_my_split(char *s, char c)
{
	int		i;
	int		word_len;
	int		index;
	char	**result;

	i = 0;
	index = 0;
	result = ft_alloc(sizeof(char *) * (count_words(s, c) + 1));
	while (s && s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\r'))
			i++;
		if (s[i] && s[i] != c && s[i] != '\r')
		{
			word_len = count_chars(&s[i], c);
			result[index] = ft_alloc(word_len + 1);
			fill_word(result[index++], &s[i], word_len);
			i += word_len;
		}
	}
	return (result[index] = NULL, result);
}
