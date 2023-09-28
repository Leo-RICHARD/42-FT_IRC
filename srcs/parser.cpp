/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:56:51 by astucky           #+#    #+#             */
/*   Updated: 2022/10/28 18:35:42 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	Server::parse(const std::string input, std::vector<Client *>::iterator c)
{
	Client *ptr = *c;
	int cmd;
	std::string message;
	ptr->add_to_buffer(input);
	while ((message = ptr->get_request()) != "")
	{
		if (message[0] == ' ')
		{
			send_message(ptr, ERR_UNKNOWNCOMMAND(message));
			continue ;
		}
		cmd = 666;
		std::vector<std::string> message_split = split_command(message);

		for (int i = 0; i < 13; i++)
			if (lowercase(message_split[0]) == _cmds_list[i])
				cmd = i;

		if (!ptr->is_registered())
		{
			if (cmd < 3)
				(this->*(_commands[cmd]))(message_split, ptr); 
			else if (lowercase(message_split[0]) != "cap")
				send_message(ptr, ERR_NOTREGISTERED);
			if (ptr->is_registered())
				send_message(ptr, RPL_WELCOME(ptr->get_nickname()));
		}
		else
		{
			if (cmd == 0 || cmd == 2)
				send_message(ptr, ERR_ALREADYREGISTRED);
			else if (cmd > 14)
				send_message(ptr, ERR_UNKNOWNCOMMAND(message_split[0]));
			else
				{
					(this->*(_commands[cmd]))(message_split, ptr);
					if (cmd == 3)
						return;
				}
		}
	}
}
