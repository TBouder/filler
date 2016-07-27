/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 19:26:23 by ebouther          #+#    #+#             */
/*   Updated: 2016/07/27 22:25:29 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"

typedef struct	s_env
{
	int		is_set_letter;
	int		is_set_map_size;
	int		is_set_board;

	char	**map;
	int		map_size_x;
	int		map_size_y;

	char	*piece;
	int		piece_size_x;
	int		piece_size_y;

	char	letter;
}				t_env;

#endif
