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

uint64_t		ch64(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (~x & z));
}

uint64_t		maj64(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint64_t		sigma064(uint64_t x)
{
	return (cycle_shift_right64(x, 28) ^
			cycle_shift_right64(x, 34) ^
			cycle_shift_right64(x, 39));
}

uint64_t		sigma164(uint64_t x)
{
	return (cycle_shift_right64(x, 14) ^
			cycle_shift_right64(x, 18) ^
			cycle_shift_right64(x, 41));
}

uint64_t		delta064(uint64_t x)
{
	return (cycle_shift_right64(x, 1) ^
			cycle_shift_right64(x, 8) ^
			x >> 7);
}
