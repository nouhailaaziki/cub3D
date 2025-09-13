/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:53:22 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/13 23:40:43 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

// void	render_2d_map(void *param)
// {
// 	t_engine	*engine;
// 	int			i;
// 	int			j;
// 	int			x;
// 	int			y;
// 	int			px;
// 	int			py;
// 	uint32_t	color;

// 	i = 0;
// 	engine = (t_engine *)param;
// 	while (engine->data.map[i])
// 	{
// 		j = 0;
// 		while (engine->data.map[i][j])
// 		{
// 			if (engine->data.map[i][j] == '1')
// 				color = 0xFF0000FF;
// 			else
// 				color = 0xFFFFFFFF;
// 			y = 0;
// 			while (y < CELL_SIZE)
// 			{
// 				x = 0;
// 				while (x < CELL_SIZE)
// 				{
// 					mlx_put_pixel(engine->image, j * CELL_SIZE + x, i * CELL_SIZE + y, color);
// 					x++;
// 				}
// 				y++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	px = engine->player.posx * CELL_SIZE;
// 	py = engine->player.posy * CELL_SIZE;
// 	y = -CELL_SIZE/4;
//     while (y < CELL_SIZE/4)
// 	{
// 		x = -CELL_SIZE/4;
//         while (x < CELL_SIZE/4)
// 		{
//             mlx_put_pixel(engine->image, px + x, py + y, 0xFFFF0000);
// 			x++;
// 		}
// 			y++;
// 	}
// }

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
	mlx_loop_hook(engine->mlx, render_horizon, engine);
	if (mlx_image_to_window(engine->mlx, engine->image, 0, 0) == -1)
		return (mlx_strerror(mlx_errno), 1);
	mlx_loop_hook(engine->mlx, raycast_frame, engine);
	mlx_loop_hook(engine->mlx, rotation_controller, engine);
	mlx_loop_hook(engine->mlx, wanderer_controls, engine);
	mlx_close_hook(engine->mlx, farewell_wanderer, engine);
	mlx_loop(engine->mlx);
	mlx_terminate(engine->mlx);
	return (0);
}
