/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:58:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/11/19 18:49:44 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad_bonus.h"

char	*check_backup(char **backup )
{
	char	*line;
	char	*temp;
	size_t	count;

	count = 0;
	while (backup[0][count] && backup[0][count] != '\n')
		count++;
	line = ft_substr(backup[0], 0, count + 1);
	temp = *backup;
	*backup = ft_substr(temp, count + 1, ft_strlen(temp) - count);
	return (line);
}

static void	check_buf(char **buf, char **backup, ssize_t read_line)
{
	buf[0][read_line] = '\0';
	if (!*backup)
		backup[0] = ft_strdup("");
	backup[0] = ft_strjoin(backup[0], buf[0]);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buf;
	ssize_t		read_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_alloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		check_buf(&buf, &backup, read_line);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (!backup || *backup == '\0')
		return (NULL);
	return (check_backup(&backup));
}
