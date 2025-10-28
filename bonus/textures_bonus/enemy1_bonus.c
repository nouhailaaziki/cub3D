/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:11:08 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/10/23 13:31:36 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/launchpad_bonus.h"

int	load_enemy_textures(t_engine *engine)
{
	char	*frames[6];
	int		i;

	frames[0] = "./tex/fire1.png";
	frames[1] = "./tex/fire2.png";
	frames[2] = "./tex/fire3.png";
	frames[3] = "./tex/fire4.png";
	frames[4] = "./tex/fire5.png";
	frames[5] = "./tex/fire6.png";
	i = 0;
	while (i < 6)
	{
		engine->enemy_frames[i] = mlx_load_png(frames[i]);
		if (!engine->enemy_frames[i])
			return (mlx_delete_texture(engine->enemy_frames[i]), 1);
		i++;
	}
	return (0);
}

void	cleanup_enemy_textures(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (engine->enemy_frames[i])
			mlx_delete_texture(engine->enemy_frames[i]);
		i++;
	}
}

void	calculate_enemy_screen_position(t_engine *engine, t_pos_data *pos)
{
	double	camera_cord;
	double	enemy_pos_x;
	double	enemy_pos_y;

	enemy_pos_x = (pos->map_x + 0.5) - engine->player.posx;
	enemy_pos_y = (pos->map_y + 0.5) - engine->player.posy;
	camera_cord = 1.0 / (engine->player.planex * engine->player.diry
			- engine->player.dirx * engine->player.planey);
	pos->t_x = camera_cord * (engine->player.diry * enemy_pos_x
			- engine->player.dirx * enemy_pos_y);
	pos->t_y = camera_cord * (-engine->player.planey * enemy_pos_x
			+ engine->player.planex * enemy_pos_y);
}

void	calculate_enemy_sprite_data(double t_x, double t_y, t_sprite_data *sp)
{
	sp->height = (int)fabs(SCREEN_HEIGHT / t_y);
	sp->width = sp->height;
	sp->v_move_screen = (int)(SCREEN_HEIGHT * 0.5 / t_y);
	sp->draw_start_y = -sp->height / 2 + SCREEN_HEIGHT / 2
		+ sp->v_move_screen;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = sp->height / 2 + SCREEN_HEIGHT / 2
		+ sp->v_move_screen;
	if (sp->draw_end_y >= SCREEN_HEIGHT)
		sp->draw_end_y = SCREEN_HEIGHT - 1;
	sp->sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + t_x / t_y));
	sp->draw_start_x = -sp->width / 2 + sp->sprite_screen_x;
	if (sp->draw_start_x < 0)
		sp->draw_start_x = 0;
	sp->draw_end_x = sp->width / 2 + sp->sprite_screen_x;
	if (sp->draw_end_x >= SCREEN_WIDTH)
		sp->draw_end_x = SCREEN_WIDTH - 1;
}
