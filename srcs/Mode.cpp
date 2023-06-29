/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:49:17 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/29 17:32:30 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::initMode()
{
	_modeFcts['k'] = &Server::mode_K;
	_modeFcts['t'] = &Server::mode_T;
	_modeFcts['i'] = &Server::mode_I;
	_modeFcts['o'] = &Server::mode_O;
}

void Server::mode_K(Client &client, std::vector<std::string> args, std::string &validModes, int i, bool change)
{
	if (args.size() == 3)
	{
		//On doit donner le bon mot de passe pour le supprimer
		if (change == false && _channels[i]->getPassword() != args[2])
		{
			std::string ERR_INVALIDMODEPARAM = "696 " + client.getNickname() + " " + args[0] + " k " + args[2] + " :Wrong password\r\n";
			send(client.getSocket(), ERR_INVALIDMODEPARAM.c_str(), ERR_INVALIDMODEPARAM.size(), 0);
		}
		//On doit vérifier le format du passsword est valide
		else if (change == true && args[2].find_first_of(" ") != std::string::npos)
		{
			std::string ERR_INVALIDKEY = "525 " + client.getNickname() + " " + args[0] + " :Key is not well-formed\r\n";
			send(client.getSocket(), ERR_INVALIDKEY.c_str(), ERR_INVALIDKEY.size(), 0);
		}
		else
		{
			_channels[i]->setMode(change, i);
			_channels[i]->setPassword(args[2]);
			_channels[i]->setSecured(change);
			validModes += 'k';
		}
	}
}

void	Server::mode_T(Client &client, std::vector<std::string> args, std::string &validModes, int i, bool change)
{
	(void)client;
	(void)args;
	_channels[i]->setMode(change, i);
	validModes += 't';
}

void	Server::mode_I(Client &client, std::vector<std::string> args, std::string &validModes, int i, bool change)
{
	(void)client;
	(void)args;
	_channels[i]->setMode(change, i);
	validModes += 'i';
}

void	Server::mode_O(Client &client, std::vector<std::string> args, std::string &validModes, int i, bool change)
{
	(void)client;
	(void)args;
	_channels[i]->setMode(change, i);
	validModes += 'o';
}


std::string	Server::toggleChannelMode(Client &client, std::vector<std::string> args, unsigned long pos, int i, bool change)
{
	//TODO: Pf pour la gestion des différents modes
	std::string validModes;
	std::string modes = args[1].substr(pos);
	
	while (pos < args[1].size())
	{
		modeFct fPtr = _modeFcts[modes[0]];
		if (fPtr)
			(this->*fPtr)(client, args, validModes, i, change);
		pos++;
		modes = args[1].substr(pos);
	}
	if (!validModes.empty())
		(change == false) ? validModes.insert(0, "-") : validModes.insert(0, "+");
	return (validModes);
}

std::string	Server::channelMode(Client &client, std::vector<std::string> args, int i)
{
	std::string::size_type addPos = args[1].rfind('+');
	std::string::size_type delPos = args[1].rfind('-');
	std::string modes;
	
	if (addPos != std::string::npos)
		modes += toggleChannelMode(client, args, ++addPos, i, true);
	if (delPos != std::string::npos)
		modes += toggleChannelMode(client, args, ++delPos, i, false);
	
	return (modes);
}

int	Server::cmdMode(std::vector<std::string> args, Client &client)
{
	//TODO Gerer le mode server
	bool 	channelExist = false;
	int		i;
	
	if (args[0][0] == '#')
	{
		//Récupere le channel
		for (i = 0; _channels[i]; ++i)
		{
			if (_channels[i]->getName() == args[0])
			{
				channelExist = true;
				break;
			}
		}
		//Si le channel n'existe pas, on retourne un msg d'erreur
		if (!channelExist)
		{
			std::string ERR_NOSUCHCHANNEL = "403 " + client.getNickname() + ":No such channel\r\n";
			send(client.getSocket(), ERR_NOSUCHCHANNEL.c_str(), ERR_NOSUCHCHANNEL.size(), 0);
			return (0);
		}
		//Si la commande comprend un channel valide, mais aucun modestring, on retourne les modes existants et l'heure de creation du channel
		if (args.size() == 1 || args[1].empty())
		{
			std::string RPL_CHANNELMODEIS = "324 " + client.getNickname() + " " + args[0] + " " +  _channels[i]->getModeChannel() + "\r\n";
			std::cout << RPL_CHANNELMODEIS << std::endl;
			send(client.getSocket(), RPL_CHANNELMODEIS.c_str(), RPL_CHANNELMODEIS.size(), 0);

			std::string RPL_CREATIONTIME = "329 " + client.getNickname() + " " + args[0] + " " + _channels[i]->getCreationTime() + "\r\n";
			send(client.getSocket(), RPL_CREATIONTIME.c_str(), RPL_CREATIONTIME.size(), 0);
		}
		else
		{
			//Channel valide + modestring, on vérifie si le client est un opérateur du channel
			if (client.getSocket() != _channels[i]->getOwner())
			{
				std::string ERR_CHANOPRIVSNEEDED = "482 " + client.getNickname() + args[0] + " :You're not channel operator\r\n";
				send(client.getSocket(), ERR_CHANOPRIVSNEEDED.c_str(), ERR_CHANOPRIVSNEEDED.size(), 0);	
			}
			else
			{
			//Channel valide + modestring, on vérifie check les modes a set ou unset		
			//Puis on envoie les nouveaux modes a tout les utilisateurs
				_channels[i]->sendMode(channelMode(client, args, i));
			}
		}
	}
	return (0);
}