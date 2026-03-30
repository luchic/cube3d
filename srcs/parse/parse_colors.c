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

static bool	check_valid_color_format(char *str, t_app *app)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ',' && !ft_isspace(*str))
		{
			exit_with_error("Invalid RGB values: non-numeric characters found.",
				app);
			return (false);
		}
		str++;
	}
	return (true);
}

static bool	is_valid_color_component(char *str, int32_t *color_component,
		t_app *app)
{
	char	*end;

	*color_component = ft_atoi(str);
	end = str;
	while (*end && ft_isdigit(*end))
		end++;
	while (*end)
	{
		if (!ft_isspace(*end))
		{
			exit_with_error("Invalid character after RGB value.", app);
			return (false);
		}
		end++;
	}
	if (*color_component < 0 || *color_component > 255)
	{
		exit_with_error("RGB color values must be between 0 and 255.", app);
		return (false);
	}
	return (true);
}

static bool	validate_and_assign_color_component(char *str_val,
		int32_t *color_component, t_app *app)
{
	char	*str;

	str = str_val;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '\0')
	{
		exit_with_error("Empty value in RGB color specification.", app);
		return (false);
	}
	return (is_valid_color_component(str, color_component, app));
}

static void	assign_color_values(char **rgb_values, int32_t color[3], t_app *app)
{
	int32_t	i;

	i = 0;
	while (i < 3)
	{
		if (!validate_and_assign_color_component(rgb_values[i], &color[i], app))
			return ;
		i++;
	}
}

void	parse_color(char *line, int32_t color[3], t_app *app)
{
	char	**rgb_values;
	int32_t	count;

	count = 0;
	if (!check_valid_color_format(line, app))
		return ;
	rgb_values = ft_split(line, ',');
	if (!rgb_values)
		exit_with_error("Memory allocation failed for color parsing.", app);
	while (rgb_values[count])
		count++;
	if (count != 3)
	{
		exit_with_error("Invalid RGB color format: must have exactly 3 values.",
			app);
		return ;
	}
	assign_color_values(rgb_values, color, app);
}
