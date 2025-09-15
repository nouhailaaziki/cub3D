/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wanderer_controls_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:12:43 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/14 09:01:22 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	check_collision(t_engine *engine, double x, double y)
{
	double	r;

	r = 0.15;
	if (engine->data.map[(int)(y)][(int)(x + r)] == '1')
		return (0);
	if (engine->data.map[(int)(y)][(int)(x - r)] == '1')
		return (0);
	if (engine->data.map[(int)(y + r)][(int)(x)] == '1')
		return (0);
	if (engine->data.map[(int)(y - r)][(int)(x)] == '1')
		return (0);
	return (1);
}

void	handle_movement(t_engine *engine, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = engine->player.posx + move_x;
	new_y = engine->player.posy + move_y;
	if (check_collision(engine, new_x, engine->player.posy))
		engine->player.posx = new_x;
	if (check_collision(engine, engine->player.posx, new_y))
		engine->player.posy = new_y;
}

void	handle_wasd_keys(t_engine *engine)
{
	if (mlx_is_key_down(engine->mlx, MLX_KEY_W))
		handle_movement(engine, engine->player.dirx
			* SPEED, engine->player.diry * SPEED);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_S))
		handle_movement(engine, -engine->player.dirx
			* SPEED, -engine->player.diry * SPEED);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_A))
		handle_movement(engine, -engine->player.planex
			* SPEED, -engine->player.planey * SPEED);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_D))
		handle_movement(engine, engine->player.planex
			* SPEED, engine->player.planey * SPEED);
}

void	wanderer_controls(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	handle_wasd_keys(engine);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_ESCAPE))
	{
		ft_putstr_fd("You chose to escape... \
SOLIDANGLE seals its gates behind you.\n", 1);
		mlx_close_window(engine->mlx);
	}
}

void	farewell_wanderer(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	ft_putstr_fd("SOLIDANGLE collapses into darkness. \
Farewell, wanderer...\n", 1);
	mlx_close_window(engine->mlx);
}
