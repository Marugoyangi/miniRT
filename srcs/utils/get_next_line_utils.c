/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:12:29 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/29 08:02:44 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (0);
}

char	*cut_nl(char *s)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	while (s[i])
	{
		if (s[i++] == '\n')
			break ;
	}
	len = i - 1;
	temp = (char *)malloc(sizeof (char) * (len + 1));
	if (temp == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

size_t	len_or_link(const char *s, t_list *first, t_list *second, int option)
{
	size_t	i;

	i = 0;
	if (s && option == 0)
	{
		while (s[i])
			i++;
		return (i);
	}
	if (option == 1)
	{
		if (first)
			first->next = second;
		if (second)
			second->prev = first;
		return (0);
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	l_s1;
	size_t	l_s2;

	l_s1 = len_or_link(s1, 0, 0, 0);
	l_s2 = len_or_link(s2, 0, 0, 0);
	p = (char *)malloc(sizeof (char) * (l_s1 + l_s2 + 1));
	if (!p)
	{
		if (s1)
			free ((char *)s1);
		return (NULL);
	}
	i = -1;
	while (++i < l_s1)
		p[i] = s1[i];
	i = -1;
	while (++i < l_s2)
		p[l_s1 + i] = s2[i];
	p[l_s1 + i] = '\0';
	if (s1)
		free ((char *)s1);
	return (p);
}

char	*ft_strdup(const char *s)
{
	size_t		i;
	size_t		len;
	char		*str;

	i = 0;
	len = len_or_link(s, 0, 0, 0);
	str = (char *)malloc(sizeof (char) * (len + 1));
	if (str == 0)
		return (0);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
