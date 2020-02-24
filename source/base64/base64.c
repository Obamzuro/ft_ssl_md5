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

void			decode_base64(char *message)
{

}

void			print_base64(char *message)
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
		remain = 8 - 6 + remain;
		if (remain % 6 == 0)
		{
			write(1, base64_str + (size_t)(source >> 2), 1);
			remain = 0;
			source = 0;
		}
		++i;
	}
	if (source && len % 3)
		write(1, base64_str + (size_t)(source >> 2), 1);
	i = 0;
	while (len % 3 && i++ < 3 - (len % 3))
		write(1, "=", 1);
}
