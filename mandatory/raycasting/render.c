/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:38:37 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/12 16:27:36 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

void	render_horizon(t_engine *engine)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			mlx_put_pixel(engine->image, x++, y, 0xFF00FFFF);
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			mlx_put_pixel(engine->image, x++, y, 0xFF000071);
		y++;
	}
}

void	draw_vertical_line(t_engine *engine, int x, uint32_t color)
{
	int	y;

	if (x < 0 || x >= (int)engine->image->width)
		return ;
	if (engine->drawstart < 0)
		engine->drawstart = 0;
	if (engine->drawend >= (int)engine->image->height)
		engine->drawend = engine->image->height - 1;
	y = engine->drawstart;
	while (y <= engine->drawend)
	{
		mlx_put_pixel(engine->image, x, y, color);
		y++;
	}
}
