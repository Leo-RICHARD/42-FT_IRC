/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPICcommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:22:10 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 19:57:36 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

bool	Server::set_topic(Channel *chan, Client *c, std::string new_topic)
{
	if (chan->is_operator(c))
		chan->set_topic(new_topic.erase(0,1));
	else
	{
		send_message(c, ERR_CHANOPRIVSNEEDED(chan->get_name()));
		return (0);
	}
	return (1);
}

void	Server::topic(std::vector<std::string> message_split, Client *c)
{    
	Channel *chan;
	std::vector<std::string> args_split = split_args(message_split[1]);

	if (args_split.size() < 1 || args_split[0][0] != '#' || (args_split.size() >= 2 && args_split[1][0] != ':'))
	{
		send_message(c, ERR_NEEDMOREPARAMS(message_split[0]));
		return ;
	}

	chan = get_chan(args_split[0]);
	if (chan)
	{
		if (chan->get_member(c->get_nickname()) == NULL)
		{
			send_message(c, ERR_NOTONCHANNEL(chan->get_name()));
			return;
		}
		if (args_split.size() == 2)
		{
			if (!set_topic(chan, c, args_split[1]))
				return;
		}
		if (chan->get_topic() != "")
			send_message(c, RPL_TOPIC(c->get_nickname(), chan->get_name(), chan->get_topic()));
		else
			send_message(c, RPL_NOTOPIC(c->get_nickname(), chan->get_name()));
	}
}
