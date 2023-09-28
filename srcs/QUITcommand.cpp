/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUITcommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:22:07 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 18:36:20 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

void	Server::msg_quit(std::vector<std::string> message_split, Client *c, std::vector<Channel *>::iterator it_channel)
{
	std::string reason;
	if ((message_split.size() >= 2) && (!message_split[1].empty()))
		reason = message_split[1];
	else
		reason = ":" + c->get_nickname();

	std::string msg = ":" + c->get_nickname() + "!" + c->get_username_only() + "@" + c->get_ip() + " QUIT " + reason + "\r\n";
	Channel *chan = get_chan((*it_channel)->get_name());
	chan->msg_everyone(msg, c->get_nickname());
	c->leave_channel(chan);
}

void	Server::quit(std::vector<std::string> message_split, Client *c)
{
	std::vector<Channel *> chans_to_leave = c->get_channels();
	if (!chans_to_leave.empty())
	{
		std::vector<Channel *>::iterator it;
		for (it = chans_to_leave.begin(); it < chans_to_leave.end(); it++)
		{
			
			Channel * chan;
			chan = get_chan((*it)->get_name());

			if (chan)
			{
				if (chan->get_all_members().size() < 2)
					remove_channel((*it));
				else
					msg_quit(message_split, c, it);
			}
		}
	}
	remove_client(std::find(_clientList.begin(), _clientList.end(), c));
}
