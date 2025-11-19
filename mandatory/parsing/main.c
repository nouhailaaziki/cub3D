/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:34:18 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/11/14 12:53:19 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

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
