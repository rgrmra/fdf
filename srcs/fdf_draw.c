/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:33:23 by rde-mour          #+#    #+#             */
/*   Updated: 2023/12/19 19:33:06 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	drawline(mlx_image_t *img, mlx_t *mlx, int x0, int y0, int x1, int y1, int32_t color)
{
	int32_t	dx;
	int32_t	sx;
	int32_t	dy;
	int32_t	sy;
	int32_t	err;
	int32_t	e2;
	int32_t c;

	c = color;
	c = ((c * 16) * 16) + 0x77;
	dx = abs (x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs (y1 - y0);
	sy = y0 < y1 ? 1 : -1; 
	err = dx + dy;
	while (1)
	{
		if (x0 >= 0 && x0 < mlx -> width && y0 >= 0 && y0 < mlx -> height)
			mlx_put_pixel(img, x0, y0, c);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }

		if (e2 <= dx) { err += dx; y0 += sy; }
	}
}

static void	clear(mlx_image_t *img)
{
	uint32_t	i;

	i = 0;
	while (i < (img -> width * img -> height * sizeof(uint32_t)))
		*(img -> pixels + (i++ * sizeof(uint8_t))) = 0x00;
}

static void	draw(t_map *map)
{
	t_field	*tmp;

	clear(map -> img);
	tmp = map-> field;
	while (tmp)
	{
		tmp -> dot_x = tmp -> x * map -> cam -> z;
		tmp -> dot_y = tmp -> y * map -> cam -> z;
		tmp -> dot_z = tmp -> z * map -> cam -> z;
/*
		double	r = sqrt(pow(map -> mlx -> height, 2) * pow(map -> mlx -> width, 2));
		double	theta = 0;
		double	phi = 0;


		double	snt = sin(theta * 3.14159 / 180);
		double	cnt	= cos(theta * 3.14159 / 180);
		double	snp = sin(phi * 3.14159 / 180);
		double	cnp = cos(phi * 3.14159 / 180);
		tmp -> dot_x = r * snt * cnp;
		tmp -> dot_y = r * cnt;
		tmp -> dot_z = -r * snt * snp;
*/
		rotate(&tmp, &(map -> cam));
		

		tmp -> dot_x += map -> cam -> x;
		tmp -> dot_y += map -> cam -> y;
		tmp = tmp-> next;
	}
}

void	print_matrix(t_map **map)
{
	t_field *tmp;
	t_field *next_x;
	t_field *next_y;

	tmp = (*map) -> field;
	next_x = (*map) -> next_x;
	next_y = (*map) -> next_y;
	draw(*map);
	if ((*map) -> cam -> z < 0)
		(*map) -> cam -> z = 0;
	while (tmp)
	{
		if (tmp -> y == next_x -> y)
			drawline((*map)-> img, (*map)-> mlx, tmp -> dot_x, tmp -> dot_y, next_x -> dot_x, next_x -> dot_y, tmp -> color);
		drawline((*map)-> img, (*map)->  mlx, next_y -> dot_x, next_y -> dot_y, tmp -> dot_x, tmp -> dot_y, tmp-> color);
		tmp = tmp -> next;
		if (next_x -> next)
			next_x = next_x -> next;
		else
			next_x = tmp;
		if (next_y -> next)
			next_y = next_y -> next;
		else
			next_y = tmp;
	}
}
