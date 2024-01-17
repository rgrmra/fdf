/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:52:31 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/17 11:36:32 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "MLX42.h"

# define WIDTH 1366
# define HEIGHT 768

# define HEX "0123456789ABCDEF"

# define SPEED 0.015

enum e_color
{
	WHITE = 0xffffff,
	RED = 0xff0000,
	ORANGE = 0xff8000,
	YELLOW = 0xffff00,
	GREEN = 0x00ff00,
	CYAN = 0x00ffff,
	BLUE = 0x0080ff,
	PURPLE = 0x8000ff,
	MAGENTA = 0xff00ff,
	PINK = 0xff0080,
	BLACK = 0x272727,
	ALPHA = 0x77
};

typedef struct s_map
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*info;
	mlx_texture_t	*texture;
	struct s_field	*field;
	struct s_field	*next_x;
	struct s_field	*next_y;
	struct s_cam	*cam;
	int64_t			x;
	int64_t			y;
	int64_t			z;
}	t_map;

typedef struct s_cam
{
	double	width;
	double	height;
	double	depth;
	double	x;
	double	y;
	double	z;
	double	x_axis;
	double	y_axis;
	double	z_axis;
}	t_cam;

typedef struct s_field
{
	double			x;
	double			y;
	double			z;
	uint32_t		color;
	double			dot_x;
	double			dot_y;
	double			dot_z;
	uint32_t		dot_color;
	struct s_field	*next;
}	t_field;

typedef struct s_draw
{
	int64_t	x0;
	int64_t y0;
	int64_t xcolor;
	int64_t x1;
	int64_t y1;
	int64_t ycolor;
	int64_t line;
	int64_t pixel;
	int64_t dx;
	int64_t sx;
	int64_t dy;
	int64_t sy;
	int64_t err;
	int64_t e2;
}	t_draw;

void	ft_clear_map(t_map *map);
void	ft_error(t_map *map, char *error);
void	fdf_color(t_map **map);
void	fdf_keys(mlx_key_data_t keydata, void *param);
void	parser_map(t_map **map, const char *path);
void	rotate(t_field **dot, t_cam **cam);
void	set_position(t_map **map, double x, double y, double z);
void	print_matrix(t_map **map);

t_map	*fdf_start_map(void);
t_field	*fdf_lstnew(int32_t x, int32_t y, int32_t z, uint32_t color);
void	fdf_lstadd_back(t_field **field, t_field *new);
void	fdf_lstclear(t_field **field);

#endif
