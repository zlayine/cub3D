/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:54:40 by zlayine           #+#    #+#             */
/*   Updated: 2020/01/13 14:29:46 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_res(char *line, t_cube *tc)
{
	char	*tmp;

	tmp = ft_strchr(line, ' ');
	if (!tmp)
		return (-1);
	tc->screen_width = ft_atoi(tmp + 1);
	if (tc->screen_width > 2560)
		tc->screen_width = 2560;
	tmp = ft_strchr(tmp + 1, ' ');
	if (!tmp)
		return (-1);
	tc->screen_height = ft_atoi(tmp + 1);
	if (tc->screen_height > 1440)
		tc->screen_height = 1440;
	if (tc->screen_width < 0 || tc->screen_height < 0)
		return (-1);
	return (1);
}

int		check_data(t_cube *tc, int step)
{
	int	i;

	if (step == 0 && (!tc->screen_width || !tc->screen_height ||
			tc->floor_color == -1 || !tc->sp_text ||
			tc->ceil_color == -1 || !tc->txt[3].path || !tc->txt[2].path ||
			!tc->txt[1].path || !tc->txt[0].path))
		return (-1);
	else if (step != 0)
	{
		if (!tc->map_width || !tc->map_height || !tc->map)
			return (-1);
		i = -1;
		while (++i < tc->map_width - 1)
			if (tc->map[0][i] != '1' || tc->map[tc->map_height - 1][i] != '1')
				return (-1);
		i = -1;
		while (++i < tc->map_height)
			if (tc->map[i][0] != '1' || tc->map[i][tc->map_width - 1] != '1')
				return (-1);
		if (step != 2)
			if (!tc->pos_x || !tc->pos_y)
				return (-1);
	}
	return (1);
}

int		set_col(char d, char *line, t_cube *tc)
{
	char	*tmp;
	int		i;
	int		color;
	int		check;

	i = 0;
	color = 0;
	if (!(tmp = ft_strchr(line, ' ')))
		return (-1);
	while (tmp)
	{
		if (!ft_isdigit(*(tmp + 1)) || (check = ft_atoi(tmp + 1)) > 255 ||
			check < 0)
			return (-1);
		color += check;
		if ((tmp = ft_strchr(tmp + 1, ',')))
			color = color << 8;
		i++;
	}
	if (d == 'F')
		tc->floor_color = color;
	else if (d == 'C')
		tc->ceil_color = color;
	return (i != 3 ? -1 : 1);
}

int		set_tex(char d, char *line, t_cube *tc)
{
	int		txt_num;
	char	*path;

	path = ft_strdup(ft_strchr(line, ' ') + 1);
	txt_num = -1;
	if (d == 'N')
		txt_num = 0;
	else if (d == 'S')
		txt_num = 2;
	else if (d == 'W')
		txt_num = 3;
	else if (d == 'E')
		txt_num = 1;
	if (!ft_strstr(path, ".png") || !file_exists(path))
		return (-1);
	if (txt_num >= 0)
		tc->txt[txt_num].path = path;
	else
		tc->sp_text = path;
	return (1);
}

int		set_dir(char d, t_cube *tc)
{
	if (d == 'N' || d == 'S')
	{
		tc->dir_x = 0;
		tc->dir_y = -1;
		tc->plane_x = 0.66;
		tc->plane_y = 0;
		if (d == 'S')
		{
			tc->dir_y = -tc->dir_y;
			tc->plane_x = -tc->plane_x;
		}
	}
	else if (d == 'W' || d == 'E')
	{
		tc->dir_x = 1;
		tc->dir_y = 0;
		tc->plane_x = 0;
		tc->plane_y = 0.66;
		if (d == 'W')
		{
			tc->dir_x = -tc->dir_x;
			tc->plane_y = -tc->plane_y;
		}
	}
	return (1);
}
