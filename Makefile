# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 15:48:47 by tbouder           #+#    #+#              #
#    Updated: 2016/09/24 12:11:31 by tbouder          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	tbouder.filler

CC			= 	gcc -Ofast -Wunreachable-code
CFLAGS		= 	-Wall -Werror -Wextra

SRC 		= 	main.c ft_get.c ft_tools.c ft_orientation.c ft_fragments.c

LIB			=	-Llibft -lft

OBJ			=	$(SRC:.c=.o)

HEADER 		=	libft/libft.h

all: $(NAME)

.SILENT : $(NAME)
$(NAME):
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -c $(HEADER) $(SRC)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

.SILENT : clean
clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)
	rm -f *.gch
	rm -rf *.dSYM

.SILENT : fclean
fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all
