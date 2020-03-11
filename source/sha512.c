/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:47:30 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:52:20 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			init_sha512_vars(u_int64_t var[8])
{
	var[0] = 0x6a09e667f3bcc908;
	var[1] = 0xbb67ae8584caa73b;
	var[2] = 0x3c6ef372fe94f82b;
	var[3] = 0xa54ff53a5f1d36f1;
	var[4] = 0x510e527fade682d1;
	var[5] = 0x9b05688c2b3e6c1f;
	var[6] = 0x1f83d9abfb41bd6b;
	var[7] = 0x5be0cd19137e2179;
}

void				print_sha512(char *message)
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
	init_sha512_vars(var);
	sha64_calc(buffer, bufferlen, var, mem);
	ft_printf("%016jx%016jx%016jx%016jx%016jx%016jx%016jx%016jx",
			var[0], var[1],
			var[2], var[3],
			var[4], var[5], var[6], var[7]);
	free(buffer);
}
