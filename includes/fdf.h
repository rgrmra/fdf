/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:52:31 by rde-mour          #+#    #+#             */
/*   Updated: 2023/12/09 12:17:24 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf_bonus.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1366
# define HEIGHT 768

typedef struct s_map {
	struct s_field	*field;
	int32_t			x;
	int32_t			y;
}	t_map;

typedef struct s_field {
	int32_t			x;
	int32_t			y;
	int32_t			z;
	struct s_field	*next;
}	t_field;

t_field	*fdf_lstnew(int32_t x, int32_t y, int32_t z);
t_field	*fdf_lstlast(t_field *field);
void	fdf_lstadd_back(t_field **field, t_field *new);
void	fdf_lstclear(t_field **field);

#endif
