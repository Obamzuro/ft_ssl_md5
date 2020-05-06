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
# include <inttypes.h>
# include <stdbool.h>
# define GET_BIT(number, position) ((number >> position) & 1)
# define SET_BIT(number, position, bit) (number = ((number & (~(1 << position))) | (bit << position)))

typedef enum		e_ssl_algh_name
{
	SSL_ALGH_MD5 = 0,
	SSL_ALGH_SHA224,
	SSL_ALGH_SHA256,
	SSL_ALGH_SHA384,
	SSL_ALGH_SHA512,
	SSL_ALGH_BASE64,
	SSL_ALGH_DES,
	SSL_ALGH_COUNT
}			t_ssl_algh_name;

typedef enum		e_ssl_errors
{
	SSL_OK = 0,
	SSL_ERROR_WRONG_ALGH,
	SSL_ERROR_WRONG_PARAM,
	SSL_ERROR_COUNT
}			t_ssl_errors;

typedef struct		s_ssl_algh_flags
{
	uint8_t		flag;
	bool		is_need_value;
	char		*help;
}			t_ssl_algh_flags;

typedef struct		s_ssl_algh_corr
{
	char			*name;
	t_ssl_algh_flags	*flags;
	void			(*func)(char *);
}			t_ssl_algh_corr;

extern u_int64_t	g_ssl_size;
extern uint8_t		*g_ssl_flags[256];
extern t_ssl_algh_name	g_ssl_current_algh;
extern t_ssl_algh_corr	g_ssl_alghs[SSL_ALGH_COUNT];
uint8_t			g_ssl_last_flag_position;

t_ssl_errors		handle_arguments(int argc, const char **argv);

void			print_md5(char *message);
void			print_sha256(char *message);
void			print_sha224(char *message);
void			print_sha512(char *message);
void			print_sha384(char *message);

u_int64_t		ft_strlen64(char *str);
__uint128_t		ft_strlen128(char *str);
void			reverse_32(void *buf, u_int64_t meslen);
void			reverse_64(void *buf, __uint128_t meslen);

uint32_t		cycle_shift_left(uint32_t num, int offset);
uint32_t		cycle_shift_right32(uint32_t num, int offset);
u_int64_t		cycle_shift_right64(u_int64_t num, int offset);

uint32_t		md5_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t		md5_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t		md5_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t		md5_i(uint32_t x, uint32_t y, uint32_t z);
void			add_size_md5(char *buffer, u_int64_t bufferlen,
		u_int64_t meslen);

uint32_t		ch32(uint32_t x, uint32_t y, uint32_t z);
uint32_t		maj32(uint32_t x, uint32_t y, uint32_t z);
uint32_t		sigma032(uint32_t x);
uint32_t		sigma132(uint32_t x);
uint32_t		delta032(uint32_t x);
uint32_t		delta132(uint32_t x);
void			add_size_sha32(char *buffer, u_int64_t bufferlen,
		u_int64_t meslen);
void			sha32_calc(char *buffer, u_int64_t bufferlen,
		uint32_t var[8], uint32_t mem[8]);

u_int64_t		ch64(u_int64_t x, u_int64_t y, u_int64_t z);
u_int64_t		maj64(u_int64_t x, u_int64_t y, u_int64_t z);
u_int64_t		sigma064(u_int64_t x);
u_int64_t		sigma164(u_int64_t x);
u_int64_t		delta064(u_int64_t x);
u_int64_t		delta164(u_int64_t x);
void			add_size_sha64(char *buffer, __uint128_t bufferlen,
		__uint128_t meslen);
void			sha64_calc(char *buffer, __uint128_t bufferlen,
		u_int64_t var[8], u_int64_t mem[8]);

void			print_base64(char *message);

void			print_des(char *message);
#endif
