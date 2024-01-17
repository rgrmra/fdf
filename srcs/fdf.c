/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:48:14 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/17 11:25:21 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	start_camera(t_map *map)
{
	map -> cam -> x = (double) map -> mlx -> width / 2;
	map -> cam -> y = (double) map -> mlx -> height / 2;
	if (map -> x > map -> y && map -> x > map -> z + 1)
		map -> cam -> z = (double) map -> mlx -> height / (map -> x * 1.5);
	else if (map -> y > map -> z + 1)
		map -> cam -> z = (double) map -> mlx -> height / (map -> y * 1.5);
	else
		map -> cam -> z = (double) map -> mlx -> height / (map -> z * 2.5);
	map -> cam -> x_axis = -0.5;
	map -> cam -> y_axis = -0.5;
	map -> cam -> z_axis = 0.65;
}

static void	centralize(t_map *map)
{
	mlx_resize_image(map -> img, map -> mlx -> width, map -> mlx -> height);
	map -> cam -> x = (map -> cam -> x / map -> cam -> width);
	map -> cam -> x *= map -> mlx -> width;
	map -> cam -> y = (map -> cam -> y / map -> cam -> height);
	map -> cam -> y *= map -> mlx -> height;
	map -> cam -> z = (map -> cam -> z / map -> cam -> height);
	map -> cam -> z *= map -> mlx -> height;
	if (mlx_is_key_down(map -> mlx, MLX_KEY_C))
	{
		map -> cam -> x = map -> mlx -> width / 2;
		map -> cam -> y = map -> mlx -> height / 2;
	}
}

static void	key_hook(void *param)
{
	t_map	*map;

	map = (t_map *) param;
	centralize(map);
	print_matrix(&map);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc < 2 || argv[1] == (void *)0)
		ft_error(0, "Error: No map informed. Use: ./fdf <map name>");
	if (argc > 2)
		ft_error(0, "Error: Too many arguments. Use: ./fdf <map name>");
	map = fdf_start_map();
	parser_map(&map, argv[1]);
	map -> mlx = mlx_init(WIDTH, HEIGHT, "Fil de Fer", true);
	if (!map -> mlx)
		ft_error(map, "Error: Failed to initiate mlx.");
	map -> img = mlx_new_image(map -> mlx, WIDTH, HEIGHT);
	if (!map -> img || mlx_image_to_window(map -> mlx, map -> img, 0, 0) < 0)
		ft_error(map, "Error: Failed to initiate image.");
	mlx_set_window_limit(map -> mlx, 1024, 576, -1, -1);
	map -> cam = (t_cam *) malloc(1 * sizeof(t_cam));
	if (!map -> cam)
		ft_error(map, "Error: Failed to initiate camera.");
	start_camera(map);
	print_matrix(&map);
	mlx_key_hook(map -> mlx, fdf_keys, map);
	mlx_loop_hook(map -> mlx, key_hook, map);
	mlx_loop(map-> mlx);
	ft_clear_map(map);
	return (EXIT_SUCCESS);
}
