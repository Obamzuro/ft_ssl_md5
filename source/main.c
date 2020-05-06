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

uint64_t		g_ssl_size = 0;
uint8_t			*g_ssl_flags[256] = { NULL, };
t_ssl_algh_name		g_ssl_current_algh;
uint8_t			g_ssl_last_flag_position;

t_ssl_algh_flags	g_ssl_algh_hashes_flags[] =
{
	{ .flag='q', .is_need_value=false, .help="quite"},
	{ .flag='r', .is_need_value=false, .help="reverse"},
	{ .flag='p', .is_need_value=false, .help="prompt"},
	{ .flag='s', .is_need_value=false, .help="string"},
};

t_ssl_algh_corr		g_ssl_alghs[SSL_ALGH_COUNT] =
{
	{.name = "md5",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = print_md5},
	{.name = "sha256",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = print_sha256},
	{.name = "sha224",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = print_sha224},
	{.name = "sha384",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = print_sha384},
	{.name = "sha512",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = print_sha512},
	{.name = "base64",
	 .func = print_base64},
	{.name = "des",
	 .func = print_des},
}

static void		print_hash(char *message, char flags[256],
		t_algh_corr *algh, char *filename)
{
	if (!flags['q'])
	{
		if (!flags['r'])
		{
			if (filename == message)
				ft_printf("%s (\"%s\") = ", algh->namecap, message);
			else
				ft_printf("%s (%s) = ", algh->namecap, filename);
			algh->func(message);
			ft_printf("\n");
		}
		else if (flags['r'])
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

static void		hash_stdin(char **argv, char flags[256],
		t_algh_corr *algh)
{
	char	*line;
	int		ret;

	line = 0;
	ret = get_file_str_inner(0, &line);
	if (flags['p'])
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

int				main(int argc, const char **argv)
{
	int			lastflag;
	t_algh_corr	algh;
	char		*initstr;

	preparation(argc, argv);
	(lastflag == argc || flags['p']) ? hash_stdin(argv, flags, &algh) : 0;
	while (lastflag < argc)
	{
		if (flags['s'])
		{
			initstr = argv[lastflag];
			flags['s'] = 0;
		}
		else
			initstr = get_file_str(argv[lastflag], argv);
		if (!initstr)
		{
			++lastflag;
			continue ;
		}
		print_hash(initstr, flags, &algh, argv[lastflag]);
		(argv[lastflag] != initstr) ? free(initstr) : 0;
		++lastflag;
	}
}
