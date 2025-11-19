/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:47:07 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 20:47:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	load_textures(t_engine *engine)
{
	engine->no = mlx_load_png(engine->data.no);
	engine->so = mlx_load_png(engine->data.so);
	engine->ea = mlx_load_png(engine->data.ea);
	engine->we = mlx_load_png(engine->data.we);
	if (engine->no == NULL || engine->so == NULL
		|| engine->ea == NULL || engine->we == NULL)
	{
		if (engine->no)
			mlx_delete_texture(engine->no);
		if (engine->so)
			mlx_delete_texture(engine->so);
		if (engine->ea)
			mlx_delete_texture(engine->ea);
		if (engine->we)
			mlx_delete_texture(engine->we);
		return (error_exit("Failed to load texture"), 1);
	}
	return (0);
}

int	get_texture_index(t_engine *engine)
{
	if (engine->side == 0)
	{
		if (engine->raydirx > 0)
			return (TEX_EAST);
		else
			return (TEX_WEST);
	}
	else
	{
		if (engine->raydiry > 0)
			return (TEX_SOUTH);
		else
			return (TEX_NORTH);
	}
}

void	draw_textured_pixel(t_engine *engine, int x, int y,
		mlx_texture_t *tex)
{
	t_tex_data	tex_data;
	uint8_t		*pixel;
	uint32_t	color;

	tex_data.tex_x = (int)(engine->wall_x * tex->width);
	tex_data.tex_y = (int)engine->tex_pos;
	if (tex_data.tex_x < 0 || tex_data.tex_x >= (int)tex->width
		|| tex_data.tex_y < 0 || tex_data.tex_y >= (int)tex->height)
		return ;
	pixel = &tex->pixels[(tex_data.tex_y * tex->width
			+ tex_data.tex_x) * 4];
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	mlx_put_pixel(engine->image, x, y, color);
}

void	cleanup_textures(t_engine *engine)
{
	if (engine->no)
		mlx_delete_texture(engine->no);
	if (engine->so)
		mlx_delete_texture(engine->so);
	if (engine->ea)
		mlx_delete_texture(engine->ea);
	if (engine->we)
		mlx_delete_texture(engine->we);
}
