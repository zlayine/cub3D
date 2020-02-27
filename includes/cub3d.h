/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:20:14 by zlayine           #+#    #+#             */
/*   Updated: 2020/01/15 11:01:11 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# include <math.h>

typedef struct	s_ray
{
	double	dir_x;
	double	dir_y;

	int		map_x;
	int		map_y;

	int		step_x;
	int		step_y;

	int		side;

	double	side_dist_x;
	double	side_dist_y;

	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;

	double	wall_x;
	int		text_x;

	int		x;
}				t_ray;

typedef struct	s_line
{
	int		x0;
	int		y0;

	int		x1;
	int		y1;

	int		dx;
	int		dy;

	int		step;

	double	xinc;
	double	yinc;

	int		text_s;

	int		color;
	int		line_height;
}				t_line;

typedef struct	s_pixel
{
	int		x;
	int		y;
	int		color;
}				t_pixel;

typedef struct	s_text
{
	char	*path;
	int		width;
	int		height;
	int		line_size;
	int		bpp;
	void	*img;
	int		endian;
	char	*img_data;
	t_pixel	*px;
}				t_text;

typedef struct	s_sprite
{
	int		sprite_x;
	int		sprite_y;

	int		start_x;
	int		end_x;

	int		start_y;
	int		end_y;

	int		text_x;
	int		text_y;

	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;

	double	transform_x;
	double	transform_y;

	t_text	txt;
}				t_sprite;

typedef struct	s_cube
{
	void		*mlx;
	void		*window;

	int			screen_width;
	int			screen_height;

	int			map_width;
	int			map_height;

	int			num_sprites;

	double		pos_x;
	double		pos_y;

	double		dir_x;
	double		dir_y;

	double		plane_x;
	double		plane_y;

	double		rot_speed;
	double		move_speed;

	char		*sp_text;

	char		**map;

	int			floor_color;
	int			ceil_color;

	t_ray		sray;
	t_text		*txt;

	t_sprite	*sp;
	double		*zbuffer;

	int			*buffer;

	void		*img;
	int			error;
	int			save;
}				t_cube;

typedef struct	s_bfh
{
	unsigned int	file_size;
	unsigned short	reversed1;
	unsigned short	reversed2;
	unsigned int	offset_bits;
}				t_bfh;

typedef struct	s_bih
{
	unsigned int	size;
	int				width;
	int				height;
	unsigned short	planes;
	unsigned short	bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	int				px_meter_x;
	int				px_meter_y;
	unsigned int	colors;
	unsigned int	important_colors;
}				t_bih;

typedef struct	s_parse
{
	int		res;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		s;
	int		f;
	int		c;
	int		map;
}				t_parse;

int				set_res(char *line, t_cube *tc);
int				check_data(t_cube *tc, int step);
int				set_tex(char d, char *line, t_cube *tc);
int				set_col(char d, char *line, t_cube *tc);
int				set_map_line(char *line, t_cube *tc);
char			*ft_strnew(void *dest, void *src);
char			**make_newdata(t_cube *tc);
int				set_map(char *line, t_cube *tc);
int				set_dir(char d, t_cube *tc);
int				set_sprite(int x, int y, t_cube *tc);
int				is_allowed(char c);
int				set_position(t_cube *tc, int x, int y);
int				set_cords(t_cube *tc);
void			parse_data(char *line, t_cube *tc, t_parse *tp);
void			init_cube(t_cube *tc, t_parse *tp);
void			print_data(t_cube *tc);
void			free_data(t_cube *tc);
t_cube			*read_map_file(char *file, t_cube *tc);
void			free_game(t_cube *tc);
int				exit_window(t_cube *tc);
void			draw_line(t_line sline, t_cube *tc, int txt);
void			dda_algo(t_line sline, t_cube *tc, int txt);
void			draw_wall(t_line sline, t_cube *tc);
t_ray			check_hit(t_cube *tc);
t_ray			check_sides(t_cube *tc);
t_ray			check_steps(t_cube *tc);
void			parse_colors(t_text *txt);
void			parse_image(t_cube *tc, int i, int action);
int				get_texture(t_cube *tc);
int				hex_color(int n1, int n2, int n3);
void			load_textures(t_cube *tc);
void			redraw(t_cube *tc);
void			start_game(t_cube *tc);
void			move_w_s(t_cube *tc, int key);
void			move_q_d(t_cube *tc, int key);
void			rotate_dir(t_cube *tc, int key);
int				key_deal(int key, t_cube *tc);
void			sprite_draw(t_cube *tc, t_sprite ts);
void			sprite_calc(t_cube *tc, int sprt_num);
void			ft_error(int error, t_cube *tc);
void			save_bmp(t_cube *tc);
void			sprite_calc_dimension(t_cube *tc, int sprt_num);
void			write_rgb(t_cube *tc, int fd);
t_bih			create_info_header(t_cube *tc);
t_bfh			create_file_header(t_cube *tc);
void			calc_camera(t_cube *tc);
int				file_exists(char *s);
int				check_parse(char *line, t_cube *tc, t_parse *tp);
int				parse_setter(char *line, t_parse *tp);
int				check_map_splits(char *line, t_cube *tc);
void			sort_sprites(t_cube *tc);

#endif
