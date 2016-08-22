/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/22 19:51:21 by tbouder          ###   ########.fr       */
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
#include <stdio.h>

/*
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

					// ft_printf("%d %d\n", value[1], value[0]);
					ft_putnbr(value[1]); ft_putchar(' ');
					// ft_putnbr(x + value[0]);
					ft_putnbr(value[0]); ft_putchar('\n');
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
		ft_putendl_fd(str, fd);

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

*/
int			main(void)
{
	// t_env	env;

	// ft_launcher(&env);

	char *str;
	int fd = open("debug", O_WRONLY|O_APPEND);
	while (get_next_line(0, &str))
	{
		dprintf(fd, "%s\n", str);


		// ft_putendl_fd(str, fd);
	}

	close(fd);

	return (0);
}
