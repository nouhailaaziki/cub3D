/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:53:22 by noaziki           #+#    #+#             */
/*   Updated: 2025/09/06 21:03:55 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/launchpad.h"

void    set_player_direction(t_player *player, char c)
{
	if (c == 'N')
	{
		1 && (player->dirX = -1, player->dirY = 0);
		1 && (player->planeX = 0, player->planeY = 0.66);
	}
	else if (c == 'S')
	{
		1 && (player->dirX = 1, player->dirY = 0);
		1 && (player->planeX = 0, player->planeY = -0.66);
	}
	else if (c == 'E')
	{
		1 && (player->dirX = 0, player->dirY = 1);
		1 && (player->planeX = 0.66, player->planeY = 0);
	}
	else if (c == 'W')
	{
		1 && (player->planeX = -0.66, player->planeY = 0);
		1 && (player->dirX = 0, player->dirY = -1);
	}
}

void	init_data(t_engine *engine)
{
	int		i;
	int		j;
	char	**map;

	1 && (i = 0, map = engine->data.map);
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				engine->player.posX = i + 0.5;
				engine->player.posY = j + 0.5;
				set_player_direction(&engine->player, map[i][j]);
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

// void draw_scene(t_engine *engine)
// {
//     for (int x = 0; x < SCREEN_WIDTH; x++)
//     {
//         // 1. Calculate ray position & direction
//         // 2. DDA until wall hit
//         // 3. Calculate wall height
//         // 4. Draw vertical line (ceiling, wall, floor)
//     }
//     // Push image to window
//     mlx_image_to_window(engine->mlx, engine->image, 0, 0);
// }


int	master(t_engine *engine)
{
	init_data(engine);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	engine->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT,
	"Welcome to SOLIDANGLE's game!", false);
	if (!engine->mlx)
		return (mlx_strerror(mlx_errno), 1);
	engine->image = mlx_new_image(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!engine->image
		|| mlx_image_to_window(engine->mlx, engine->image, 0, 0) == -1)
	{
		mlx_close_window(engine->mlx);
		return (mlx_strerror(mlx_errno), 1);
	}
	return (0);
}