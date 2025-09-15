/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:07:39 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/09/15 16:16:55 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	main(int argc, char **argv)
{
	t_engine	engine;

	if (validate_args(argc, argv) != 0)
		return (free_cub3d(&engine.data), 1);
	if (new_parsing(argv[1], &engine.data) == 0)
	{
		write(2, "Error: Parsing failed\n", 22);
		return (free_cub3d(&engine.data), 1);
	}
	if (master(&engine))
		return (free_cub3d(&engine.data), 1);
	free_cub3d(&engine.data);
	return (0);
}
