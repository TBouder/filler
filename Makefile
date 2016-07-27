# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 15:48:47 by tbouder           #+#    #+#              #
#    Updated: 2016/07/27 11:51:39 by tbouder          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	tbouder.filler

CC			= 	gcc
CFLAGS		= 	-Wall -Werror -Wextra

SRC 		= 	main.c

LIB			=	-Llibft -lft

OBJ			=	$(SRC:.c=.o)

HEADER 		=	libft/libft.h

all: $(NAME)

.SILENT : $(NAME)
$(NAME):
	# $(MAKE) re -C libft
	$(CC) $(CFLAGS) -c $(HEADER) $(SRC)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

.SILENT : clean
clean:
	# $(MAKE) clean -C libft
	rm -f $(OBJ)
	rm -f *.gch
	rm -rf *.dSYM

.SILENT : fclean
fclean: clean
	# $(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all
