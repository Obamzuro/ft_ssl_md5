# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 15:33:52 by obamzuro          #+#    #+#              #
#    Updated: 2018/06/12 18:37:45 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRCNAME = main.c

SRC = $(addprefix source/, $(SRCNAME))

OBJ = $(SRC:.c=.o)

LIBS = libft/libft.a libftprintf/libftprintf.a

HDRDIR = include\
		  libft/include\
		  libftprintf/include

HDR = include/ft_ssl.h

FLAGS = -g

all: qwe $(NAME)

$(NAME): $(OBJ) $(LIBS)
	gcc $(FLAGS) $(addprefix -I , $(HDRDIR)) -L libft -lft -L libftprintf -lftprintf $(OBJ) -o $(NAME)

qwe:
	make -C libft
	make -C libftprintf
#libft/libft.a:
#	make -C libft
#
#libftprintf/libftprintf.a:
#	make -C libftprintf

%.o:%.c $(HDR)
	gcc $(FLAGS) $(addprefix -I , $(HDRDIR)) -c $< -o $@

clean:
	make -C libft clean
	make -C libftprintf clean
	find . -name ".*.sw[pon]" -exec rm -rf {} \;
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	make -C libftprintf fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
