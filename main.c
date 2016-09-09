/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/09 20:05:53 by tbouder          ###   ########.fr       */
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

void		ft_malloc_fragments_piece(t_env *env)
{
	int		i;

	i = 0;
	env->nb_fragments = ft_detail_piece(env);
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
	while (y < env->piece_size_y)
	{
		x = 0;
		while (x < env->piece_size_x)
		{
			if (env->piece[y][x] == '*')
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

int			ft_strstr_filler(char *s1, char *s2, t_env *env)
{
	int		one;
	int		i;
	int		j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		one = 0;
		while ((s1[i + j] == '.') || (s1[i + j] == env->letter_player
			&& (s2[j] == '.' || s2[j] == '*')))
		{
			if (s1[i + j] == env->letter_player && s2[j] == '*' && one == 0)
				one++;
			else if (s1[i + j] == env->letter_player && s2[j] == '*' && one > 0)
				break;
			j++;
		}
		if (s2[j] == '\0' && one == 1)
			return (i);
		i++;
	}
	return (-1);
}

int			ft_one_activ_line(t_env *env)
{
	if (ft_isstrstr(env->piece[0], "*") && !ft_isstrstr(env->piece[1], "*"))
		return (1);
	if (!ft_isstrstr(env->piece[0], "*") && ft_isstrstr(env->piece[1], "*"))
		return (2);
	return (0);
}

void		ft_algo_one_line(t_env *env, int ln)
{
	int		r_val;
	int		y;

	y = ln;
	while (y <= env->map_size_y - env->piece_size_y)
	{
		if ((r_val = ft_strstr_filler(env->map[y], env->piece[ln], env)) != -1)
		{
			ft_printf("%d %d\n", y - ln, r_val);
			return ;
		}
		y++;
	}
}

void		ft_algo(t_env *env)
{
	ft_extract_fragments_piece(env);

	/*	[***]	*/
	if (env->piece_size_y == 1)
		ft_algo_one_line(env, 0);
	/*	[***]
		[...]	*/
	else if (env->piece_size_y == 2 && ft_one_activ_line(env) == 1)
		ft_algo_one_line(env, 0);
	/*	[...]
		[***]	*/
	else if (env->piece_size_y == 2 && ft_one_activ_line(env) == 2)
		ft_algo_one_line(env, 1);
	/*	[***]
		[***]	*/
	// else if (env->piece_size_y == 2)
		// ft_algo_two_line(env);
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
