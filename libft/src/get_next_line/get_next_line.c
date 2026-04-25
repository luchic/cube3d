/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:38:42 by nluchini          #+#    #+#             */
/*   Updated: 2025/10/16 14:17:55 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*ft_get_line(char *line)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	tmp = (char *)ft_malloc((i + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (*line && *line != '\n')
		tmp[i++] = *line++;
	if (*line == '\n')
		tmp[i++] = *line++;
	tmp[i] = '\0';
	return (tmp);
}

static char	*ft_read(char *static_buff, int fd)
{
	char	*line;
	char	*tmp;
	int		bytes_read;

	line = ft_strjoin(static_buff, "");
	if (line == NULL)
		return (NULL);
	if (ft_strchr(line, '\n') != NULL)
		return (line);
	bytes_read = read(fd, static_buff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		static_buff[bytes_read] = '\0';
		tmp = ft_strjoin(line, static_buff);
		if (!tmp)
			return (ft_free(line), NULL);
		ft_free(line);
		line = tmp;
		if (ft_strchr(line, '\n') != NULL)
			return (line);
		bytes_read = read(fd, static_buff, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		return (ft_free(line), NULL);
	return (line);
}

static int	ft_clean_buff(char *buffer)
{
	size_t	i;
	char	*bg;
	char	*end;

	bg = ft_strchr(buffer, '\n');
	if (!bg)
		return (buffer[0] = '\0', 0);
	bg++;
	if (*bg == '\0')
		return (buffer[0] = '\0', 0);
	end = ft_strchr(bg, '\0');
	if (!end)
		return (buffer[0] = '\0', 0);
	i = 0;
	while (bg != end)
		buffer[i++] = *bg++;
	buffer[i] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read(buffer, fd);
	if (line == NULL)
		return (buffer[0] = '\0', NULL);
	res = ft_get_line(line);
	ft_free(line);
	if (res == NULL)
		return (buffer[0] = '\0', NULL);
	ft_clean_buff(buffer);
	if (res[0] == '\0')
	{
		ft_free(res);
		buffer[0] = '\0';
		return (NULL);
	}
	return (res);
}
