/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:53:45 by zlayine           #+#    #+#             */
/*   Updated: 2020/01/13 15:04:04 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_cube *tc)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		tc->txt[i].img = mlx_png_file_to_image(tc->mlx, tc->txt[i].path,
					&tc->txt[i].width, &tc->txt[i].height);
		parse_image(tc, i, 1);
		i++;
	}
	i = -1;
	while (++i < tc->num_sprites)
	{
		tc->sp[i].txt.img = mlx_png_file_to_image(tc->mlx, tc->sp_text,
					&tc->sp[i].txt.width, &tc->sp[i].txt.height);
		parse_image(tc, i, 0);
	}
}

void	parse_image(t_cube *tc, int i, int action)
{
	if (action)
	{
		tc->txt[i].img_data = mlx_get_data_addr(tc->txt[i].img, &tc->txt[i].bpp,
				&tc->txt[i].line_size, &tc->txt[i].endian);
		parse_colors(&tc->txt[i]);
	}
	else
	{
		tc->sp[i].txt.img_data = mlx_get_data_addr(tc->sp[i].txt.img,
				&tc->sp[i].txt.bpp, &tc->sp[i].txt.line_size,
				&tc->sp[i].txt.endian);
		parse_colors(&tc->sp[i].txt);
	}
}

int		hex_color(int n1, int n2, int n3)
{
	int	color;

	color = (unsigned char)n1;
	color = color << 8;
	color += (unsigned char)n2;
	color = color << 8;
	color += (unsigned char)n3;
	return (color);
}

void	parse_colors(t_text *txt)
{
	int	line;
	int	color;
	int	i;

	line = 0;
	txt->px = malloc(sizeof(t_pixel) * (txt->height * (txt->line_size / 4) +
				txt->width));
	while (line < txt->height)
	{
		i = 0;
		while (i < txt->line_size)
		{
			color = hex_color((unsigned char)txt->img_data[i + 2],
					(unsigned char)txt->img_data[i + 1],
					(unsigned char)txt->img_data[i]);
			txt->px[line * txt->width + (i / 4)].x = i / 4;
			txt->px[line * txt->width + (i / 4)].y = line;
			txt->px[line * txt->width + (i / 4)].color = color;
			i += 4;
		}
		txt->img_data = txt->img_data + txt->line_size;
		line++;
	}
}

int		get_texture(t_cube *tc)
{
	double	rx;
	double	ry;
	int		side;

	rx = tc->sray.dir_x;
	ry = tc->sray.dir_y;
	side = tc->sray.side;
	if (rx >= 0)
	{
		if (side && ry >= 0)
			return (0);
		else if (side && ry < 0)
			return (2);
		return (3);
	}
	else
	{
		if (side && ry >= 0)
			return (0);
		else if (side && ry < 0)
			return (2);
		return (1);
	}
}
