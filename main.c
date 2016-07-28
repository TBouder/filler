/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:23:17 by tbouder           #+#    #+#             */
/*   Updated: 2016/07/28 23:38:43 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_get_board(t_env *env, char *str, int y)
{
	int		x;

	x = 0;
	while (x < env->map_size_x)
	{
		env->map[y][x] = str[x];
		x++;
	}
	if (y == env->map_size_y)
		env->is_set_board = TRUE;
}

void		ft_dbmalloc(char **str, int x, int y)
{
	int		i;

	i = 0;
	str = malloc(sizeof(char **) * y);
	while (i < y)
	{
		str[i] = ft_strnew(x);
		i++;
	}
}

void		ft_get_map_size(t_env *env, char *str)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	if (ft_strncmp(str, "Plateau", 8))
	{
		split = ft_strsplit(str, ' ');
		env->map_size_y = ft_atoi(split[1]);
		env->map_size_x = ft_atoi(split[2]);
		ft_dbmalloc(env->map, env->map_size_x, env->map_size_y);
		env->is_set_map_size = TRUE;
	}
}

void		ft_get_player(t_env *env, char *str)
{
	if (ft_strncmp(str, "$$$ exec p1 : [", 16))
	{
		env->letter = 'O';
		env->is_set_letter = TRUE;
	}
	else if (ft_strncmp(str, "$$$ exec p2 : [", 16))
	{
		env->letter = 'X';
		env->is_set_letter = TRUE;
	}
}

void		debug(char *str, t_env *env)
{
	static int i = 0;
	int fd = open("debug", O_RDWR, O_APPEND);
	if (i == 0)
	{
		ft_putstr_fd("is_set_letter : ", fd);ft_putnbr_fd(env->is_set_letter, fd);ft_putchar_fd('\n', fd);
		ft_putstr_fd("is_set_map_size : ", fd);ft_putnbr_fd(env->is_set_map_size, fd);ft_putchar_fd('\n', fd);
		ft_putstr_fd("is_set_board : ", fd);ft_putnbr_fd(env->is_set_board, fd);ft_putchar_fd('\n', fd);
		i = 1;
	}
	if (0)
		ft_putendl_fd(str, fd);
	close(fd);
}

void		ft_launcher(t_env *env)
{
	char	*str;
	int		y;

	y = 0;
	env->is_set_letter = FALSE;
	env->is_set_map_size = FALSE;
	env->is_set_board = FALSE;
	int fd = open("debug", O_WRONLY);
	while (get_next_line(0, &str))
	{
		// ft_putstr_fd("STR : ", fd);ft_putstr_fd(str, fd); ft_putchar_fd('\n',  fd);
		if (env->is_set_letter == FALSE)
			ft_get_player(env, str);
		else if (env->is_set_letter == TRUE && env->is_set_map_size == FALSE)
		{
			ft_get_map_size(env, str);
				// ft_putstr_fd("X : ", fd);ft_putnbr_fd(env->map_size_x, fd); ft_putchar_fd('\n',  fd);
				// ft_putstr_fd("Y : ", fd);ft_putnbr_fd(env->map_size_y, fd); ft_putchar_fd('\n',  fd);
		}
		else if (env->is_set_letter == TRUE && env->is_set_map_size == TRUE && env->is_set_board == FALSE)
		{
			ft_get_board(env, str, y++);
				// ft_putstr_fd("Y_mv : ", fd);ft_putnbr_fd(y, fd); ft_putchar_fd('\n',  fd);
		}


	}
	ft_strdel(&str);
	close(fd);
}

int			main(void)
{
	t_env	env;

	ft_launcher(&env);
	// if (env.letter != 0)
		// ft_putstr("7 5\n");
	return (0);
}
