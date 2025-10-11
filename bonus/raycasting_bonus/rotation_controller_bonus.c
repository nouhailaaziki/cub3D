/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_controller_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:10:53 by noaziki           #+#    #+#             */
/*   Updated: 2025/10/09 16:17:15 by hajel-ho         ###   ########.fr       */
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
		rotate_player(engine, -0.01);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_RIGHT))
		rotate_player(engine, 0.01);
}

void	rotate_via_mouse(void *param)
{
	t_engine	*engine;
	double		deltax;

	engine = (t_engine *)param;
	if (engine->mouse || mlx_is_key_down(engine->mlx, MLX_KEY_M))
	{
		engine->mouse = 1;
		mlx_get_mouse_pos(engine->mlx, &engine->mousex, &engine->mousey);
		deltax = engine->mousex - engine->prev_mousex;
		engine->prev_mousex = engine->mousex;
		if (deltax > 0)
			rotate_player(engine, 0.01);
		else if (deltax < 0)
			rotate_player(engine, -0.01);
	}
}

int	get_tile_color(char c)
{
	if (c == '1')
		return (0xD42525FF);
	else if (c == 'D')
		return (0xFFA500FF);
	else if (c == 'O')
		return (0x00FF00FF);
	return (0x696969FF);
}
