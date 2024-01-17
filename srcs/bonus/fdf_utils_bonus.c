/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:35:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/17 11:21:39 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_field	*fdf_lstnew(int32_t x, int32_t y, int32_t z, uint32_t color)
{
	t_field	*new;

	new = (t_field *) ft_calloc(1, sizeof(t_field));
	if (!new)
		ft_error(0, "Error: Failed to allocate memory.");
	new -> x = x;
	new -> dot_x = x;
	new -> y = y;
	new -> dot_y = y;
	new -> z = z;
	new -> dot_z = z;
	new -> color = color;
	new -> dot_color = color;
	new -> next = 0;
	return (new);
}

static t_field	*fdf_lstlast(t_field *field)
{
	if (!field)
		return (0);
	while (field -> next)
		field = field -> next;
	return (field);
}

void	fdf_lstadd_back(t_field **field, t_field *new)
{
	if (!field || !new)
		return ;
	if (!(*field))
		*field = new;
	else
		fdf_lstlast(*field)-> next = new;
}

void	fdf_lstclear(t_field **field)
{
	t_field	*tmp;

	if (!field)
		return ;
	while (*field)
	{
		tmp = *field;
		*field = (*field)-> next;
		free(tmp);
	}
}

t_map	*fdf_start_map(void)
{
	t_map	*map;

	map = 0;
	map = (t_map *) ft_calloc(1, sizeof(t_map));
	if (!map)
		ft_error(map, "Error: Failed to allocate memory.");
	map -> mlx = 0;
	map -> img = 0;
	map -> info = 0;
	map -> texture = 0;
	map -> field = 0;
	map -> next_x = 0;
	map -> next_y = 0;
	map -> cam = 0;
	map -> x = 0;
	map -> y = 0;
	map -> z = 0;
	return (map);
}
