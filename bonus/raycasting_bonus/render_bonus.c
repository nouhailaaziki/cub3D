/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:38:37 by noaziki           #+#    #+#             */
/*   Updated: 2025/11/19 18:48:41 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad_bonus.h"

void	render_horizon(void *param)
{
	int			x;
	int			y;
	t_engine	*engine;
	t_colors	colors;

	y = 0;
	engine = (t_engine *)param;
	colors = engine->data.ceiling;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			mlx_put_pixel(engine->image, x++, y, (colors.r << 24)
				+ (colors.g << 16) + (colors.b << 8) + 255);
		y++;
	}
	colors = engine->data.floor;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			mlx_put_pixel(engine->image, x++, y, (colors.r << 24)
				+ (colors.g << 16) + (colors.b << 8) + 255);
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

void	get_map_dimensions(t_engine *e, int *h, int *w)
{
	int	len;

	*h = 0;
	*w = 0;
	while (e->data.map[*h])
	{
		len = ft_strlen(e->data.map[*h]);
		if (len > *w)
			*w = len;
		(*h)++;
	}
}
