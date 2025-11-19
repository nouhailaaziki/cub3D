/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:07:39 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/11/19 18:47:57 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad_bonus.h"

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
