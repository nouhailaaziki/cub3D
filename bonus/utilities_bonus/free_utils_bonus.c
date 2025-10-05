/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:43:58 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/27 15:18:55 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cub3d(t_data *data)
{
	if (data->map)
		free_array(data->map);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->no)
		free(data->no);
	if (data->ea)
		free(data->ea);
	if (data->f)
		free(data->f);
	if (data->c)
		free(data->c);
}

int	openning_file(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 6);
		ft_putstr_fd("Failed to open the file\n", 2);
		exit(1);
	}
	return (fd);
}
