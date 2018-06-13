/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:53:03 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/13 19:57:57 by obamzuro         ###   ########.fr       */
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

void		add_size(char *buffer, uint64_t bufferlen,
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

void		init_abcd(t_abcd *abcd)
{
	abcd->a = 0x67452301;
	abcd->b = 0xEFCDAB89;
	abcd->c = 0x98BADCFE;
	abcd->d = 0x10325476;
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

void		procceed_rounds(char *buffer, uint64_t bufferlen, t_abcd *abcd)
{
	uint64_t	i;
	int			j;
	uint32_t	temp;
	t_abcd		mem;

	init_abcd(abcd);
	i = 0;
	while (i < bufferlen)
	{
		mem = *abcd;
		j = 0;
		while (j < 64)
		{
			if (j < 16)
				abcd->a = abcd->b + (cycle_shift_left(abcd->a + ((abcd->b & abcd->c) | (~abcd->b & abcd->d)) + ((uint32_t *)(buffer + i))[j] + g_md5_t[j], g_md5_s[j]));
			else if (j < 32)
				abcd->a = abcd->b + (cycle_shift_left(abcd->a + ((abcd->b & abcd->d) | (abcd->c & ~abcd->d)) + ((uint32_t *)(buffer + i))[(5 * j + 1) % 16] + g_md5_t[j], g_md5_s[j]));
			else if (j < 48)
				abcd->a = abcd->b + (cycle_shift_left(abcd->a + (abcd->b ^ abcd->c ^ abcd->d) + ((uint32_t *)(buffer + i))[(3 * j + 5) % 16] + g_md5_t[j], g_md5_s[j]));
			else
				abcd->a = abcd->b + (cycle_shift_left(abcd->a + (abcd->c ^ (abcd->b | ~abcd->d)) + ((uint32_t *)(buffer + i))[(7 * j) % 16] + g_md5_t[j], g_md5_s[j]));
			//printf("%d - %zd %zd %zd %zd\n", j, abcd->a, abcd->b, abcd->c, abcd->d);
			temp = abcd->a;
			abcd->a = abcd->d;
			abcd->d = abcd->c;
			abcd->c = abcd->b;
			abcd->b = temp;
			++j;
		}
		abcd->a = mem.a + abcd->a;
		abcd->b = mem.b + abcd->b;
		abcd->c = mem.c + abcd->c;
		abcd->d = mem.d + abcd->d;
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
	return (cycle_shift_right64(x, 2) ^
			cycle_shift_right64(x, 13) ^
			cycle_shift_right64(x, 22));
}

uint32_t		sigma132(uint32_t x)
{
	return (cycle_shift_right32(x, 6) ^
			cycle_shift_right32(x, 11) ^
			cycle_shift_right32(x, 25));
}

uint64_t		sigma164(uint64_t x)
{
	return (cycle_shift_right64(x, 6) ^
			cycle_shift_right64(x, 11) ^
			cycle_shift_right64(x, 25));
}

uint32_t		delta032(uint32_t x)
{
	return (cycle_shift_right32(x, 7) ^
			cycle_shift_right32(x, 18) ^
			x >> 3);
}

uint64_t		delta064(uint64_t x)
{
	return (cycle_shift_right64(x, 7) ^
			cycle_shift_right64(x, 18) ^
			x >> 3);
}

uint32_t		delta132(uint32_t x)
{
	return (cycle_shift_right32(x, 17) ^
			cycle_shift_right32(x, 19) ^
			x >> 10);
}

uint64_t		delta164(uint64_t x)
{
	return (cycle_shift_right64(x, 17) ^
			cycle_shift_right64(x, 19) ^
			x >> 10);
}

void		init_sha256(uint32_t	var[8])
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

void		print_sha256(char *buffer, uint64_t bufferlen)
{
	uint32_t	w[64];
	uint32_t	i;
	int			j;
	uint32_t	var[8];
	uint32_t	mem[8];
	uint32_t	temp1;
	uint32_t	temp2;

	init_sha256(var);
	i = 0;
	while (i < bufferlen)
	{
		j = 0;
		while (j < 8)
		{
			mem[j] = var[j];
			++j;
		}
		j = 0;
		while (j < 16)
		{
			w[j] = ((uint32_t *)(buffer + i))[j];
			++j;
		}
		while (j < 64)
		{
			w[j] = w[j - 16] + delta032(w[j - 15]) + w[j - 7] + delta132(w[j - 2]);
			++j;
		}
		j = 0;
		//print_memory(w, 64 * 4);
		while (j < 64)
		{
			temp1 = var[7] + sigma132(var[4]) + ch32(var[4], var[5], var[6]) + w[j] + g_sha_k32[j];
			temp2 = sigma032(var[0]) + maj32(var[0], var[1], var[2]);
			var[7] = var[6];
			var[6] = var[5];
			var[5] = var[4];
			var[4] = var[3] + temp1;
			var[3] = var[2];
			var[2] = var[1];
			var[1] = var[0];
			var[0] = temp1 + temp2;
			//ft_printf("%d - %x %x %x %x %x %x %x %x\n", j, var[0], var[1], var[2], var[3],
			//	var[4], var[5], var[6], var[7]);
			++j;
		}
		j = 0;
		while (j < 8)
		{
			var[j] = mem[j] + var[j];
			++j;
		}
		i += 64;
	}
	ft_printf("%x%x%x%x%x%x%x%x\n", var[0], var[1], var[2], var[3],
			var[4], var[5], var[6], var[7]);
}

void		print_md5(char *line, char params[256])
{

}

void		hash_stdin(char **argv, char params[256],
		void (*hashfun)(char *))
{
	char	*line;
	int		ret;

	ret = get_next_line(0, &line);
	if (ret == -1)
		ft_printf(2, "%s: STDIN ERROR\n", argv[0]);
	else
		hashfun(line);
}

int			main(int argc, char **argv)
{
	char		params[256];
	char		*message;
	char		*buffer;
	uint64_t	meslen;
	uint64_t	bufferlen;
	t_abcd		abcd;
	int			lastparam;
	void		(*hashfun)(char *);

	lastparam = preparation(argc, argv, params, hashfun);
	if (params['p'])
		hash_stdin(argv, params, hashfun);
	while (lastparam < argc)
	{
		hashfun(argv[lastparam]);
		++lastparam;
	}
	message = argv[1];
	meslen = ft_strlen64(argv[1]);
	bufferlen = ((meslen + 8) / 64 + 1) * 64;
	buffer = ft_strnew(bufferlen + 1);
	ft_strcpy(buffer, message);
	buffer[meslen] = 0x80;
	reverse_32(buffer, meslen);
	add_size_sha(buffer, bufferlen, meslen * 8);
	print_sha256(buffer, bufferlen);
	//print_memory(buffer, bufferlen);
	//procceed_rounds(buffer, bufferlen, &abcd);
	//ft_printf("%zd %zd %zd %zd\n", abcd.a, abcd.b, abcd.c, abcd.d);
	//ft_printf("%x %x %x %x\n", abcd.a, abcd.b, abcd.c, abcd.d);
	//reverse_32(&abcd, 16);
	//ft_printf("%x%x%x%x\n", abcd.a, abcd.b, abcd.c, abcd.d);
}
