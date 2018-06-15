/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:47:07 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:48:47 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		init_sha256_vars(uint32_t var[8])
{
	var[0] = 0x6a09e667;
	var[1] = 0xbb67ae85;
	var[2] = 0x3c6ef372;
	var[3] = 0xa54ff53a;
	var[4] = 0x510e527f;
	var[5] = 0x9b05688c;
	var[6] = 0x1f83d9ab;
	var[7] = 0x5be0cd19;
}

void			print_sha256(char *message)
{
	char		*buffer;
	uint64_t	meslen;
	uint64_t	bufferlen;
	uint32_t	var[8];
	uint32_t	mem[8];

	meslen = ft_strlen64(message);
	bufferlen = ((meslen + 8) / 64 + 1) * 64;
	buffer = ft_strnew(bufferlen + 1);
	ft_strcpy(buffer, message);
	buffer[meslen] = 0x80;
	reverse_32(buffer, meslen);
	add_size_sha32(buffer, bufferlen, meslen * 8);
	init_sha256_vars(var);
	sha32_calc(buffer, bufferlen, var, mem);
	ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x", var[0], var[1],
			var[2], var[3],
			var[4], var[5], var[6], var[7]);
	free(buffer);
}
