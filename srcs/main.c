/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:48:14 by rde-mour          #+#    #+#             */
/*   Updated: 2023/12/09 20:35:45 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <stdbool.h>
#include "fdf.h"

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void	ft_key_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}
/*
static void	print_square(mlx_t *mlx, mlx_image_t *img,
		int32_t width, int32_t height)
{
	int	i;
	int	w;
	int	h;

	w = mlx -> width / 2 - width / 2;
	h = mlx -> height / 2 - height / 2;
	mlx_resize_image(img, mlx -> width, mlx -> height);
	i = 0;
	while (i++ < width)
	{
		mlx_put_pixel(img, w + i, h, 0xFFFFFFFF);
		mlx_put_pixel(img, w + i, h + height, 0xFFFFFFFF);
	}
	i = 0;
	while (i++ < height)
	{
		mlx_put_pixel(img, w, h + i, 0xFFFFFFFF);
		mlx_put_pixel(img, w + width, h + i, 0xFFFFFFFF);
	}
}
*/
static void	print_matrix(mlx_t *mlx, mlx_image_t *img, t_map *map)
{
	t_field	*tmp;
	int	i;
	int	w;
	int	h;
	int	size;

	size = 30;
	w = 25;
	h = 25;
	mlx_resize_image(img, mlx -> width, mlx -> height);
	tmp = map -> field;
	while (tmp)
	{
		i = 0;
		while (i++ < size)
		{
			mlx_put_pixel(img, tmp -> x * size + i + w, tmp -> y * size + h, 0xFFFFFFFF);
			mlx_put_pixel(img, tmp -> x * size + w, tmp -> y * size + i + h, 0xFFFFFFFF);
		}
		tmp = tmp -> next;
	}
}

static void	build_map(t_map **map, const char *str)
{
	char			**splited;
	int32_t			i;
	int32_t			x;
	static int32_t	y;

	if (!str)
		return ;
	i = 0;
	x = 0;
	splited = NULL;
	splited = ft_split(str, ' ');
	if (!splited)
		return ;
	while (*(splited + x))
	{
		fdf_lstadd_back(&((*map)-> field),
				fdf_lstnew(x, y,
					ft_atoi(*(splited + x))));
		free(*(splited + x++));
	}
	free(splited);
	if (((*map)-> x) == 0)
		(*map)-> x = x;
	(*map)-> y = ++y;
}

static void	print_map(const char *path, t_map **map)
{
	t_field	*tmp;
	int32_t	x;

	ft_printf("map: %s\n", path);
	x = (*map)-> x;
	tmp = (*map)-> field;
	while (tmp)
	{
		ft_printf("% 3d", tmp -> z);
		if (tmp -> x == x - 1)
			ft_printf("\n");
		tmp = tmp -> next;
	}
	ft_printf("\nwidth: %.3d, height: %.3d\n", (*map)-> x, (*map)-> y);
}

static int	check_map(t_map **map)
{
	t_field	*tmp;
	int		size;

	if (!map || !(*map))
		return (0);
	size = 0;
	tmp = (*map)-> field;
	while (tmp)
	{
		size++;
		tmp = tmp -> next;
	}
	ft_printf("%d\n", size);
	ft_printf("%d\n", (*map)-> x * (*map)-> y);
	if (size == (*map)-> x * (*map)-> y)
		return (1);
	fdf_lstclear(&((*map)-> field));
	free(*map);
	return (0);
}

static int	parser_map(t_map **map, const char *path)
{
	int		fd;
	char	*str;

	fd = open(path, O_RDONLY, 0666);
	ft_printf("file descriptor: %d\n", fd);
	if (fd < 0)
		exit (1);
	*map = (t_map *) malloc(1 * sizeof(t_map));
	if (fd < 0 || !(*map))
		exit (1);
	(*map)-> field = NULL;
	(*map)-> x = 0;
	(*map)-> y = 0;
	str = NULL;
	str = get_next_line(fd);
	while (str)
	{
		build_map(map, str);
		free(str);
		str = 0;
		str = get_next_line(fd);
	}
	close(fd);
	print_map(path, map);
	return (check_map(map));
}

int32_t	main(int32_t argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;

	map = malloc(1 * sizeof(t_map));
	if (argc == 1 || argv[1] == (void *)0 || !parser_map(&map, argv[1]))
		return (0);
	mlx = mlx_init(WIDTH, HEIGHT, "Fil de Fer", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, mlx -> width, mlx -> height);
	if (!img)
		ft_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		ft_error();
	//mlx_put_string(mlx, argv[1], 5, 5);
	mlx_set_window_limit(mlx, WIDTH, HEIGHT, WIDTH, HEIGHT);
	//print_square(mlx, img, map -> x, map -> y);
	print_matrix(mlx, img, map);
	mlx_loop_hook(mlx, ft_key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	fdf_lstclear(&(map-> field));
	free(map);
	return (EXIT_SUCCESS);
}
