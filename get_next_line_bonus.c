/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hicunha- <hicunha-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:34:55 by hicunha-          #+#    #+#             */
/*   Updated: 2023/11/13 21:34:55 by hicunha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*process_line(char *new_line, char *buff, int buffer_size,
	int *line_length)
{
	char	*line;

	auto int index = 0;
	auto int size_line = 0;
	auto int buffer_index = 0;
	line = new_line;
	*line_length += buffer_size;
	new_line = malloc((*line_length + 1) * sizeof(char));
	if (new_line)
	{
		new_line[*line_length] = 0;
		while (line && line[size_line])
			new_line[index++] = line[size_line++];
		size_line = 0;
		while (buff && buff[size_line])
		{
			if (size_line < buffer_size)
				new_line[index++] = buff[size_line];
			else
				buff[buffer_index++] = buff[size_line];
			buff[size_line++] = 0;
		}
	}
	free(line);
	return (new_line);
}

char	*read_buffer(int fd, char buff[FOPEN_MAX][BUFFER_SIZE + 1], int *sz_bf)
{
	auto int flag = 1;
	auto int size_line = 0;
	auto char *line = NULL;
	while (flag > 0)
	{
		if (!buff[fd][0])
			*sz_bf = read(fd, buff[fd], BUFFER_SIZE);
		if (*sz_bf == -1)
		{
			free(line);
			line = NULL;
		}
		flag = *sz_bf;
		if (*sz_bf > 0)
		{
			*sz_bf = 0;
			while (buff[fd][*sz_bf] && buff[fd][*sz_bf] != '\n')
				(*sz_bf)++;
			flag = (flag == *sz_bf);
			*sz_bf += buff[fd][*sz_bf] == '\n';
			line = process_line(line, buff[fd], *sz_bf, &size_line);
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[FOPEN_MAX][BUFFER_SIZE + 1];

	auto int sz_bf = 0;
	if ((fd < 0 || fd > FOPEN_MAX) || !BUFFER_SIZE)
		return (NULL);
	while (buff[fd][sz_bf])
		sz_bf++;
	return (read_buffer(fd, buff, &sz_bf));
}

/*
int main(int argc, char const *argv[])
{
	int		fd;
	char	*line;

	fd = open(".lovezin.txt", O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}*/
