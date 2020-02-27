/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:02:44 by zlayine           #+#    #+#             */
/*   Updated: 2019/12/28 20:26:01 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_cube *tc)
{
	int	i;

	ft_del(tc->buffer);
	i = -1;
	while (++i < 4)
		ft_del(tc->txt[i].px);
}

int		exit_window(t_cube *tc)
{
	mlx_clear_window(tc->mlx, tc->window);
	mlx_destroy_window(tc->mlx, tc->window);
	free_game(tc);
	free_data(tc);
	exit(0);
}

int		is_allowed(char c)
{
	if (c == '1' || c == '0' || c == '2' || c == 'N' ||
			c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	free_data(t_cube *tc)
{
	int	i;

	ft_del(tc->sp);
	i = -1;
	while (++i < 4)
		if (tc->txt)
			ft_del(tc->txt[i].path);
	ft_del(tc->txt);
	ft_del(tc->sp_text);
	if (tc->error == 1)
		ft_del(tc->zbuffer);
	i = -1;
	while (++i < tc->map_height)
		if (tc->map)
			ft_del(tc->map[i]);
	if (i)
		ft_del(tc->map);
	ft_del(tc);
}

int		file_exists(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
		return (0);
	return (1);
}
