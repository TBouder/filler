/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/02 12:45:38 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- Trouver le milieu
- Regarder ou l'on est par rapport au milieu
- Regarder ou est l'adv par rapport au milieu

- Rusher vers le center de la map le plus possible

- Si on recoit une piece plus grande horizontalement, privilegier l'horizontale
- Si on recoit une piece plus grande verticalement, privilegier la verticale
*/

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

int			ft_dot_before(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] == '.' || str[i] == c))
		i++;
	return (i);
}

int			ft_hori_verti(t_env *env)
{
	if (env->piece_size_x > env->piece_size_y)
		return (1); //HORIZONTAL
	else if (env->piece_size_x < env->piece_size_y)
		return (-1); //VERTICAL
	else
		return (0); //OSEF
}

int			ft_pos_cmp_middle_y(t_env *env, int y)
{
	// 1 => top
	// -1 => down
	if (y > env->middle_y1)
		return (-1);
	else if (y < env->middle_y2 && env->middle_y2 != -1)
		return (1);
	else
		return (1);
}

int			ft_pos_cmp_middle_x(t_env *env, int x)
{
	// 1 => right
	// -1 => left
	if (x > env->middle_x1)
		return (-1);
	else if (x < env->middle_x2 && env->middle_x2 != -1)
		return (1);
	else
		return (1);
}

int			ft_detail_piece(t_env *env)
{
	int		x;
	int		y;
	int		nb;

	y = 0;
	nb = 0;
	while (y < env->piece_size_y)
	{
		x = 0;
		while (x < env->piece_size_x)
		{
			if (env->piece[y][x] == '*')
				nb++;
			x++;
		}
		y++;
	}
	return (nb);
}

int		**ft_test(t_env *env)
{
	int		**r_value;
	int		i;
	int		y;
	int		x;
	int		nb_elem;

	i = 0;
	nb_elem = ft_detail_piece(env);

	r_value = (int **)malloc(sizeof(int *) * nb_elem);
	while (i < nb_elem)
	{
		r_value[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}

	i = 0;
	y = 0;
	while (y < env->piece_size_y)
	{
		x = 0;
		while (x < env->piece_size_x)
		{
			if (env->piece[y][x] == '*')
			{
				r_value[i][0] = y;
				r_value[i][1] = x;
				i++;
			}
			x++;
		}
		y++;
	}
	return (r_value);
}

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
		{
			if (y1 == 0)
				get_next_line(0, &str);
			ft_get_board(env, str, y1++);
		}
		else if (env->phase == 3)
			ft_get_piece_size(env, str);
		else if (env->phase == 4)
		{
			ft_get_piece(env, str, y2++);
			// ft_debug(env);
			// ft_algo(env);
			ft_algo_clear(env);
		}
		// else if (env->phase == 5)
			// env->phase = 1;
	}
	ft_strdel(&str);
}

int			main(void)
{
	t_env	env;

	ft_launcher(&env);
	return (0);
}
