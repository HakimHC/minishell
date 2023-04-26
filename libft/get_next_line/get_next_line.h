/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:34:03 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 02:29:09 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <stddef.h>

char	*get_next_line(int fd);
char	*get_l(char *buff);
char	*read_buffer(char *s, int i);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
size_t	*ft_strlen_gnl(char const *str);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_strdup_gnl(char const *s1);

#endif
