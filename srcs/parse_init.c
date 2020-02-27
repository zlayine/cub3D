/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:54:37 by zlayine           #+#    #+#             */
/*   Updated: 2019/12/29 12:07:52 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_sprite(int x, int y, t_cube *tc)
{
	t_sprite	*tmp;
	int			i;

	i = 0;
	if (tc->num_sprites > 0)
	{
		if (!(tmp = malloc(sizeof(t_sprite) * (tc->num_sprites + 1))))
			return (-1);
		while (i < tc->num_sprites)
		{
			tmp[i].sprite_x = tc->sp[i].sprite_x;
			tmp[i].sprite_y = tc->sp[i].sprite_y;
			i++;
		}
		free(tc->sp);
		tc->sp = tmp;
	}
	else if (!(tc->sp = malloc(sizeof(t_sprite))))
		return (-1);
	tc->sp[tc->num_sprites].sprite_x = x;
	tc->sp[tc->num_sprites].sprite_y = y;
	tc->num_sprites++;
	return (1);
}

int		set_position(t_cube *tc, int x, int y)
{
	int		pos;
	double	inc;

	inc = 0;
	if (tc->pos_x != 0)
		return (-1);
	if (x < tc->screen_width / 2 && y < tc->screen_height / 2)
		inc = 0.5;
	else if (x > tc->screen_width / 2 && y > tc->screen_height / 2)
		inc = -0.5;
	tc->pos_x = x + inc;
	tc->pos_y = y + inc;
	pos = set_dir(tc->map[y][x], tc);
	return (pos);
}

int		set_cords(t_cube *tc)
{
	int	x;
	int	y;

	y = -1;
	if (!(tc->zbuffer = malloc(sizeof(double) * tc->screen_width)))
		return (-1);
	while (++y < tc->map_height)
	{
		x = -1;
		while (++x < tc->map_width)
		{
			if (!is_allowed(tc->map[y][x]))
				return (-1);
			if (ft_isalpha(tc->map[y][x]))
				if (set_position(tc, x, y) < 0)
					return (-1);
			if (tc->map[y][x] == '2')
			{
				if (set_sprite(x, y, tc) < 0)
					return (-1);
			}
		}
	}
	return (1);
}

void	parse_data(char *line, t_cube *tc, t_parse *tp)
{
	int	r;

	r = check_parse(line, tc, tp);
	if (r == -1)
		tc->error = 2;
	if (line[0] == 'R')
		r = set_res(line, tc);
	else if (line[0] == 'N' && line[1] == 'O')
		r = set_tex('N', line, tc);
	else if (line[0] == 'S' && line[1] == 'O')
		r = set_tex('S', line, tc);
	else if (line[0] == 'W' && line[1] == 'E')
		r = set_tex('W', line, tc);
	else if (line[0] == 'E' && line[1] == 'A')
		r = set_tex('E', line, tc);
	else if (line[0] == 'S')
		r = set_tex('O', line, tc);
	else if (line[0] == 'F')
		r = set_col('F', line, tc);
	else if (line[0] == 'C')
		r = set_col('C', line, tc);
	else if (is_allowed(line[0]))
		r = set_map(line, tc);
	if (r == -1)
		tc->error = 2;
}

void	init_cube(t_cube *tc, t_parse *tp)
{
	tc->num_sprites = 0;
	tc->map_width = 0;
	tc->map_height = 0;
	tc->error = 0;
	tc->floor_color = -1;
	tc->ceil_color = -1;
	tc->screen_height = 0;
	tc->screen_width = 0;
	tc->pos_x = 0;
	tc->pos_y = 0;
	tc->move_speed = 0.15;
	tc->rot_speed = 0.05;
	tc->txt = malloc(sizeof(t_text) * 4);
	tp->map = 0;
	tp->res = 0;
	tp->no = 0;
	tp->so = 0;
	tp->we = 0;
	tp->ea = 0;
	tp->s = 0;
	tp->f = 0;
	tp->c = 0;
}
