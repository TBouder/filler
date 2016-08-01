/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 17:15:15 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/01 18:50:18 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_get_player(t_env *env, char *str)
{
	if (ft_strncmp(str, "$$$ exec p1 : [", 15))
	{
		env->letter = 'O';
		env->phase = 1;
	}
	else if (ft_strncmp(str, "$$$ exec p2 : [", 15))
	{
		env->letter = 'X';
		env->phase = 1;
	}
}

void		ft_get_map_size(t_env *env, char *str)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	if (ft_strncmp(str, "Plateau", 8))
	{
		split = ft_strsplit(str, ' ');
		env->map_size_y = ft_atoi(split[1]);
		env->map_size_x = ft_atoi(split[2]);
		env->map = ft_dbmalloc(env->map_size_x, env->map_size_y);
		ft_find_middle(env);
		env->phase = 2;
	}
}

void		ft_get_board(t_env *env, char *str, int y)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (!ft_isspace(str[x]))
		x++;
	while (ft_isspace(str[x]) || ft_isnumber(str[x]))
		x++;
	while (i < env->map_size_x)
	{
		env->map[y][i] = str[x];
		x++;
		i++;
	}
	if (y == env->map_size_y)
		env->phase = 3;
}

void		ft_get_piece_size(t_env *env, char *str)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	if (ft_strncmp(str, "Piece", 6))
	{
		split = ft_strsplit(str, ' ');
		env->piece_size_y = ft_atoi(split[1]);
		env->piece_size_x = ft_atoi(split[2]);
		env->piece = ft_dbmalloc(env->piece_size_x, env->piece_size_y);
		env->phase = 4;
	}
}

void		ft_get_piece(t_env *env, char *str, int y)
{
	int		x;

	x = 0;
	while (x < env->piece_size_x)
	{
		env->piece[y][x] = str[x];
		x++;
	}
	if (y == env->piece_size_y)
		env->phase = 5;
}
