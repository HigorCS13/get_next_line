/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hicunha- <hicunha-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:56:07 by hicunha-          #+#    #+#             */
/*   Updated: 2023/11/06 20:35:08 by hicunha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	polish_list(t_list *list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buff || !clean_node)
		return ;
	last_node = find_last_node(list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[++i])
		buff[k++] = last_node->str_buf[i];
	buff[k] = '\0';
	clean_node->str_buf = buff;
	clean_node->next = NULL;
	dealloc(&list, clean_node, buff);
}

static char	*get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

static void	append(t_list **list, char *buff)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buff;
	new_node->next = NULL;
}

static void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buff;

	while (!found_newline(*list))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ;
		char_read = read(fd, buff, BUFFER_SIZE);
		if (!char_read)
		{
			free(buff);
			return ;
		}
		buff[char_read] = '\0';
		append(list, buff);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	polish_list(list);
	return (next_line);
}

/*#include <stdio.h>

int	main()
{
	int		fd;
	int		lines;
	char	*line;

	lines = 1;
	fd = open("lorem_ipsum.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%d->%s\n", lines++, line);
		free(line);
	}
	return (0);
}*/