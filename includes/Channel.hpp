/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:22:10 by ajeanne           #+#    #+#             */
/*   Updated: 2023/06/28 19:43:00 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# define CHANLIMIT 24
# include <ctime>
# include "Client.hpp"


class Client;

class	Channel	{
	
	public:
		Channel(); 
		Channel(std::string name, Client& owner);
		~Channel(void);

		std::string					getCreationTime(void) const;
		std::string					getName(void) const;
		std::string					getTopic(void) const;
		std::string 				getModeChannel(void) const;
		std::vector<std::string>	getUsrList(void) const;
		int							getOwner(void) const;

		void						setLogMsg(std::string logMsg);
		void						setTopic(std::string topic, Client &user);
		void 						setPassword(std::string password);
		void						setSecured(bool	secured);
		void						setMode(bool active, char i);


		void						addUser(Client &user);
		void						addModo(Client &user);
		void						remUser(Client &user);
		void						remModo(Client &user);
		void						sendMsg(std::string msg, Client &user) const;
		void						sendMode(std::string msg, Client &user) const;

	private:
		
		std::string					_creationTime;
		std::string					_name;
		std::string					_logMsg;
		std::string					_topic;
		std::string					_password;
		bool						_secured;
		int							_owner;
		std::map<int, Client*> 		_usrList;
		std::map<int, Client*>		_modoList;
		std::map<char, bool> 		_mode;
};

#endif