/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/07/27 12:22:42 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		ft_get_board(t_env *env, char *str, int y)
{
	int		x;

	x = 0;
	while (x < env->map_size_x)
	{
		env->map[y][x] = str[x];
		x++;
	}
	if (y == env->map_size_y)
		env->is_set_board = TRUE;
}

void			ft_dbmalloc(char **str, int x, int y)
{
	int		i;

	i = 0;
	str = malloc(sizeof(char **) * y);
	while (i < y)
	{
		str[i] = ft_strnew(x);
		i++;
	}
}

static void		ft_get_map_size(t_env *env, char *str)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	if (ft_strncmp(str, "Plateau", 7) == 0)
	{
		split = ft_strsplit(str, ' ');
		env->map_size_y = ft_atoi(split[1]);
		env->map_size_x = ft_atoi(split[2]);
		ft_dbmalloc(env->map, env->map_size_x, env->map_size_y);
		env->is_set_map_size = TRUE;
	}
}

static void		ft_get_player(t_env *env, char *str)
{
	if (ft_strncmp(str, "$$$ exec p1 : [", 15) == 0)
	{
		env->letter = 'O';
		env->is_set_letter = TRUE;
	}
	else if (ft_strncmp(str, "$$$ exec p2 : [", 15) == 0)
	{
		env->letter = 'X';
		env->is_set_letter = TRUE;
	}
}

void		ft_launcher(t_env *env)
{
	char	*str;
	int		y;

	str = NULL;
	y = 0;
	env->is_set_letter = FALSE;
	env->is_set_map_size = FALSE;
	env->is_set_board = FALSE;
	ft_putstr("CICGHHJFE");
	while (get_next_line(0, &str))
	{
		if (env->is_set_letter == FALSE)
			ft_get_player(env, str);
		if (env->is_set_letter == TRUE && env->is_set_map_size == FALSE)
			ft_get_map_size(env, str);
		if (env->is_set_letter == TRUE && env->is_set_map_size == TRUE && env->is_set_board == FALSE)
			ft_get_board(env, str, y++);
		if (env->is_set_letter == TRUE && env->is_set_map_size == TRUE && env->is_set_board == TRUE)
		{
			ft_putstr("13 15\n");
		}
	}
	ft_strdel(&str);
}

int			main(void)
{
	t_env	env;

	ft_launcher(&env);
	// if (env.letter != 0)
		// ft_putstr("7 5\n");
	return (0);
}
