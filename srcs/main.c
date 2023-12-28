/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:48:14 by rde-mour          #+#    #+#             */
/*   Updated: 2023/12/28 11:43:00 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(void)
{
	exit(EXIT_FAILURE);
}

static void	start_camera(t_map *map)
{
	map -> cam -> x = (double) map -> mlx -> width / 2;
	map -> cam -> y = (double) map -> mlx -> height / 2;
	if (map -> x > map -> y)
		map -> cam -> z = (double) map -> mlx -> height / (map -> x + 5);
	else
		map -> cam -> z = (double) map -> mlx -> height / (map -> y + 5);
	map -> cam -> x_axis = -0.5;
	map -> cam -> y_axis = -0.5;
	map -> cam -> z_axis = 0.8;
}

static void	screen_movement(t_map *map)
{
	if (mlx_is_key_down(map -> mlx, MLX_KEY_I))
		map -> cam -> x_axis -= 0.015;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_K))
		map -> cam -> x_axis += 0.015;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_J))
		map -> cam -> y_axis -= 0.015;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_L))
		map -> cam -> y_axis += 0.015;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_U))
		map -> cam -> z_axis -= 0.015;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_O))
		map -> cam -> z_axis += 0.015;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_A))
		map -> cam -> x -= 1.15;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_D))
		map -> cam -> x += 1.15;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_W))
		map -> cam -> y -= 1.15;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_S))
		map -> cam -> y += 1.15;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_Q))
		map -> cam -> z -= 0.15;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_E))
		map -> cam -> z += 0.15;
}

static void	key_hook(void *param)
{
	t_map	*map;

	map = (t_map *) param;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(map -> mlx);
		return ;
	}
	mlx_resize_image(map -> img, map -> mlx -> width, map -> mlx -> height);
	screen_movement(map);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_R))
		start_camera(map);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_F))
		set_position(&map, 0.0, 0.0, 0.0);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_H))
		set_position(&map, M_PI, 0.0, 0.0);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_T))
		set_position(&map, M_PI / 2, 0.0, M_PI);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_Y))
		set_position(&map, -M_PI / 2, 0.0, 0.0);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_V))
		set_position(&map, 0.0, -M_PI / 2, M_PI / 2);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_B))
		set_position(&map, 0.0, M_PI / 2, -M_PI / 2);
	if (mlx_is_key_down(map -> mlx, MLX_KEY_C))
	{
		map -> cam -> x = map -> mlx -> width / 2;
		map -> cam -> y = map -> mlx -> height / 2;
	}
	print_matrix(&map);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc == 1 || argv[1] == (void *)0)
		return (-1);
	parser_map(&map, argv[1]);
	map -> mlx = mlx_init(WIDTH, HEIGHT, "Fil de Fer", true);
	if (!map -> mlx)
		ft_error();
	map -> img = mlx_new_image(map -> mlx,
			map -> mlx -> width, map -> mlx -> height);
	if (!map -> img || mlx_image_to_window(map -> mlx, map -> img, 0, 0) < 0)
		ft_error();
	map -> cam = (t_cam *) malloc(1 * sizeof(t_cam));
	if (!map -> cam)
		ft_error();
	start_camera(map);
	print_matrix(&map);
	mlx_loop_hook(map-> mlx, key_hook, map);
	mlx_loop(map-> mlx);
	mlx_terminate(map -> mlx);
	fdf_lstclear(&(map -> field));
	free(map -> cam);
	free(map);
	return (EXIT_SUCCESS);
}
