/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 12:00:30 by zlayine           #+#    #+#             */
/*   Updated: 2020/01/13 15:00:01 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bfh	create_file_header(t_cube *tc)
{
	t_bfh			bfh;

	bfh.reversed1 = 0;
	bfh.reversed2 = 0;
	bfh.file_size = 2 + sizeof(t_bfh) + sizeof(t_bih) +
		tc->screen_width * tc->screen_height * 3;
	bfh.offset_bits = 0x36;
	return (bfh);
}

t_bih	create_info_header(t_cube *tc)
{
	t_bih			bih;

	bih.size = sizeof(t_bih);
	bih.width = tc->screen_width;
	bih.height = tc->screen_height;
	bih.planes = 1;
	bih.bit_count = 24;
	bih.compression = 0;
	bih.image_size = 0;
	bih.px_meter_x = 5000;
	bih.px_meter_y = 5000;
	bih.colors = 0;
	bih.important_colors = 0;
	return (bih);
}

void	save_bmp(t_cube *tc)
{
	t_bfh			bfh;
	t_bih			bih;
	int				fd;
	unsigned short	file_type;

	bfh = create_file_header(tc);
	bih = create_info_header(tc);
	fd = open("cub3D.bmp", O_WRONLY | O_TRUNC | O_CREAT);
	if (fd < 0)
		ft_error(4, tc);
	file_type = 0x4d42;
	write(fd, &file_type, sizeof(file_type));
	write(fd, &bfh, sizeof(bfh));
	write(fd, &bih, sizeof(bih));
	write_rgb(tc, fd);
	close(fd);
	free_game(tc);
	free_data(tc);
	exit(0);
}

void	write_rgb(t_cube *tc, int fd)
{
	unsigned char	rgb[tc->screen_width * tc->screen_height * 3];
	int				y;
	int				x;
	int				pos;
	int				pos_c;

	y = tc->screen_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < tc->screen_width)
		{
			pos = y * tc->screen_width + x;
			pos_c = (tc->screen_height - y - 1) * tc->screen_width + x;
			rgb[pos_c * 3] = (unsigned char)(tc->buffer[pos] & 0x0000FF);
			rgb[pos_c * 3 + 1] = (unsigned char)((tc->buffer[pos]
				& 0x00FF00) >> 8);
			rgb[pos_c * 3 + 2] = (unsigned char)(tc->buffer[pos] >> 16);
			x++;
		}
		y--;
	}
	write(fd, &rgb, tc->screen_width * tc->screen_height * 3);
}
