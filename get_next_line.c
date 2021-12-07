/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unclebrendi <unclebrendi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 00:13:12 by unclebrendi       #+#    #+#             */
/*   Updated: 2021/12/08 00:13:14 by unclebrendi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*ft_strcpy_ur(char	*dst, char	*src, int j)
{
	int	i;

	i = 0;
	while (src[j])
		dst[i++] = src[j++];
	return (dst);
}

char	*ft_realloc(char *str, size_t size)
{
	char	*new;

	new = malloc(sizeof(char) * size);
	if (str)
		new = ft_strdup(str);
	return (new);
}

char	*ft_strlcpy_l(char *dst, char *src, int i)
{
	int	j;

	j = 0;
	while (src[j] != '\n' && src[j])
	{
		if (i == BUFFER_SIZE)
			dst = ft_realloc(dst, (ft_strlen(dst) + BUFFER_SIZE));
		dst[i++] = src[j++];
	}
	return (dst);
}

int	find_nl(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*unret = NULL;
	char		*rd;
	int			i;

	i = -1;
	if (!unret)
		unret = malloc(sizeof(char) * BUFFER_SIZE);
	ret = malloc(sizeof(char) * BUFFER_SIZE + 1);
	ft_bzero(ret, BUFFER_SIZE + 1);
	while (unret[++i])
		ret[i] = unret[i];
	ft_bzero(unret, BUFFER_SIZE);
	rd = malloc(sizeof(char) * BUFFER_SIZE);
	while (read(fd, rd, BUFFER_SIZE) > 0)
	{
		ret = ft_strlcpy_l(ret, rd, ft_strlen(ret));
		if (rd[find_nl(rd)] == '\n')
			unret = ft_strcpy_ur(unret, rd, find_nl(rd) + 1);
		if (rd[find_nl(rd)] == '\n')
			break ;
	}
	free (rd);
	return (ret);
}
