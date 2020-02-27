/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:01:11 by zlayine           #+#    #+#             */
/*   Updated: 2020/01/13 14:22:46 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_line sline, t_cube *tc, int txt)
{
	double	prev_x;
	double	prev_y;
	int		text_y;
	int		d;
	int		i;

	prev_x = sline.x0;
	prev_y = sline.y0;
	i = 0;
	while (++i <= sline.step)
	{
		if (txt)
		{
			sline.text_s = get_texture(tc);
			d = (i + sline.y0) * 256 - tc->screen_height * 128 +
				sline.line_height * 128;
			text_y = ((d * tc->txt[sline.text_s].height) /
				sline.line_height) / 256;
			sline.color = tc->txt[sline.text_s].px[tc->txt[sline.text_s].height
				* text_y + tc->sray.text_x].color;
		}
		tc->buffer[(int)(prev_x + tc->screen_width * prev_y)] = sline.color;
		prev_x = prev_x + sline.xinc;
		prev_y = prev_y + sline.yinc;
	}
}

void	dda_algo(t_line sline, t_cube *tc, int txt)
{
	sline.dx = sline.x1 - sline.x0;
	sline.dy = sline.y1 - sline.y0;
	if (abs(sline.dx) > abs(sline.dy))
		sline.step = abs(sline.dx);
	else
		sline.step = abs(sline.dy);
	sline.xinc = (double)sline.dx / (double)sline.step;
	sline.yinc = (double)sline.dy / (double)sline.step;
	draw_line(sline, tc, txt);
}

void	draw_wall(t_line sline, t_cube *tc)
{
	int	start;

	if (tc->sray.wall_dist == 0)
		sline.line_height = tc->screen_height - 1;
	else
		sline.line_height = (int)(tc->screen_height / tc->sray.wall_dist);
	sline.y0 = -sline.line_height / 2 + tc->screen_height / 2;
	if (sline.y0 < 0)
		sline.y0 = 0;
	sline.y1 = sline.line_height / 2 + tc->screen_height / 2;
	if (sline.y1 >= tc->screen_height)
		sline.y1 = tc->screen_height - 1;
	start = sline.y0;
	sline.color = 0xFFFFFF;
	dda_algo(sline, tc, 1);
	sline.y0 = sline.y1;
	sline.y1 = tc->screen_height - 1;
	sline.color = tc->floor_color;
	dda_algo(sline, tc, 0);
	sline.y0 = 0;
	sline.y1 = start;
	sline.color = tc->ceil_color;
	dda_algo(sline, tc, 0);
}
