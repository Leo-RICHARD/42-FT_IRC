/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PARTcommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:21:55 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 19:35:32 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<ft_irc.hpp>

std::vector<std::string>	Server::part_parse(std::vector<std::string> message_split, Client *c)
{
	if (message_split[1].find('#') == message_split[1].npos)
		send_message(c, ERR_NOSUCHCHANNEL(message_split[1]));
	std::vector<std::string> args_split = split_args(message_split[1]);
	if (args_split.size() >= 2 && args_split[1][0] != ':')
	{
		args_split.clear();
		return (args_split);
	}
	if (args_split[0].find(",#"))
		args_split = split_by_comma(args_split[0]);
	return (args_split);
}

void	Server::msg_part(std::vector<std::string> message_split, Client *c, Channel *chan)
{
	size_t i;
	std::string reason;

	i = message_split[1].find(" :");
	if (i != message_split[1].npos)
		reason = message_split[1].substr(i);

	std::string msg = ":" + c->get_nickname() + "!" + c->get_username_only() + "@" + c->get_ip() + " PART " + chan->get_name() + reason + "\r\n";
	chan->msg_everyone(msg, "\0");

}

void	Server::part(std::vector<std::string> message_split, Client *c)
{
	int			i, len;
	Channel		*chan;

	if (message_split[1].empty())
	{
		send_message(c, ERR_NEEDMOREPARAMS(message_split[0]));
		return ;
	}
	i = -1;
	std::vector<std::string> args_split = part_parse(message_split, c);
	if (args_split.size() == 0)
		return;
	len = args_split.size();
	while (++i < len && args_split[i][0] == '#')
	{
		chan = get_chan(args_split[i]);
		if (chan)
		{
			if (chan->get_member(c->get_nickname()) == NULL)
				send_message(c, ERR_NOTONCHANNEL(args_split[i]));
			else
			{
				c->leave_channel(chan);
				if (!chan->get_all_members().size())
					remove_channel(chan);
				else
					msg_part(message_split, c, chan);
			}
		}
		else
			send_message(c, ERR_NOSUCHCHANNEL(args_split[i]));
	}
}
