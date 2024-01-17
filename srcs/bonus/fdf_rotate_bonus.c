/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:37:42 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/17 11:50:23 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	rotate_x(t_field **dot, double rotation)
{
	int64_t	y;
	int64_t	z;

	y = (*dot)-> dot_y;
	z = (*dot)-> dot_z;
	(*dot)-> dot_y = y * cos(rotation) + z * sin(rotation);
	(*dot)-> dot_z = -y * sin(rotation) + z * cos(rotation);
}

static void	rotate_y(t_field **dot, double rotation)
{
	int64_t	x;
	int64_t	z;

	x = (*dot)-> dot_x;
	z = (*dot)-> dot_z;
	(*dot)-> dot_x = x * cos(rotation) + z * sin(rotation);
	(*dot)-> dot_z = -x * sin(rotation) + z * cos(rotation);
}

static void	rotate_z(t_field **dot, double rotation)
{
	int64_t	x;
	int64_t	y;

	x = (*dot)-> dot_x;
	y = (*dot)-> dot_y;
	(*dot)-> dot_x = x * cos(rotation) - y * sin(rotation);
	(*dot)-> dot_y = x * sin(rotation) + y * cos(rotation);
}

void	rotate(t_field **dot, t_cam **cam)
{
	rotate_x(dot, (*cam)-> x_axis);
	rotate_y(dot, (*cam)-> y_axis);
	rotate_z(dot, (*cam)-> z_axis);
}

void	set_position(t_map **map, double x, double y, double z)
{
	(*map)-> cam -> x_axis = x;
	(*map)-> cam -> y_axis = y;
	(*map)-> cam -> z_axis = z;
}
