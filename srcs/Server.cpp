/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:17:19 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/17 20:23:10 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
const char* welcomeMessage = "Welcome to the IRC server!\r\n";

Server::Server()
{}

Server::~Server()
{}

/* Creation socket d'écoute (listen socket) est un type de socket utilisé \
par un serveur pour écouter les connexions entrantes des clients. */
int	Server::createSocket()
{
    int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == -1) 
    {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        return 1;
    }
	_Sockets.push_back(listenSocket); //IPv4 + TCP
    std::cout << "Creation socket serveur " << _Sockets[0] << std::endl;
	return 0;
}

/* Définir les informations de l'adresse du serveur \
pour spécifier sur quelle adresse IP et quel port le serveur \
va écouter les connexions entrantes des clients.*/
void	Server::serverInfo()
{
    std::memset(&_serverAddress, 0, sizeof(_serverAddress));
    _serverAddress.sin_family = AF_INET; //type d'adresse utilise par le socket IPv4
    _serverAddress.sin_addr.s_addr = INADDR_ANY; //socket ecoute toutes les connexions entrantes sur IP dispo du serveur
    _serverAddress.sin_port = htons(_port);
}

/*Lié socket d'ecoute à une adresse IP et\
à un numéro de port spécifiques à l'aide de la fonction bind()*/
int Server::link_SocketServer()
{
    if (bind(_Sockets[0], reinterpret_cast<sockaddr*>(&_serverAddress), sizeof(_serverAddress)) == -1) {
        std::cerr << "Erreur lors du bind du socket" << std::endl;
        close(_Sockets[0]);
        return 1;
    }
    return 0;
}

//Mettre le socket en mode écoute de connection
int	Server::listenSocket()
{
    if (listen(_Sockets[0], SOMAXCONN) == -1) {
        std::cerr << "Erreur lors de la mise en écoute du socket" << std::endl;
        close(_Sockets[0]);
        return 1;
    }
	std::cout << "Le serveur est en écoute sur le port " << _port << std::endl;
    return 0;
}

// Accepter les connexions entrantes
int Server::acceptConnexions()
{
    socklen_t clientAddressLength = sizeof(_clientAddress);
    int _clientSocket = accept(_Sockets[0], reinterpret_cast<sockaddr*>(&_clientAddress), &clientAddressLength);
    if (_clientSocket != -1) 
    {
        _Sockets.push_back(_clientSocket);
        _fds.fd = _clientSocket;
        _fds.events = POLLIN;

        std::cout << "Nouvelle connexion acceptée. Socket : " << _clientSocket << std::endl;

        int flags = fcntl(_clientSocket, F_GETFL, 0);
        fcntl(_clientSocket, F_SETFL, flags | O_NONBLOCK);
        
        send(_clientSocket, welcomeMessage, std::strlen(welcomeMessage), 0);
        return (1);
    }
    return (0);
}

// Supprimer les sockets clients déconnectés de la liste
void Server::socketToRemove()
{
    for (std::vector<int>::iterator it = _socketsToRemove.begin(); it != _socketsToRemove.end(); ++it) 
    {
        _client = *it;
        _Sockets.erase(std::remove(_Sockets.begin(), _Sockets.end(), _client), _Sockets.end());
        close(_client);
    }
}

int Server::serverManagement()
{
    if (createSocket())
		return (1);
	serverInfo();
	if (link_SocketServer())
		return (1);
	if (listenSocket())
		return (1);
    //Socket d'ecoute en mode non bloquant
    int flags = fcntl(_Sockets[0], F_GETFL, 0);
    fcntl(_Sockets[0], F_SETFL, flags | O_NONBLOCK);
    
    return (0);
}

void Server::manageClientMsg()
{
    char    buffer[BUFFER_SIZE];
    
    ssize_t bytesRead = recv(_client, buffer, sizeof(buffer), 0);
    // if (bytesRead == -1) 
    // {
    //     perror("Erreur lors de la lecture des données du client");
    //     std::cerr << strerror(errno) << std::endl;
    // }
    if (bytesRead > 0)
    {
        std::string command(buffer, bytesRead);
        buffer[bytesRead] = '\0';
        std::cout << "Message reçu du client " << _client << ": " << buffer << std::endl;

        std::istringstream iss(command);
        std::string cmd, arg1, arg2;
        iss >> cmd >> arg1 >> arg2;
        
        if (cmd == "NICK")
            std::cout << "NICK" << std::endl;
        if (cmd == "CAP")
            std::cout << "CAP LS" << std::endl;
        if (cmd == "/die")
            std::cout << "Commande 'die' reçue. Fermeture du serveur." << std::endl;
        else if (cmd == "/nick") 
            std::cout << "Commande 'nick' reçue. Nouveau pseudo : " << arg1 << std::endl;
        else if (cmd == "/join") 
            std::cout << "Commande 'join' reçue. Rejoindre le canal : " << arg1 << std::endl;
        else if (cmd == "/register") 
            std::cout << "Commande 'register' reçue. Informations d'enregistrement : " << arg1 << " " << arg2 << std::endl;
        std::string response = "Bien reçu !\r\n";
        send(_client, response.c_str(), response.size(), 0);
    } 
    else if (bytesRead == 0) 
    {
        _socketsToRemove.push_back(_client);
        std::cout << "Déconnexion du client " << _client << std::endl;
    } 
    else if (errno != EWOULDBLOCK && errno != EAGAIN) 
    {
        _socketsToRemove.push_back(_client);
        std::cerr << "Erreur lors de la lecture du client " << _client << std::endl;
    }
    memset(buffer, 0, sizeof(buffer));
}

int Server::dataManagement()
{
    _ret = 0;
    while(true)
    {
        for (std::vector<int>::iterator it = _Sockets.begin(); it != _Sockets.end(); ++it) 
        {
            _client = *it;
            if ((_ret = poll(&_fds, *it, 100)) <= 0)  
            {
                if (_ret == 0 || errno == EINTR)
                {
                    continue;
                }
                perror("Poll failed");
                return(1);
            }
            if (_client == 3)
            {
                if (acceptConnexions())
                    it = _Sockets.begin();
            }
            else
            {
                _client = *it;
                manageClientMsg();
            }
        }
        //socketToRemove();
    }

    //socketToRemove();
}
int Server::start(int port) 
{
    _port = port;
    serverManagement();
    dataManagement();
    close(_Sockets[0]);
    return 0;
}