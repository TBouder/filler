/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/26 19:54:38 by tbouder          ###   ########.fr       */
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


/*
** The ft_test() function will define the value [int *] var which is the X
** and Y coordinate to return and to use as answer for the Virtual Machine.
** Here, we have theses variables :
**	- one_letter	-> must be 1, indicate the number of player marking (O or X)
**						that have been encounter.
**	- error			-> must be 0, indicate the number of categorical stop.
**
** We will go through the piece, from the end to the beginning (while
** coo.y_piece >= 0 and coo.x_piece >= 0). Note that coo.x_piece is
** reinitialized at the end, to keep the starting pos from the loop in the
** calling function.
** Here the possibilities :
**	-	if we match the letter_player and the current element of the piece is a
**		star, then, we free value (USEFULLLLLL ???????) and we increase the var
**		one_letter.
**	-	if we match the letter_adv and the current element of the piece is a
**		star, then, we increase error (no match possible).
**	-	if we are out of map, we increase error, we shouldn't be here.
**	-	if we match the letter_player and the current element of the piece is
**		dot, then, it's okay and we keep it (do nothing for now).
**	-	if we match the letter_player and the current element of the piece is
**		no letter_player, no letter_adv, no dot, then, there is an error in the
**		map, we increase error.
** At the end of the loop, we move to the previous element of the piece by
** decreasing coo.x_piece. If it reach -1, we reset it to its original position.
**
** If we match one_letter = 1, so we have one and only one * matching a
** letter_player mark, and error is null (0), we initialize the value with the
** coordinate of the map, witch are the start of the piece in the map. Else, we
** return NULL.
** ------------------------------------
** ARG -	Take as args the whole env as [t_env] and the various coordinates
**			as [t_coo].
** RET -	Return a *int with the X and Y answer coordinate, or NULL if error.
** ------------------------------------
*/
int			*ft_test(t_env *env, t_coo coo)
{
	/*>>*/int fd = open("debug", O_WRONLY|O_APPEND);

	int		one_letter;
	int		error;
	int		*value;

	value = ft_nbrnew(2);
	one_letter = 0;
	error = 0;

	// int			dot_line_acceptance_map;
	// int			dot_line_piece;
	// dot_line_acceptance_map = ft_count_char_line(env->map, env->map_size_x, y, '.');
	// dot_line_acceptance_map += ft_count_char_line(env->map, env->map_size_x, y, env->letter_adv);
	// dot_line_piece = ft_count_char_line(env->piece, env->piece_size_x, y, '.');

	while (coo.y_piece >= 0)
	{
		while (coo.x_piece >= 0)
		{
			/*>>*/	dprintf(fd, "Test : [%d-%d] -- [%d-%d]", coo.y_piece, coo.x_piece, coo.y_piece + coo.y_map, coo.x_piece + coo.x_map);
			/*>>*/	dprintf(fd, " | On map : [%c]", env->map[coo.y_piece + coo.y_map][coo.x_piece + coo.x_map]);
			/*>>*/	dprintf(fd, " | Piece : [%c]", env->piece[coo.y_piece][coo.x_piece]);
			if (ft_isletter(env, coo.x_piece + coo.x_map, coo.y_piece + coo.y_map) == 1) //A REMPLACER PAR letter_player
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
					error++; // NEED BREAK ??
				}
			}
			else if (ft_isletter(env, coo.x_piece + coo.x_map, coo.y_piece + coo.y_map) == -1) // TO DEL
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

/*
** The ft_try_piece() function will define the value [int *] var which is the X
** and Y coordinate to return and to use as answer for the Virtual Machine.
** Here, we have theses variables :
**	- coo.x_map		-> the X position, in the map, we are currently testing.
**	- coo.y_map		-> the Y position, in the map, we are currently testing.
**	- coo.x_piece	-> the X position of the last element of the piece.
**	- coo.y_piece	-> the Y position of the last element of the piece.
**	- coo.x_buff	-> same as coo.x_piece, will tell us when we reach the start
**						of the current line.
**	- coo.y_buff	-> same as coo.y_piece, will tell us when we reach the first
**						line of the piece.
**
** NOTE : The coo.[x.y]_map are moving, the coo.[x.y]_buff helps us to determine
** where we are inside of the piece, and the coo.[x.y]_piece are used in the
** ft_test() function.
**
** First, value will be NULL and we will enter the first loop, in which we will
** call the ft_test() function. We will have a value for value, or NULL.
** Then
**	-	if NULL is returned and both coo.x_buff and coo.y_buff are 0, it means
**		that we have reached the beginning of the piece without any possibility
**		to push it inside the map -> NULL is returned.
**	- 	if NULL is returned and ONLY coo.x_buff is 0, it means that we have
**	 	reached the beginning of the line. Then, we reset coo.x_map and
**		coo.x_buff to their original positions X and we decrease both coo.y_map
**		and coo.y_buff to move to the line above (we test a new line).
**	-	if NULL is returned and coo.x_buff is greater than 0, we decrease both
**		coo.x_map and coo.x_buff to move in the line and test a new position.
** If value is not NULL, we return it.
** ------------------------------------
** ARG -	Take as args the whole env as [t_env] and the x and y positions in
**			the map as [int].
** RET -	Return a *int with the X and Y answer coordinate, or NULL if error.
** ------------------------------------
*/
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
				return (NULL);
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
** The ft_count_total_dots() function will count all the dots in the map to
** determine if there is space for another piece.
** ------------------------------------
** ARG -	Take as args the map as [char **], the width as [int] and the height
**			as [int].
** RET -	Return the number of dots.
** ------------------------------------
*/
int			ft_count_total_dots(char **to_look, int size_x, int size_y)
{
	int		count;
	int		x;
	int		y;

	count = 0;
	y = 0;
	while (y < size_y)
	{
		x = 0;
		while (x < size_x)
		{
			if (to_look[y][x] == '.')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/*
** The ft_count_line_dots() function will count the number of char [c] in the
** line y
** ------------------------------------
** ARG -	Take as args the map as [char **], the width as [int] and the line
**			to test as [int].
** RET -	Return the number of char [c].
** ------------------------------------
*/
int			ft_count_char_line(char **to_look, int size_x, int pos_y, char c)
{
	int		count;
	int		x;

	count = 0;
	x = 0;
	while (x < size_x)
	{
		if (to_look[pos_y][x] == c)
			count++;
		x++;
	}
	return (count);
}

/*
** FT_ALGO parcours la map et des que l'on rencontre notre lettre, on test la
** possibilite de mettre la piece via la fonction X
*/
int			ft_algo(t_env *env)
{
	/*>>*/int fd = open("debug", O_WRONLY|O_APPEND);
	int			x;
	int			y;
	int			*value;
	int			dot_map;

	y = 0;
	dot_map = ft_count_total_dots(env->map, env->map_size_x, env->map_size_y);
	if (dot_map == 0)
		ft_printf("END");

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
