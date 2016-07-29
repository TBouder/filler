/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 19:26:23 by ebouther          #+#    #+#             */
/*   Updated: 2016/07/29 17:20:11 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"

typedef struct	s_env
{
	int		phase;

	char	**map;
	int		map_size_x;
	int		map_size_y;

	char	**piece;
	int		piece_size_x;
	int		piece_size_y;

	char	letter;
}				t_env;

char			**ft_dbmalloc(int x, int y);

void			ft_get_player(t_env *env, char *str);
void			ft_get_map_size(t_env *env, char *str);
void			ft_get_board(t_env *env, char *str, int y);
void			ft_get_piece_size(t_env *env, char *str);
void			ft_get_piece(t_env *env, char *str, int y);

#endif
