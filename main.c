/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 19:00:58 by tbouder           #+#    #+#             */
/*   Updated: 2016/04/12 12:07:29 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		ft_word_len(char *str)
{
	int		i;

	i = 0;
	while (!ft_isspace(str[i]))
		i++;
	return (i);
}

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

static void		ft_extract_player(char *name, char *s, t_env *env, int id)
{
	int		len;
	int		i;

	s += 9;
	i = 0;
	len = ft_word_len(s);
	if (id == 0)
		env->p1 = ft_strnew(len + 1);
	else
		env->p2 = ft_strnew(len + 1);
	while (!ft_isspace(s[i]))
	{
		if (id == 0)
			env->p1[i] = s[i];
		else
			env->p2[i] = s[i];
		env->p_id = id;
		i++;
	}
	s += i;
	s += 4;
	i = 0;
	while (s[i] != ']')
	{
		while (name[i] == s[i])
			i++;
		if (s[i] == ']')
			ft_putendl("OK");
		else
			ft_putendl("KO");
	}
	ft_putendl(s);
}

int				main(int ac, char **av)
{
	int		fd;
	t_fill	*map;
	t_env	env;
	char	*s;

	map = NULL;
	fd = open(av[1], O_RDONLY);
	if (ac == 2 && fd != -1)
	{
		if (get_next_line(fd, &s) == 1)
			ft_extract_player(av[0], s, &env, 0);
		if (get_next_line(fd, &s) == 1)
			ft_extract_player(av[0], s, &env, 1);

		while (get_next_line(fd, &s) == 1)
			ft_extract_map(s, &map);
		ft_strdel(&s);

		ft_putendl(env.p1);
		ft_putendl(env.p2);
		ft_print_map(map);
	}
	return (0);
}
