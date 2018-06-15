/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_funcs_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:46:54 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:46:56 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	md5_h(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t	md5_i(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (x | ~z));
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
