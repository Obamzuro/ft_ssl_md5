/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha64_funcs_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:47:41 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:51:58 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const uint64_t	g_sha_k64[] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
	0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926,
	0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910,
	0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

uint64_t		delta164(uint64_t x)
{
	return (cycle_shift_right64(x, 19) ^
			cycle_shift_right64(x, 61) ^
			x >> 6);
}

void			add_size_sha64(char *buffer, __uint128_t bufferlen,
		__uint128_t meslen)
{
	buffer[bufferlen - 1] = (meslen & 0xFF00000000000000) >> 56;
	buffer[bufferlen - 2] = (meslen & 0x00FF000000000000) >> 48;
	buffer[bufferlen - 3] = (meslen & 0x0000FF0000000000) >> 40;
	buffer[bufferlen - 4] = (meslen & 0x000000FF00000000) >> 32;
	buffer[bufferlen - 5] = (meslen & 0x00000000FF000000) >> 24;
	buffer[bufferlen - 6] = (meslen & 0x0000000000FF0000) >> 16;
	buffer[bufferlen - 7] = (meslen & 0x000000000000FF00) >> 8;
	buffer[bufferlen - 8] = (meslen & 0x00000000000000FF);
	buffer[bufferlen - 9] = (meslen >> 64 & 0xFF00000000000000) >> 56;
	buffer[bufferlen - 10] = (meslen >> 64 & 0x00FF000000000000) >> 48;
	buffer[bufferlen - 11] = (meslen >> 64 & 0x0000FF0000000000) >> 40;
	buffer[bufferlen - 12] = (meslen >> 64 & 0x000000FF00000000) >> 32;
	buffer[bufferlen - 13] = (meslen >> 64 & 0x00000000FF000000) >> 24;
	buffer[bufferlen - 14] = (meslen >> 64 & 0x0000000000FF0000) >> 16;
	buffer[bufferlen - 15] = (meslen >> 64 & 0x000000000000FF00) >> 8;
	buffer[bufferlen - 16] = (meslen >> 64 & 0x00000000000000FF);
}

void			sha64_cycle(uint64_t var[8], uint64_t w[80])
{
	uint64_t	temp1;
	uint64_t	temp2;
	int			j;

	j = 0;
	while (j < 80)
	{
		temp1 = var[7] + sigma164(var[4]) +
			ch64(var[4], var[5], var[6]) + w[j] + g_sha_k64[j];
		temp2 = sigma064(var[0]) + maj64(var[0], var[1], var[2]);
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

void			sha64_calc(char *buffer, __uint128_t bufferlen,
		uint64_t var[8], uint64_t mem[8])
{
	uint64_t	w[80];
	uint64_t	i;
	int			j;

	i = 0;
	while (i < bufferlen)
	{
		ft_memcpy(mem, var, 64);
		j = -1;
		while (++j < 16)
			w[j] = ((uint64_t *)(buffer + i))[j];
		while (j < 80)
		{
			w[j] = w[j - 16] + delta064(w[j - 15])
				+ w[j - 7] + delta164(w[j - 2]);
			++j;
		}
		sha64_cycle(var, w);
		j = -1;
		while (++j < 8)
			var[j] = mem[j] + var[j];
		i += 128;
	}
}
