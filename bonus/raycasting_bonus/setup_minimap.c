/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:53:17 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/14 13:06:43 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:53:17 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/14 13:30:01 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

void	minimap_pixel_block(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i;
	int	j;
	int	size;

	size = 6;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i >= 0 && y + j >= 0
				&& x + i < (int)img->width
				&& y + j < (int)img->height)
				mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	shade_minimap_background(t_engine *engine, int radius)
{
	int	x;
	int	y;

	y = -radius;
	while (y < radius)
	{
		x = -radius;
		while (x < radius)
		{
			if ((x * x) + (y * y) <= radius * radius)
				mlx_put_pixel(engine->image, radius + x,
					radius + y, 0x800000FF);
			x++;
		}
		y++;
	}
}

void	trace_minimap_border(t_engine *engine, int radius)
{
	int		angle;
	int		center_x;
	int		center_y;
	float	rad;

	center_x = radius;
	center_y = radius;
	angle = 0;
	while (angle < 360)
	{
		rad = angle * M_PI / 180.0;
		minimap_pixel_block(engine->image,
			center_x + radius * cos(rad),
			center_y + radius * sin(rad),
			0x3e3e42FF);
		angle++;
	}
}

void	draw_map_tiles(t_engine *engine, int radius, int x, int y)
{
	float	res_x;
	float	res_y;
	float	dist;
	int		center_x;
	int		center_y;

	center_x = radius;
	center_y = radius;
	res_x = (x + 0.5) - engine->player.posx;
	res_y = (y + 0.5) - engine->player.posy;
	dist = sqrt(res_x * res_x + res_y * res_y);
	if (dist * 8 < radius)
	{
		if (engine->data.map[y][x] == '1')
			minimap_pixel_block(engine->image,
				center_x + (int)(res_x * 7.5),
				center_y + (int)(res_y * 7.5),
				0xD42525FF);
		else
			minimap_pixel_block(engine->image,
				center_x + (int)(res_x * 7.5),
				center_y + (int)(res_y * 7.5),
				0x696969FF);
	}
}

void	render_minimap(t_engine *engine)
{
	int	centerx;
	int	centery;
	int	y;
	int	x;

	centerx = 100;
	centery = 100;
	y = 0;
	shade_minimap_background(engine, 100);
	trace_minimap_border(engine, 100);
	while (engine->data.map[y])
	{
		x = 0;
		while (engine->data.map[y][x])
			draw_map_tiles(engine, 100, x++, y);
		y++;
	}
	minimap_pixel_block(engine->image, centerx, centery, 0xF5DEB3FF);
}
