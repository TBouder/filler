/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 19:32:07 by tbouder           #+#    #+#             */
/*   Updated: 2016/04/06 19:58:37 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_fill	*ft_fillnew(char *s, t_fill *prev, int id)
{
	t_fill	*fill;

	if (!(fill = (t_fill *)malloc(sizeof(t_fill))))
		return (NULL);
	fill->content = ft_strnew(ft_strlen(s));
	ft_strcpy(fill->content, s);
	fill->line_id = id;
	fill->next = NULL;
	fill->prev = prev;
	return (fill);
}

void			ft_fillend(char *s, t_fill **fill, int id)
{
	t_fill	*new_fill;
	t_fill	*start;
	t_fill	**tmp;

	new_fill = *fill;
	start = *fill;
	if (new_fill)
	{
		tmp = &new_fill;
		while (new_fill->next != NULL)
		{
			tmp = &new_fill;
			new_fill = new_fill->next;
		}
		new_fill->next = ft_fillnew(s, *tmp, id);
	}
	else
		*fill = ft_fillnew(s, NULL, id);
}
