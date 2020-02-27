/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:00:05 by zlayine           #+#    #+#             */
/*   Updated: 2020/01/15 10:41:26 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_camera(t_cube *tc)
{
	t_line	sline;
	double	camera_x;
	int		x;

	x = -1;
	while (++x < tc->screen_width)
	{
		camera_x = 2 * x / (double)tc->screen_width - 1;
		tc->sray.x = x;
		tc->sray.dir_x = tc->dir_x + tc->plane_x * camera_x;
		tc->sray.dir_y = tc->dir_y + tc->plane_y * camera_x;
		tc->sray.map_x = (int)tc->pos_x;
		tc->sray.map_y = (int)tc->pos_y;
		tc->sray.delta_dist_x = fabs(1 / tc->sray.dir_x);
		tc->sray.delta_dist_y = fabs(1 / tc->sray.dir_y);
		tc->sray = check_steps(tc);
		tc->zbuffer[x] = tc->sray.wall_dist;
		sline.x0 = x;
		sline.x1 = x;
		draw_wall(sline, tc);
	}
}

void	redraw(t_cube *tc)
{
	int		x;

	if (!tc->save)
		mlx_clear_window(tc->mlx, tc->window);
	calc_camera(tc);
	x = -1;
	sort_sprites(tc);
	while (++x < tc->num_sprites)
		sprite_calc(tc, x);
	if (tc->save)
		save_bmp(tc);
	else
		mlx_put_image_to_window(tc->mlx, tc->window, tc->img, 0, 0);
}

void	start_game(t_cube *tc)
{
	int	bpp;
	int	sl;
	int	endian;

	tc->mlx = mlx_init();
	if (!tc->save)
		tc->window = mlx_new_window(tc->mlx, tc->screen_width,
			tc->screen_height, "cub3D");
	tc->img = mlx_new_image(tc->mlx, tc->screen_width, tc->screen_height);
	tc->buffer = (int*)mlx_get_data_addr(tc->img, &bpp, &sl, &endian);
	load_textures(tc);
	redraw(tc);
	if (!tc->save)
	{
		mlx_hook(tc->window, 2, 0, key_deal, tc);
		mlx_hook(tc->window, 17, 1L << 17, exit_window, tc);
	}
	if (!tc->save)
		mlx_loop(tc->mlx);
}
