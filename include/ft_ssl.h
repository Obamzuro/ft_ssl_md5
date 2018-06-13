/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:52:34 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/13 19:41:01 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SSL_H
# define __FT_SSL_H
# include "libft.h"
# include "ft_printf.h"
# define PARAMS "rpsq"
# define AM_PARAMS 4
# define AM_ALGHS 4
typedef struct	s_abcd
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_abcd;

typedef struct	s_algh_corr
{
	char	*name;
	void	(*func)(char *);
}				t_algh_corr;

int				preparation(int argc, char **argv,
		char params[256], t_algh_corr *alghs);
#endif
