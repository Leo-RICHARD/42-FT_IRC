/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICEcommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:21:02 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 19:55:46 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

void	Server::notice(std::vector<std::string> message_split, Client *c)
{
	std::vector<std::string> args_split = split_args(message_split[1]);

	bool no_text = 1;
	for (int i = message_split[1].find(':'); message_split[1][i + 1] && no_text; i++)
		if (message_split[1][i + 1] != ' ' && message_split[1][i + 1] != '\n')
			no_text = 0;
	if (message_split[1].find(':') != std::string::npos && !no_text && args_split.size() >= 2 && args_split[1][0] == ':')
	{
		if (args_split[0][0] == '#')
		{
			Channel *chan = get_chan(args_split[0]);
			if (chan == NULL || !chan->get_member(c->get_nickname()))
				return;
			send_message_to_chan(args_split[0], args_split[1], c);
		}
		else
		{
			Client *recipient = NULL;
			recipient = get_client(args_split[0]);
			if (recipient == NULL)
				return;
			std::string msg = ":" + c->get_nickname() + " NOTICE " + recipient->get_nickname() + ' ' + args_split[args_split.size() - 1] + "\r\n";
			send_message(recipient, msg);
		}

	}

}
