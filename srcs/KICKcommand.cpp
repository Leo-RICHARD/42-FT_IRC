/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICKcommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:20:46 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 19:53:59 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

void	Server::msg_kick(Channel *chan, std::string name, std::string reason, Client *c)
{
	Client *outcast;

	if ((outcast = chan->get_member(name)))
	{
		std::string msg = ":" + c->get_nickname() + "!" + c->get_username_only() + "@" + c->get_ip() + " KICK " + chan->get_name() + ' ' + name + ' ' + reason + "\r\n";
		chan->msg_everyone(msg, "\0");
		outcast->leave_channel(chan);
	}
}

void	Server::parse_kick(std::vector<std::string> args_split, std::vector<std::string> *chan_split, std::vector<std::string> *outcast_split, std::string *reason, Client *c)
{
	if (args_split[0].find('#') == std::string::npos)
	{
		send_message(c, ERR_NOSUCHCHANNEL(args_split[0]));
		return;
	}
	if (args_split[0].find(",#") != std::string::npos)
		*chan_split = split_by_comma(args_split[0]);
	else
		chan_split->push_back(args_split[0]);

	if (args_split[1].find(",") != std::string::npos)
		*outcast_split = split_by_comma(args_split[1]);
	else
		outcast_split->push_back(args_split[1]);

	if (args_split.size() > 2)
		*reason = args_split[2];
	else
		reason->clear();
}

void	Server::kick(std::vector<std::string> message_split, Client *c)
{
	std::vector<std::string> args_split = split_args(message_split[1]);
	std::vector<std::string> chan_split;
	std::vector<std::string> outcast_split;
	std::string reason;
	Channel *chan = NULL;

	if (message_split.size() < 2 || message_split.empty() \
			|| args_split.empty() || args_split.size() < 2 || (args_split.size() == 3 && args_split[2][0] != ':'))
		send_message(c, ERR_NEEDMOREPARAMS(message_split[0]));
	else
	{
		parse_kick(args_split, &chan_split, &outcast_split, &reason, c);
		for (std::vector<std::string>::iterator it = chan_split.begin(); it < chan_split.end(); it++)
		{
			chan = get_chan(*it);

			if (chan == NULL)
				send_message(c, ERR_NOSUCHCHANNEL(*it));
			else if (chan->get_member(c->get_nickname()) == NULL)
				send_message(c, ERR_NOTONCHANNEL(*it));
			else if (!chan->is_operator(c))
				send_message(c, ERR_CHANOPRIVSNEEDED(*it));
			else
				for (std::vector<std::string>::iterator it = outcast_split.begin(); it < outcast_split.end(); it++)
					msg_kick(chan, (*it), reason, c);
		}
	}
}
