/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:38:37 by noaziki           #+#    #+#             */
/*   Updated: 2025/10/01 19:35:03 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

void	render_horizon(void *param)
{
	int			x;
	int			y;
	t_engine	*engine;

	y = 0;
	engine = (t_engine *)param;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			mlx_put_pixel(engine->image, x++, y, 0xFF000000);
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			mlx_put_pixel(engine->image, x++, y, 0xFF000000);
		y++;
	}
}

void	raycast_frame(void *param)
{
	t_engine	*engine;
	int			x;
	int			tex_index;

	engine = (t_engine *)param;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		setup_ray(engine, x);
		set_ray_deltas(engine);
		set_initial_sides(engine);
		perform_dda(engine);
		calculate_wall_projection(engine);
		tex_index = get_texture_index(engine);
		if (engine->side == 1)
			draw_textured_line(engine, x, tex_index);
		else
			draw_textured_line(engine, x, tex_index);
		x++;
	}
	render_minimap(engine);
}
