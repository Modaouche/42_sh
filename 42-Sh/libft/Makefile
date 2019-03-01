# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 15:06:27 by modaouch          #+#    #+#              #
#    Updated: 2018/12/12 15:35:41 by modaouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = libft.h

SRC = ft_atoi.c\
	  ft_bzero.c\
	  ft_sqrt.c\
	  ft_recursive_power_c.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_isspace.c\
	  ft_isprint.c\
	  ft_itoa.c\
	  ft_memalloc.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memdel.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_putchar.c\
	  ft_putchar_fd.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_putnbr.c\
	  ft_putnbr_fd.c\
	  ft_putstr.c\
	  ft_putstr_fd.c\
	  ft_strcat.c\
	  ft_strchr.c\
	  ft_strclr.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strdel.c\
	  ft_strdup.c\
	  ft_strndup.c\
	  ft_strequ.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strlcat.c\
	  ft_strlen.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strncat.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_strnequ.c\
	  ft_strnew.c\
	  ft_strrchr.c\
	  ft_strchrnull.c\
	  ft_strsplit.c\
	  ft_strstr.c\
	  ft_strnstr.c\
	  ft_strsub.c\
	  ft_strtrim.c\
	  ft_strcapitalize.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  ft_swap.c\
	  ft_strcdup.c\
	  ft_occur.c\
	  ft_print_bits.c\
	  ft_itoa_base.c\
	  ft_strjoin_free.c\
	  ft_nbrlen.c\
	  ft_strclen.c\
	  ft_is_in_str.c\
	  ft_multijoin.c\
	  ft_multisplit.c\
#	  get_next_line.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS += -Wall -Wextra -Werror #-g3 -fsanitize=address

all : $(NAME)

$(NAME) : $(OBJ) Makefile $(HEADER)
	ar rc $@ $(OBJ)
	ranlib $@

clean :
	rm -rf $(OBJ)

fclean :
	rm -rf $(OBJ)
	rm -rf $(NAME)

re : fclean all
