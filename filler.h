/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 19:26:23 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/26 18:09:18 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"

typedef struct	s_env
{
	int			phase;

	char		**map;
	int			map_size_x;
	int			map_size_y;

	int			middle_x1;
	int			middle_y1;
	int			middle_x2;
	int			middle_y2;

	char		**piece;
	int			piece_size_x;
	int			piece_size_y;

	char		letter_player;
	char		letter_adv;
}				t_env;

typedef struct	s_fill_current
{
	int			pos_x;
	int			pos_y;

	int			orientation;
	int			nb_elem_piece;
}				t_fill_current;

typedef struct	s_coo
{
	int			x_buff;
	int			y_buff;

	int			x_piece;
	int			y_piece;

	int			x_map;
	int			y_map;
}				t_coo;


/*
** Some Tools
*/
char			**ft_dbmalloc(int x, int y);
void			ft_find_middle(t_env *env);
int				ft_isletter(t_env *env, int x, int y);
int				ft_detail_piece(t_env *env);

/*
** Get infos from VM
*/
void			ft_get_player(t_env *env, char *str);
void			ft_get_map_size(t_env *env, char *str);
// void			ft_get_board(t_env *env, char *str, int y);
void			ft_get_board(t_env *env, char *str);
void			ft_get_piece_size(t_env *env, char *str);
void			ft_get_piece(t_env *env, char *str);
// void			ft_get_piece(t_env *env, char *str, int y);

/*
** Some details about the pos
*/
int				ft_hori_verti(t_env *env);
int				ft_pos_cmp_middle_y(t_env *env, int y);
int				ft_pos_cmp_middle_x(t_env *env, int x);

//DEBUG
void			ft_debug(t_env *env);
void			ft_debug2(t_fill_current current_env);

#endif
