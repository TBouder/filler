/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 19:26:23 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/12 10:44:51 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"

typedef struct	s_env
{
	int			phase;
	char		**map_save;


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

#endif
