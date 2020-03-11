/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:46:28 by obamzuro          #+#    #+#             */
/*   Updated: 2020/02/24 15:37:25 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

static void		init_md5vars(uint32_t md5vars[4])
{
	md5vars[0] = 0x67452301;
	md5vars[1] = 0xEFCDAB89;
	md5vars[2] = 0x98BADCFE;
	md5vars[3] = 0x10325476;
}

static uint32_t	md5_round_calc(char *buffer, u_int64_t i, int j,
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

static void		md5_rounds(char *buffer, u_int64_t bufferlen, uint32_t var[4])
{
	u_int64_t	i;
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

void			print_md5(char *message)
{
	uint32_t	md5vars[4];
	char		*buffer;
	u_int64_t	meslen;
	u_int64_t	bufferlen;

	meslen = ft_strlen64(message);
	bufferlen = ((meslen + 8) / 64 + 1) * 64;
	buffer = ft_strnew(bufferlen + 1);
	ft_strcpy(buffer, message);
	buffer[meslen] = 0x80;
	add_size_md5(buffer, bufferlen, meslen * 8);
	md5_rounds(buffer, bufferlen, md5vars);
	reverse_32(md5vars, 16);
	ft_printf("%08x%08x%08x%08x", md5vars[0], md5vars[1],
			md5vars[2], md5vars[3]);
	free(buffer);
}
