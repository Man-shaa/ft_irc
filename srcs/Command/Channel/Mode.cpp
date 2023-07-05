/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:49:17 by ccheyrou          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/07/04 20:55:52 by msharifi         ###   ########.fr       */
=======
/*   Updated: 2023/07/03 17:54:35 by msharifi         ###   ########.fr       */
>>>>>>> 572949c ([WIP] Mode User (deso j'avais pas vu que je suis sur le main UwU))
=======
/*   Updated: 2023/07/04 23:23:09 by ccheyrou         ###   ########.fr       */
>>>>>>> 404ad83 ([WIP] Mode l)
=======
/*   Updated: 2023/07/05 15:44:32 by ccheyrou         ###   ########.fr       */
>>>>>>> 6ffca4c ([ADD] mode OLI and [TODO] join inviteonly condition)
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::initMode()
{
	_modeFcts['k'] = &Server::mode_K;
	_modeFcts['t'] = &Server::mode_T;
	_modeFcts['i'] = &Server::mode_I;
	_modeFcts['o'] = &Server::mode_O;
	_modeFcts['l'] = &Server::mode_L;
}

bool Server::containsUppercase(const std::string& param)
{
	for (std::size_t i = 0; i < param.length(); ++i) {
		if (std::isupper(param[i]))
			return (true);
	}
	return (false);
}

bool Server::isDigits(const std::string& str)
{
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if (!std::isdigit(*it))
			return (false);
	}
	return (true);
}

void Server::mode_K(Client &client, std::string param, std::string &validModes, int i, bool change)
{
	std::cout << "param: " << param << std::endl;
	if (!param.empty())
	{
		//On doit donner le bon mot de passe pour le supprimer
		if (change == false && _channels[i]->getPassword() != param)
		{
			std::string ERR_INVALIDMODEPARAM = "696 " + client.getNickname() + " " + _channels[i]->getName() + " k " + param + " :Wrong password\r\n";
			send(client.getSocket(), ERR_INVALIDMODEPARAM.c_str(), ERR_INVALIDMODEPARAM.size(), 0);
		}
		//On doit vérifier le format du passsword est valide
		else if (change == true && (param.size() < 6 || !containsUppercase(param)))
		{
			std::string ERR_INVALIDKEY = "525 " + client.getNickname() + " " + _channels[i]->getName() + " :Your password must be at least 6 characters long and must contain at least one uppercase.\r\n";
			send(client.getSocket(), ERR_INVALIDKEY.c_str(), ERR_INVALIDKEY.size(), 0);
		}
		else
		{
			_channels[i]->setMode(change, 'k');
			_channels[i]->setPassword(param, change);
			_channels[i]->setSecured(change);
			validModes += 'k';
			change == false ? std::cout << "Password is unset: " << param << "\n" << std::endl : std::cout << "Password is set: " << param << "\n" << std::endl;
		}
		
	}
	else
	{
		std::string ERR_NEEDMOREPARAMS = "461 " + client.getNickname() + " MODE :Password is missing\r\n";
		send(client.getSocket(), ERR_NEEDMOREPARAMS.c_str(), ERR_NEEDMOREPARAMS.size(), 0);
	}
}

void	Server::mode_T(Client &client, std::string param, std::string &validModes, int i, bool change)
{
	(void)client;
	(void)param;
	_channels[i]->setMode(change, 't');
	validModes += 't';
}

void	Server::mode_I(Client &client, std::string param, std::string &validModes, int i, bool change)
{
	(void)client;
	(void)param;
	_channels[i]->setMode(change, 'i');
	validModes += 'i';
}

void	Server::mode_O(Client &client, std::string param, std::string &validModes, int i, bool change)
{
	if (!param.empty())
	{
		if (change == true)
			_channels[i]->addModo(client);
<<<<<<< HEAD
			std::vector<std::string> listOP = _channels[i]->getOpeList();
			std::string op;
			for (std::vector<std::string>::const_iterator it = listOP.begin(); it != listOP.end(); ++it)
			{
				op += *it + " ";
			}
			std::cout << op << std::endl;
		}
		if (change == false)
		{
			_channels[i]->remOperator(client);
			std::vector<std::string> listOP = _channels[i]->getOpeList();
			std::string op;
			for (std::vector<std::string>::const_iterator it = listOP.begin(); it != listOP.end(); ++it)
			{
				op += *it + " ";
			}
			std::cout << op << std::endl;
=======
		if (change == false)
			_channels[i]->remModo(client);
		
		//RPL_NAMREPLY sent to client
		std::vector<std::string> listUsr = _channels[i]->getUsrList();
		std::string RPL_NAMREPLY = "353 " + client.getNickname() + " = " + _channels[i]->getName() + " :";
		for (std::vector<std::string>::const_iterator it = listUsr.begin(); it != listUsr.end(); ++it)
		{
			if (it == listUsr.begin())
				RPL_NAMREPLY += *it;
			else
				RPL_NAMREPLY += " " + *it;
>>>>>>> 6ffca4c ([ADD] mode OLI and [TODO] join inviteonly condition)
		}
		RPL_NAMREPLY += "\r\n";
		std::cout << RPL_NAMREPLY << std::endl;
		send(client.getSocket(), RPL_NAMREPLY.c_str(), RPL_NAMREPLY.size(), 0);
		
		//RPL_ENDOFNAMES sent to client
		std::string RPL_ENDOFNAMES = "366 " + client.getNickname() + " " + _channels[i]->getName() + " :End of NAMES list\r\n";
		send(client.getSocket(), RPL_ENDOFNAMES.c_str(), RPL_ENDOFNAMES.size(), 0);
		
		_channels[i]->setMode(change, 'o');
		validModes += 'o';
	}
	else
	{
		std::string ERR_NEEDMOREPARAMS = "461 " + client.getNickname() + " MODE :User is missing\r\n";
		send(client.getSocket(), ERR_NEEDMOREPARAMS.c_str(), ERR_NEEDMOREPARAMS.size(), 0);
	}
}

void	Server::mode_L(Client &client, std::string param, std::string &validModes, int i, bool change)
{
	(void)client;
	if ((change == true && !param.empty()) || change == false)
	{
		if (change == true && (atoi(param.c_str()) < 0 || atoi(param.c_str()) > 2147483647 || !isDigits(param)))
		{
			std::string ERR_INVALIDMODEPARAM = "696 " + client.getNickname() + " " + _channels[i]->getName() + " l " + param + " :Wrong number limit\r\n";
			send(client.getSocket(), ERR_INVALIDMODEPARAM.c_str(), ERR_INVALIDMODEPARAM.size(), 0);
		}
		else
		{
			_channels[i]->setMode(change, 'l');
			_channels[i]->setMaxUsr(atoi(param.c_str()), change);
			validModes += 'l';
			change == false ? std::cout << "User is unset\n" << std::endl : std::cout << "User limit is set: " << param << "\n" << std::endl;
		}
	}
	else	
	{
		std::string ERR_NEEDMOREPARAMS = "461 " + client.getNickname() + " MODE :User limit number is missing\r\n";
		send(client.getSocket(), ERR_NEEDMOREPARAMS.c_str(), ERR_NEEDMOREPARAMS.size(), 0);
	}
}


std::string	Server::toggleChannelMode(Client &client, char mode, std::string param, int i, bool change)
{
	std::string validModes;

	modeFct fPtr = _modeFcts[mode];
	if (fPtr)
		(this->*fPtr)(client, param, validModes, i, change);
	return (validModes);
}

std::string	Server::channelMode(Client &client, std::map<std::string, std::string> args, int i)
{
	std::string addModes;
	std::string delModes;
	for (std::map<std::string, std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
	{
		if ((it->first)[0] == '+')
			addModes += toggleChannelMode(client, (it->first)[1], it->second, i, true);
		if ((it->first)[0] == '-')
			delModes += toggleChannelMode(client, (it->first)[1], it->second, i, false);
	}
	if (!addModes.empty())
		addModes.insert(0, "+");
	if (!delModes.empty())
		delModes.insert(0, "-");

	std::cout << (addModes + delModes) << std::endl;
	return (addModes + delModes);
}

bool Server::isSign(char c)
{
    if (c == '-' || c == '+')
        return (true);
    return (false);
}

bool    Server::isValidChanMode(std::string mode)
{
	if (mode == "+i" || mode == "+t" || mode == "+k" || mode == "+o" || mode == "+l" || mode == "-i" || mode == "-t" || mode == "-k" || mode == "-o" || mode == "-l")
		return (true);
	return false;
}

bool    Server::isParNeededMode(std::string mode)
{
	if (mode == "+k" || mode == "+o" || mode == "+l" || mode == "-o" || mode == "-k")
		return true;
	return (false);
} 

std::string	Server::parseMode(std::string mode)
{
	std::string	toExec;
	const char	*m = mode.c_str();
    char    latestSign = '\0';
    while (*m)    
	{
        if (isSign(*m))
            latestSign = *m; 
        else if (!isSign(*m) && *(m + 1) != '\0')
            toExec.append(1, latestSign).append(1, *m).append(1,' ');
        else
            toExec.append(1, latestSign).append(1, *m);
        m++;
    }
	std::cout << toExec << std::endl;
	return(toExec);
}

std::string	Server::checkArg(Client &client, std::vector<std::string> args, int i)
{
	std::map<std::string, std::string> modes;
	std::string params;
	size_t j = 2;

	std::istringstream	issm(parseMode(args[1]));
	std::string			tokenm;
	int					mNb = 0, pNb = 0;
	while (issm >> tokenm)    
	{
		if (!isValidChanMode(tokenm))
		{
			std::string ERR_UMODEUNKNOWNFLAG = "501 " + client.getNickname() + " :Unknown MODE flag\r\n";
			send(client.getSocket(), ERR_UMODEUNKNOWNFLAG.c_str(), ERR_UMODEUNKNOWNFLAG.size(), 0);
			return ("");
		}
		else
		{
			if (isParNeededMode(tokenm))
			{
				if (args.size() > j)
				{
					modes[tokenm] = args[j];
					j++;
					pNb++;
				}
				else
					modes[tokenm] = "";
			}
			else
				modes[tokenm] = "";
			mNb++;
		}
	}
		
	return (channelMode(client, modes, i));
}

int	Server::cmdMode(std::vector<std::string> args, Client &client)
{
	// MODE CHANNEL
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
			std::string ERR_NOSUCHCHANNEL = "403 " + client.getNickname() + " :No such channel\r\n";
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
			if (!_channels[i]->clientIsOp(client.getSocket()))
			{
				std::string ERR_CHANOPRIVSNEEDED = "482 " + client.getNickname() + args[0] + " :You're not channel operator\r\n";
				send(client.getSocket(), ERR_CHANOPRIVSNEEDED.c_str(), ERR_CHANOPRIVSNEEDED.size(), 0);	
			}
			else
			{
			//Channel valide + modestring, on vérifie check les modes a set ou unset		
			//Puis on envoie les nouveaux modes a tout les utilisateurs
				//_channels[i]->sendMode(channelMode(client, args, i));
				_channels[i]->sendMode(checkArg(client, args, i));
			}
		}
	}
	return (0);
}