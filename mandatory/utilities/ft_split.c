/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:02:59 by noaziki           #+#    #+#             */
/*   Updated: 2025/10/05 18:30:23 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

static size_t	ft_counter(char *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	inword;

	i = 0;
	count = 0;
	inword = 0;
	while (s[i])
	{
		if (s[i] != c && inword == 0)
		{
			count++;
			inword = 1;
		}
		else if (s[i] == c)
			inword = 0;
		i++;
	}
	return (count);
}

static char	**ft_fill_arr(char *s, char c, char **arr)
{
	size_t		i;
	size_t		j;
	size_t		start;
	size_t		count;
	size_t		end;

	i = 0;
	j = 0;
	count = ft_counter(s, c);
	while (j < count)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i - 1;
		arr[j] = ft_substr(s, start, (end - start) + 1);
		if (!arr[j])
			return (NULL);
		j++;
	}
	arr[j] = 0;
	return (arr);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_counter(s, c);
	result = (char **)ft_alloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = ft_fill_arr(s, c, result);
	return (result);
}
