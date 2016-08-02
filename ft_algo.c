/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/02 16:03:03 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/02 16:03:25 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_algo_pos_possibilities(t_env *env, t_fill_current current_env, int base_x, int base_y)
{
	int		x;
	int		y;
	int		fusion_one;
	int		error;

	fusion_one = 0;
	error = 0;
	//Vertical, down, right
	if ((current_env.orientation == -1 || current_env.orientation == 0) && current_env.pos_y == -1 && current_env.pos_x == 1)
	{
		x = 0;
		while (x < env->piece_size_x)
		{
			y = 0;
			while (y < env->piece_size_y)
			{
				if (env->map[base_y - y][base_x + x] == 'o' || env->map[base_y - y][base_x + x] == 'O')
					fusion_one++;
				if (env->map[base_y - y][base_x + x] == 'x' || env->map[base_y - y][base_x + x] == 'X')
					error++;
				if (fusion_one > 1 || error != 0)
					break ;
				y++;
			}
			if (fusion_one > 1 || error != 0)
				break ;
			x++;
		}
		if (fusion_one == 1 && error == 0)
			return (0);
		else
			return (1);
	}

	//Horizontal, down, right
	if ((current_env.orientation == 1 || current_env.orientation == 0) && current_env.pos_y == -1 && current_env.pos_x == 1)
	{
		x = 0;
		while (x < env->piece_size_x)
		{
			y = 0;
			while (y < env->piece_size_y)
			{
				if (env->map[base_y + y][base_x + x] == 'o' || env->map[base_y + y][base_x + x] == 'O')
					fusion_one++;
				if (env->map[base_y + y][base_x + x] == 'x' || env->map[base_y + y][base_x + x] == 'X')
					error++;
				if (fusion_one > 1 || error != 0)
					break ;
				y++;
			}
			if (fusion_one > 1 || error != 0)
				break ;
			x++;
		}
		if (fusion_one == 1 && error == 0)
			return (0);
		else
			return (1);
	}
	// if (current_env.orientation == -1 && current_env.pos_y == -1 && current_env.pos_x == -1);//Vertical, down, left
	// if (current_env.orientation == -1 && current_env.pos_y == 1 && current_env.pos_x == -1);//Vertical, top, left
	// if (current_env.orientation == -1 && current_env.pos_y == 1 && current_env.pos_x == 1);//Vertical, top, right

	// if (current_env.orientation == 1 && current_env.pos_y == -1 && current_env.pos_x == -1);//Horizontal, down, left
	// if (current_env.orientation == 1 && current_env.pos_y == 1 && current_env.pos_x == -1);//Horizontal, top, left
	// if (current_env.orientation == 1 && current_env.pos_y == 1 && current_env.pos_x == 1);//Horizontal, top, right

	// if (current_env.orientation == 0 && current_env.pos_y == -1 && current_env.pos_x == -1);//Cube, down, left
	// if (current_env.orientation == 0 && current_env.pos_y == 1 && current_env.pos_x == -1);//Cube, top, left
	// if (current_env.orientation == 0 && current_env.pos_y == 1 && current_env.pos_x == 1);//Cube, top, right
	return (1);
}

void		ft_algo_clear(t_env *env)
{
	int				x;
	int				y;
	t_fill_current	current_env;

	x = 0;
	y = 0;
	current_env.orientation = ft_hori_verti(env);
	current_env.nb_elem_piece = ft_detail_piece(env);

	while (y < env->map_size_y)
	{
		x = 0;
		while (x < env->map_size_x)
		{
			if (env->map[y][x] == 'o' || env->map[y][x] == 'O')
			{
				current_env.pos_x = ft_pos_cmp_middle_x(env, x);
				current_env.pos_y = ft_pos_cmp_middle_y(env, y);
				// ft_debug2(current_env);
				int fd = open("debug", O_WRONLY);
				if (ft_algo_pos_possibilities(env, current_env, x, y) == 0)
				{
					ft_putnbr_fd(y, fd); ft_putchar_fd(' ', fd); ft_putnbr_fd(x, fd);ft_putchar_fd('\n', fd);
					ft_putnbr(y); ft_putchar(' '); ft_putnbr(x);ft_putchar('\n');
				}
				close(fd);
			}
			x++;
		}
		y++;
	}
}
