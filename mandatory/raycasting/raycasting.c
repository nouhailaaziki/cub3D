/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:39:54 by noaziki           #+#    #+#             */
/*   Updated: 2025/11/16 16:31:59 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

void	set_ray_deltas(t_engine *engine)
{
	engine->mapx = (int)engine->player.posx;
	engine->mapy = (int)engine->player.posy;
	if (engine->raydirx == 0)
		engine->deltadistx = 1e30;
	else
		engine->deltadistx = fabs(1 / engine->raydirx);
	if (engine->raydiry == 0)
		engine->deltadisty = 1e30;
	else
		engine->deltadisty = fabs(1 / engine->raydiry);
}

void	set_initial_sides(t_engine *engine)
{
	if (engine->raydirx < 0)
	{
		engine->stepx = -1;
		engine->sidedistx = (engine->player.posx - engine->mapx)
			* engine->deltadistx;
	}
	else
	{
		engine->stepx = 1;
		engine->sidedistx = (engine->mapx + 1.0 - engine->player.posx)
			* engine->deltadistx;
	}
	if (engine->raydiry < 0)
	{
		engine->stepy = -1;
		engine->sidedisty = (engine->player.posy - engine->mapy)
			* engine->deltadisty;
	}
	else
	{
		engine->stepy = 1;
		engine->sidedisty = (engine->mapy + 1.0 - engine->player.posy)
			* engine->deltadisty;
	}
}

int	dda_step(t_engine *engine, int h)
{
	if (engine->sidedistx < engine->sidedisty)
	{
		engine->sidedistx += engine->deltadistx;
		engine->mapx += engine->stepx;
		engine->side = 0;
	}
	else
	{
		engine->sidedisty += engine->deltadisty;
		engine->mapy += engine->stepy;
		engine->side = 1;
	}
	if (engine->mapy < 0 || engine->mapx < 0 || engine->mapy >= h)
		return (1);
	if (engine->mapx >= (int)ft_strlen(engine->data.map[engine->mapy]))
		return (1);
	if (engine->data.map[engine->mapy][engine->mapx] == '1')
		return (1);
	return (0);
}

void	perform_dda(t_engine *engine)
{
	int	hit;
	int	h;
	int	w;

	hit = 0;
	get_map_dimensions(engine, &h, &w);
	while (hit == 0)
		hit = dda_step(engine, h);
}

void	calculate_wall_projection(t_engine *engine)
{
	if (engine->side == 0)
		engine->perpwalldist = (engine->mapx - engine->player.posx \
		+ (1 - engine->stepx) / 2) / engine->raydirx;
	else
		engine->perpwalldist = (engine->mapy - engine->player.posy \
		+ (1 - engine->stepy) / 2) / engine->raydiry;
	engine->lineheight = (int)(SCREEN_HEIGHT / engine->perpwalldist);
	engine->drawstart = -engine->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (engine->drawstart < 0)
		engine->drawstart = 0;
	engine->drawend = engine->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (engine->drawend >= SCREEN_HEIGHT)
		engine->drawend = SCREEN_HEIGHT - 1;
}
