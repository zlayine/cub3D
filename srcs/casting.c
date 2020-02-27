/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:53:52 by zlayine           #+#    #+#             */
/*   Updated: 2019/12/26 18:34:08 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	check_steps(t_cube *tc)
{
	tc->sray.step_x = 1;
	if (tc->sray.dir_x < 0)
	{
		tc->sray.step_x = -1;
		tc->sray.side_dist_x = (tc->pos_x - tc->sray.map_x) *
			tc->sray.delta_dist_x;
	}
	else
		tc->sray.side_dist_x = (tc->sray.map_x + 1.0 - tc->pos_x)
			* tc->sray.delta_dist_x;
	if (tc->sray.dir_y < 0)
	{
		tc->sray.step_y = -1;
		tc->sray.side_dist_y = (tc->pos_y - tc->sray.map_y) *
			tc->sray.delta_dist_y;
	}
	else
	{
		tc->sray.step_y = 1;
		tc->sray.side_dist_y = (tc->sray.map_y + 1.0 - tc->pos_y)
			* tc->sray.delta_dist_y;
	}
	tc->sray = check_hit(tc);
	return (check_sides(tc));
}

t_ray	check_sides(t_cube *tc)
{
	if (tc->sray.side == 0)
		tc->sray.wall_dist = (tc->sray.map_x - tc->pos_x + (1 - tc->sray.step_x)
				/ 2) / tc->sray.dir_x;
	else
		tc->sray.wall_dist = (tc->sray.map_y - tc->pos_y + (1 - tc->sray.step_y)
				/ 2) / tc->sray.dir_y;
	if (tc->sray.side == 0)
		tc->sray.wall_x = tc->pos_y + tc->sray.wall_dist * tc->sray.dir_y;
	else
		tc->sray.wall_x = tc->pos_x + tc->sray.wall_dist * tc->sray.dir_x;
	tc->sray.wall_x -= floor((tc->sray.wall_x));
	tc->sray.text_x = (int)(tc->sray.wall_x * (double)tc->txt[0].width);
	if (tc->sray.side == 0 && tc->sray.dir_x > 0)
		tc->sray.text_x = tc->txt[0].width - tc->sray.text_x - 1;
	if (tc->sray.side == 1 && tc->sray.dir_y < 0)
		tc->sray.text_x = tc->txt[0].width - tc->sray.text_x - 1;
	return (tc->sray);
}

t_ray	check_hit(t_cube *tc)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (tc->sray.side_dist_x < tc->sray.side_dist_y)
		{
			tc->sray.side_dist_x += tc->sray.delta_dist_x;
			tc->sray.map_x += tc->sray.step_x;
			tc->sray.side = 0;
		}
		else
		{
			tc->sray.side_dist_y += tc->sray.delta_dist_y;
			tc->sray.map_y += tc->sray.step_y;
			tc->sray.side = 1;
		}
		if (tc->map[tc->sray.map_y][tc->sray.map_x] == '1')
			hit = 1;
	}
	return (tc->sray);
}
