/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keys_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:08:46 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/16 22:03:46 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	fdf_close(mlx_key_data_t keydata, t_map *map)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(map -> mlx);
	}
}

void	fdf_info(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *) param;
	if (keydata.key == MLX_KEY_F1 && keydata.action == MLX_PRESS)
	{
		if (map -> info)
		{
			mlx_delete_image(map -> mlx, map -> info);
			map -> info = 0;
			return ;
		}
		if (!map -> texture)
		{
			map -> texture = mlx_load_png("imgs/keymaps.png");
			if (!map -> texture)
				ft_error(map, "Error: Failed to load png.");
		}
		map -> info = mlx_texture_to_image(map -> mlx, map -> texture);
		if (!map -> info)
			ft_error(map, "Error: Failed to create image.");
		if (mlx_image_to_window(map -> mlx, map -> info, 0, 0) < 0)
			ft_error(map, "Error: Failed to insert image.");
	}
	else
		fdf_close(keydata, map);
}

static uint32_t	get_color(t_map *map, t_field *tmp)
{
	if (mlx_is_key_down(map -> mlx, MLX_KEY_1))
		return (WHITE);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_2))
		return (RED);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_3))
		return (ORANGE);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_4))
		return (YELLOW);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_5))
		return (GREEN);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_6))
		return (CYAN);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_7))
		return (BLUE);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_8))
		return (PURPLE);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_9))
		return (MAGENTA);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_0))
		return (PINK);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_X))
		return (tmp -> dot_color);
	return (tmp -> color);
}

void	fdf_color(t_map **map)
{
	t_field		*tmp;

	if (!map)
		return ;
	if (mlx_is_key_down((*map)-> mlx, MLX_KEY_LEFT_CONTROL))
	{
		tmp = (*map)-> field;
		while (tmp)
		{
			tmp -> color = get_color(*map, tmp);
			tmp = tmp -> next;
		}
	}
}
