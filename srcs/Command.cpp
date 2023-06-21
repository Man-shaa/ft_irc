/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:41:05 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/21 20:02:28 by ccheyrou         ###   ########.fr       */
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


int		Server::cmdUser(std::string & arg1, std::string & arg2, Client &client)
{
	(void)arg2;
	//TODO Gérer le <realname> cf. https://modern.ircdocs.horse/#user-message
	//TODO Gérer le ERR_ALREADYREGISTERED :  "<client> :You may not reregister"
	//TODO Tronquer le username si il dépasse la taille de USERLEN = 12
	if (arg1.empty())
		arg1 = "default name";
	std::string answer = "001 " + arg1 + " :Welcome to the Internet Relay Network " + arg1 + "\r\n";
	_clients[client.getId()]->setNickName(arg1);
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	return (0);
}

int		Server::cmdJoin(std::string & arg1, std::string & arg2, Client &client)
{
	(void)arg2;
	bool channelExist = false;
	int i;
	for (i = 0; _channels[i]; ++i) //faire une fonction qui recupere le nombre de channel existant
	{
		if (_channels[i]->getName() == arg1)
		{
			channelExist = true;
			//Autorisation ou non d'y acceder
		}
	}
	
	if (!channelExist)
	{
		addChannel(arg1, client);
		std::cout << "Create new channel" << std::endl;
	}
	
	//1er message
	std::string join = ":" + client.getNickname() + " JOIN " + arg1 + "\r\n";
	send(client.getSocket(), join.c_str(), join.size(), 0);

	std::string topic =  "332 " + client.getNickname() + " " + arg1 + " :" + _channels[i]->getTopic() + "\r\n";
	std::cout << topic << std::endl;
	send(client.getSocket(), topic.c_str(), topic.size(), 0);

	std::vector<std::string> listUsr = _channels[i]->getUsrList();
	for (std::vector<std::string>::const_iterator it = listUsr.begin(); it != listUsr.end(); ++it)
	{
		std::string reply = "353 " + client.getNickname() + "=" + arg1 + " :" + *it;
		std::cout << reply << std::endl;
		send(client.getSocket(), reply.c_str(), reply.size(), 0);
	}
	std::string answer = "366 " + client.getNickname() + " " + arg1 + " :End of /NAMES list\r\n";
	send(_fd, answer.c_str(), answer.size(), 0);

	//2eme message

	//3eme message
	//boucle for sur chacun des clients 
	//qui cree un std::string avec : nom du client + symbole du type de channel + nom channel + :nickname
	//std::string answer = client.getNickname() + arg1 + " :End of /NAMES list\r\n";
	//send(_fd, answer.c_str(), answer.size(), 0);

	return (0);
}

int		Server::cmdPing(std::string & arg1, std::string & arg2, Client &client)
{
	(void)arg2;
	std::string pong = "server.name " + arg1 + "\r\n";
	send(client.getSocket(), pong.c_str(), pong.size(), 0);
	return (0);
}

//TODO cf. https://modern.ircdocs.horse/#user-message
int		Server::cmdMode(std::string & arg1, std::string & arg2, Client &client)
{
	(void)arg1;
	(void)arg2;
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