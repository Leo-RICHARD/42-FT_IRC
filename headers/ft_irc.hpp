/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:04:33 by astucky           #+#    #+#             */
/*   Updated: 2022/09/23 16:26:36 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_H
#define FT_IRC_H

#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <vector>

/* en test */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <algorithm>

/* A supprimer ! */
#include <stdio.h>

class Server;
class Client;
class Channel;

#include "Server.hpp"
#include "Client.hpp"
#include "numericMessages.hpp"
#include "Channel.hpp"

std::vector<std::string> split_command(std::string s);
std::vector<std::string> split_args(std::string s);
std::vector<std::string> split_by_comma(std::string const &s);
std::string const	lowercase(std::string const &);

void irc(unsigned short, std::string);

#endif
