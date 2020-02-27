/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:53:48 by zlayine           #+#    #+#             */
/*   Updated: 2019/12/28 20:26:32 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(int error, t_cube *tc)
{
	if (error == 1)
	{
		ft_putstr("Error: Invalid map file name\n");
		ft_del(tc);
	}
	else if (error == 3)
	{
		ft_putstr("Error: Invalid arguments\n");
		ft_del(tc);
	}
	else if (error == 2 || error == 4 || error == 5)
	{
		if (error == 2)
			ft_putstr("Error: Invalid map data\n");
		else if (error == 4)
			ft_putstr("Error: Error file already exists\n");
		else if (error == 5)
			ft_putstr("Error: File not found\n");
		free_data(tc);
	}
	exit(0);
}
