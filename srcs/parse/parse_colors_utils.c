/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:15:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/03 13:15:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parse_error	check_valid_color_format(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ',' && !ft_isspace(*str))
			return (PARSE_ERR_INVALID_RGB);
		str++;
	}
	return (PARSE_SUCCESS);
}

int32_t	count_str_array(char **values)
{
	int32_t	count;

	count = 0;
	while (values[count])
		count++;
	return (count);
}

t_parse_error	assign_color_values(char **rgb_values, int32_t color[3])
{
	int32_t			i;
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
