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

static int	count_words(char *s, char c)
{
	int	word_count;
	int	i;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			word_count++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (word_count);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		arr_index;
	char	**array;

	if (!s)
		return (0);
	array = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!(array))
		return (0);
	array[count_words(s, c)] = 0;
	arr_index = 0;
	while (*s && *s == c)
		s++;
	j = 0;
	while (s[j])
	{
		i = j;
		while (s[j] && s[j] != c)
			j++;
		array[arr_index++] = ft_substr(s, i, j - i);
		while (s[j] && s[j] == c)
			j++;
	}
	return (array);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32)))
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	number = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		number *= 10;
		number += nptr[i] - '0';
		i++;
	}
	return (number * sign);
}