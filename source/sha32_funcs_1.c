/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha32_funcs_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:47:12 by obamzuro          #+#    #+#             */
/*   Updated: 2018/06/15 12:49:15 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t		ch32(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~x & z));
}

uint32_t		maj32(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t		sigma032(uint32_t x)
{
	return (cycle_shift_right32(x, 2) ^
			cycle_shift_right32(x, 13) ^
			cycle_shift_right32(x, 22));
}

uint32_t		sigma132(uint32_t x)
{
	return (cycle_shift_right32(x, 6) ^
			cycle_shift_right32(x, 11) ^
			cycle_shift_right32(x, 25));
}

uint32_t		delta032(uint32_t x)
{
	return (cycle_shift_right32(x, 7) ^
			cycle_shift_right32(x, 18) ^
			x >> 3);
}
