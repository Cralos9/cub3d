/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:57:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/10 15:09:00 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_element(char *line)
{
	int		i;
	char	*ele[7];

	ele[0] = "NO";
	ele[1] = "SO";
	ele[2] = "WE";
	ele[3] = "EA";
	ele[4] = "C";
	ele[5] = "F";
	ele[6] = 0;
	i = 0;
	while (ele[i])
	{
		if (i < 4 && !ft_strncmp(line, ele[i], 2))
			return (i);
		else if (i >= 4 && !ft_strncmp(line, ele[i], 1))
			return (i);
		i++;
	}
	return (-1);
}

int	check_rgb(int **cc, char *line)
{
	char	**rgb;
	int		i;

	i = 0;
	line += advance_space(line);
	rgb = ft_split(line, ',');
	while (rgb[i])
	{
		cc[0][i] = ft_atoi(rgb[i]);
		if (!color(cc[0][i]))
			break ;
		i++;
	}
	ft_free_dp((void **)rgb);
	if (i == 3)
		return (0);
	return (-1);
}

int	check_path(char *line)
{
	int	fd;

	line += advance_space(line);
	fd = open(line, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	line += 1;
	if (ft_strncmp(ft_strchr(line, '.'), ".xpm", 5))
		return (-1);
	return (0);
}

int	check_row(char *line)
{
	int	len;

	len = ft_strlen(line);
	if ((line[0] != '1' || line[len] != '1'))
		return (-1);
	return (0);
}

int	check_first_row(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == '1')
		i++;
	if (line[i] == '\0')
		return (0);
	return (-1);
}
