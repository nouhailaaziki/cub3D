/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:36:06 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/08/29 21:11:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*hr;
	int		i;
	int		j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	hr = malloc(len1 + len2 + 1);
	if (!hr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		hr[j++] = s1[i++];
	}
	i = 0;
	while (s2 && s2[i])
	{
		hr[j++] = s2[i++];
	}
	free(s1);
	s1 = NULL;
	return (hr[j] = '\0', hr);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	st;
	size_t			i;
	char			*hr;

	st = ft_strlen(s);
	i = 0;
	if (!s || start > st)
		return (ft_strdup(""));
	hr = malloc(len + 1);
	if (!hr)
		return (NULL);
	while (s[start] && i < len)
		hr[i++] = s[start++];
	hr[i] = '\0';
	return (hr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strdup( char *s1)
{
	int		i;
	char	*hr;

	i = 0;
	while (s1[i])
		i++;
	hr = malloc((sizeof(char) * i) + 1);
	if (!hr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		hr[i] = s1[i];
		i++;
	}
	hr[i] = '\0';
	return (hr);
}
