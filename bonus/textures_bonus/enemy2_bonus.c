/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:02:25 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/11/19 18:49:01 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad_bonus.h"

void	draw_enemy_pixel(t_engine *e, t_draw_enemy d)
{
	uint8_t			*p;
	uint32_t		color;
	mlx_texture_t	*tex;

	tex = e->enemy_frames[(int)(e->animation_time * 5) % 6];
	p = &tex->pixels[(d.tex_y * tex->width + d.tex_x) * 4];
	color = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	if ((color & 0x00FFFFFF) != 0)
		mlx_put_pixel(e->image, d.x, d.y, color);
}

void	draw_enemy_column(t_engine *e, t_sprite_data *sp, int stripe_x)
{
	int				y;
	int				d;
	int				tex_x;
	t_draw_enemy	dat;
	mlx_texture_t	*tex;

	tex = e->enemy_frames[(int)(e->animation_time * 5) % 6];
	tex_x = (int)((stripe_x - (-sp->width / 2 + sp->sprite_screen_x))
			* tex->width / sp->width);
	if (tex_x < 0 || tex_x >= (int)tex->width)
		return ;
	y = sp->draw_start_y;
	while (y < sp->draw_end_y)
	{
		d = (y - sp->v_move_screen) * 256 - SCREEN_HEIGHT * 128
			+sp->height * 128;
		dat.tex_x = tex_x;
		dat.tex_y = ((d * tex->height) / sp->height) / 256;
		dat.x = stripe_x;
		dat.y = y;
		draw_enemy_pixel(e, dat);
		y++;
	}
}

void	render_enemy_at_position(t_engine *engine, int map_x, int map_y)
{
	t_pos_data		pos;
	t_sprite_data	sprite;
	int				stripe_x;

	pos.map_x = map_x;
	pos.map_y = map_y;
	calculate_enemy_screen_position(engine, &pos);
	if (pos.t_y <= 0)
		return ;
	calculate_enemy_sprite_data(pos.t_x, pos.t_y, &sprite);
	stripe_x = sprite.draw_start_x;
	while (stripe_x < sprite.draw_end_x)
	{
		if (pos.t_y > 0 && stripe_x > 0 && stripe_x < SCREEN_WIDTH
			&& pos.t_y < engine->buffer[stripe_x])
			draw_enemy_column(engine, &sprite, stripe_x);
		stripe_x++;
	}
}

void	render_all_enemies(t_engine *engine)
{
	int	y;
	int	x;

	y = 0;
	while (engine->data.map[y])
	{
		x = 0;
		while (engine->data.map[y][x])
		{
			if (engine->data.map[y][x] == 'M')
				render_enemy_at_position(engine, x, y);
			x++;
		}
		y++;
	}
}

void	update_enemies_hook(void *param)
{
	t_engine	*engine;
	double		current_time;

	engine = (t_engine *)param;
	current_time = mlx_get_time();
	engine->animation_time = current_time;
}
