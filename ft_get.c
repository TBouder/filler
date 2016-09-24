/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 17:15:15 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/24 12:26:39 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_get_player(t_env *env, char *str)
{
	env->direction_x = 0;
	if (ft_isstrstr(str, "$$$ exec p1 : ["))
	{
		env->letter_player = 'O';
		env->letter_adv = 'X';
	}
	else if (ft_isstrstr(str, "$$$ exec p2 : ["))
	{
		env->letter_player = 'X';
		env->letter_adv = 'O';
	}
}

void		ft_get_map_size(t_env *env, char *str)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	if (env->map == NULL)
	{
		split = ft_strsplit(str, ' ');
		MAX_MAP_Y = ft_atoi(split[1]);
		MAX_MAP_X = ft_atoi(split[2]);
		env->map = ft_dbmalloc(MAX_MAP_X, MAX_MAP_Y);
		ft_dbstrdel(split);
	}
	env->phase = 1;
}

void		ft_get_board(t_env *env, char *str)
{
	int		y;
	int		x;
	int		i;

	y = 0;
	while (y < MAX_MAP_Y)
	{
		get_next_line(0, &str);
		x = 0;
		i = 0;
		while (ft_isspace(str[x]) || ft_isnumber(str[x]))
			x++;
		while (i < MAX_MAP_X)
		{
			env->map[y][i] = str[x];
			x++;
			i++;
		}
		y++;
	}
	env->direction_x == 0 ? ft_choose_direction(env) : 0;
	env->phase = 0;
}

void		ft_get_piece_size(t_env *env, char *str)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	if (env->piece == NULL)
	{
		split = ft_strsplit(str, ' ');
		MAX_PIECE_Y = ft_atoi(split[1]);
		MAX_PIECE_X = ft_atoi(split[2]);
		ft_dbstrdel(split);
		env->piece = ft_dbmalloc(MAX_PIECE_X, MAX_PIECE_Y);
	}
	env->phase = 2;
}

void		ft_get_piece(t_env *env, char *str)
{
	int		y;
	int		x;

	y = 0;
	env->nb_fragments = 0;
	while (y < MAX_PIECE_Y)
	{
		get_next_line(0, &str);
		x = 0;
		while (x < MAX_PIECE_X)
		{
			env->piece[y][x] = str[x];
			if (str[x] == '*')
				env->nb_fragments++;
			x++;
		}
		y++;
	}
	env->phase = 3;
}
