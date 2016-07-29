/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 17:19:43 by tbouder           #+#    #+#             */
/*   Updated: 2016/07/29 19:39:20 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char		**ft_dbmalloc(int x, int y)
{
	char	**str;
	int		i;

	i = 0;
	str = (char **)malloc(sizeof(char *) * y + 1);
	while (i <= y)
	{
		str[i] = ft_strnew(x);
		i++;
	}
	return (str);
}

void		ft_find_middle(t_env *env)
{
	env->middle_x1 = env->map_size_x / 2;
	env->middle_y1 = env->map_size_y / 2;
	env->middle_x2 = -1;
	env->middle_y2 = -1;
	if (env->map_size_x % 2 == 0)
		env->middle_x2 = (env->map_size_x / 2) + 1;
	if (env->map_size_y % 2 == 0)
		env->middle_y2 = (env->map_size_y / 2) + 1;
}
