/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:12:32 by jeongbpa          #+#    #+#             */
/*   Updated: 2023/05/23 14:45:53 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	char			*content;
	int				fd;
}					t_list;

void	ft_lstadd(t_list *first, t_list *second);
t_list	*find_fd(t_list *saved, int fd);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, char c);
char	*cut_nl(char *s);
size_t	len_or_link(const char *s, t_list *first, t_list *second, int option);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
#endif