/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:53:22 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/12 17:36:35 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

void	setup_keys(void *param)
{
	t_engine *engine;

	engine = (t_engine *)param;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_W))
	{
		engine->player.posx += engine->player.dirx * SPEED;
		engine->player.posy += engine->player.diry * SPEED;
	}
	if (mlx_is_key_down(engine->mlx, MLX_KEY_S))
	{
		engine->player.posx -= engine->player.dirx * SPEED;
		engine->player.posy -= engine->player.diry * SPEED;
	}
	if (mlx_is_key_down(engine->mlx, MLX_KEY_A))
	{
		engine->player.posx -= engine->player.planex * SPEED;
		engine->player.posy -= engine->player.planey * SPEED;
	}
	if (mlx_is_key_down(engine->mlx, MLX_KEY_D))
	{
		engine->player.posx += engine->player.planex * SPEED;
		engine->player.posy += engine->player.planey * SPEED;
	}
}

void	raycast_frame(void *param)
{
	t_engine	*engine;
	int			x;

	engine = (t_engine *)param;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		setup_ray(engine, x);
		set_ray_deltas(engine);
		set_initial_sides(engine);
		perform_dda(engine);
		calculate_wall_projection(engine);
		if (engine->side == 1)
			draw_vertical_line(engine, x, 0xFF0000);
		else
			draw_vertical_line(engine, x, 0xFF0000);
		x++;
	}
}

int	master(t_engine *engine)
{
	init_data(engine);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	engine->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT,
			"Welcome to SOLIDANGLE's game!", false);
	if (!engine->mlx)
		return (mlx_strerror(mlx_errno), 1);
	engine->image = mlx_new_image(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!engine->image)
		return (mlx_strerror(mlx_errno), 1);
	render_horizon(engine);
	if (mlx_image_to_window(engine->mlx, engine->image, 0, 0) == -1)
		return (mlx_strerror(mlx_errno), 1);
	mlx_loop_hook(engine->mlx, raycast_frame, engine);
	mlx_loop_hook(engine->mlx, setup_keys, engine);
	mlx_loop(engine->mlx);
	return (0);
}
