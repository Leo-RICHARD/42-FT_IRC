/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICKcommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:19:56 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 18:35:23 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

void	Server::nick(std::vector<std::string> message_split, Client *c)
{
	if (message_split.size() == 1 || message_split[1].empty())
		send_message(c, ERR_NONICKNAMEGIVEN);
	else if (lowercase(c->get_nickname()) == lowercase(message_split[1]))
		send_message(c, ERR_NICKNAMEINUSE(c->get_nickname()));
	else if (get_client(message_split[1]))
		send_message(c, ERR_NICKCOLLISION(message_split[1]));
	else if (message_split[1].find_first_of("#&@ ") != std::string::npos || message_split[1].size() > 9)
		send_message(c, ERR_ERRONEUSNICKNAME(message_split[1]));
	else
		c->set_nickname(message_split[1]);
}
