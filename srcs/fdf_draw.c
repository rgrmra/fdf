/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:33:23 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/08 23:02:50 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint32_t	gradient(t_draw *draw)
{
	double		color[3];
	uint32_t	new[3];
	uint32_t	newcolor;
	uint32_t	pixel;

	pixel = draw -> line - draw -> pixel;
	*(color) = (double)((draw -> ycolor >> 16) - (draw -> xcolor >> 16)) \
			/ (double) draw -> line;
	*(color + 1) = (double)(((draw -> ycolor >> 8) & 0xFF) - \
			((draw -> xcolor >> 8) & 0xFF)) / (double) draw -> line;
	*(color + 2) = (double)((draw -> ycolor & 0xFF) - \
			(draw -> xcolor & 0xFF)) / (double) draw -> line;
	*new = (draw -> xcolor >> 16) + round(pixel * *color);
	*(new + 1) = ((draw -> xcolor >> 8) & 0xFF) + round(pixel * *(color + 1));
	*(new + 2) = (draw -> xcolor & 0xFF) + round(pixel * *(color + 2));
	newcolor = (*new << 16) + (*(new + 1) << 8) + *(new + 2);
	newcolor = newcolor * 256 + TRANSPARENCY;
	return (newcolor);
}

static void	calculate(t_map *map, t_field *from, t_draw *draw)
{
	if ((from -> dot_x >= 0 && from -> dot_x < map -> mlx -> width)
		&& (from -> dot_y >= 0 && from -> dot_y < map -> mlx -> height))
		mlx_put_pixel(map -> img, from -> dot_x, from -> dot_y,
			from -> color * 256 + TRANSPARENCY);
	while (draw -> pixel)
	{
		if ((draw -> x0 >= 0 && draw -> x0 < map -> mlx -> width)
			&& (draw -> y0 >= 0 && draw -> y0 < map -> mlx -> height))
			mlx_put_pixel(map -> img, draw -> x0, draw -> y0, gradient(draw));
		if (draw -> x0 == draw -> x1 && draw -> y0 == draw -> y1)
			return ;
		draw -> e2 = 2 * draw -> err;
		if (draw -> e2 >= draw -> dy)
		{
			draw -> err += draw -> dy;
			draw -> x0 += draw -> sx;
		}
		if (draw -> e2 <= draw -> dx)
		{
			draw -> err += draw -> dx;
			draw -> y0 += draw -> sy;
		}
		draw -> pixel -= 1;
	}
}

static void	drawline(t_map *map, t_field *from, t_field *to)
{
	t_draw	draw;

	if (!to)
		to = from;
	draw.x0 = (int) from -> dot_x;
	draw.x1 = (int) to -> dot_x;
	draw.xcolor = from -> color;
	draw.y0 = (int) from -> dot_y;
	draw.y1 = (int) to -> dot_y;
	draw.ycolor = to -> color;
	draw.dx = abs(draw.x1 - draw.x0);
	if (draw.x0 < draw.x1)
		draw.sx = 1;
	else
		draw.sx = -1;
	draw.dy = -abs(draw.y1 - draw.y0);
	if (draw.y0 < draw.y1)
		draw.sy = 1;
	else
		draw.sy = -1;
	draw.err = draw.dx + draw.dy;
	draw.pixel = sqrt(pow(draw.dx, 2) + pow(draw.dy, 2));
	draw.line = draw.pixel;
	calculate(map, from, &draw);
}

static void	prepare_matrix(t_map *map)
{
	t_field		*tmp;
	uint32_t	i;

	i = 0;
	while (i < (map -> img -> width * map -> img -> height * sizeof(uint32_t)))
	{
		*(map -> img -> pixels + (i++ * sizeof(uint8_t))) = 0x33;
		*(map -> img -> pixels + (i++ * sizeof(uint8_t))) = 0x33;
		*(map -> img -> pixels + (i++ * sizeof(uint8_t))) = 0x33;
		*(map -> img -> pixels + (i++ * sizeof(uint8_t))) = 0xff;
	}
	tmp = map-> field;
	while (tmp)
	{
		tmp -> dot_x = tmp -> x * map -> cam -> z;
		tmp -> dot_y = tmp -> y * map -> cam -> z;
		tmp -> dot_z = tmp -> z * map -> cam -> z;
		rotate(&tmp, &(map -> cam));
		tmp -> dot_x += map -> cam -> x;
		tmp -> dot_y += map -> cam -> y;
		tmp = tmp-> next;
	}
}

void	print_matrix(t_map **map)
{
	t_field	*tmp;
	t_field	*next_x;
	t_field	*next_y;

	tmp = (*map)-> field;
	next_x = (*map)-> next_x;
	next_y = (*map)-> next_y;
	prepare_matrix(*map);
	if ((*map)-> cam -> z < 0)
		(*map)-> cam -> z = 0;
	while (tmp)
	{
		if (next_x && tmp -> y == next_x -> y)
			drawline(*map, tmp, next_x);
		drawline(*map, tmp, next_y);
		tmp = tmp -> next;
		if (next_x && next_x -> next)
			next_x = next_x -> next;
		else
			next_x = tmp;
		if (next_y && next_y -> next)
			next_y = next_y -> next;
		else
			next_y = tmp;
	}
}
