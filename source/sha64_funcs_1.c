/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha64_funcs_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:47:36 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:47:37 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

u_int64_t		ch64(u_int64_t x, u_int64_t y, u_int64_t z)
{
	return ((x & y) ^ (~x & z));
}

u_int64_t		maj64(u_int64_t x, u_int64_t y, u_int64_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

u_int64_t		sigma064(u_int64_t x)
{
	return (cycle_shift_right64(x, 28) ^
			cycle_shift_right64(x, 34) ^
			cycle_shift_right64(x, 39));
}

u_int64_t		sigma164(u_int64_t x)
{
	return (cycle_shift_right64(x, 14) ^
			cycle_shift_right64(x, 18) ^
			cycle_shift_right64(x, 41));
}

u_int64_t		delta064(u_int64_t x)
{
	return (cycle_shift_right64(x, 1) ^
			cycle_shift_right64(x, 8) ^
			x >> 7);
}
