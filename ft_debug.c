/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 10:44:00 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/13 10:44:19 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_debug(t_env *env)
{
	int		fd;
	int		i;

	fd = open("debug", O_WRONLY|O_APPEND);
	i = 0;
	ft_putstr_fd("O or X : ", fd);ft_putchar_fd(env->letter, fd); ft_putchar_fd('\n', fd);
	ft_putstr_fd("Map X : ", fd);ft_putnbr_fd(env->map_size_x, fd); ft_putchar_fd('\n', fd);
	ft_putstr_fd("Map Y : ", fd);ft_putnbr_fd(env->map_size_y, fd); ft_putchar_fd('\n', fd);

	ft_putstr_fd("Middle X1 : ", fd);ft_putnbr_fd(env->middle_x1, fd); ft_putchar_fd('\n', fd);
	ft_putstr_fd("Middle X2 : ", fd);ft_putnbr_fd(env->middle_x2, fd); ft_putchar_fd('\n', fd);
	ft_putstr_fd("Middle Y1 : ", fd);ft_putnbr_fd(env->middle_y1, fd); ft_putchar_fd('\n', fd);
	ft_putstr_fd("Middle Y2 : ", fd);ft_putnbr_fd(env->middle_y2, fd); ft_putchar_fd('\n', fd);

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
	ft_putstr_fd("\n\n", fd);
	close(fd);
}

void		ft_debug2(t_fill_current current_env)
{
	int fd = open("debug", O_WRONLY);

	current_env.pos_y == 1 ? ft_putstr_fd("POS Y : TOP\n", fd) : ft_putstr_fd("POS Y : DOWN\n", fd);
	current_env.pos_x == 1 ? ft_putstr_fd("POS X : RIGHT\n", fd) : ft_putstr_fd("POS X : LEFT\n", fd);

	if (current_env.orientation == 1)
		ft_putstr_fd("PIECE HORIZONTALE\n", fd);
	else if (current_env.orientation == -1)
		ft_putstr_fd("PIECE VERTICALE\n", fd);
	else
		ft_putstr_fd("PIECE EGALE\n", fd);

	ft_putstr_fd("NB ElEM PIECE : ", fd); ft_putnbr_fd(current_env.nb_elem_piece, fd); ft_putchar_fd('\n', fd);

	close(fd);
}
