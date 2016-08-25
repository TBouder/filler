/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/25 12:27:54 by tbouder          ###   ########.fr       */
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
void		ft_print_map(t_env *env)
{
	int fd = open("debug", O_WRONLY|O_APPEND);
	int		i = 0;
	while (i < env->map_size_y)
	{
		dprintf(fd, "[%s]\n", env->map[i]);
		i++;
	}
	dprintf(fd, "\n");
	i = 0;
	while (i < env->piece_size_y)
	{
		dprintf(fd, "[%s]\n", env->piece[i]);
		i++;
	}
	dprintf(fd, "\n\n");
}

int			*ft_test(t_env *env, t_coo coo)
{
	/*>>*/int fd = open("debug", O_WRONLY|O_APPEND);

	int		one_letter;
	int		error;
	int		*value;

	value = ft_nbrnew(2);
	one_letter = 0;
	error = 0;

	while (coo.y_piece >= 0)
	{
		while (coo.x_piece >= 0)
		{
			/*>>*/	dprintf(fd, "Test : [%d-%d] -- [%d-%d]", coo.y_piece, coo.x_piece, coo.y_piece + coo.y_map, coo.x_piece + coo.x_map);
			/*>>*/	dprintf(fd, " | On map : [%c]", env->map[coo.y_piece + coo.y_map][coo.x_piece + coo.x_map]);
			/*>>*/	dprintf(fd, " | Piece : [%c]", env->piece[coo.y_piece][coo.x_piece]);
			if (ft_isletter(env, coo.x_piece + coo.x_map, coo.y_piece + coo.y_map) == 1)
			{
				if (env->piece[coo.y_piece][coo.x_piece] == '*')
				{
					if (value && value[0])
						free(value);
					/*>>*/dprintf(fd, " (OK) : [%d-%d]", value[1], value[0]);
					one_letter++;
				}
			}
			else if (ft_isletter(env, coo.x_piece + coo.x_map, coo.y_piece + coo.y_map) == 2)
			{
				if (env->piece[coo.y_piece][coo.x_piece] == '*')
				{
					/*>>*/ft_putstr_fd(" (ENCOUNTER BAD LETTER)", fd);
					error++;
				}
			}
			else if (ft_isletter(env, coo.x_piece + coo.x_map, coo.y_piece + coo.y_map) == -1)
			{
				if (env->piece[coo.y_piece][coo.x_piece] == '*')
				{
					/*>>*/ft_putstr_fd(" (OUT OF MAP)", fd);
					error++;
				}
			}
			else if (ft_isletter(env, coo.x_piece + coo.x_map, coo.y_piece + coo.y_map) == 1)
			{
				if (env->piece[coo.y_piece][coo.x_piece] == '.')
					/*>>*/ft_putstr_fd(" (Empty)", fd);
			}
			else if (env->map[coo.y_piece + coo.y_map][coo.x_piece + coo.x_map] != '.')
			{
				error++;
				/*>>*/ft_putstr_fd(" (Error)", fd);
			}
			coo.x_piece--;
			/*>>*/ft_putstr_fd("\n", fd);
		}
		coo.x_piece = env->piece_size_x - 1;
		coo.y_piece--;
	}

	if (one_letter == 1 && error == 0)
	{
		value[0] = coo.x_map;
		value[1] = coo.y_map;
		/*>>*/dprintf(fd, "GOOD : [%d-%d]\n", value[1], value[0]);
		return (value);
	}
	else
	{
		/*>>*/dprintf(fd, "Nb error : %d [BAD]\n", error);
		return (NULL);
	}
}


int			*ft_try_piece(t_env *env, int x, int y)
{
	/*>>*/int fd = open("debug", O_WRONLY|O_APPEND);
	t_coo	coo;
	int		*value;

	value = NULL;
	coo.x_map = x;
	coo.y_map = y;
	coo.x_piece = env->piece_size_x - 1;
	coo.y_piece = env->piece_size_y - 1;
	coo.x_buff = coo.x_piece;
	coo.y_buff = coo.y_piece;

	while (value == NULL)
	{
		if (coo.x_map < 0 || coo.y_map < 0)
			return (NULL);
		/*>>*/dprintf(fd, "------------------->[%d-%d]\n", coo.y_piece, coo.x_piece);
		value = ft_test(env, coo);
		/*>>*/dprintf(fd, "<-------------------\n\n");
		if (value == NULL)
		{
			if (coo.x_buff == 0 && coo.y_buff == 0)
			{
				return (NULL);
			}
			else if (coo.x_buff == 0)
			{
				coo.x_map = x;
				coo.x_buff = coo.x_piece;
				coo.y_map--;
				coo.y_buff--;
			}
			if (coo.x_buff > 0)
			{
				coo.x_map--;
				coo.x_buff--;
			}

		}
	}
	return (value);
}


/*
** FT_ALGO parcours la map et des que l'on rencontre notre lettre, on test la
** possibilite de mettre la piece via la fonction X
*/
int			ft_algo(t_env *env)
{
	/*>>*/int fd = open("debug", O_WRONLY|O_APPEND);
	int				x;
	int				y;
	int				*value;

	y = 0;
	ft_print_map(env);
	while (y < env->map_size_y)
	{
		x = 0;
		while (x < env->map_size_x)
		{
			if (ft_isletter(env, x, y) == 1)
			{
				value = ft_try_piece(env, x, y);
				if (value != NULL)
				{
					ft_printf("%d %d\n", value[1], value[0]);
					/*>>*/dprintf(fd, "%d %d\n", value[1], value[0]);
					free(value);
					return (1);
				}
				/*>>*/else
					/*>>*/ft_putstr_fd("==========NOP==========\n\n", fd);
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
	while (get_next_line(0, &str))
	{
		if (ft_isstrstr(str, "$$$ exec "))
			ft_get_player(env, str);
		if (ft_isstrstr(str, "Plateau"))
		{
			ft_get_map_size(env, str);
			get_next_line(0, &str);
		}
		if (env->phase == 1)
			ft_get_board(env, str);
		if (ft_isstrstr(str, "Piece"))
			ft_get_piece_size(env, str);
		if (env->phase == 2)
			ft_get_piece(env, str);
		if (env->phase == 3)
			ft_algo(env);
	}
	ft_strdel(&str);
}

int			main(void)
{
	static t_env	env;

	ft_launcher(&env);
	return (0);
}
