/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/10 18:10:04 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- Trouver le milieu
- Regarder ou l'on est par rapport au milieu
- Regarder ou est l'adv par rapport au milieu

- Rusher vers le center de la map le plus possible

- Si on recoit une piece plus grande horizontalement, privilegier l'horizontale
- Si on recoit une piece plus grande verticalement, privilegier la verticale
*/

#include "filler.h"
#include <stdio.h>

#define MAP(y, x)		env->map[y][x]
#define MAP_X			env->map_size_x
#define MAP_Y			env->map_size_y

#define PIECE_X			env->piece_size_x
#define PIECE_Y			env->piece_size_y
#define PIECE(y, x)		env->piece[y][x]


/*******************************************************************************
**	Fragments
*******************************************************************************/
void		ft_malloc_fragments_piece(t_env *env)
{
	int		i;

	i = 0;
	env->fragments = (int **)malloc(sizeof(int *) * env->nb_fragments);
	while (i < env->nb_fragments)
	{
		env->fragments[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
}

void		ft_extract_fragments_piece(t_env *env)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = 0;
	ft_malloc_fragments_piece(env);
	while (y < PIECE_Y)
	{
		x = 0;
		while (x < PIECE_X)
		{
			if (PIECE(y, x) == '*')
			{
				env->fragments[i][0] = y;
				env->fragments[i][1] = x;
				i++;
			}
			x++;
		}
		y++;
	}
}

/*******************************************************************************
**	ALGO
*******************************************************************************/
// OPTI TIME :
// MODIFIER L'ETAT ACTIF D'UNE LIGNE AU MOMENT DU PLACEMENT
// EVITER LES REMALLOCS

int			ft_test_activ_lines(t_env *env, int y)
{
	int		i;

	i = 0;
	while (i < PIECE_Y)
	{
		if (env->activ_line[y + i] == 1)
			return (1);
		i++;
	}
	return (0);
}

int			ft_test_fragments(t_env *env, int pos_x, int pos_y)
{
	int		i;
	int		x;
	int		y;
	int		star_match;

	i = 0;
	star_match = 0;
	while (i < env->nb_fragments)
	{
		x = env->fragments[i][1];
		y = env->fragments[i][0];
		if (pos_y + y > MAP_Y - 1 || pos_x + x > MAP_X - 1)
			return (0);
		if (MAP(pos_y + y, pos_x + x) == env->letter_player)
			star_match++;
		if (MAP(pos_y + y, pos_x + x) == env->letter_adv || star_match > 1)
			return (0);
		i++;
	}
	if (star_match == 1)
		return (1);
	return (0);
}

void		ft_algo_up(t_env *env)
{
	int		x;
	int		y;

	y = 0;
	while (y < MAP_Y)
	{
		x = 0;
		while (x < MAP_X)
		{
			// if (ft_test_activ_lines(env, y) == 0)
			// // if (env->activ_line[y] == 0)
			// 	break ;
			if (ft_test_fragments(env, x, y) == 1)
			{
				ft_printf("%d %d\n", y, x);
				return ;
			}
			x++;
		}
		y++;
	}
	ft_printf("0 0\n");
}

void		ft_algo_down(t_env *env)
{
	int		x;
	int		y;

	y = MAP_Y;
	while (y > 0)
	{
		x = MAP_X;
		while (x > 0)
		{
			if (ft_test_fragments(env, x, y) == 1)
			{
				ft_printf("%d %d\n", y, x);
				return ;
			}
			x--;
		}
		y--;
	}
	ft_printf("0 0\n");
}

void		ft_algo_right(t_env *env)
{
	int		x;
	int		y;

	x = MAP_X;
	while (x > 0)
	{
		y = MAP_Y;
		while (y > 0)
		{
			if (ft_test_fragments(env, x, y) == 1)
			{
				ft_printf("%d %d\n", y, x);
				return ;
			}
			y--;
		}
		x--;
	}
	ft_printf("0 0\n");
}

void		ft_algo_left(t_env *env)
{
	int		x;
	int		y;

	x = 0;
	while (x < MAP_X)
	{
		y = 0;
		while (y < MAP_Y)
		{
			// if (ft_test_activ_lines(env, y) == 0)
			// // if (env->activ_line[y] == 0)
			// 	break ;
			if (ft_test_fragments(env, x, y) == 1)
			{
				ft_printf("%d %d\n", y, x);
				return ;
			}
			y++;
		}
		x++;
	}
	ft_printf("0 0\n");
}
/*******************************************************************************
**	MAIN
*******************************************************************************/
void		ft_algo(t_env *env)
{
	ft_extract_fragments_piece(env);
	// if (rand() % 2 == 1)
	// 	ft_algo_up(env);
	// else

	// ft_algo_up(env);
	// ft_algo_down(env);
	// ft_algo_right(env);
	// ft_algo_left(env);
}

void		ft_launcher(t_env *env)
{
	char	*str;

	env->phase = 0;
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
			ft_algo(env);
	}
	ft_strdel(&str);
}

int			main(void)
{
	static t_env	env;

	ft_launcher(&env);
	return (0);
}
