# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 15:48:47 by tbouder           #+#    #+#              #
#    Updated: 2016/08/23 16:43:39 by tbouder          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	tbouder.filler

CC			= 	gcc
CFLAGS		= 	-Wall -Werror -Wextra

SRC 		= 	main.c ft_get.c ft_tools.c ft_debug.c ft_pos_infos.c

LIB			=	libft/libft.a

OBJ			=	$(SRC:.c=.o)

HEADER 		=	libft/libft.h

all: $(NAME)

.SILENT : $(NAME)
$(NAME):
	# $(MAKE) re -C library
	$(CC) $(CFLAGS) -c $(HEADER) $(SRC)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

.SILENT : clean
clean:
	# $(MAKE) clean -C library
	rm -f $(OBJ)
	rm -f *.gch
	rm -rf *.dSYM

.SILENT : fclean
fclean: clean
	# $(MAKE) fclean -C library
	rm -f $(NAME)

re: fclean all
