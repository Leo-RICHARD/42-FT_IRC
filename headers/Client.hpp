/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:16:33 by astucky           #+#    #+#             */
/*   Updated: 2022/10/15 17:35:10 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ft_irc.hpp>

struct user
{
    std::string username;
    std::string hostname;
    std::string servername;
    std::string realname;
};

class 	Client
{
    //attributes
	private :

    	int             			_sd;
    	Server*          			_serv;
    	bool            			_password;
    	std::string     			_nickname;
    	user            			_user;
    	std::string     			_buffer;
    	int             			_channels_joined;
		std::vector<Channel *>	_invited;
		struct sockaddr_in			_address;
		std::vector<Channel *>		_channels;

    public :

		//construction-destruction
		Client(int sd, Server *serv, sockaddr_in address);
		~Client(void);

		//getters
		user					get_username(void) const;
		std::string				get_username_only(void) const;
		std::string				get_nickname(void) const;
		int						get_sd(void) const;
		bool					get_pass(void) const;
		std::string				get_ip() const;
		std::vector<Channel *>	get_channels() const;
		bool					is_registered(void) const;
		bool					can_still_join() const;

		//setters
		void	set_username(std::string const &, std::string const &, std::string const &, std::string const &);
		void	set_nickname(std::string const &);
		void	set_sd(int const &);
		void	set_pass(bool);
		void	join_channel(Channel *);
		void	leave_channel(Channel *);
		void	add_to_buffer(const std::string &input);
		const	std::string get_request(void);
		void	invite(Channel *);
		bool	is_invited(Channel *);
		void	remove_invite(Channel *);
};