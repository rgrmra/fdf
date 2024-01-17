/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:08:19 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/17 12:24:30 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_map(t_map **map, double x, double y)
{
	t_field	*tmp;
	int64_t	size;

	if (!map || !(*map) || !(*map)-> x)
		ft_error(*map, "Error: Failed to parser map. File is empty.");
	size = (*map)-> x;
	tmp = (*map)-> field;
	(*map)-> next_x = tmp -> next;
	(*map)-> next_y = tmp -> next;
	while (--size)
		(*map)-> next_y = (*map)-> next_y -> next;
	x += 0.5 - (int) x;
	y += 0.5 - (int) y;
	while (tmp && ++size)
	{
		tmp -> x += ((*map)-> x / 2.0) - (*map)-> x + x;
		tmp -> y += ((*map)-> y / 2.0) - (*map)-> y + y;
		if ((*map)-> z < tmp -> z || (*map)-> z < fabs(tmp -> z))
			(*map)-> z = fabs(tmp -> z);
		tmp = tmp -> next;
	}
}

static uint32_t	ft_atoc(const char *str)
{
	uint32_t	color;
	int32_t		hex;
	int32_t		i;

	if (!str)
		return (WHITE);
	while (*str && *str != 'x')
		str++;
	if (!*str)
		return (WHITE);
	i = 0;
	color = 0;
	while (*(str + i))
	{
		hex = 0;
		while (hex < 16)
		{
			if (HEX[hex] == *(str + i) || HEX[hex] + 32 == *(str + i))
				color = (color * 16) + hex;
			hex++;
		}
		i++;
	}
	return (color);
}

static void	build_map(t_map **map, char *str)
{
	char			**splited;
	int32_t			x;

	ft_strrplc(str, '\n', '\0');
	splited = ft_split(str, ' ');
	if (!splited)
		return ;
	x = 0;
	while (*(splited + x))
	{
		if ((*map)-> x == 0 || ((*map)-> x > x))
			fdf_lstadd_back(&((*map)-> field),
				fdf_lstnew(x, (*map)-> y,
					ft_atol(*(splited + x)),
					ft_atoc(ft_strchr(*(splited + x), ','))));
		free(*(splited + x++));
	}
	free(splited);
	if ((*map)-> x == 0)
		(*map)-> x = x;
	while (x < (*map)-> x)
		fdf_lstadd_back(&(*map)-> field, fdf_lstnew(x++, (*map)-> y, 0, 0x0));
	(*map)-> y += 1;
}

void	parser_map(t_map **map, const char *path)
{
	int32_t	fd;
	char	*str;

	str = ft_strrchr(path, '.');
	if (!str || ft_strncmp(".fdf", ft_strrchr(path, '.'), 5) != 0)
		ft_error(*map, "Error: Invalid file: Please use a *.fdf file.");
	fd = open(path, O_RDONLY, 0666);
	if (fd < 0)
		ft_error(*map, "Error: Failed to open file. Check if the file exists.");
	str = get_next_line(fd);
	while (str)
	{
		build_map(map, str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	check_map(map, (*map)-> x / 2, (*map)-> y / 2);
}
