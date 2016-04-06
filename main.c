/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 19:00:58 by tbouder           #+#    #+#             */
/*   Updated: 2016/04/06 21:52:58 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		ft_print_map(t_fill *map)
{
	while (map)
	{
		ft_putendl(map->content);
		map = map->next;
	}
}

static void		ft_extract_map(char *s, t_fill **map)
{
	static int	i = 0;

	ft_fillend(s, map, i);
	i++;
}

int		main(int ac, char **av)
{
	int		fd;
	t_fill	*map;
	char	*s;

	map = NULL;
	fd = open(av[1], O_RDONLY);
	if (ac == 2 && fd != -1)
	{
		while (get_next_line(fd, &s) == 1)
			ft_extract_map(s, &map);
		ft_strdel(&s);
		
		ft_print_map(map);
	}
	return (0);
}
