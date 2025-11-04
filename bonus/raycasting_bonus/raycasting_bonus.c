/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:39:54 by noaziki           #+#    #+#             */
/*   Updated: 2025/10/15 16:14:48 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

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

void	update_ray_step(t_engine *e)
{
	if (e->sidedistx < e->sidedisty)
	{
		e->sidedistx += e->deltadistx;
		e->mapx += e->stepx;
		e->side = 0;
	}
	else
	{
		e->sidedisty += e->deltadisty;
		e->mapy += e->stepy;
		e->side = 1;
	}
}

void	perform_dda(t_engine *e)
{
	int		hit;
	char	c;

	hit = 0;
	e->hit_door = 0;
	while (!hit)
	{
		update_ray_step(e);
		c = e->data.map[e->mapy][e->mapx];
		if (c == '1')
		{
			hit = 1;
			e->hit_door = 0;
		}
		else if (c == 'D')
		{
			hit = 1;
			e->hit_door = 1;
		}
	}
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
