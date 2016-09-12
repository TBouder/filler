/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/12 09:50:50 by tbouder          ###   ########.fr       */
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
#include <stdio.h> /////////////////////////////

#define MAP(y, x)		env->map[y][x]
#define MAX_MAP_X		env->map_size_x
#define MAX_MAP_Y		env->map_size_y

#define MAX_PIECE_X		env->piece_size_x
#define MAX_PIECE_Y		env->piece_size_y
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
	while (y < MAX_PIECE_Y)
	{
		x = 0;
		while (x < MAX_PIECE_X)
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
**	ORIENTATION
*******************************************************************************/
void		ft_hori_verti(t_env *env)
{
	if (env->piece_size_x > env->piece_size_y)
		env->piece_orientation == 1; //Horizontal
	else if (env->piece_size_x < env->piece_size_y)
		env->piece_orientation == -1; //Vertical
	else
		env->piece_orientation == 0; //Cube
}


int			ft_pos_cmp_middle_y(t_env *env, int y)
{
	// 1 => top
	// -1 => down
	if (y > env->middle_y1)
		return (-1);
	else if (y < env->middle_y2 && env->middle_y2 != -1)
		return (1);
	else
		return (1);
}

int			ft_pos_cmp_middle_x(t_env *env, int x)
{
	// 1 => right
	// -1 => left
	if (x > env->middle_x1)
		return (-1);
	else if (x < env->middle_x2 && env->middle_x2 != -1)
		return (1);
	else
		return (1);
}


/*******************************************************************************
**	ALGO
*******************************************************************************/

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
		if (pos_y + y > MAX_MAP_Y - 1 || pos_x + x > MAX_MAP_X - 1)
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

void		ft_algo_verti(t_env *env, int direction)
{
	int		x;
	int		y;

	y = direction == -1 ? MAX_MAP_Y : 0;
	while (direction == -1 ? y > 0 : y < MAX_MAP_Y)
	{
		x = direction == -1 ? MAX_MAP_X : 0;
		while (direction == -1 ? x > 0 : x < MAX_MAP_X)
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
	while (direction == -1 ? x > 0 : x < MAX_MAP_X)
	{
		y = direction == -1 ? MAX_MAP_Y : 0;
		while (direction == -1 ? y > 0 : y < MAX_MAP_Y)
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

/*******************************************************************************
**	MAIN
*******************************************************************************/
void		ft_algo(t_env *env)
{
	ft_extract_fragments_piece(env);
	if (env->piece_orientation == 1)
	{
		ft_algo_hori(env, -1); // RIGHT
		ft_algo_hori(env, 1); // LEFT
	}
	if (env->piece_orientation == -1)
	{
		ft_algo_verti(env, -1); // DOWN
		ft_algo_verti(env, 1); // TOP
	}
	if (env->piece_orientation == 0)
	{
		ft_algo_hori(env, -1); // RIGHT
		ft_algo_hori(env, 1); // LEFT

		ft_algo_verti(env, -1); // DOWN
		ft_algo_verti(env, 1); // TOP
	}
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
