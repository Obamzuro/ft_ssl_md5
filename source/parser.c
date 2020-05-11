/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:40:12 by obamzuro          #+#    #+#             */
/*   Updated: 2020/02/24 16:34:09 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

//static void			check_flags(uint8_t flag, const char **argv)
//{
//	uint8_t		i;
//
//	i = 0;
//	while (i < AM_PARAMS)
//	{
//		if (flag == PARAMS[i])
//			return ;
//		++i;
//	}
//	ft_fprintf(2, "%s: illegal option -- %c\nusage:\
//			%s command [-%s] [command args]\n",
//			argv[0], flag, argv[0], PARAMS);
//	exit(EXIT_FAILURE);
//}

static t_ssl_errors			ssl_fill_flag(int argc, const char **argv, 
		uint16_t *current_arg, uint8_t flag)
{
	uint8_t		algh_flag;

	algh_flag = 0;
	while (algh_flag < sizeof(g_ssl_current_algh.flags) / sizeof(*g_ssl_current_algh.flags))
	{
		if (g_ssl_current_algh.flags[algh_flag].flag == flag)
		{
			if (g_ssl_current_algh.flags[algh_flag].is_need_value == true)
			{
				if (argv[*current_arg + 1] == NULL)
					return (SSL_ERROR_WRONG_PARAM);
				g_ssl_flags[argv[*current_arg][1]] = (char *)argv[*current_arg + 1];
				*current_arg += 1;
			}
			else
				g_ssl_flags[argv[*current_arg][1]] = (char *)0x1;
			return (SSL_OK);
		}
		++algh_flag;
	}
	return (SSL_ERROR_WRONG_PARAM);
}

static t_ssl_errors			ssl_fill_flags(int argc, const char **argv)
{
	t_ssl_errors	returned_value;
	uint16_t		current_arg;

	current_arg = 2;
	while (current_arg < argc)
	{
		if (argv[current_arg][0] != '-' || !ft_strcmp(argv[current_arg], "--"))
		{
			g_ssl_last_flag_position = current_arg;
			return (SSL_OK);
		}
		else if (argv[current_arg][0] == '-')
		{
			if (argv[current_arg][1] == '\0' ||
					argv[current_arg][2] != '\0')
				return (SSL_ERROR_WRONG_PARAM);
			returned_value = ssl_fill_flag(argc, argv, &current_arg, argv[current_arg][1]);
			if (returned_value != SSL_OK)
				return (returned_value);
		}
		++current_arg;
	}
	g_ssl_last_flag_position = current_arg;
	return (SSL_OK);
}

static t_ssl_errors			ssl_select_algh(int argc, const char **argv)
{
	uint16_t	algh_number;

	if (argc > 1)
	{
		algh_number = 0;
		while (algh_number < SSL_ALGH_COUNT)
		{
			if (!ft_strcmp(g_ssl_alghs[algh_number].name, argv[1]))
			{
				g_ssl_current_algh = g_ssl_alghs[algh_number];
				return (SSL_OK);
			}
			++algh_number;
		}
	}
	return (SSL_ERROR_WRONG_ALGH);
}

t_ssl_errors				handle_arguments(int argc, const char **argv)
{
	t_ssl_errors	returned_value;
	uint32_t	i;
	char		*temp;

	returned_value = ssl_select_algh(argc, argv);
	if (returned_value != SSL_OK)
		return (returned_value);
	returned_value = ssl_fill_flags(argc, argv);
	if (returned_value != SSL_OK)
		return (returned_value);
	return (SSL_OK);
}
