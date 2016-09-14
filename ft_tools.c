/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 17:19:43 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/13 15:21:43 by tbouder          ###   ########.fr       */
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

void		ft_print_update(t_env *env)
{
	int		fd;
	int		count1;
	int		count2;

	fd = open("debug", O_WRONLY | O_APPEND);
	count1 = 0;
	count2 = 0;
	while (count1 < MAX_MAP_Y)
	{
		ft_putendl_fd(env->map[count1], fd);
		count1++;
	}
	ft_putendl_fd("=================", fd);
	while (count2 < MAX_PIECE_Y)
	{
		ft_putendl_fd(env->piece[count2], fd);
		count2++;
	}
	ft_putstr_fd("\n\n", fd);
}
