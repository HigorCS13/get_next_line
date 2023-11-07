/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hicunha- <hicunha-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:38:48 by hicunha-          #+#    #+#             */
/*   Updated: 2023/11/07 20:50:48 by hicunha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		len_to_newline(t_list *list);
void	copy_str(t_list *list, char *str);
void	dealloc(t_list **list, t_list *clean_node, char *buff);
int		found_newline(t_list *list);
t_list	*find_last_node(t_list *list);

#endif