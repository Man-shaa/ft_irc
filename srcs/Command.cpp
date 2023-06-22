/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:41:05 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/22 17:05:35 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include "Server.hpp"

void	Server::initCmd()
{
	_mapFcts["USER"] = &Server::cmdUser;
	_mapFcts["JOIN"] = &Server::cmdJoin;
	_mapFcts["MODE"] = &Server::cmdMode;
	_mapFcts["PING"] = &Server::cmdPing;
}


int		Server::cmdUser(std::vector<std::string> args, Client &client)
{
	//TODO Gérer le <realname> cf. https://modern.ircdocs.horse/#user-message
	//TODO Gérer le ERR_ALREADYREGISTERED :  "<client> :You may not reregister"
	//TODO Tronquer le username si il dépasse la taille de USERLEN = 12
	if (args[0].empty())
		args[0] = "default name";
	std::string answer = "001 " + args[0] + " :Welcome to the Internet Relay Network " + args[0] + "\r\n";
	_clients[client.getId()]->setNickName(args[0]);
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	return (0);
}

int		Server::cmdJoin(std::vector<std::string> args, Client &client)
{
	//TODO Servers MAY restrict the number of channels a client may be joined to at one time cf. https://modern.ircdocs.horse/#chanlimit-parameter
	//TODO Definir le type de channel accepte cf.https://modern.ircdocs.horse/#chantypes-parameter
	bool channelExist = false;
	int i;
	
	for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
	{
		std::cout << *it << std::endl;
		for (i = 0; _channels[i]; ++i) 
		{
			if (_channels[i]->getName() == *it)
			{
				channelExist = true;
				//Autorisation ou non d'y acceder
			}
		}
		
		if (!channelExist)
		{
			addChannel(*it, client);
			std::cout << "Create new channel " << *it << std::endl;
		}
		
		//JOIN sent to client
		std::string JOIN = ":" + client.getNickname() + " JOIN " + *it + "\r\n";
		send(client.getSocket(), JOIN.c_str(), JOIN.size(), 0);

		//RPL_RPL_TOPIC sent to client
		std::string RPL_TOPIC =  "332 " + client.getNickname() + " " + *it + " :" + _channels[i]->getTopic() + "\r\n";
		send(client.getSocket(), RPL_TOPIC.c_str(), RPL_TOPIC.size(), 0);

		//RPL_NAMREPLY sent to client
		std::vector<std::string> listUsr = _channels[i]->getUsrList();
		std::string RPL_NAMREPLY = "353 " + client.getNickname() + "=" + *it + " :";
		for (std::vector<std::string>::const_iterator it = listUsr.begin(); it != listUsr.end(); ++it)
			RPL_NAMREPLY += *it + " ";
		RPL_NAMREPLY += "\r\n";
		send(client.getSocket(), RPL_NAMREPLY.c_str(), RPL_NAMREPLY.size(), 0);
		
		//RPL_ENDOFNAMES sent to client
		std::string RPL_ENDOFNAMES = "366 " + client.getNickname() + " " + *it + " :End of /NAMES list\r\n";
		send(_fd, RPL_ENDOFNAMES.c_str(), RPL_ENDOFNAMES.size(), 0);
	}

	return (0);
}

int		Server::cmdPing(std::vector<std::string> args, Client &client)
{
	std::string pong = "server.name " + args[0] + "\r\n";
	send(client.getSocket(), pong.c_str(), pong.size(), 0);
	return (0);
}

//TODO cf. https://modern.ircdocs.horse/#user-message
int		Server::cmdMode(std::vector<std::string> args, Client &client)
{
	(void)args;
	(void)client;
	// bool channelExist = false;
	
	// for (int i = 0; i < MAX_CHANNELS i++)
	// 	if (_channels[i]->getName() == arg1)
	// 		channelExist = true;
	// if (!channelExist)
    // {
    //     std::string ERR_NOSUCHCHANNEL = client.getNickname() + "::No such channel\r\n";
    //     send(client.getSocket(), ERR_NOSUCHCHANNEL.c_str(), ERR_NOSUCHCHANNEL.size(), 0);
    // }
	
	// if (arg2.empty())
	// {
	// 	std::string RPL_CHANNELMODEIS = client.getNickname() + <usermode> + "\r\n";
	// 	send(client.getSocket(), RPL_CHANNELMODEIS.c_str(), RPL_CHANNELMODEIS.size(), 0);
	// }
	// else
	// {
		// Vérifier les privileges	du client
		// 	NON : ERR_CHANOPRIVSNEEDED  "<client> <channel> :You're not channel operator"
		// 	OUI :
	//}
	return (0);
}