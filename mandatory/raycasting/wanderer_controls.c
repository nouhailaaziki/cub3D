/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wanderer_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:12:43 by noaziki           #+#    #+#             */
/*   Updated: 2025/10/06 17:30:04 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

int	check_collision(t_engine *engine, double x, double y)
{
	int	mx;
	int	my;
	int	h;
	int	w;

	mx = (int)floor(x);
	my = (int)floor(y);
	get_map_dimensions(engine, &h, &w);
	if (!isfinite(x) || !isfinite(y))
		return (0);
	if (my < 0 || mx < 0 || my >= h)
		return (0);
	if (mx >= ft_strlen(engine->data.map[my]))
		return (0);
	if (engine->data.map[my][mx] == '1')
		return (0);
	return (1);
}

void	handle_movement(t_engine *engine, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	int		h;
	int		w;

	new_x = engine->player.posx + move_x;
	new_y = engine->player.posy + move_y;
	if (!isfinite(new_x) || !isfinite(new_y))
		return ;
	get_map_dimensions(engine, &h, &w);
	if (new_x < 0.0)
		new_x = 0.0;
	if (new_y < 0.0)
		new_y = 0.0;
	if (new_x >= (double)(w - 1))
		new_x = (double)(w - 1) - 0.001;
	if (new_y >= (double)(h - 1))
		new_y = (double)(h - 1) - 0.001;
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
