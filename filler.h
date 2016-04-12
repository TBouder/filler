/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 19:01:14 by tbouder           #+#    #+#             */
/*   Updated: 2016/04/12 11:32:45 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include  <fcntl.h>
# include "libft/libft.h"

# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct		s_fill
{
	int				line_id;
	char			*content;
	struct s_fill	*next;
	struct s_fill	*prev;
}					t_fill;

typedef struct		s_env
{
	int				p_nb;
	char			*p_name
}					t_env;

void				ft_fillend(char *s, t_fill **fill, int id);


#endif
