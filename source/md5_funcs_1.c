/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_funcs_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:46:49 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:46:50 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	cycle_shift_left(uint32_t num, int offset)
{
	return ((num << offset) | (num >> (32 - offset)));
}

uint32_t	cycle_shift_right32(uint32_t num, int offset)
{
	return ((num >> offset) | (num << (32 - offset)));
}

u_int64_t	cycle_shift_right64(u_int64_t num, int offset)
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
