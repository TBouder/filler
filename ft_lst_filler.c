/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/12 13:10:29 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*******************************************************************************
**	LST
*******************************************************************************/
static t_lst_filler	*ft_listnew(int x, int y)
{
	t_lst_filler	*list;

	if (!(list = (t_lst_filler *)malloc(sizeof(t_lst_filler))))
		return (NULL);
	list->x = x;
	list->y = y;
	list->next = NULL;
	return (list);
}

void			ft_listsend(t_lst_filler **list, int x, int y)
{
	t_lst_filler	*new_list;

	new_list = *list;
	if (new_list)
	{
		while (new_list->next != NULL && new_list->y < y)
			new_list = new_list->next;
		while (new_list->next != NULL && new_list->x < x)
			new_list = new_list->next;
		new_list->next = ft_listnew(x, y);
	}
	else
		*list = ft_listnew(x, y);
}
