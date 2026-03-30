/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:37:21 by stefan           #+#    #+#             */
/*   Updated: 2025/08/14 16:37:21 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_split_values(char **values)
{
	int32_t	i;

	i = 0;
	if (!values)
		return ;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}

static t_parse_error	check_valid_color_format(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ',' && !ft_isspace(*str))
			return (PARSE_ERR_INVALID_RGB);
		str++;
	}
	return (PARSE_SUCCESS);
}

static t_parse_error	is_valid_color_component(char *str,
		int32_t *color_component)
{
	char	*end;

	*color_component = ft_atoi(str);
	end = str;
	while (*end && ft_isdigit(*end))
		end++;
	while (*end)
	{
		if (!ft_isspace(*end))
			return (PARSE_ERR_INVALID_RGB);
		end++;
	}
	if (*color_component < 0 || *color_component > 255)
		return (PARSE_ERR_INVALID_RGB);
	return (PARSE_SUCCESS);
}

static t_parse_error	validate_and_assign_color_component(char *str_val,
		int32_t *color_component)
{
	char	*str;

	str = str_val;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '\0')
		return (PARSE_ERR_INVALID_RGB);
	return (is_valid_color_component(str, color_component));
}

static t_parse_error	assign_color_values(char **rgb_values, int32_t color[3])
{
	int32_t	i;
	t_parse_error	error;

	i = 0;
	while (i < 3)
	{
		error = validate_and_assign_color_component(rgb_values[i], &color[i]);
		if (error != PARSE_SUCCESS)
			return (error);
		i++;
	}
	return (PARSE_SUCCESS);
}

t_parse_error	parse_color(char *line, int32_t color[3], t_app *app)
{
	char	**rgb_values;
	int32_t	count;
	t_parse_error	error;

	count = 0;
	error = check_valid_color_format(line);
	if (error != PARSE_SUCCESS)
		return (error);
	rgb_values = ft_split(line, ',');
	if (!rgb_values)
		return (PARSE_ERR_ALLOC);
	while (rgb_values[count])
		count++;
	if (count != 3)
	{
		free_split_values(rgb_values);
		return (PARSE_ERR_INVALID_RGB);
	}
	error = assign_color_values(rgb_values, color);
	free_split_values(rgb_values);
	(void)app;
	return (error);
}
