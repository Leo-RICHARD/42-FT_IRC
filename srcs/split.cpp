/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:53:32 by astucky           #+#    #+#             */
/*   Updated: 2022/06/17 18:54:16 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::vector<std::string>	split_command(std::string s)
{
	std::vector<std::string> ret;
	std::stringstream sstream(s);
	std::string word;
	sstream >> word;
	ret.push_back(word);
	if (s.length() > word.length() + 1)
		ret.push_back(s.substr(word.length() + 1));
	else
		ret.push_back("");
	return ret;
}

std::vector<std::string>	split_args(std::string s)
{
	std::vector<std::string> ret;
	std::stringstream sstream(s);
	std::string word = "";
	std::string special_word = "";
	while (sstream >> word)
	{
		if (word[0] == ':')
		{
			special_word = word;
			while (sstream >> word)
				special_word += " " + word;
			ret.push_back(special_word);
		}
		else
			ret.push_back(word);
	}
	return ret;
}

std::vector<std::string>	split_by_comma(std::string const &str)
{
	std::vector<std::string> args;
	std::string segment;
	std::stringstream stream(str);

	while(std::getline(stream, segment, ','))
	{
	   args.push_back(segment);
	}
	return (args);
}
