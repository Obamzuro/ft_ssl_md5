# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 15:33:52 by obamzuro          #+#    #+#              #
#    Updated: 2020/02/24 16:43:14 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRCNAME = main.c			\
		  parser.c			\
		  additional_funcs.c\
		  md5.c				\
		  md5_funcs_1.c		\
		  md5_funcs_2.c		\
		  sha224.c			\
		  sha256.c			\
		  sha32_funcs_1.c	\
		  sha32_funcs_2.c	\
		  sha384.c			\
		  sha512.c			\
		  sha64_funcs_1.c	\
		  sha64_funcs_2.c	\
		  base64/base64.c

SRC = $(addprefix source/, $(SRCNAME))

OBJ = $(SRC:.c=.o)

LIBS = libft/libft.a libftprintf/libftprintf.a

HDRDIR = include\
		  libft/include\
		  libftprintf/include

HDR = include/ft_ssl.h

FLAGS = -Wall -Wextra -Werror -g

all: lib $(NAME)

$(NAME): $(OBJ) $(LIBS)
	gcc $(FLAGS) $(addprefix -I , $(HDRDIR)) -L libft -lft -L libftprintf -lftprintf $(OBJ) -o $(NAME)

lib:
	make -C libft
	make -C libftprintf

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

.PHONY: clean fclean re all lib
