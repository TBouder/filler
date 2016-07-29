/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 17:19:43 by tbouder           #+#    #+#             */
/*   Updated: 2016/07/29 17:19:58 by tbouder          ###   ########.fr       */
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
