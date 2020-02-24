/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:52:34 by obamzuro          #+#    #+#             */
/*   Updated: 2020/02/24 18:04:30 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SSL_H
# define __FT_SSL_H
# include "libft.h"
# include "ft_printf.h"
# include <errno.h>
# include <stdint.h>
# include <string.h>
# define PARAMS "rpsq"
# define AM_PARAMS 4
# define AM_ALGHS 6

extern uint64_t		g_size;

typedef struct	s_algh_corr
{
	char	*name;
	char	*namecap;
	void	(*func)(char *);
}				t_algh_corr;

int				preparation(int argc, char **argv,
		char params[256], t_algh_corr *alghs);

void			print_md5(char *message);
void			print_sha256(char *message);
void			print_sha224(char *message);
void			print_sha512(char *message);
void			print_sha384(char *message);

uint64_t		ft_strlen64(char *str);
__uint128_t		ft_strlen128(char *str);
void			reverse_32(void *buf, uint64_t meslen);
void			reverse_64(void *buf, __uint128_t meslen);

uint32_t		cycle_shift_left(uint32_t num, int offset);
uint32_t		cycle_shift_right32(uint32_t num, int offset);
uint64_t		cycle_shift_right64(uint64_t num, int offset);

uint32_t		md5_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t		md5_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t		md5_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t		md5_i(uint32_t x, uint32_t y, uint32_t z);
void			add_size_md5(char *buffer, uint64_t bufferlen,
		uint64_t meslen);

uint32_t		ch32(uint32_t x, uint32_t y, uint32_t z);
uint32_t		maj32(uint32_t x, uint32_t y, uint32_t z);
uint32_t		sigma032(uint32_t x);
uint32_t		sigma132(uint32_t x);
uint32_t		delta032(uint32_t x);
uint32_t		delta132(uint32_t x);
void			add_size_sha32(char *buffer, uint64_t bufferlen,
		uint64_t meslen);
void			sha32_calc(char *buffer, uint64_t bufferlen,
		uint32_t var[8], uint32_t mem[8]);

uint64_t		ch64(uint64_t x, uint64_t y, uint64_t z);
uint64_t		maj64(uint64_t x, uint64_t y, uint64_t z);
uint64_t		sigma064(uint64_t x);
uint64_t		sigma164(uint64_t x);
uint64_t		delta064(uint64_t x);
uint64_t		delta164(uint64_t x);
void			add_size_sha64(char *buffer, __uint128_t bufferlen,
		__uint128_t meslen);
void			sha64_calc(char *buffer, __uint128_t bufferlen,
		uint64_t var[8], uint64_t mem[8]);

void			print_base64(char *message);
#endif
