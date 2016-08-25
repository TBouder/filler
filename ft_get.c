/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 17:15:15 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/24 23:34:53 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_get_player(t_env *env, char *str)
{
	if (ft_isstrstr(str, "$$$ exec p1 : ["))
		env->letter = 'O';
	else if (ft_isstrstr(str, "$$$ exec p2 : ["))
		env->letter = 'X';
}

void		ft_get_map_size(t_env *env, char *str)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	split = ft_strsplit(str, ' ');
	env->map_size_y = ft_atoi(split[1]);
	env->map_size_x = ft_atoi(split[2]);
	env->map = ft_dbmalloc(env->map_size_x, env->map_size_y);
	ft_find_middle(env);
	env->phase = 1;
}

void		ft_get_board(t_env *env, char *str)
{
	int		i;
	int		x;
	int		y;

	y = 0;
	while (y < env->map_size_y)
	{
		x = 0;
		i = 0;
		get_next_line(0, &str);
		while (ft_isspace(str[x]) || ft_isnumber(str[x]))
			x++;
		while (i < env->map_size_x)
		{
			env->map[y][i] = str[x];
			x++;
			i++;
		}
		y++;
	}
	env->phase = 0;
}

void		ft_get_piece_size(t_env *env, char *str)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	split = ft_strsplit(str, ' ');
	env->piece_size_y = ft_atoi(split[1]);
	env->piece_size_x = ft_atoi(split[2]);
	env->piece = ft_dbmalloc(env->piece_size_x, env->piece_size_y);
	env->phase = 2;
}

void		ft_get_piece(t_env *env, char *str)
{
	int		x;
	int		y;

	y = 0;
	while (y < env->piece_size_y)
	{
		x = 0;
		get_next_line(0, &str);
		while (x < env->piece_size_x)
		{
			env->piece[y][x] = str[x];
			x++;
		}
		y++;
	}
	env->phase = 3;
}
