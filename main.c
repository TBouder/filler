/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/19 15:23:31 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_algo_verti(t_env *env, int direction)
{
	int		x;
	int		y;

	y = direction == -1 ? MAX_MAP_Y : 0;
	while (direction == -1 ? y >= 0 : y + MAX_PIECE_Y <= MAX_MAP_Y)
	{
		x = direction == -1 ? MAX_MAP_X : 0;
		while (direction == -1 ? x >= 0 : x + MAX_PIECE_X <= MAX_MAP_X)
		{
			if (ft_test_fragments(env, x, y) == 1)
			{
				ft_printf("%d %d\n", y, x);
				return ;
			}
			x += direction;
		}
		y += direction;
	}
	ft_printf("0 0\n");
}

void		ft_algo_hori(t_env *env, int direction)
{
	int		x;
	int		y;

	x = direction == -1 ? MAX_MAP_X : 0;
	while (direction == -1 ? x >= 0 : x + MAX_PIECE_X <= MAX_MAP_X)
	{
		y = direction == -1 ? MAX_MAP_Y : 0;
		while (direction == -1 ? y >= 0 : y + MAX_PIECE_Y <= MAX_MAP_Y)
		{
			if (ft_test_fragments(env, x, y) == 1)
			{
				ft_printf("%d %d\n", y, x);
				return ;
			}
			y += direction;
		}
		x += direction;
	}
	ft_printf("0 0\n");
}

void		ft_algo(t_env *env)
{
	ft_hori_verti(env);
	ft_extract_fragments_piece(env);
	env->piece_orientation >= 0 ? ft_algo_hori(env, env->direction_x) : 0;
	env->piece_orientation == -1 ? ft_algo_verti(env, env->direction_y) : 0;
}

void		ft_launcher(t_env *env)
{
	char	*str;

	env->phase = 0;
	env->map = NULL;
	while (get_next_line(0, &str))
	{
		if (ft_isstrstr(str, "$$$ exec "))
			ft_get_player(env, str);
		if (ft_isstrstr(str, "Plateau"))
		{
			ft_get_map_size(env, str);
			get_next_line(0, &str);
		}
		if (env->phase == 1)
			ft_get_board(env, str);
		if (ft_isstrstr(str, "Piece"))
			ft_get_piece_size(env, str);
		if (env->phase == 2)
			ft_get_piece(env, str);
		if (env->phase == 3)
		{
			ft_print_update(env);
			ft_algo(env);
		}
	}
	ft_strdel(&str);
}

int			main(void)
{
	static t_env	env;

	close(open("debug", O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP
		| S_IROTH));
	ft_launcher(&env);
	return (0);
}
