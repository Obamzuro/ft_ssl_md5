/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:52:34 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/14 20:24:58 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SSL_H
# define __FT_SSL_H
# include "libft.h"
# include "ft_printf.h"
# include <errno.h>
# define PARAMS "rpsq"
# define AM_PARAMS 4
# define AM_ALGHS 3
typedef struct	s_algh_corr
{
	char	*name;
	char	*namecap;
	void	(*func)(char *);
}				t_algh_corr;

int				preparation(int argc, char **argv,
		char params[256], t_algh_corr *alghs);

void			print_md5(char *message);
void			print_sha256(char *message);
void			print_sha224(char *message);
void			print_sha512(char *message);
#endif
