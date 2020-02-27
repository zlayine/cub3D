/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:56:51 by zlayine           #+#    #+#             */
/*   Updated: 2020/01/15 11:22:21 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			sprite_draw(t_cube *tc, t_sprite ts)
{
	int	color;
	int	d;
	int	y;
	int	stripe;

	stripe = ts.start_x;
	while (stripe < ts.end_x)
	{
		ts.text_x = (int)(256 * (stripe - (-ts.sprite_width / 2 +
			ts.sprite_screen_x)) * ts.txt.width / ts.sprite_width) / 256;
		if (ts.transform_y > 0 && stripe > 0 && stripe < tc->screen_width &&
				ts.transform_y < tc->zbuffer[stripe])
		{
			y = ts.start_y - 1;
			while (++y < ts.end_y)
			{
				d = y * 256 - tc->screen_height * 128 + ts.sprite_height * 128;
				ts.text_y = ((d * ts.txt.height) / ts.sprite_height) / 256;
				color = ts.txt.px[ts.txt.width * ts.text_y + ts.text_x].color;
				if (color & 0x00FFFFFF)
					tc->buffer[stripe + tc->screen_width * y] = color;
			}
		}
		stripe++;
	}
}

void			sprite_calc(t_cube *tc, int sprt_num)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = tc->sp[sprt_num].sprite_x - tc->pos_x + 0.5;
	sprite_y = tc->sp[sprt_num].sprite_y - tc->pos_y + 0.5;
	inv_det = 1.0 / (tc->plane_x * tc->dir_y - tc->dir_x * tc->plane_y);
	tc->sp[sprt_num].transform_x = inv_det * (tc->dir_y * sprite_x -
			tc->dir_x * sprite_y);
	tc->sp[sprt_num].transform_y = inv_det * (-tc->plane_y * sprite_x +
			tc->plane_x * sprite_y);
	tc->sp[sprt_num].sprite_screen_x = (int)((tc->screen_width / 2) *
			(1 + tc->sp[sprt_num].transform_x / tc->sp[sprt_num].transform_y));
	tc->sp[sprt_num].sprite_height = abs((int)(tc->screen_height /
				tc->sp[sprt_num].transform_y));
	sprite_calc_dimension(tc, sprt_num);
}

void			sprite_calc_dimension(t_cube *tc, int sprt_num)
{
	tc->sp[sprt_num].start_y = -tc->sp[sprt_num].sprite_height / 2 +
		tc->screen_height / 2;
	if (tc->sp[sprt_num].start_y < 0)
		tc->sp[sprt_num].start_y = 0;
	tc->sp[sprt_num].end_y = tc->sp[sprt_num].sprite_height / 2 +
		tc->screen_height / 2;
	if (tc->sp[sprt_num].end_y >= tc->screen_height)
		tc->sp[sprt_num].end_y = tc->screen_height - 1;
	tc->sp[sprt_num].sprite_width = abs((int)(tc->screen_height /
				tc->sp[sprt_num].transform_y));
	tc->sp[sprt_num].start_x = -tc->sp[sprt_num].sprite_width / 2 +
		tc->sp[sprt_num].sprite_screen_x;
	if (tc->sp[sprt_num].start_x < 0)
		tc->sp[sprt_num].start_x = 0;
	tc->sp[sprt_num].end_x = tc->sp[sprt_num].sprite_width / 2 +
		tc->sp[sprt_num].sprite_screen_x;
	if (tc->sp[sprt_num].end_x >= tc->screen_width)
		tc->sp[sprt_num].end_x = tc->screen_width - 1;
	sprite_draw(tc, tc->sp[sprt_num]);
}

static double	calc_dist(int pos, t_cube *tc)
{
	double	x;
	double	y;

	x = (tc->pos_x - tc->sp[pos].sprite_x) * (tc->pos_x - tc->sp[pos].sprite_x);
	y = (tc->pos_y - tc->sp[pos].sprite_y) * (tc->pos_y - tc->sp[pos].sprite_y);
	return (x + y);
}

void			sort_sprites(t_cube *tc)
{
	int			i;
	int			j;
	double		dist1;
	double		dist2;
	t_sprite	tmp;

	i = -1;
	while (++i < tc->num_sprites - 1)
	{
		j = i;
		dist1 = calc_dist(i, tc);
		while (++j < tc->num_sprites)
		{
			dist2 = calc_dist(j, tc);
			if (dist1 < dist2)
			{
				tmp = tc->sp[i];
				tc->sp[i] = tc->sp[j];
				tc->sp[j] = tmp;
			}
		}
	}
}
