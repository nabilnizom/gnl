/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohd-ni <amohd-ni@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 00:18:36 by amohd-ni          #+#    #+#             */
/*   Updated: 2021/12/15 14:49:44 by amohd-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
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
	free (str);
	return (new);
}

char	*ft_strcpy_l(char *dst, char *src, int i)
{
	int	j;

	j = 0;
	while (src[j] != '\n' && src[j])
	{
		if (i == BUFFER_SIZE)
			dst = ft_realloc(dst, (ft_strlen(dst) + BUFFER_SIZE));
		dst[i++] = src[j++];
	}
	if (src[j] == '\n')
		dst[i] = src[j];
	i++;
	dst[i] = '\0';
	return (dst);
}

int	find_nl(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*unret = NULL;
	char		*rd;

	if (!unret)
		unret = malloc(sizeof(char) * BUFFER_SIZE + 1);
	ret = malloc(sizeof(char) * BUFFER_SIZE + 2);
	ft_bzero(ret, BUFFER_SIZE + 1);
	if (unret)
		ret = ft_strcpy_ur(ret, unret, 0);
	ft_bzero(unret, BUFFER_SIZE + 1);
	rd = malloc(sizeof(char) * BUFFER_SIZE + 1);
	rd[BUFFER_SIZE] = '\0';
	while (read(fd, rd, BUFFER_SIZE) > 0)
	{
		ret = ft_strcpy_l(ret, rd, ft_strlen(ret));
		if (find_nl(rd) > 0)
			unret = ft_strcpy_ur(unret, rd, find_nl(rd));
		if (find_nl(rd) >= 0)
			break ;
	}
	free (rd);
	return (ret);
}
