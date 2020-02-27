/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:55:59 by zlayine           #+#    #+#             */
/*   Updated: 2019/12/28 11:03:06 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_map_line(char *line, t_cube *tc)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = malloc(sizeof(char) * (tc->map_width + 1))))
		return (0);
	tc->map[tc->map_height] = tmp;
	while (i < ft_strlen(line))
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	tc->map_height++;
	return (1);
}

char	**make_newdata(t_cube *tc)
{
	char	**tmp;
	int		i;

	i = -1;
	if (!(tmp = malloc(sizeof(char*) * (tc->map_height + 1))))
		return (NULL);
	while (++i < tc->map_height)
	{
		if (!(tmp[i] = malloc(sizeof(char) * (tc->map_width + 1))))
			return (NULL);
		ft_strlcpy(tmp[i], tc->map[i], tc->map_width + 1);
		free(tc->map[i]);
	}
	return (tmp);
}

int		set_map(char *line, t_cube *tc)
{
	char	**tmp;
	int		i;

	i = -1;
	if (check_data(tc, 0) < 0)
		return (-1);
	if (tc->map_width == 0)
		tc->map_width = ft_strlen(line);
	if (tc->map_height > 0)
	{
		if (!(tmp = make_newdata(tc)))
			return (-1);
		free(tc->map);
		tc->map = tmp;
	}
	else if (!(tc->map = malloc(sizeof(char*) * (tc->map_height + 1))))
		return (-1);
	if (!set_map_line(line, tc))
		return (-1);
	return (1);
}

t_cube	*read_map_file(char *file, t_cube *tc)
{
	int		fd;
	int		r;
	char	*line;
	t_parse	*tp;

	tp = malloc(sizeof(t_parse));
	init_cube(tc, tp);
	fd = open(file, O_RDONLY);
	r = 1;
	while (r == 1)
	{
		r = get_next_line(fd, &line);
		if (r < 0)
			ft_error(5, tc);
		parse_data(line, tc, tp);
		free(line);
	}
	free(tp);
	if (!tc->error && (set_cords(tc) < 0 || check_data(tc, 1) < 0))
		tc->error = 1;
	close(fd);
	return (tc);
}
