/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:53:03 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/14 22:10:30 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	ft_strlen64(char *str)
{
	uint64_t	i;

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

void		add_size_md5(char *buffer, uint64_t bufferlen,
		uint64_t meslen)
{
	buffer[bufferlen - 5] = (meslen & 0x00000000FF000000) >> 24;
	buffer[bufferlen - 6] = (meslen & 0x0000000000FF0000) >> 16;
	buffer[bufferlen - 7] = (meslen & 0x000000000000FF00) >> 8;
	buffer[bufferlen - 8] = (meslen & 0x00000000000000FF);
	buffer[bufferlen - 1] = (meslen & 0xFF00000000000000) >> 56;
	buffer[bufferlen - 2] = (meslen & 0x00FF000000000000) >> 48;
	buffer[bufferlen - 3] = (meslen & 0x0000FF0000000000) >> 40;
	buffer[bufferlen - 4] = (meslen & 0x000000FF00000000) >> 32;
}

void		add_size_sha(char *buffer, uint64_t bufferlen,
		uint64_t meslen)
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

void		add_size_sha64(char *buffer, __uint128_t bufferlen,
		__uint128_t meslen)
{
	buffer[bufferlen - 1] = (meslen & 0x00000000FF000000) >> 24;
	buffer[bufferlen - 2] = (meslen & 0x0000000000FF0000) >> 16;
	buffer[bufferlen - 3] = (meslen & 0x000000000000FF00) >> 8;
	buffer[bufferlen - 4] = (meslen & 0x00000000000000FF);
	buffer[bufferlen - 5] = (meslen & 0xFF00000000000000) >> 56;
	buffer[bufferlen - 6] = (meslen & 0x00FF000000000000) >> 48;
	buffer[bufferlen - 7] = (meslen & 0x0000FF0000000000) >> 40;
	buffer[bufferlen - 8] = (meslen & 0x000000FF00000000) >> 32;
	buffer[bufferlen - 9] = (meslen >> 64 & 0x00000000FF000000) >> 24;
	buffer[bufferlen - 10] = (meslen >> 64 & 0x0000000000FF0000) >> 16;
	buffer[bufferlen - 11] = (meslen >> 64 & 0x000000000000FF00) >> 8;
	buffer[bufferlen - 12] = (meslen >> 64 & 0x00000000000000FF);
	buffer[bufferlen - 13] = (meslen >> 64 & 0xFF00000000000000) >> 56;
	buffer[bufferlen - 14] = (meslen >> 64 & 0x00FF000000000000) >> 48;
	buffer[bufferlen - 15] = (meslen >> 64 & 0x0000FF0000000000) >> 40;
	buffer[bufferlen - 16] = (meslen >> 64 & 0x000000FF00000000) >> 32;
}

void		reverse_32(void *bufp, uint64_t meslen)
{
	uint64_t	i;
	uint64_t	stop;
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

const int	g_md5_t[] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const int	g_md5_s[] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

void		init_md5vars(uint32_t md5vars[4])
{
	md5vars[0] = 0x67452301;
	md5vars[1] = 0xEFCDAB89;
	md5vars[2] = 0x98BADCFE;
	md5vars[3] = 0x10325476;
}

uint32_t	cycle_shift_left(uint32_t num, int offset)
{
	return ((num << offset) | (num >> (32 - offset)));
}

uint32_t	cycle_shift_right32(uint32_t num, int offset)
{
	return ((num >> offset) | (num << (32 - offset)));
}

uint64_t	cycle_shift_right64(uint64_t num, int offset)
{
	return ((num >> offset) | (num << (64 - offset)));
}

uint32_t	md5_f(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | (~x & z));
}

uint32_t	md5_g(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | (y & ~z));
}

uint32_t	md5_h(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t	md5_i(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (x | ~z));
}

uint32_t	md5_round_calc(char *buffer, uint64_t i, int j,
		uint32_t var[4])
{
	uint32_t	temp;

	if (j < 16)
		temp = var[1] + (cycle_shift_left(var[0] +
					md5_f(var[1], var[2], var[3]) +
					((uint32_t *)(buffer + i))[j] +
					g_md5_t[j], g_md5_s[j]));
	else if (j < 32)
		temp = var[1] + (cycle_shift_left(var[0] +
					md5_g(var[1], var[2], var[3]) +
					((uint32_t *)(buffer + i))[(5 * j + 1) % 16] +
					g_md5_t[j], g_md5_s[j]));
	else if (j < 48)
		temp = var[1] + (cycle_shift_left(var[0] +
					md5_h(var[1], var[2], var[3]) +
					((uint32_t *)(buffer + i))[(3 * j + 5) % 16] +
					g_md5_t[j], g_md5_s[j]));
	else
		temp = var[1] + (cycle_shift_left(var[0] +
					md5_i(var[1], var[2], var[3]) +
					((uint32_t *)(buffer + i))[(7 * j) % 16] +
					g_md5_t[j], g_md5_s[j]));
	return (temp);
}

void		md5_rounds(char *buffer, uint64_t bufferlen, uint32_t var[4])
{
	uint64_t	i;
	int			j;
	uint32_t	temp;
	uint32_t	pvar[4];

	init_md5vars(var);
	i = 0;
	while (i < bufferlen)
	{
		ft_memcpy(pvar, var, 16);
		j = -1;
		while (++j < 64)
		{
			temp = md5_round_calc(buffer, i, j, var);
			var[0] = var[3];
			var[3] = var[2];
			var[2] = var[1];
			var[1] = temp;
		}
		var[0] += pvar[0];
		var[1] += pvar[1];
		var[2] += pvar[2];
		var[3] += pvar[3];
		i += 64;
	}
}

const uint32_t	g_sha_k32[] = {
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

const uint64_t g_sha_k64[] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

uint32_t		ch32(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~x & z));
}

uint64_t		ch64(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~x & z));
}

uint32_t		maj32(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint64_t		maj64(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t		sigma032(uint32_t x)
{
	return (cycle_shift_right32(x, 2) ^
			cycle_shift_right32(x, 13) ^
			cycle_shift_right32(x, 22));
}

uint64_t		sigma064(uint64_t x)
{
	return (cycle_shift_right64(x, 28) ^
			cycle_shift_right64(x, 34) ^
			cycle_shift_right64(x, 39));
}

uint32_t		sigma132(uint32_t x)
{
	return (cycle_shift_right32(x, 6) ^
			cycle_shift_right32(x, 11) ^
			cycle_shift_right32(x, 25));
}

uint64_t		sigma164(uint64_t x)
{
	return (cycle_shift_right64(x, 14) ^
			cycle_shift_right64(x, 18) ^
			cycle_shift_right64(x, 41));
}

uint32_t		delta032(uint32_t x)
{
	return (cycle_shift_right32(x, 7) ^
			cycle_shift_right32(x, 18) ^
			x >> 3);
}

uint64_t		delta064(uint64_t x)
{
	return (cycle_shift_right64(x, 1) ^
			cycle_shift_right64(x, 8) ^
			x >> 7);
}

uint32_t		delta132(uint32_t x)
{
	return (cycle_shift_right32(x, 17) ^
			cycle_shift_right32(x, 19) ^
			x >> 10);
}

uint64_t		delta164(uint64_t x)
{
	return (cycle_shift_right64(x, 19) ^
			cycle_shift_right64(x, 61) ^
			x >> 6);
}

void		init_sha256_vars(uint32_t var[8])
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

void		init_sha224_vars(uint32_t var[8])
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

void		init_sha512_vars(uint64_t var[8])
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

void		sha256_cycle(uint32_t var[8], uint32_t w[64])
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

void		sha512_cycle(uint64_t var[8], uint64_t w[80])
{
	uint64_t	temp1;
	uint64_t	temp2;
	int			j;

	j = 0;
	while (j < 80)
	{
	ft_printf("%d - %016jx %016jx %016jx %016jx %016jx %016jx %016jx %016jx\n", j, var[0], var[1], var[2], var[3],
			var[4], var[5], var[6], var[7]);
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

void		sha256_calc(char *buffer, uint64_t bufferlen,
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
		sha256_cycle(var, w);
		j = -1;
		while (++j < 8)
			var[j] = mem[j] + var[j];
		i += 64;
	}
}

void		sha512_calc(char *buffer, __uint128_t bufferlen,
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
		print_memory(w, 1024);
		sha512_cycle(var, w);
		j = -1;
		while (++j < 8)
			var[j] = mem[j] + var[j];
		i += 128;
	}
}

void		print_md5(char *message)
{
	uint32_t	md5vars[4];
	char		*buffer;
	uint64_t	meslen;
	uint64_t	bufferlen;

	meslen = ft_strlen64(message);
	bufferlen = ((meslen + 8) / 64 + 1) * 64;
	buffer = ft_strnew(bufferlen + 1);
	ft_strcpy(buffer, message);
	buffer[meslen] = 0x80;
	add_size_md5(buffer, bufferlen, meslen * 8);
	md5_rounds(buffer, bufferlen, md5vars);
	reverse_32(md5vars, 16);
	ft_printf("%08x%08x%08x%08x", md5vars[0], md5vars[1], md5vars[2], md5vars[3]);
	free(buffer);
}

void		print_sha256(char *message)
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
	add_size_sha(buffer, bufferlen, meslen * 8);
	init_sha256_vars(var);
	sha256_calc(buffer, bufferlen, var, mem);
	ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x", var[0], var[1], var[2], var[3],
			var[4], var[5], var[6], var[7]);
	free(buffer);
}

void		print_sha224(char *message)
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
	add_size_sha(buffer, bufferlen, meslen * 8);
	init_sha224_vars(var);
	sha256_calc(buffer, bufferlen, var, mem);
	ft_printf("%08x%08x%08x%08x%08x%08x%08x", var[0], var[1], var[2], var[3],
			var[4], var[5], var[6]);
	free(buffer);
}

void		print_sha512(char *message)
{
	char		*buffer;
	__uint128_t	meslen;
	__uint128_t	bufferlen;
	uint64_t	var[8];
	uint64_t	mem[8];

	meslen = ft_strlen128(message);
	bufferlen = ((meslen + 16) / 128 + 1) * 128;
	buffer = ft_strnew(bufferlen + 1);
	ft_strcpy(buffer, message);
	buffer[meslen] = 0x80;
	reverse_32(buffer, meslen);
	add_size_sha64(buffer, bufferlen, meslen * 8);
	init_sha512_vars(var);
	sha512_calc(buffer, bufferlen, var, mem);
	ft_printf("%016jx%016jx%016jx%016jx%016jx%016jx%016jx%016jx", var[0], var[1], var[2], var[3],
			var[4], var[5], var[6], var[7]);
	free(buffer);
}

void		print_hash(char *message, char params[256],
		t_algh_corr *algh, char *filename)
{
	if (!params['q'])
	{
		if (!params['r'])
		{
			if (filename == message)
				ft_printf("%s (\"%s\") = ", algh->namecap, message);
			else
				ft_printf("%s (%s) = ", algh->namecap, filename);
			algh->func(message);
			ft_printf("\n");
		}
		else if (params['r'])
		{
			algh->func(message);
			if (filename == message)
				ft_printf(" \"%s\"\n", message);
			else
				ft_printf(" %s\n", filename);
		}
	}
	else
	{
		algh->func(message);
		ft_printf("\n");
	}
}

int			get_file_str_inner(int fd, char **ret)
{
	uintmax_t	size;
	char		*temp;
	char		*buf;
	int			readret;

	size = 1024;
	*ret = (char *)malloc(size);
	ft_bzero(*ret, size);
	buf = (char *)malloc(size);
	ft_bzero(buf, size);
	while ((readret = read(fd, buf, 1023)) >= 0)
	{
		if (!readret)
			break ;
		temp = *ret;
		*ret = (char *)malloc(size);
		ft_bzero(*ret, size);
		ft_strcpy(*ret, temp);
		ft_strcat(*ret, buf);
		ft_bzero(buf, 1024);
		free(temp);
		size += 1024;
	}
	free(buf);
	return (readret);
}

void		hash_stdin(char **argv, char params[256],
		t_algh_corr *algh)
{
	char	*line;
	int		ret;

	line = 0;
	ret = get_file_str_inner(0, &line);
	if (params['p'])
		ft_printf("%s", line);
	if (ret == -1)
		ft_fprintf(2, "%s: STDIN ERROR\n", argv[0]);
	else
	{
		algh->func(line);
		ft_printf("\n");
	}
	free(line);
}

char		*get_file_str(char *filename, char **argv)
{
	char		*ret;
	int			fd;
	int			readret;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "%s: %s: %s\n", argv[0], filename,
				strerror(errno));
		return (0);
	}
	readret = get_file_str_inner(fd, &ret);
	if (readret == -1)
	{
		ft_fprintf(2, "%s: File reading Error: %s\n", argv[0], filename);
		free(ret);
		return (0);
	}
	return (ret);
}

int			main(int argc, char **argv)
{
	char		params[256];
	int			lastparam;
	t_algh_corr	algh;
	char		*initstr;

	lastparam = preparation(argc, argv, params, &algh);
	if (lastparam == argc || params['p'])
		hash_stdin(argv, params, &algh);
	while (lastparam < argc)
	{
		if (params['s'])
		{
			initstr = argv[lastparam];
			params['s'] = 0;
		}
		else
			initstr = get_file_str(argv[lastparam], argv);
		if (!initstr)
		{
			++lastparam;
			continue ;
		}
		print_hash(initstr, params, &algh, argv[lastparam]);
		if (argv[lastparam] != initstr)
			free(initstr);
		++lastparam;
	}
	system("leaks ft_ssl");
}
