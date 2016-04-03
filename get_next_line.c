/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chray <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:44:20 by chray             #+#    #+#             */
/*   Updated: 2016/03/18 17:38:52 by chray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					ft_read_check(const char *s, int c)
{
	int				index;

	index = 0;
	while (s[index] && c != s[index])
		index++;
	if (c != s[index])
		return (0);
	return (1);
}

char				*join_line(char *str, char **line, char *buf, int *i)
{
	int				j;
	char			tmp;
	int				flag;

	*i = 1;
	j = 0;
	flag = 0;
	if (buf != NULL && str == NULL)
		str = ft_strdup(buf);
	while (str[j] != '\n' && str[j])
		j++;
	tmp = str[j];
	if (str[j] == '\0')
		flag = 1;
	str[j] = '\0';
	*line = ft_strjoin(*line, str);
	if (str[j + 1] == '\0' || flag == 1)
		str = NULL;
	else if (tmp == '\n')
		str = &(str[j + 1]);
	return (str);
}

int					get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static char		*str = NULL;
	int				ret;
	int				i;

	ret = 0;
	i = 0;
	if ((void*)line == NULL || fd < 0)
		return (-1);
	*line = NULL;
	if (str != NULL)
		str = join_line(str, line, buf, &i);
	if (str == NULL || str[0] == '\0')
	{
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			str = join_line(str, line, buf, &i);
			if (ft_read_check(buf, '\n') != 0)
				break ;
		}
	}
	if (i == 1)
		return (1);
	return (ret < 0 ? -1 : 0);
}
