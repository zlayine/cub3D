/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:53:55 by zlayine           #+#    #+#             */
/*   Updated: 2020/01/13 14:34:52 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_w_s(t_cube *tc, int key)
{
	int move;

	if (key == 13)
		move = 1;
	else
		move = -1;
	tc->pos_x = tc->pos_x + move * tc->dir_x * tc->move_speed;
	tc->pos_y = tc->pos_y + move * tc->dir_y * tc->move_speed;
	if (tc->map[(int)(tc->pos_y + move * tc->dir_y * tc->move_speed)][(int)
			(tc->pos_x + move * tc->dir_x * tc->move_speed)] == '1')
		tc->pos_x = tc->pos_x - move * tc->dir_x * tc->move_speed;
	if (tc->map[(int)(tc->pos_y + move * tc->dir_y * tc->move_speed)][(int)
			(tc->pos_x + move * tc->dir_x * tc->move_speed)] == '1')
		tc->pos_y = tc->pos_y - move * tc->dir_y * tc->move_speed;
}

void	move_q_d(t_cube *tc, int key)
{
	int	step_y;
	int	step_x;

	if (key == 0)
	{
		step_x = 1;
		step_y = 1;
		if (tc->dir_x != 0)
			step_y = -1;
	}
	else
	{
		step_x = -1;
		step_y = -1;
		if (tc->dir_x != 0)
			step_y = 1;
	}
	tc->pos_x = tc->pos_x + tc->dir_y * step_x * tc->move_speed;
	tc->pos_y = tc->pos_y + tc->dir_x * step_y * tc->move_speed;
	if (tc->map[(int)(tc->pos_y + tc->dir_x * step_y * tc->move_speed)][(int)
			(tc->pos_x + tc->dir_y * step_x * tc->move_speed)] == '1')
		tc->pos_x = tc->pos_x - tc->dir_y * step_x * tc->move_speed;
	if (tc->map[(int)(tc->pos_y + tc->dir_x * step_y * tc->move_speed)][(int)
			(tc->pos_x + tc->dir_y * step_x * tc->move_speed)] == '1')
		tc->pos_y = tc->pos_y - tc->dir_x * step_y * tc->move_speed;
}

void	rotate_dir(t_cube *tc, int key)
{
	double	old_dir_x;
	double	old_plane_x;
	int		rot;

	if (key == 124)
		rot = 1;
	else
		rot = -1;
	old_dir_x = tc->dir_x;
	tc->dir_x = tc->dir_x * cos(rot * tc->rot_speed) - tc->dir_y * sin(rot *
			tc->rot_speed);
	tc->dir_y = old_dir_x * sin(rot * tc->rot_speed) + tc->dir_y * cos(rot *
			tc->rot_speed);
	old_plane_x = tc->plane_x;
	tc->plane_x = tc->plane_x * cos(rot * tc->rot_speed) - tc->plane_y *
		sin(rot * tc->rot_speed);
	tc->plane_y = old_plane_x * sin(rot * tc->rot_speed) + tc->plane_y *
		cos(rot * tc->rot_speed);
}

int		key_deal(int key, t_cube *tc)
{
	if (key == 53)
		exit_window(tc);
	if (key == 13 || key == 1)
		move_w_s(tc, key);
	if (key == 2 || key == 0)
		move_q_d(tc, key);
	if (key == 124 || key == 123)
		rotate_dir(tc, key);
	redraw(tc);
	return (0);
}
