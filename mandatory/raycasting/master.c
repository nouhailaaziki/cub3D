/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:53:22 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/12 21:38:11 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

void	setup_rotation(void *param)
{
	t_engine	*engine;
	double		old_dirx;
	double		old_planex;

	engine = (t_engine *)param;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_LEFT))
	{
		old_dirx = engine->player.dirx;
		engine->player.dirx = engine->player.dirx * cos(-0.05) - engine->player.diry * sin(-0.05);
		engine->player.diry = old_dirx * sin(-0.05) + engine->player.diry * cos(-0.05);
		old_planex = engine->player.planex;
		engine->player.planex = engine->player.planex * cos(-0.05) - engine->player.planey * sin(-0.05);
		engine->player.planey = old_planex * sin(-0.05) + engine->player.planey * cos(-0.05);
	}
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_RIGHT))
	{
		old_dirx = engine->player.dirx;
		engine->player.dirx = engine->player.dirx * cos(0.05) - engine->player.diry * sin(0.05);
		engine->player.diry = old_dirx * sin (0.05) + engine->player.diry * cos(0.05);
		old_planex = engine->player.planex;
		engine->player.planex = engine->player.planex * cos(0.05) - engine->player.planey * sin(0.05);
		engine->player.planey = old_planex * sin(0.05) + engine->player.planey * cos(0.05);
	}
}

int	check_collision(t_engine *engine, double x, double y)
{
	double r = 0.15;

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


void	setup_keys(void *param)
{
	t_engine *engine = (t_engine *)param;
	double new_x, new_y;

	if (mlx_is_key_down(engine->mlx, MLX_KEY_W))
	{
		new_x = engine->player.posx + engine->player.dirx * SPEED;
		new_y = engine->player.posy + engine->player.diry * SPEED;
		if (check_collision(engine, new_x, engine->player.posy))
			engine->player.posx = new_x;
		if (check_collision(engine, engine->player.posx, new_y))
			engine->player.posy = new_y;
	}
	if (mlx_is_key_down(engine->mlx, MLX_KEY_S))
	{
		new_x = engine->player.posx - engine->player.dirx * SPEED;
		new_y = engine->player.posy - engine->player.diry * SPEED;
		if (check_collision(engine, new_x, engine->player.posy))
			engine->player.posx = new_x;
		if (check_collision(engine, engine->player.posx, new_y))
			engine->player.posy = new_y;
	}
	if (mlx_is_key_down(engine->mlx, MLX_KEY_A))
	{
		new_x = engine->player.posx - engine->player.planex * SPEED;
		new_y = engine->player.posy - engine->player.planey * SPEED;
		if (check_collision(engine, new_x, engine->player.posy))
			engine->player.posx = new_x;
		if (check_collision(engine, engine->player.posx, new_y))
			engine->player.posy = new_y;
	}
	if (mlx_is_key_down(engine->mlx, MLX_KEY_D))
	{
		new_x = engine->player.posx + engine->player.planex * SPEED;
		new_y = engine->player.posy + engine->player.planey * SPEED;
		if (check_collision(engine, new_x, engine->player.posy))
			engine->player.posx = new_x;
		if (check_collision(engine, engine->player.posx, new_y))
			engine->player.posy = new_y;
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
	mlx_loop_hook(engine->mlx, setup_rotation, engine);
	mlx_loop_hook(engine->mlx, setup_keys, engine);
	mlx_loop(engine->mlx);
	return (0);
}
