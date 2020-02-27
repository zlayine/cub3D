/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:04:36 by zlayine           #+#    #+#             */
/*   Updated: 2020/01/13 19:45:07 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_cube	*tc;

	tc = (t_cube*)malloc(sizeof(t_cube));
	tc->save = 0;
	if (argc == 3 && ft_strcmp("--save", argv[2]) == 0)
	{
		tc->save = 1;
		argc--;
	}
	if (argc == 2)
	{
		if (!ft_strstr(argv[1], ".cub"))
			ft_error(1, tc);
		else
			tc = read_map_file(argv[1], tc);
		if (tc->error != 0)
			ft_error(2, tc);
		else
			start_game(tc);
	}
	else
		ft_error(3, tc);
	return (0);
}
