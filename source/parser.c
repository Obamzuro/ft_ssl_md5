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

static void			reset_params(char params[256])
{
	int		i;

	i = 0;
	while (i < 256)
	{
		params[i] = 0;
		++i;
	}
}

static void			check_params(char param, char **argv)
{
	int		i;

	i = 0;
	while (i < AM_PARAMS)
	{
		if (param == PARAMS[i])
			return ;
		++i;
	}
	ft_fprintf(2, "%s: illegal option -- %c\nusage:\
			%s command [-%s] [command args]\n",
			argv[0], param, argv[0], PARAMS);
	exit(EXIT_FAILURE);
}

static t_algh_corr	*return_command(int argc, char **argv,
			t_algh_corr *alghs)
{
	int		i;

	if (argc > 1)
	{
		i = -1;
		while (++i < AM_ALGHS)
		{
			if (!ft_strcmp(alghs[i].name, argv[1]))
				return (&alghs[i]);
		}
	}
	ft_fprintf(2, "%s: Error: '%s' is an invalid command.\n\n",
			argv[0], argv[1]);
	ft_fprintf(2, "Standard commands:\n\n");
	ft_fprintf(2, "Message Digest commands:\n");
	i = -1;
	while (++i < AM_ALGHS)
		ft_fprintf(2, "%s\n", alghs[i].name);
	ft_fprintf(2, "\nCipher commands:\n");
	exit(EXIT_FAILURE);
	return (0);
}

static void			fill_alghs(t_algh_corr *alghs)
{
	alghs[0].name = "md5";
	alghs[0].namecap = "MD5";
	alghs[0].func = print_md5;
	alghs[1].name = "sha256";
	alghs[1].namecap = "SHA256";
	alghs[1].func = print_sha256;
	alghs[2].name = "sha224";
	alghs[2].namecap = "SHA224";
	alghs[2].func = print_sha224;
	alghs[3].name = "sha512";
	alghs[3].namecap = "SHA512";
	alghs[3].func = print_sha512;
	alghs[4].name = "sha384";
	alghs[4].namecap = "SHA384";
	alghs[4].func = print_sha384;
	alghs[5].name = "base64";
	alghs[5].namecap = "BASE64";
	alghs[5].func = print_base64;
}

int					preparation(int argc, char **argv,
		char params[256], t_algh_corr *algh)
{
	int			i;
	char		*temp;
	t_algh_corr	alghs[AM_ALGHS];

	fill_alghs(alghs);
	*algh = *return_command(argc, argv, alghs);
	reset_params(params);
	i = 2;
	while (i < argc)
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && !argv[i][1]))
			return (i);
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 0)
			return (i + 1);
		temp = argv[i] + 1;
		while (*temp)
		{
			check_params(*temp, argv);
			params[(int)*temp++] = 1;
		}
		++i;
	}
	return (i);
}
