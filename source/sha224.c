/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:47:01 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:47:03 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		init_sha224_vars(uint32_t var[8])
{
	var[0] = 0xc1059ed8;
	var[1] = 0x367cd507;
	var[2] = 0x3070dd17;
	var[3] = 0xf70e5939;
	var[4] = 0xffc00b31;
	var[5] = 0x68581511;
	var[6] = 0x64f98fa7;
	var[7] = 0xbefa4fa4;
}

void			print_sha224(char *message)
{
	char		*buffer;
	u_int64_t	meslen;
	u_int64_t	bufferlen;
	uint32_t	var[8];
	uint32_t	mem[8];

	meslen = ft_strlen64(message);
	bufferlen = ((meslen + 8) / 64 + 1) * 64;
	buffer = ft_strnew(bufferlen + 1);
	ft_strcpy(buffer, message);
	buffer[meslen] = 0x80;
	reverse_32(buffer, meslen);
	add_size_sha32(buffer, bufferlen, meslen * 8);
	init_sha224_vars(var);
	sha32_calc(buffer, bufferlen, var, mem);
	ft_printf("%08x%08x%08x%08x%08x%08x%08x", var[0], var[1], var[2], var[3],
			var[4], var[5], var[6]);
	free(buffer);
}
