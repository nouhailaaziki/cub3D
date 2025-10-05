/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:34:18 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/10/04 18:27:59 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

int	main(int argc, char **argv)
{
	t_engine	engine;

	if (validate_args(argc, argv) != 0)
		return (1);
	if (new_parsing(argv[1], &engine.data) == 0)
	{
		error_exit("Parsing failed");
		return (free_cub3d(&engine.data), 1);
	}
	if (master(&engine))
		return (free_cub3d(&engine.data), 1);
	free_cub3d(&engine.data);
	return (0);
}
