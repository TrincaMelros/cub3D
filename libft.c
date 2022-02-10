/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:15:00 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/10 17:15:01 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	unsigned int	i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	int		i;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	ptr = (char *)malloc(sizeof(*ptr) * len + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != (unsigned char)c)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		z;

	if (!s1 || !s2)
		return (0);
	i = (ft_strlen(s1) + ft_strlen(s2));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	z = 0;
	while (s2[z])
	{
		str[i] = s2[z];
		i++;
		z++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	s1;
	unsigned int	s2;
	unsigned int	rlen;

	if (!s)
		return (0);
	rlen = ft_strlen(s);
	if (start >= rlen)
	{
		str = malloc(sizeof(char));
		*str = '\0';
		return (str);
	}
	if (rlen < len)
		return (ft_strdup(s + start));
	str = (char *)malloc(len + 1);
	if (!(str))
		return (0);
	s1 = start;
	s2 = 0;
	while (s1 < rlen && s2 < len)
		str[s2++] = s[s1++];
	str[s2] = '\0';
	return (str);
}