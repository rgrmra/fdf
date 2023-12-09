/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:35:52 by rde-mour          #+#    #+#             */
/*   Updated: 2023/12/06 19:53:33 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_field	*fdf_lstnew(int32_t x, int32_t y, int32_t z)
{
	t_field	*new;

	new = (t_field *) malloc(1 * sizeof(t_field));
	if (!new)
		return (0);
	new -> x = x;
	new -> y = y;
	new -> z = z;
	new -> next = 0;
	return (new);
}

t_field	*fdf_lstlast(t_field *field)
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
