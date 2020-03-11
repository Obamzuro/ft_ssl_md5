/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:53:03 by obamzuro          #+#    #+#             */
/*   Updated: 2020/02/24 18:09:55 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		print_hash(char *message, char params[256],
		t_algh_corr *algh, char *filename)
{
	if (!params['q'])
	{
		if (!params['r'])
		{
			if (filename == message)
				ft_printf("%s (\"%s\") = ", algh->namecap, message);
			else
				ft_printf("%s (%s) = ", algh->namecap, filename);
			algh->func(message);
			ft_printf("\n");
		}
		else if (params['r'])
		{
			algh->func(message);
			if (filename == message)
				ft_printf(" \"%s\"\n", message);
			else
				ft_printf(" %s\n", filename);
		}
	}
	else
	{
		algh->func(message);
		if (!ft_strcmp(algh->name, "base64"))
			return ;
		ft_printf("\n");
	}
}

uint64_t		g_size = 0;
char			params[256];

static int		get_file_str_inner(int fd, char **ret)
{
	uintmax_t	size;
	char		*temp;
	char		*buf;
	int			readret;

	size = 1024;
	*ret = (char *)malloc(size);
	ft_bzero(*ret, size);
	buf = (char *)malloc(size);
	ft_bzero(buf, size);
	g_size = 0;
	while ((readret = read(fd, buf, 1024)) >= 0)
	{
		g_size += readret;
		if (!readret)
			break ;
		temp = *ret;
		*ret = (char *)malloc(size);
		ft_bzero(*ret, size);
		ft_memcpy(*ret, temp, size - 1024);
		ft_memcpy(*ret + size - 1024, buf, readret);
		ft_bzero(buf, 1024);
		free(temp);
		size += 1024;
	}
	free(buf);
	return (readret);
}

static void		hash_stdin(char **argv, char params[256],
		t_algh_corr *algh)
{
	char	*line;
	int		ret;

	line = 0;
	ret = get_file_str_inner(0, &line);
	if (params['p'])
		ft_printf("%s", line);
	if (ret == -1)
		ft_fprintf(2, "%s: STDIN ERROR\n", argv[0]);
	else
	{
		algh->func(line);
		ft_printf("\n");
	}
	free(line);
}

static char		*get_file_str(char *filename, char **argv)
{
	char		*ret;
	int			fd;
	int			readret;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "%s: %s: %s\n", argv[0], filename,
				strerror(errno));
		return (0);
	}
	readret = get_file_str_inner(fd, &ret);
	if (readret == -1)
	{
		ft_fprintf(2, "%s: File reading Error: %s\n", argv[0], filename);
		free(ret);
		return (0);
	}
	return (ret);
}

int				main(int argc, char **argv)
{
	int			lastparam;
	t_algh_corr	algh;
	char		*initstr;

	lastparam = preparation(argc, argv, params, &algh);
	(lastparam == argc || params['p']) ? hash_stdin(argv, params, &algh) : 0;
	while (lastparam < argc)
	{
		if (params['s'])
		{
			initstr = argv[lastparam];
			params['s'] = 0;
		}
		else
			initstr = get_file_str(argv[lastparam], argv);
		if (!initstr)
		{
			++lastparam;
			continue ;
		}
		print_hash(initstr, params, &algh, argv[lastparam]);
		(argv[lastparam] != initstr) ? free(initstr) : 0;
		++lastparam;
	}
}
