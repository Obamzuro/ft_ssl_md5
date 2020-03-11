/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:37:12 by obamzuro          #+#    #+#             */
/*   Updated: 2020/02/24 18:10:18 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const char			*base64_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void		strip_extra_chars(char *message)
{
	uint64_t	i;
	char		*temp;

	i = 0;
	while (i < g_size)
	{
		if (!ft_strchr(base64_str, message[i]) && message[i] != '=')
		{
			ft_memcpy(message + i, message + i + 1, g_size - i - 1);
			--g_size;
			--i;
		}
		++i;
	}
}

static void			decode_base64(char *message)
{
	uint8_t		dstn;
	uint8_t		remain;
	uint64_t	i;

	i = 0;
	remain = 0;
	strip_extra_chars(message);
	while (i < g_size)
	{
		dstn = 0;
		if (message[i] == '=')
			break ;
		dstn |= ((ft_strchr(base64_str, message[i]) - base64_str) << (2 + ((6 - remain) % 6)));
		if (message[i + 1] != '=')
			dstn |= (ft_strchr(base64_str, message[i + 1]) - base64_str) >> ((remain + 4) % 6);
		if (dstn != 0 || message[i + 1] != '=')
			write(1, &dstn, 1);
		remain = (remain + 4) % 6;
		if (!remain)
			++i;
		++i;
	}
}

static void			encode_base64(char *message)
{
	uint8_t			source;
	uint8_t			remain;
	uint64_t		len;
	uint64_t		i;

	source = 0;
	remain = 0;
	i = 0;
	len = g_size;
	while (i < g_size)
	{
		source |= (*((uint8_t *)(message + i)) >> (2 + remain)) << 2;
		write(1, base64_str + (size_t)(source >> 2), 1);
		source = *((uint8_t *)(message + i)) << (6 - remain);
		remain = 2 + remain;
		if (remain % 6 == 0)
		{
			write(1, base64_str + (size_t)(source >> 2), 1);
			remain = 0;
			source = 0;
		}
		++i;
	}
	if (len % 3)
		write(1, base64_str + (size_t)(source >> 2), 1);
	i = 0;
	while (len % 3 && i++ < 3 - (len % 3))
		write(1, "=", 1);
}

void			print_base64(char *message)
{
	if (params['d'])
		decode_base64(message);
	else
		encode_base64(message);
}
