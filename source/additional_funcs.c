/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:46:22 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:46:40 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

u_int64_t	ft_strlen64(char *str)
{
	u_int64_t	i;

	i = 0;
	while (*str++)
		++i;
	return (i);
}

__uint128_t	ft_strlen128(char *str)
{
	__uint128_t	i;

	i = 0;
	while (*str++)
		++i;
	return (i);
}

void		reverse_32(void *bufp, u_int64_t meslen)
{
	u_int64_t	i;
	u_int64_t	stop;
	char		*buffer;

	buffer = (char *)bufp;
	i = 0;
	stop = (meslen / 4 + 1) * 4;
	while (i < stop)
	{
		ft_strreverse(buffer + i, 4);
		i += 4;
	}
}

void		reverse_64(void *bufp, __uint128_t meslen)
{
	__uint128_t	i;
	__uint128_t	stop;
	char		*buffer;

	buffer = (char *)bufp;
	i = 0;
	stop = (meslen / 8 + 1) * 8;
	while (i < stop)
	{
		ft_strreverse(buffer + i, 8);
		i += 8;
	}
}
