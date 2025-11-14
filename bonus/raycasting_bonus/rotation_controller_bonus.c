/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_controller_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:10:53 by noaziki           #+#    #+#             */
/*   Updated: 2025/11/14 12:48:41 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

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
		rotate_player(engine, -0.03);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_RIGHT))
		rotate_player(engine, 0.03);
}

void	toggle_mouse_mode(t_engine *engine)
{
	bool	key_down;

	key_down = mlx_is_key_down(engine->mlx, MLX_KEY_M);
	if (key_down && !engine->mouse_key_prev)
	{
		engine->mouse = !engine->mouse;
		if (engine->mouse)
		{
			mlx_set_cursor_mode(engine->mlx, MLX_MOUSE_DISABLED);
			mlx_get_mouse_pos(engine->mlx, &engine->mousex, &engine->mousey);
			engine->prev_mousex = engine->mousex;
		}
		else
			mlx_set_cursor_mode(engine->mlx, MLX_MOUSE_NORMAL);
	}
	engine->mouse_key_prev = key_down;
}

void	rotate_via_mouse(void *param)
{
	t_engine	*engine;
	double		deltax;

	engine = (t_engine *)param;
	toggle_mouse_mode(engine);
	if (!engine->mouse)
		return ;
	mlx_get_mouse_pos(engine->mlx, &engine->mousex, &engine->mousey);
	deltax = engine->mousex - engine->prev_mousex;
	engine->prev_mousex = engine->mousex;
	if (deltax != 0)
		rotate_player(engine, deltax * 0.002);
}
