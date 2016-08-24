/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/24 15:43:07 by tbouder          ###   ########.fr       */
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

#include <stdio.h> ///////////////////////////

int			*ft_test(t_env *env, t_coo coo)
{
	// /*>>*/int fd = open("debug", O_WRONLY|O_APPEND);

	int		one_letter;
	int		error;
	int		*value;
	int		to_cmp_y;
	int		to_cmp_x;

	value = ft_nbrnew(2);
	one_letter = 0;
	error = 0;

	while (coo.y_piece < env->piece_size_y)
	{
		while (coo.x_piece < env->piece_size_x)
		{
			to_cmp_y = coo.y_map + coo.y_piece;
			to_cmp_x = coo.x_map + coo.x_piece;
			// /*>>*/	dprintf(fd, "Test : [%d-%d] -- [%d-%d]", coo.y_piece, coo.x_piece, to_cmp_y, to_cmp_x);
			if (ft_isletter(env, to_cmp_x, to_cmp_y) == 1 && env->piece[coo.y_piece][coo.x_piece] == '*')
			{
				// /*>>*/ft_putstr_fd(" (OK)", fd);
				value[0] = to_cmp_x;
				value[1] = to_cmp_y;
				one_letter++;
			}
			else if (ft_isletter(env, to_cmp_x, to_cmp_y) == 2 && env->piece[coo.y_piece][coo.x_piece] == '*')
			;// /*>>*/ft_putstr_fd(" (ENCOUNTER BAD LETTER)", fd);
			else if (ft_isletter(env, to_cmp_x, to_cmp_y) == -1 && env->piece[coo.y_piece][coo.x_piece] == '*')
			;// /*>>*/ft_putstr_fd(" (OUT OF MAP)", fd);
			else if (ft_isletter(env, to_cmp_x, to_cmp_y) == 1 && env->piece[coo.y_piece][coo.x_piece] == '.')
			{
				// /*>>*/ft_putstr_fd(" (Empty)", fd);
				;
			}
			else if (env->map[to_cmp_y][to_cmp_x] != '.')
			{
				error++;
				// /*>>*/ft_putstr_fd(" (Error)", fd);
			}
			coo.x_piece++;
			// /*>>*/ft_putstr_fd("\n", fd);
		}
		coo.x_piece = 0;
		coo.y_piece++;
	}

	if (one_letter == 1 && error == 0)
	{
		// /*>>*/dprintf(fd, "GOOD : [%d-%d]\n", value[1], value[0]);
		return (value);
	}
	else
	// /*>>*/dprintf(fd, "Nb error : %d [BAD]\n", error);
	return (NULL);
}

int			*ft_will_call_ft_test(t_env *env, int x, int y)
{
	// /*>>*/int fd = open("debug", O_WRONLY|O_APPEND);
	t_coo	coo;
	int		*value;

	value = NULL;
	coo.x_map = x;
	coo.y_map = y;
	coo.x_piece = 0;
	coo.y_piece = 0;
	coo.x_buff = coo.x_piece;
	coo.y_buff = coo.y_piece;
	while (value == NULL)
	{
		// /*>>*/dprintf(fd, "------------------->[%d-%d]\n", coo.y_buff, coo.x_buff);
		value = ft_test(env, coo);
		// /*>>*/dprintf(fd, "[%d-%d]<-------------------\n\n", coo.y_buff, coo.x_buff);
		if (value == NULL)
		{
			if (coo.x_buff == env->piece_size_x && coo.y_buff == env->piece_size_y)
			{
				//Nous sommes arrives au bout de la piece, donc on ne peut pas la mettre ici, donc on passe a la pos suivante
				return (NULL);
			}
			else if (coo.x_buff < env->piece_size_x)
			{
				//La current pos de la piece n'a rien donnee mais il nous reste une partie de la piece a tester (X)
				// On avance dans le buffer, et on recule dans la map
				coo.x_buff++;
				coo.x_map--;
				if (coo.x_map < env->map_size_x)
					return (NULL);
			}
			else if (coo.x_buff >= env->piece_size_x)
			{
				//La current pos de la piece n'a rien donnee mais il nous reste une partie, vers le bas (Y)
				coo.x_buff = 0;
				coo.x_map = x;
				coo.y_buff++;
				coo.y_map--;
				if (coo.y_map < env->map_size_y)
					return (NULL);
			}
		}
	}
	return (value);
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
			// [La case de la piece] -- [La case sur la map]
			dprintf(fd, "Test : [%d-%d] -- [%d-%d]", y_piece, x_piece, y + y_piece, x + x_piece);

			// if (ft_isletter(env, x, y) == 1 && env->piece[y_piece][x_piece] == '*')
			if (ft_isletter(env, x + x_piece, y + y_piece) == 1 && env->piece[y_piece][x_piece] == '*')
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

void		ft_print_map(t_env *env)
{
	int fd = open("debug", O_WRONLY|O_APPEND);
	int		i = 0;
	while (i < env->map_size_y)
	{
		dprintf(fd, "[%s]\n", env->map[i]);
		i++;
	}
	dprintf(fd, "\n\n");
}

int			ft_algo(t_env *env)
{
	int				x;
	int				y;
	int				*value;
	t_fill_current	current_env;

	current_env.orientation = ft_hori_verti(env);
	current_env.nb_elem_piece = ft_detail_piece(env);
	int fd = open("debug", O_WRONLY|O_APPEND);

	y = 0;
	ft_print_map(env);
	while (y < env->map_size_y)
	{
		x = 0;
		while (x < env->map_size_x)
		{
			if (env->map[y][x] == 'o' || env->map[y][x] == 'O')
			// if (ft_isletter(env, x, y) == 1)
			{
				// value = ft_check_if_match(env, x, y);
				value = ft_will_call_ft_test(env, x, y);
				if (value != NULL)
				{
					ft_printf("%d %d\n", value[1], value[0]);
					free(value);
					return (1);
				}
				else
					ft_putstr_fd("NOP\n", fd);
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

	env->phase = 0;
	/*>>*/ int fd = open("debug", O_WRONLY|O_APPEND);
	while (get_next_line(0, &str))
	{
		if (ft_isstrstr(str, "$$$ exec "))
		{
			dprintf(fd, "PASSAGE 1 : %s\n", str);
			ft_get_player(env, str);
		}
		if (ft_isstrstr(str, "Plateau"))
		{
			dprintf(fd, "PASSAGE 2 : %s\n", str);
			ft_get_map_size(env, str);
			get_next_line(0, &str);
		}
		if (env->phase == 2)
		{
			dprintf(fd, "PASSAGE 3 : %s\n", str);
			ft_get_board(env, str);
		}
		if (ft_isstrstr(str, "Piece"))
		{
			dprintf(fd, "PASSAGE 4 : %s\n", str);
			ft_get_piece_size(env, str);
		}
		if (env->phase == 4)
		{
			dprintf(fd, "PASSAGE 5 : %s\n", str);
			ft_get_piece(env, str);
		}
		if (env->phase == 5)
		{
			dprintf(fd, "PASSAGE 6 : %s\n", str);
			ft_algo(env);
		}
	}
	ft_strdel(&str);
}

int			main(void)
{
	static t_env	env;

	ft_launcher(&env);
	return (0);
}
