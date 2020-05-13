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
uint16_t		g_ssl_last_flag_position;
t_ssl_algh		g_ssl_current_algh;

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

t_ssl_algh			g_ssl_alghs[SSL_ALGH_COUNT] =
{
	{.name = "md5",
	 .type_name = SSL_ALGH_HASH_MD5,
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "sha224",
	 .type_name = SSL_ALGH_HASH_SHA224,
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "sha256",
	 .type_name = SSL_ALGH_HASH_SHA256,
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "sha384",
	 .type_name = SSL_ALGH_HASH_SHA384,
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "sha512",
	 .type_name = SSL_ALGH_HASH_SHA512,
	 .flags = g_ssl_algh_hashes_flags,
	 .func = ssl_print_hash},
	{.name = "base64",
	 .type_name = SSL_ALGH_ENCODE_BASE64,
	 .flags = g_ssl_algh_base64_flags,
	 .func = ssl_print_base64},
	{.name = "des",
	 .type_name = SSL_ALGH_CYPHER_DES,
	 .flags = g_ssl_algh_des_flags,
	 .func = ssl_print_des},
};

t_ssl_algh_hash		g_ssl_hash_alghs[SSL_ALGH_HASH_COUNT - SSL_ALGH_HASH_MD5] =
{
	{.hash_type = SSL_ALGH_HASH_MD5, .func = print_md5},
	{.hash_type = SSL_ALGH_HASH_SHA224, .func = print_sha224},
	{.hash_type = SSL_ALGH_HASH_SHA256, .func = print_sha256},
	{.hash_type = SSL_ALGH_HASH_SHA384, .func = print_sha384},
	{.hash_type = SSL_ALGH_HASH_SHA512, .func = print_sha512},
};

static t_ssl_errors		ssl_print_hash_inner(char *message, const char *filename)
{
	t_ssl_errors	returned_value;

	if (!g_ssl_flags['q'])
	{
		if (!g_ssl_flags['r'])
		{
			if (filename == message)
				ft_printf("%s (\"%s\") = ", g_ssl_current_algh.name, message);
			else
				ft_printf("%s (%s) = ", g_ssl_current_algh.name, filename);
			returned_value = g_ssl_hash_alghs[g_ssl_current_algh.type_name].func(message);
			if (returned_value != SSL_OK)
				return (returned_value);
			ft_printf("\n");
		}
		else if (g_ssl_flags['r'])
		{
			returned_value = g_ssl_hash_alghs[g_ssl_current_algh.type_name].func(message);
			if (returned_value != SSL_OK)
				return (returned_value);
			if (filename == message)
				ft_printf(" \"%s\"\n", message);
			else
				ft_printf(" %s\n", filename);
		}
	}
}


static ssize_t		ft_get_file_content(int fd, char **ret)
{
	char		*temp;
	char		*buf;
	uint32_t	size;
	uint32_t	was_read;
	ssize_t		sum_line_size;

	size = 1024;
	sum_line_size = 0;
	*ret = (char *)ft_memalloc(size);
	buf = (char *)ft_memalloc(size);
	while ((was_read = read(fd, buf, 1024)) >= 0)
	{
		sum_line_size += was_read;
		if (!was_read)
			break ;
		temp = *ret;
		*ret = (char *)malloc(size);
		ft_bzero(*ret, size);
		ft_memcpy(*ret, temp, size - 1024);
		ft_memcpy(*ret + size - 1024, buf, was_read);
		ft_bzero(buf, 1024);
		free(temp);
		sum_line_size += 1024;
	}
	free(buf);
	if (was_read == -1)
	{
		free(ret);
		return (-1);
	}
	return (sum_line_size);
}

static char		*ft_get_file(const char *filename)
{
	char		*file_content;
	ssize_t		ret;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	ret = ft_get_file_content(fd, &file_content);
	if (ret == -1)
		return (NULL);
	return (file_content);
}

void			handle_error(t_ssl_errors error)
{
	return ;
}

static t_ssl_errors		ssl_print_hash_stdin(void)
{
	t_ssl_errors	returned_value;
	char			*line;

	line = NULL;
	if (ft_get_file_content(0, &line) == -1)
		return (SSL_ERROR_GET_FILE_ERROR);
	if (g_ssl_flags['p'])
		ft_printf("%s", line);
	returned_value = g_ssl_hash_alghs[g_ssl_current_algh.type_name].func(line);
	free(line);
	if (returned_value != SSL_OK)
		return (SSL_ERROR_HASH);
	ft_printf("/n");
	return (SSL_OK);
}

t_ssl_errors			ssl_print_hash(int argc, const char **argv)
{
	char	*initstr;

	if (g_ssl_last_flag_position == argc || g_ssl_flags['p'])
		ssl_print_hash_stdin();
	while (g_ssl_last_flag_position < argc)
	{
		if (g_ssl_flags['s'])
		{
			initstr = (char *)argv[g_ssl_last_flag_position];
			g_ssl_flags['s'] = NULL;
		}
		else
		{
			initstr = ft_get_file(argv[g_ssl_last_flag_position]);
			if (!initstr)
			{
				ft_printf("Can't open the file: %s/n", argv[g_ssl_last_flag_position]);
				++g_ssl_last_flag_position;
				continue ;
			}
		}
		ssl_print_hash_inner(initstr, argv[g_ssl_last_flag_position]);
		if (argv[g_ssl_last_flag_position] != initstr)
			free(initstr);
		++g_ssl_last_flag_position;
	}
	return (SSL_OK);
}

int				main(int argc, const char **argv)
{
	t_ssl_algh		algh;
	t_ssl_errors	returned_value;

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
}
