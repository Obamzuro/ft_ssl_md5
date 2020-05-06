/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:53:03 by obamzuro          #+#    #+#             */
/*   Updated: 2020/02/24 18:09:55 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int g_ip[] =
{
	  58, 50, 42, 34, 26, 18, 10, 2,
	  60, 52, 44, 36, 28, 20, 12, 4,
	  62, 54, 46, 38, 30, 22, 14, 6,
	  64, 56, 48, 40, 32, 24, 16, 8,
	  57, 49, 41, 33, 25, 17,  9, 1,
	  59, 51, 43, 35, 27, 19, 11, 3,
	  61, 53, 45, 37, 29, 21, 13, 5,
	  63, 55, 47, 39, 31, 23, 15, 7
};

int g_e[] =
{
	  32,  1,  2,  3,  4,  5,
	   4,  5,  6,  7,  8,  9,
	   8,  9, 10, 11, 12, 13,
	  12, 13, 14, 15, 16, 17,
	  16, 17, 18, 19, 20, 21,
	  20, 21, 22, 23, 24, 25,
	  24, 25, 26, 27, 28, 29,
	  28, 29, 30, 31, 32,  1
};

int g_p[] =
{
	  16,  7, 20, 21,
	  29, 12, 28, 17,
	   1, 15, 23, 26,
	   5, 18, 31, 10,
	   2,  8, 24, 14,
	  32, 27,  3,  9,
	  19, 13, 30,  6,
	  22, 11,  4, 25
};

int g_fp[] =
{
	  40, 8, 48, 16, 56, 24, 64, 32,
	  39, 7, 47, 15, 55, 23, 63, 31,
	  38, 6, 46, 14, 54, 22, 62, 30,
	  37, 5, 45, 13, 53, 21, 61, 29,
	  36, 4, 44, 12, 52, 20, 60, 28,
	  35, 3, 43, 11, 51, 19, 59, 27,
	  34, 2, 42, 10, 50, 18, 58, 26,
	  33, 1, 41,  9, 49, 17, 57, 25
};

int g_s[8][4][16] =
{
{
		14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
		4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
		15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
},
{
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
},
{
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
},
{
	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
},
{
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
},
{
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
},
{
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
},
{
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
}
};

int g_pc1[] =
{
	  57, 49, 41, 33, 25, 17,  9,
	   1, 58, 50, 42, 34, 26, 18,
	  10,  2, 59, 51, 43, 35, 27,
	  19, 11,  3, 60, 52, 44, 36,
	  63, 55, 47, 39, 31, 23, 15,
	   7, 62, 54, 46, 38, 30, 22,
	  14,  6, 61, 53, 45, 37, 29,
	  21, 13,  5, 28, 20, 12,  4
};

int g_pc2[] =
{
	  14, 17, 11, 24,  1,  5,
	   3, 28, 15,  6, 21, 10,
	  23, 19, 12,  4, 26,  8,
	  16,  7, 27, 20, 13,  2,
	  41, 52, 31, 37, 47, 55,
	  30, 40, 51, 45, 33, 48,
	  44, 49, 39, 56, 34, 53,
	  46, 42, 50, 36, 29, 32
};

int g_shifts[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

void			permute(bool *source, bool *destination,
		int *permutation_table, size_t table_size)
{
	uint64_t	i;

	i = 0;
	while (i < table_size)
	{
		destination[i] = source[permutation_table[i] - 1];
		++i;
	}
}

void			shift_left(bool table[28], int count_shifts)
{
	uint64_t	i;
	bool		first;

	i = 0;
	while (i < count_shifts)
	{
		first = table[0];
		memcpy(table, table + 1, 28 - 1);
		table[28 - 1] = first;
		++i;
	}
}

void			generate_keys(bool key[64], bool keys[16][48])
{
	bool		key56[56] = { 0, };
	bool		left[28];
	bool		right[28];
	bool		combine[56];
	uint64_t	i;

	permute(key, key56, g_pc1, 56);
	i = 0;
	while (i < 28)
	{
		left[i] = key56[i];
		right[i] = key56[i + 28];
		++i;
	}
	i = 0;
	while (i < 16)
	{
		shift_left(left, g_shifts[i]);
		shift_left(right, g_shifts[i]);
		memcpy(combine, left, 28);
		memcpy(combine + 28, right, 28);
		permute(combine, keys[i], g_pc2, 48);
		++i;
	}
}

void			xor_bool(bool *array, bool *key, const size_t array_size)
{
	uint32_t	i;

	i = 0;
	while (i < array_size)
	{
		array[i] ^= key[i];
		++i;
	}
}

char			*encrypt(bool message[64], bool keys[16][48])
{
	bool		initial_perm[64] = { 0, };
	bool		final_perm[64] = { 0, };
	bool		left[32];
	bool		right[32];
	bool		right_expanded[48];
	bool		right_expanded_s[32];
	bool		right_expanded_s_permuted[32];
	char		cipher[9] = { 0, };
	uint32_t	i;
	uint32_t	j;
	uint32_t	k;
	uint8_t		row;
	uint8_t		col;
	uint8_t		val;

	permute(message, initial_perm, g_ip, 64);
	memcpy(left, initial_perm, 32);
	memcpy(right, initial_perm + 32, 32);
	i = 0;
	while (i < 16)
	{
		permute(right, right_expanded, g_e, 48);
		xor_bool(right_expanded, keys[i], 48);
		j = 0;
		while (j < 8)
		{
			row = 2 * right_expanded[j * 6] + right_expanded[j * 6 + 5];
			col = 8 * right_expanded[j * 6 + 1] + 4 * right_expanded[j * 6 + 2] +
				2 * right_expanded[j * 6 + 3] + right_expanded[j * 6 + 4];
			val = g_s[j][row][col];
			k = 0;
			while (k < 4)
			{
				right_expanded_s[j * 4 + k] = GET_BIT(val, 3 - k);
				++k;
			}
			++j;
		}
		permute(right_expanded_s, right_expanded_s_permuted, g_p, 32);
		xor_bool(left, right_expanded_s_permuted, 32);
		//??????
		if (i != 15)
		{
			bool temp[32];
			memcpy(temp, left, 32);
			memcpy(left, right, 32);
			memcpy(right, temp, 32);
		}
		++i;
	}
	memcpy(initial_perm, left, 32);
	memcpy(initial_perm + 32, right, 32);
	permute(initial_perm, final_perm, g_fp, 64);
	i = 0;
	while (i < 64)
	{
		SET_BIT(cipher[i / 8], 7 - i % 8, final_perm[i]);
		++i;
	}
	ft_printf("cipher = %s", cipher);
	char *kek = (char *)malloc(8);
	memcpy(kek, cipher, 8);
	return (kek);
}

void			encode_des(char *message, char *key)
{
	bool		keys[16][48] = {{ 0, }};
	bool		key_binary[64];
	bool		message_binary[64];
	char		*cipher;
	uint32_t	i;

	i = 0;
	while (i < 64)
	{
		key_binary[i] = GET_BIT(key[i / 8], 7 - (i % 8));
		++i;
	}
	i = 0;
	while (i < 64)
	{
		message_binary[i] = GET_BIT(message[i / 8], 7 - (i % 8));
		++i;
	}
	generate_keys(key_binary, keys);
	cipher = encrypt(message_binary, keys);
	i = 0;
	bool  temp[48] = { 0, };
	while (i < 8)
	{
		memcpy(temp, keys[i], 48);
		memcpy(keys[i], keys[15 - i], 48);
		memcpy(keys[15 - i], temp, 48);
		++i;
	}
	bool		cipher_binary[64];
	i = 0;
	while (i < 64)
	{
		cipher_binary[i] = GET_BIT(cipher[i / 8], 7 - (i % 8));
		++i;
	}
	encrypt(cipher_binary, keys);
}

void			print_des(char *message)
{
//	encode_des(message, "12345678");
	encode_des(message, "12345678");
}
