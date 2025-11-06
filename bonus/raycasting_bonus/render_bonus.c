/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:38:37 by noaziki           #+#    #+#             */
/*   Updated: 2025/11/06 16:14:07 by hajel-ho         ###   ########.fr       */
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
			mlx_put_pixel(engine->image, x++, y, 0xCFA463FF);
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			mlx_put_pixel(engine->image, x++, y, 0x7A5A2CFF);
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
	check_game_over(engine);
	while (x < SCREEN_WIDTH)
	{
		setup_ray(engine, x);
		set_ray_deltas(engine);
		set_initial_sides(engine);
		perform_dda(engine);
		calculate_wall_projection(engine);
		tex_index = get_texture_index(engine);
		draw_textured_line(engine, x, tex_index);
		engine->buffer[x] = engine->perpwalldist;
		x++;
	}
	render_all_enemies(engine);
	render_minimap(engine);
}
