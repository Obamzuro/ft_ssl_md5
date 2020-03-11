/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:47:25 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:50:08 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		init_sha384_vars(u_int64_t var[8])
{
	var[0] = 0xcbbb9d5dc1059ed8;
	var[1] = 0x629a292a367cd507;
	var[2] = 0x9159015a3070dd17;
	var[3] = 0x152fecd8f70e5939;
	var[4] = 0x67332667ffc00b31;
	var[5] = 0x8eb44a8768581511;
	var[6] = 0xdb0c2e0d64f98fa7;
	var[7] = 0x47b5481dbefa4fa4;
}

void			print_sha384(char *message)
{
	char		*buffer;
	__uint128_t	meslen;
	__uint128_t	bufferlen;
	u_int64_t	var[8];
	u_int64_t	mem[8];

	meslen = ft_strlen128(message);
	bufferlen = ((meslen + 16) / 128 + 1) * 128;
	buffer = ft_strnew(bufferlen + 1);
	ft_strcpy(buffer, message);
	buffer[meslen] = 0x80;
	reverse_64(buffer, meslen);
	add_size_sha64(buffer, bufferlen, meslen * 8);
	init_sha384_vars(var);
	sha64_calc(buffer, bufferlen, var, mem);
	ft_printf("%016jx%016jx%016jx%016jx%016jx%016jx", var[0], var[1],
			var[2], var[3],
			var[4], var[5]);
	free(buffer);
}
