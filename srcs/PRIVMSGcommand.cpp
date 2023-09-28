/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSGcommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:22:05 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 19:54:55 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>



int		no_text(const std::string &s)
{
	int i = s.find(':');
	while (s[++i])
		if (s[i] != ' ' && s[i] != '\n')
			return 0;
	return 1;
}

void	Server::send_message_to_chan(std::string arg_chan, std::string text, Client *c)
{
	Channel *chan;
	std::string sender;

	sender = c->get_nickname();
	chan = get_chan(arg_chan);
	if (chan == NULL)
	{
		send_message(c, ERR_NOSUCHCHANNEL(arg_chan));
		return ;
	}
	if (!chan->get_member(sender))
	{
		send_message(c, ERR_CANNOTSENDTOCHAN(chan->get_name()));
		return ;
	}
	std::string msg = ":" + sender + " PRIVMSG " + arg_chan + ' ' + text + "\r\n";
	chan->msg_everyone(msg, sender);
}


void	Server::privmsg(std::vector<std::string> message_split, Client *c)
{
	std::vector<std::string> args_split = split_args(message_split[1]);
	if (message_split[1].find(':') == std::string::npos || no_text(message_split[1]))
		send_message(c, ERR_NOTEXTTOSEND);
	else if (args_split.size() < 2)
		send_message(c, ERR_NORECIPIENT);
	else if (args_split.size() > 2 || args_split[1][0] != ':')
		return;
	else
	{
		std::string text = args_split[args_split.size() - 1];
		args_split = split_by_comma(args_split[0]);
		int len = args_split.size();
		for (int i = 0; i < len; i++)
		{
			if (args_split[i][0] == '#')
				send_message_to_chan(args_split[i], text, c);
			else
			{
				Client *recipient = NULL;
				
				recipient = get_client(args_split[i]);
				if (recipient == NULL)
				{
					send_message(c, ERR_NOSUCHNICK(args_split[i]));
					return;
				}
				std::string msg = ":" + c->get_nickname() + " PRIVMSG " + recipient->get_nickname() + ' ' + text + "\r\n";
				send_message(recipient, msg);
			}
		}
	}
}
