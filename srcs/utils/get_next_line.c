/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:12:26 by jeongbpa          #+#    #+#             */
/*   Updated: 2023/05/27 14:15:13 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_lstclear(t_list **lst, int fd)
{
	t_list	*curr;

	if (lst && *lst)
	{
		curr = *lst;
		if (curr->fd == fd)
		{
			len_or_link(0, curr->prev, curr->next, 1);
			if (curr->content)
				free(curr->content);
			if (curr->next)
				*lst = curr->next;
			else
				*lst = curr->prev;
			free(curr);
			return (1);
		}
	}
	return (1);
}

t_list	*ft_lstnew(t_list **saved, int fd, int option)
{
	t_list	*new;

	if (option == 0 || (option == 1 && !(*saved)))
	{
		new = (t_list *)malloc(sizeof(t_list));
		if (!new)
			return (NULL);
		new -> content = NULL;
		new -> fd = fd;
		new -> next = NULL;
		new -> prev = NULL;
		if (option == 1)
			*saved = new;
		else
			return (new);
	}
	else if (option == 1 && (*saved)->fd != fd)
		*saved = find_fd(*saved, fd);
	return (NULL);
}

char	*read_line(t_list *saved)
{
	char	*last;
	char	*return_line;
	char	*temp;

	last = 0;
	temp = saved -> content;
	last = ft_strchr(saved -> content, '\n');
	if (last)
	{
		*(last) = '\n';
		return_line = cut_nl(saved -> content);
		saved -> content = ft_strdup(last + 1);
		free(temp);
		return (return_line);
	}
	if (len_or_link((saved -> content), 0, 0, 0) > 0)
	{
		return_line = ft_strdup(saved -> content);
		saved -> content[0] = '\0';
		return (return_line);
	}
	return (NULL);
}

t_list	*find_fd(t_list *saved, int fd)
{
	while (saved->prev)
		saved = saved -> prev;
	while (saved)
	{
		if (saved->fd == fd)
			return (saved);
		if (!saved->next)
		{
			len_or_link(0, saved, ft_lstnew(&saved, fd, 0), 1);
			return (saved->next);
		}
		saved = saved->next;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*saved;
	char			buf[BUFFER_SIZE + 1];
	int				read_bytes;
	char			*return_line;

	if (fd >= 0 && BUFFER_SIZE > 0)
		ft_lstnew(&saved, fd, 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !saved)
		return (NULL);
	while (1)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0 && ft_lstclear(&saved, fd))
			return (NULL);
		buf[read_bytes] = '\0';
		saved -> content = ft_strjoin(saved -> content, buf);
		if (!(saved -> content) && ft_lstclear(&saved, fd))
			return (NULL);
		if (!read_bytes || ft_strchr(buf, '\n'))
			break ;
	}
	return_line = read_line(saved);
	if (!return_line)
		ft_lstclear(&saved, fd);
	return (return_line);
}
