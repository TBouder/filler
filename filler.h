/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 19:26:23 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/12 15:31:11 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"

# define MAP(y, x)		env->map[y][x]
# define MAX_MAP_X		env->map_size_x
# define MAX_MAP_Y		env->map_size_y
# define MAX_PIECE_X	env->piece_size_x
# define MAX_PIECE_Y	env->piece_size_y
# define PIECE(y, x)	env->piece[y][x]

typedef struct	s_env
{
	int			phase;

	char		**map;
	int			*activ_line;
	int			map_size_x;
	int			map_size_y;

	char		**piece;
	int			piece_orientation;
	int			piece_size_x;
	int			piece_size_y;

	int			**fragments;
	int			nb_fragments;

	char		letter_player;
	char		letter_adv;

	int			direction_x;
	int			direction_y;
	int			tmp;
}				t_env;

/*
** Some Tools
*/
char			**ft_dbmalloc(int x, int y);
int				ft_detail_piece(t_env *env);

/*
** Get infos from VM
*/
void			ft_get_player(t_env *env, char *str);
void			ft_get_map_size(t_env *env, char *str);
void			ft_get_board(t_env *env, char *str);
void			ft_get_piece_size(t_env *env, char *str);
void			ft_get_piece(t_env *env, char *str);

/*
** Get the fragmets (the * of each piece)
*/
void			ft_extract_fragments_piece(t_env *env);
int				ft_test_fragments(t_env *env, int pos_x, int pos_y);

/*
** Get the general orientation
*/
void			ft_hori_verti(t_env *env);
void			ft_choose_direction(t_env *env);

#endif
