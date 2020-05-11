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
t_ssl_algh_corr	g_ssl_current_algh;
uint8_t			g_ssl_last_flag_position;

t_ssl_algh_flags	g_ssl_algh_hashes_flags[] =
{
	{ .flag='q', .is_need_value=false, .help="quite mode"},
	{ .flag='r', .is_need_value=false, .help="reverse the format of the ouput"},
	{ .flag='p', .is_need_value=false, .help="echo STDIN to STDOUT"},
	{ .flag='s', .is_need_value=true, .help="print the hash of the next given string"},
};

t_ssl_algh_flags	g_ssl_algh_base64_flags[] =
{
	{ .flag='d', .is_need_value=false, .help="decode mode" },
	{ .flag='e', .is_need_value=false, .help="encode mode (default)" },
	{ .flag='i', .is_need_value=true, .help="input file" },
	{ .flag='o', .is_need_value=true, .help="output file" },
};

t_ssl_algh_flags	g_ssl_algh_des_flags[] =
{
	{ .flag='a', .is_need_value=false, .help="base64 mode" },
	{ .flag='d', .is_need_value=false, .help="decrypt mode" },
	{ .flag='e', .is_need_value=false, .help="encrypt mode (default)" },
	{ .flag='i', .is_need_value=true, .help="input file" },
	{ .flag='k', .is_need_value=true, .help="key in hex" },
	{ .flag='o', .is_need_value=true, .help="output file" },
	{ .flag='p', .is_need_value=true, .help="password in ascii" },
	{ .flag='s', .is_need_value=true, .help="salt in hex" },
	{ .flag='v', .is_need_value=true, .help="initialization vector in hex" },
};

t_ssl_algh_corr		g_ssl_alghs[SSL_ALGH_COUNT] =
{
	{.name = "md5",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "sha256",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "sha224",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "sha384",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "sha512",
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "base64",
	 .flags = g_ssl_algh_base64_flags,
	 .func = ssl_print_base64},
	{.name = "des",
	 .flags = g_ssl_algh_des_flags,
	 .func = ssl_print_des},
};

//static void		ssl_print_hash(char *message, char flags[256],
//		t_algh_corr *algh, char *filename)
//{
//	if (!flags['q'])
//	{
//		if (!flags['r'])
//		{
//			if (filename == message)
//				ft_printf("%s (\"%s\") = ", algh->namecap, message);
//			else
//				ft_printf("%s (%s) = ", algh->namecap, filename);
//			algh->func(message);
//			ft_printf("\n");
//		}
//		else if (flags['r'])
//		{
//			algh->func(message);
//			if (filename == message)
//				ft_printf(" \"%s\"\n", message);
//			else
//				ft_printf(" %s\n", filename);
//		}
//	}
//	else
//	{
//		algh->func(message);
//		if (!ft_strcmp(algh->name, "base64"))
//			return ;
//		ft_printf("\n");
//	}
//}
//
//static int		get_file_str_inner(int fd, char **ret)
//{
//	uintmax_t	size;
//	char		*temp;
//	char		*buf;
//	int			readret;
//
//	size = 1024;
//	*ret = (char *)malloc(size);
//	ft_bzero(*ret, size);
//	buf = (char *)malloc(size);
//	ft_bzero(buf, size);
//	g_size = 0;
//	while ((readret = read(fd, buf, 1024)) >= 0)
//	{
//		g_size += readret;
//		if (!readret)
//			break ;
//		temp = *ret;
//		*ret = (char *)malloc(size);
//		ft_bzero(*ret, size);
//		ft_memcpy(*ret, temp, size - 1024);
//		ft_memcpy(*ret + size - 1024, buf, readret);
//		ft_bzero(buf, 1024);
//		free(temp);
//		size += 1024;
//	}
//	free(buf);
//	return (readret);
//}
//
//static void		hash_stdin(char **argv, char flags[256],
//		t_algh_corr *algh)
//{
//	char	*line;
//	int		ret;
//
//	line = 0;
//	ret = get_file_str_inner(0, &line);
//	if (flags['p'])
//		ft_printf("%s", line);
//	if (ret == -1)
//		ft_fprintf(2, "%s: STDIN ERROR\n", argv[0]);
//	else
//	{
//		algh->func(line);
//		ft_printf("\n");
//	}
//	free(line);
//}
//
//static char		*get_file_str(char *filename, char **argv)
//{
//	char		*ret;
//	int			fd;
//	int			readret;
//
//	fd = open(filename, O_RDONLY);
//	if (fd == -1)
//	{
//		ft_fprintf(2, "%s: %s: %s\n", argv[0], filename,
//				strerror(errno));
//		return (0);
//	}
//	readret = get_file_str_inner(fd, &ret);
//	if (readret == -1)
//	{
//		ft_fprintf(2, "%s: File reading Error: %s\n", argv[0], filename);
//		free(ret);
//		return (0);
//	}
//	return (ret);
//}

void			handle_error(t_ssl_errors error)
{
	return ;
}

static t_ssl_errors		ssl_print_hash_stdin(void)
{
	t_ssl_errors	returned_value;
	char			*line;

	line = NULL;
	returned_value = ft_get_file_content(0, &line);
	if (returned_value != SSL_OK)
		return (returned_value);
	if (g_ssl_flags['p'])
		ft_printf("%s", line);
	ssl_print_hash_func();
	free(line);
}

t_ssl_errors			ssl_print_hash(int argc, const char **argv)
{
	if (g_ssl_last_flag_position == argc || g_ssl_flags['p'])
		ssl_print_hash_stdin();
	return (SSL_OK);
}

int				main(int argc, const char **argv)
{
	t_ssl_algh_corr	algh;
	t_ssl_errors	returned_value;
	char			*initstr;

	returned_value = handle_arguments(argc, argv);
	if (returned_value != SSL_OK)
	{
		handle_error(returned_value);
		return (returned_value);
	}
	returned_value = g_ssl_current_algh.func(argc, argv);
	if (returned_value != SSL_OK)
	{
		handle_error(returned_value);
		return (returned_value);
	}
//
//	(lastflag == argc || flags['p']) ? hash_stdin(argv, flags, &algh) : 0;
//	while (lastflag < argc)
//	{
//		if (flags['s'])
//		{
//			initstr = argv[lastflag];
//			flags['s'] = 0;
//		}
//		else
//			initstr = get_file_str(argv[lastflag], argv);
//		if (!initstr)
//		{
//			++lastflag;
//			continue ;
//		}
//		ssl_print_hash(initstr, flags, &algh, argv[lastflag]);
//		(argv[lastflag] != initstr) ? free(initstr) : 0;
//		++lastflag;
//	}
}
