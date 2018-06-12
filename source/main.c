/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:53:03 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/12 19:50:33 by obamzuro         ###   ########.fr       */
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
	buffer[bufferlen - 8] = (meslen & 0x00000000FF000000) >> 24;
	buffer[bufferlen - 7] = (meslen & 0x0000000000FF0000) >> 16;
	buffer[bufferlen - 6] = (meslen & 0x000000000000FF00) >> 8;
	buffer[bufferlen - 5] = (meslen & 0x00000000000000FF);
	buffer[bufferlen - 4] = (meslen & 0xFF00000000000000) >> 56;
	buffer[bufferlen - 3] = (meslen & 0x00FF000000000000) >> 48;
	buffer[bufferlen - 2] = (meslen & 0x0000FF0000000000) >> 40;
	buffer[bufferlen - 1] = (meslen & 0x000000FF00000000) >> 32;
}

void		reverse_32(char *buffer, uint64_t meslen)
{
	uint64_t	i;
	uint64_t	stop;

	i = 0;
	stop = (meslen / 4 + 1) * 4;
	while (i < stop)
	{
		ft_strreverse(buffer + i, 4);
		i += 4;
	}
}

int			main(int argc, char **argv)
{
	char		*message;
	char		*buffer;
	uint64_t	meslen;
	uint64_t	bufferlen;

	message	= argv[1];
	meslen = ft_strlen(argv[1]);
	bufferlen = ((meslen + 8) / 64 + 1) * 64;
	buffer = ft_strnew(bufferlen + 1);
	ft_strcpy(buffer, message);
	buffer[meslen] = 0x80;
	reverse_32(buffer, meslen);
	add_size(buffer, bufferlen, meslen * 8);
	print_memory(buffer, bufferlen);
}
