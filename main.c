/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/02 18:48:20 by tbouder          ###   ########.fr       */
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

int			ft_isletter(t_env *env, int x, int y)
{
	if (x > env->map_size_x || y > env->map_size_y)
		return (0);
	if (env->letter == 'O')
	{
		if (env->map[y][x] == 'o' || env->map[y][x] == 'O')
			return (1);
	}
	else if (env->letter == 'X')
	{
		if (env->map[y][x] == 'x' || env->map[y][x] == 'X')
			return (1);
	}
	return (0);
}

int			*ft_check_if_match(t_env *env, int x, int y)
{
	int		x_piece;
	int		y_piece;
	int		one_letter;
	int		error;
	int		*value;

	value = ft_nbrnew(2);
	y_piece = 0;
	one_letter = 0;
	error = 0;

	int fd = open("debug", O_WRONLY|O_APPEND);
	while (y_piece < env->piece_size_y)
	{
		x_piece = 0;
		while (x_piece < env->piece_size_x)
		{
			// La case de la piece
			ft_putstr_fd("Test : [", fd);ft_putnbr_fd(y_piece, fd);ft_putchar_fd('-', fd); ft_putnbr_fd(x_piece, fd);ft_putstr_fd("]", fd);

			// La case sur la map
			ft_putstr_fd(" -- [", fd);ft_putnbr_fd(y + y_piece, fd);ft_putchar_fd('-', fd); ft_putnbr_fd(x + x_piece, fd);ft_putstr_fd("]", fd);
			if (ft_isletter(env, x + x_piece, y + y_piece) == 1 && env->piece[y_piece][x_piece] == '*')

			// ft_putstr_fd(" -- [", fd);ft_putnbr_fd(y, fd);ft_putchar_fd('-', fd); ft_putnbr_fd(x, fd);ft_putstr_fd("]", fd);
			// if (ft_isletter(env, x, y) == 1 && env->piece[y_piece][x_piece] == '*')
			{
				ft_putstr_fd(" (OK)", fd);
				value[0] = x + x_piece;
				value[1] = y + y_piece;
				one_letter++;
			}
			else if (ft_isletter(env, x + x_piece, y + y_piece) == 1 && env->piece[y_piece][x_piece] == '.')
			{
				ft_putstr_fd(" (Empty)", fd);
				;
			}
			else if (env->map[y + y_piece][x + x_piece] != '.')
			{
				ft_putstr_fd(" (Error)", fd);
				error++;
			}
			x_piece++;
			ft_putstr_fd("\n", fd);

		}
		y_piece++;
	}
	if (one_letter == 1 && error == 0)
	{
		ft_putstr_fd("GOOD : [", fd); ft_putnbr_fd(value[1], fd); ft_putstr_fd(" - ", fd); ft_putnbr_fd(value[0], fd); ft_putstr_fd("]\n", fd);
		return (value);
	}
	ft_putnbr_fd(error, fd);
	ft_putstr_fd("\nBAD\n", fd);
	return (NULL);

	close(fd);
}

int			ft_algo(t_env *env)
{
	int				x;
	int				y;
	int				*value;
	t_fill_current	current_env;

	y = 0;
	current_env.orientation = ft_hori_verti(env);
	current_env.nb_elem_piece = ft_detail_piece(env);
	int fd = open("debug", O_WRONLY|O_APPEND);

	while (y < env->map_size_y)
	{
		x = 0;
		while (x < env->map_size_x)
		{
			if (ft_isletter(env, x, y) == 1)
			{
				value = ft_check_if_match(env, x, y);
				if (value != NULL)
				{
					// ft_putnbr(y + value[1]);
					ft_putnbr(value[1]);
					ft_putchar(' ');
					// ft_putnbr(x + value[0]);
					ft_putnbr(value[0]);
					ft_putchar('\n');
					free(value);
					return (1);
				}
				else
				{
					ft_putstr_fd("NOP", fd);
				}

				// current_env.pos_x = ft_pos_cmp_middle_x(env, x);
				// current_env.pos_y = ft_pos_cmp_middle_y(env, y);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void		ft_launcher(t_env *env)
{
	char	*str;
	int		y1;
	int		y2;

	y1 = 0;
	y2 = 0;
	env->phase = 0;

	int fd = open("debug", O_WRONLY|O_APPEND);
	while (get_next_line(0, &str))
	{
		// ft_putendl_fd(str, fd);

		if (ft_isstrstr(str, "$$$ exec "))
			ft_get_player(env, str);

		else if (ft_isstrstr(str, "Plateau"))
			ft_get_map_size(env, str);

		else if (env->phase == 2)
		{
			if (y1 == 0)
				get_next_line(0, &str);
			ft_get_board(env, str, y1++);
		}

		else if (ft_isstrstr(str, "Piece"))
		{
			y1 = 0;
			ft_get_piece_size(env, str);
		}

		else if (env->phase == 4)
			ft_get_piece(env, str, y2++);
		if (env->phase == 5)
		{
			y2 = 0;
			// ft_debug(env);
			ft_algo(env);
		}


	}
	ft_strdel(&str);
	close(fd);
}

int			main(void)
{
	t_env	env;

	ft_launcher(&env);
	return (0);
}
