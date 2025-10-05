/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:53:22 by noaziki           #+#    #+#             */
/*   Updated: 2025/10/01 19:34:12 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	master(t_engine *engine)
{
	init_data(engine);
	if (load_textures(engine) != 0)
		return (1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	engine->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT,
			"Welcome to SOLIDANGLE's game!", false);
	if (!engine->mlx)
		return (mlx_strerror(mlx_errno), 1);
	engine->image = mlx_new_image(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!engine->image)
		return (mlx_strerror(mlx_errno), 1);
	mlx_loop_hook(engine->mlx, render_horizon, engine);
	if (mlx_image_to_window(engine->mlx, engine->image, 0, 0) == -1)
		return (mlx_strerror(mlx_errno), 1);
	mlx_loop_hook(engine->mlx, raycast_frame, engine);
	mlx_loop_hook(engine->mlx, rotate_via_keys, engine);
	mlx_loop_hook(engine->mlx, rotate_via_mouse, engine);
	mlx_set_cursor_mode(engine->mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(engine->mlx, wanderer_controls, engine);
	mlx_close_hook(engine->mlx, farewell_wanderer, engine);
	mlx_loop(engine->mlx);
	mlx_terminate(engine->mlx);
	return (0);
}
