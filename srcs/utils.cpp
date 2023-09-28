/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:23:58 by astucky           #+#    #+#             */
/*   Updated: 2022/10/28 16:18:48 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

std::string const	lowercase(std::string const &str)
{
	int i;
	std::string strr;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '}')
			strr += ']';
		else if (str[i] == '{')
			strr += '[';
		else if (str[i] == '|')
			strr += '\\';
		else if (str[i] > 64 && str[i] < 91)
			strr += str[i] + 32;
		else
			strr += str[i];
	}
	return (strr);
}
