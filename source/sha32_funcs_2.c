/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha32_funcs_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:47:20 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:47:21 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const uint32_t		g_sha_k32[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t			delta132(uint32_t x)
{
	return (cycle_shift_right32(x, 17) ^
			cycle_shift_right32(x, 19) ^
			x >> 10);
}

void				add_size_sha32(char *buffer, u_int64_t bufferlen,
		u_int64_t meslen)
{
	buffer[bufferlen - 1] = (meslen & 0x00000000FF000000) >> 24;
	buffer[bufferlen - 2] = (meslen & 0x0000000000FF0000) >> 16;
	buffer[bufferlen - 3] = (meslen & 0x000000000000FF00) >> 8;
	buffer[bufferlen - 4] = (meslen & 0x00000000000000FF);
	buffer[bufferlen - 5] = (meslen & 0xFF00000000000000) >> 56;
	buffer[bufferlen - 6] = (meslen & 0x00FF000000000000) >> 48;
	buffer[bufferlen - 7] = (meslen & 0x0000FF0000000000) >> 40;
	buffer[bufferlen - 8] = (meslen & 0x000000FF00000000) >> 32;
}

static void			sha32_cycle(uint32_t var[8], uint32_t w[64])
{
	uint32_t	temp1;
	uint32_t	temp2;
	int			j;

	j = 0;
	while (j < 64)
	{
		temp1 = var[7] + sigma132(var[4]) +
			ch32(var[4], var[5], var[6]) + w[j] + g_sha_k32[j];
		temp2 = sigma032(var[0]) + maj32(var[0], var[1], var[2]);
		var[7] = var[6];
		var[6] = var[5];
		var[5] = var[4];
		var[4] = var[3] + temp1;
		var[3] = var[2];
		var[2] = var[1];
		var[1] = var[0];
		var[0] = temp1 + temp2;
		++j;
	}
}

void				sha32_calc(char *buffer, u_int64_t bufferlen,
		uint32_t var[8], uint32_t mem[8])
{
	uint32_t	w[64];
	uint32_t	i;
	int			j;

	i = 0;
	while (i < bufferlen)
	{
		ft_memcpy(mem, var, 32);
		j = -1;
		while (++j < 16)
			w[j] = ((uint32_t *)(buffer + i))[j];
		while (j < 64)
		{
			w[j] = w[j - 16] + delta032(w[j - 15])
				+ w[j - 7] + delta132(w[j - 2]);
			++j;
		}
		sha32_cycle(var, w);
		j = -1;
		while (++j < 8)
			var[j] = mem[j] + var[j];
		i += 64;
	}
}
