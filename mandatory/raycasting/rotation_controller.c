/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_controller.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:10:53 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/14 12:44:37 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

void	rotate_player(t_engine *engine, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = engine->player.dirx;
	engine->player.dirx = engine->player.dirx
		* cos(angle) - engine->player.diry * sin(angle);
	engine->player.diry = old_dirx
		* sin(angle) + engine->player.diry * cos(angle);
	old_planex = engine->player.planex;
	engine->player.planex = engine->player.planex
		* cos(angle) - engine->player.planey * sin(angle);
	engine->player.planey = old_planex
		* sin(angle) + engine->player.planey * cos(angle);
}

void	rotate_via_keys(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_LEFT))
		rotate_player(engine, -0.01);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_RIGHT))
		rotate_player(engine, 0.01);
}
