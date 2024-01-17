/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:20:13 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/16 22:03:35 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_clear_map(t_map *map)
{
	if (!map)
		return ;
	if (map -> info)
		mlx_delete_image(map -> mlx, map -> info);
	if (map -> texture)
		mlx_delete_texture(map -> texture);
	if (map -> field)
		mlx_terminate(map -> mlx);
	if (map -> mlx)
		fdf_lstclear(&(map -> field));
	if (map -> cam)
		free(map -> cam);
	free(map);
}

void	ft_error(t_map *map, char *error)
{
	ft_clear_map(map);
	if (errno)
		perror("Error");
	else
		ft_putendl_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
