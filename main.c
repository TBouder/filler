/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 19:00:58 by tbouder           #+#    #+#             */
/*   Updated: 2016/04/12 12:37:15 by tbouder          ###   ########.fr       */
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

static int		ft_extract_player_helper(char *name, char *s)
{
	int		i;

	i = 0;
	s += 15;
	while (s[i] && s[i] != ']')
	{
		while (name[i] == s[i])
			i++;
		if (s[i] == ']')
			return (1);
		i++;
	}
	return (0);
}

static int		ft_extract_player(int fd, char *name, t_env *env)
{
	char	*s;
	int		p1;
	int		p2;

	p1 = 0;
	p2 = 0;
	if (get_next_line(fd, &s) == 1)
		p1 = ft_extract_player_helper(name, s);
	if (get_next_line(fd, &s) == 1)
		p2 = ft_extract_player_helper(name, s);
	if (p2 == p1)
		return (0);
	else
	{
		if (p1)
			env->p_id = 1;
		if (p2)
			env->p_id = 2;
	}
	return (1);
}

int				main(int ac, char **av)
{
	int		fd;
	t_fill	*map;
	t_env	*env;
	char	*s;

	map = NULL;
	env = malloc(sizeof(env));
	fd = open(av[1], O_RDONLY);
	if (ac == 2 && fd != -1)
	{
		ft_extract_player(fd, av[0], env);
		while (get_next_line(fd, &s) == 1)
			ft_extract_map(s, &map);
		ft_strdel(&s);
		env->p_name = ft_strnew(ft_strlen(av[0]));
		ft_strcpy(env->p_name, av[0]);
		ft_nbrendl(env->p_id);
		ft_putendl(env->p_name);
		ft_print_map(map);
	}
	return (0);
}
