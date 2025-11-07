/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_textures2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:27:45 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/10/15 16:18:02 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

mlx_texture_t	*get_texture(t_engine *e, int t)
{
	if (t == TEX_DOOR)
		return (e->door);
	if (t == TEX_NORTH)
		return (e->no);
	if (t == TEX_SOUTH)
		return (e->so);
	if (t == TEX_EAST)
		return (e->ea);
	return (e->we);
}

void	calculate_texture_data(t_engine *e)
{
	if (e->side == 0)
		e->wall_x = e->player.posy + e->perpwalldist * e->raydiry;
	else
		e->wall_x = e->player.posx + e->perpwalldist * e->raydirx;
	e->wall_x -= floor(e->wall_x);
	e->tex_pos = (e->drawstart - SCREEN_HEIGHT / 2
			+ e->lineheight / 2) * (1.0 * e->current_tex->height
			/ e->lineheight);
}

void	draw_textured_line(t_engine *e, int x, int t)
{
	int	y;

	e->current_tex = get_texture(e, t);
	calculate_texture_data(e);
	y = e->drawstart;
	while (y <= e->drawend)
	{
		draw_textured_pixel(e, x, y, e->current_tex);
		e->tex_pos += 1.0 * e->current_tex->height / e->lineheight;
		y++;
	}
}
