/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 17:15:15 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/12 14:24:44 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_get_player(t_env *env, char *str)
{
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
	split = ft_strsplit(str, ' ');
	env->map_size_y = ft_atoi(split[1]);
	env->map_size_x = ft_atoi(split[2]);
	env->map = ft_dbmalloc(env->map_size_x, env->map_size_y);
	env->phase = 1;
}

void		ft_get_board(t_env *env, char *str)
{
	int		i;
	int		y;
	int		x;

	y = 0;
	while (y < env->map_size_y)
	{
		get_next_line(0, &str);
		x = 0;
		i = 0;
		while (ft_isspace(str[x]) || ft_isnumber(str[x]))
			x++;
		while (x < env->map_size_x)
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
	int		y;
	int		x;

	y = 0;
	env->nb_fragments = 0;
	while (y < env->piece_size_y)
	{
		get_next_line(0, &str);
		x = 0;
		while (x < env->piece_size_x)
		{
			env->piece[y][x] = str[x];
			//OPTI GET PIECE
			if (str[x] == '*')
				env->nb_fragments++;
			x++;
		}
		y++;
	}
	env->phase = 3;
}
