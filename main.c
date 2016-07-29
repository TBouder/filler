/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/07/29 17:20:13 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_debug(t_env *env)
{
	int		fd;
	int		i;

	fd = open("debug", O_WRONLY);
	i = 0;
	ft_putstr_fd("O or X : ", fd);ft_putchar_fd(env->letter, fd); ft_putchar_fd('\n', fd);
	ft_putstr_fd("Map X : ", fd);ft_putnbr_fd(env->map_size_x, fd); ft_putchar_fd('\n', fd);
	ft_putstr_fd("Map Y : ", fd);ft_putnbr_fd(env->map_size_y, fd); ft_putchar_fd('\n', fd);

	while (i < env->map_size_y)
	{
		ft_putchar_fd('[', fd); ft_putstr_fd(env->map[i], fd); ft_putendl_fd("]", fd);
		i++;
	}
	ft_putstr_fd("Piece X : ", fd);ft_putnbr_fd(env->piece_size_x, fd); ft_putchar_fd('\n', fd);
	ft_putstr_fd("Piece Y : ", fd);ft_putnbr_fd(env->piece_size_y, fd); ft_putchar_fd('\n', fd);
	i = 0;
	while (i < env->piece_size_y)
	{
		ft_putchar_fd('[', fd); ft_putstr_fd(env->piece[i], fd); ft_putendl_fd("]", fd);
		i++;
	}
	close(fd);

}

void		ft_launcher(t_env *env)
{
	char	*str;
	int		y1;
	int		y2;

	y1 = 0;
	y2 = 0;
	env->phase = 0;

	while (get_next_line(0, &str))
	{
		if (env->phase == 0)
			ft_get_player(env, str);
		else if (env->phase == 1)
			ft_get_map_size(env, str);
		else if (env->phase == 2)
			ft_get_board(env, str, y1++);
		else if (env->phase == 3)
			ft_get_piece_size(env, str);
		else if (env->phase == 4)
		{
			ft_get_piece(env, str, y2++);
			ft_debug(env);
		}
	}
	ft_strdel(&str);
}

int			main(void)
{
	t_env	env;

	ft_launcher(&env);
	return (0);
}
