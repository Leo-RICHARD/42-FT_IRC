/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:23:07 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 16:01:27 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ft_irc.hpp>

class	Channel
{
	private:
		std::string									_name;
		std::vector< std::pair<Client *, bool> >	_members;
		int											_capacity;
		bool										_invite_only;
		std::string									_topic;

	public :

		Channel(std::string const &);
		~Channel();

		// getters
		std::string								get_name() const;
		bool									checkname(std::string const &) const;
		std::string								get_name(std::string const &) const;
		Client*									get_member(std::string const &);
		std::vector<std::pair<Client *, bool> >	get_all_members() const;
		int										get_op_nbr();
		std::string								get_topic() const;
		bool									has_room() const;
		bool									empty() const;
		bool									is_invite_only() const;
		bool									is_operator(Client *) const;

		// modifiers
		void	set_topic(std::string const &);
		void	add_member(Client *, bool);
		void	remove_member(Client *);
		void	set_invite_only(bool);
		void	set_op(Client *c, bool val);

		// other

		void	msg_everyone(std::string message, std::string sender_nick);
};
