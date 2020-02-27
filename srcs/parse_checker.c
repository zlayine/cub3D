/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 20:17:15 by zlayine           #+#    #+#             */
/*   Updated: 2019/12/28 11:42:31 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_map_splits(char *line, t_cube *tc)
{
	if (tc->map_height && line[0] == '\0' && check_data(tc, 2) < 0)
		return (1);
	return (0);
}

int		check_parse(char *line, t_cube *tc, t_parse *tp)
{
	if (line[0] == 'R' && tp->res)
		return (-1);
	else if (line[0] == 'N' && line[1] == 'O' && tp->no)
		return (-1);
	else if (line[0] == 'S' && line[1] == 'O' && tp->so)
		return (-1);
	else if (line[0] == 'W' && line[1] == 'E' && tp->we)
		return (-1);
	else if (line[0] == 'E' && line[1] == 'A' && tp->ea)
		return (-1);
	else if (line[0] == 'S' && tp->s)
		return (-1);
	else if (line[0] == 'F' && tp->f)
		return (-1);
	else if (line[0] == 'C' && tp->c)
		return (-1);
	else if (check_map_splits(line, tc))
		return (-1);
	return (parse_setter(line, tp));
}

int		parse_setter(char *line, t_parse *tp)
{
	if (line[0] == 'R')
		tp->res = 1;
	else if (line[0] == 'N' && line[1] == 'O')
		tp->no = 1;
	else if (line[0] == 'S' && line[1] == 'O')
		tp->so = 1;
	else if (line[0] == 'W' && line[1] == 'E')
		tp->we = 1;
	else if (line[0] == 'E' && line[1] == 'A')
		tp->ea = 1;
	else if (line[0] == 'S')
		tp->s = 1;
	else if (line[0] == 'F')
		tp->f = 1;
	else if (line[0] == 'C')
		tp->c = 1;
	return (0);
}
