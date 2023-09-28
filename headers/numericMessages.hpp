/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericMessages.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:23:41 by astucky           #+#    #+#             */
/*   Updated: 2022/10/28 18:15:23 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define SERVER static_cast<std::string>("ft_irc")
#define SERVERHEADER static_cast<std::string>(":" + SERVER)

#define RPL_WELCOME(nick) (SERVERHEADER + " 001 " + nick + " :Welcome to our server !\r\n")
#define RPL_CHANNELMODEIS(chan, mode) (SERVERHEADER + " 324 " + chan + " " + mode + "\r\n")
#define RPL_NOTOPIC(nick, channel) (SERVERHEADER + " 331 " + nick + " " + channel + " :No topic is set\r\n")
#define RPL_TOPIC(nick, channel, topic) (SERVERHEADER + " 332 " + nick + " " + channel + " :" + topic + "\r\n")
#define RPL_INVITING(nick, invited, channel) (SERVERHEADER + " 341 " + nick + " " + invited + " " + channel + "\r\n")
#define RPL_NAMREPLY(nick, channel, name_list) (SERVERHEADER + " 353 " + nick + " = " + channel + " :" + name_list + "\r\n")
#define RPL_YOUREOPER(nick) (SERVERHEADER + " 381 " + nick + " :You are now an IRC operator\r\n")

#define ERR_NOSUCHNICK(nick) (SERVERHEADER + " 401 " + nick + " :No such nick\r\n")
#define ERR_NOSUCHCHANNEL(channel) (SERVERHEADER + " 403 " + channel + " :No such channel\r\n")
#define ERR_CANNOTSENDTOCHAN(channel) (SERVERHEADER + " 404 " + channel + " :You cannot send a message to this channel\r\n")
#define ERR_TOOMANYCHANNELS(channel) (SERVERHEADER + " 405 " + channel + " :You have joined too many channels\r\n")
#define ERR_NORECIPIENT (SERVERHEADER + " 411 " + " :Target not found\r\n")
#define ERR_NOTEXTTOSEND (SERVERHEADER + " 412 " + " :No text to send\r\n")
#define ERR_UNKNOWNCOMMAND(command) (SERVERHEADER + " 421 " + command + " :Unknown command\r\n")
#define ERR_NONICKNAMEGIVEN (SERVERHEADER + " 431 " + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(nick) (SERVERHEADER + " 432 " + nick + " :Invalid nickname\r\n")
#define ERR_NICKNAMEINUSE(nick) (SERVERHEADER + " 433 " + nick + " :You already use that nickname\r\n")
#define ERR_NICKCOLLISION(nick) (SERVERHEADER + " 436 " + nick + " :Nickname collision\r\n")
#define ERR_NOTONCHANNEL(channel) (SERVERHEADER + " 442 " + channel + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL(nick, channel) (SERVERHEADER + " 443 " + nick + " " + channel + " :is already on channel\r\n")
#define ERR_NOTREGISTERED (SERVERHEADER + " 451 " + " :User not registered\r\n")
#define ERR_NEEDMOREPARAMS(command) (SERVERHEADER + " 461 " + command + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED (SERVERHEADER + " 462 " + " :Client already registered\r\n")
#define ERR_PASSWDMISMATCH (SERVERHEADER + " 464 "+ " :Incorrect password\r\n")
#define ERR_CHANNELISFULL(channel) (SERVERHEADER + " 471 " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_UNKNOWNMODE(mode) (SERVERHEADER + " 472 " + mode + " :Unknown mode\r\n")
#define ERR_INVITEONLYCHAN(channel) (SERVERHEADER + " 473 " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_CHANOPRIVSNEEDED(channel) (SERVERHEADER + " 482 " + channel + " :You're not channel operator\r\n")
#define ERR_NOOPERHOST (SERVERHEADER + " 491 " + " :You cannot become operator\r\n")
