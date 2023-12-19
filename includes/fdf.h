/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:52:31 by rde-mour          #+#    #+#             */
/*   Updated: 2023/12/19 19:20:26 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf_bonus.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1366
# define HEIGHT 768
# define HEX "0123456789ABCDEF"

typedef struct s_map {
	mlx_t			*mlx;
	mlx_image_t		*img;
	struct s_field	*field;
	struct s_field	*next_x;
	struct s_field	*next_y;
	struct s_cam	*cam;
	int32_t			x;
	int32_t			y;
}	t_map;

typedef struct s_cam {
	double	x;
	double	y;
	double	z;
	double	x_axis;
	double	y_axis;
	double	z_axis;
}	t_cam;

typedef struct s_field {
	double			x;
	double			y;
	double			z;
	double			dot_x;
	double			dot_y;
	double			dot_z;
	int32_t			color;
	struct s_field	*next;
}	t_field;

void	ft_error(void);
void	parser_map(t_map **map, const char *path);
void	rotate(t_field **dot, t_cam **cam);
void	set_position(t_map **map, double x, double y, double z);
void	print_matrix(t_map **map);

t_field	*fdf_lstnew(int32_t x, int32_t y, int32_t z, unsigned long color);
t_field	*fdf_lstlast(t_field *field);
void	fdf_lstadd_back(t_field **field, t_field *new);
void	fdf_lstclear(t_field **field);

#endif
