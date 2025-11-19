/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:07:39 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/11/15 13:22:54 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	main(int argc, char **argv)
{
	t_engine	engine;

	if (validate_args(argc, argv) != 0)
		return (1);
	if (new_parsing(argv[1], &engine.data) == 0)
		error_exit("Parsing failed");
	if (master(&engine))
	{
		close_fd();
		return (1);
	}
	return (close_fd(), 0);
}
