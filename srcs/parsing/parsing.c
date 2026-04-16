/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:58:56 by sruff             #+#    #+#             */
/*   Updated: 2026/04/16 17:52:19 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool check_file_extension(const char *file)
{
	int32_t len;
	
	if (!file)
		return(false);
	len = ft_strlen(file);
	if (len <= 4)
		return (false);
	if (ft_strncmp(file + len - 4, ".cub", 5) == 0)
		return (true);
	return (false);
	
	
} 

t_parse_error	parse_map(t_app *app, const char *file)
{
	//t_parse_error	error;

	(void)app;
	// open file to check if it exists/permission
	if (!check_file_extension(file))
		return (PARSE_ERR_INVALID_EXTENSION);
	
	//read file
	// parse file
	// validate map
	//init_player(app);
	return (PARSE_SUCCESS);
}