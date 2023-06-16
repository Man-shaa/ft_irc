/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:17:19 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/16 16:07:05 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
const char* welcomeMessage = "Welcome to the IRC server!\r\n";

Server::Server()
{};

Server::~Server()
{};

/* Creation socket d'écoute (listen socket) est un type de socket utilisé \
par un serveur pour écouter les connexions entrantes des clients. */
int	Server::createSocket()
{
	_listenSocket = socket(AF_INET, SOCK_STREAM, 0); //IPv4 + TCP
    if (_listenSocket == -1) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        return 1;
    }
	return 0;
}

/* Définir les informations de l'adresse du serveur \
pour spécifier sur quelle adresse IP et quel port le serveur \
va écouter les connexions entrantes des clients.*/
void	Server::serverInfo(int port)
{
    std::memset(&_serverAddress, 0, sizeof(_serverAddress));
    _serverAddress.sin_family = AF_INET; //type d'adresse utilise par le socket IPv4
    _serverAddress.sin_addr.s_addr = INADDR_ANY; //socket ecoute toutes les connexions entrantes sur IP dispo du serveur
    _serverAddress.sin_port = htons(port);
}

/*Lié socket d'ecoute à une adresse IP et\
à un numéro de port spécifiques à l'aide de la fonction bind()*/
int Server::link_SocketServer()
{
    if (bind(_listenSocket, reinterpret_cast<sockaddr*>(&_serverAddress), sizeof(_serverAddress)) == -1) {
        std::cerr << "Erreur lors du bind du socket" << std::endl;
        close(_listenSocket);
        return 1;
    }
    return 0;
}

//Mettre le socket en mode écoute de connection
int	Server::listenSocket()
{
    if (listen(_listenSocket, SOMAXCONN) == -1) {
        std::cerr << "Erreur lors de la mise en écoute du socket" << std::endl;
        close(_listenSocket);
        return 1;
    }
	std::cout << "Le serveur est en écoute sur le port 6667" << std::endl;
    return 0;
}

// Accepter les connexions entrantes
void Server::acceptConnexions()
{
    socklen_t clientAddressLength = sizeof(_clientAddress);
    int _clientSocket = accept(_listenSocket, reinterpret_cast<sockaddr*>(&_clientAddress), &clientAddressLength);

    if (_clientSocket != -1) 
    {
        _clientSockets.push_back(_clientSocket);
        std::cout << "Nouvelle connexion acceptée. Socket : " << _clientSocket << std::endl;

        int flags = fcntl(_clientSocket, F_GETFL, 0);
        fcntl(_clientSocket, F_SETFL, flags | O_NONBLOCK);
        
        send(_clientSocket, welcomeMessage, std::strlen(welcomeMessage), 0);
    }
}

// Supprimer les sockets clients déconnectés de la liste
void Server::socketToRemove()
{
    for (std::vector<int>::iterator it = _socketsToRemove.begin(); it != _socketsToRemove.end(); ++it) 
    {
        int client = *it;
        _clientSockets.erase(std::remove(_clientSockets.begin(), _clientSockets.end(), client), _clientSockets.end());
        close(client);
    }
}

void Server::manageClientMessage()
{
    char buffer[BUFFER_SIZE];
    for (std::vector<int>::iterator it = _clientSockets.begin(); it != _clientSockets.end(); ++it) 
    {
        int client = *it;
        ssize_t bytesRead = recv(client, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead > 0)
        {
            std::string command(buffer, bytesRead);
            buffer[bytesRead] = '\0';
            std::cout << "Message reçu du client " << client << ": " << buffer << std::endl;

            std::istringstream iss(command);
            std::string cmd, arg1, arg2;
            iss >> cmd >> arg1 >> arg2;
            if (cmd == "NICK")
                std::cout << "yo connecte" << std::endl;
            if (cmd == "die")
                std::cout << "Commande 'die' reçue. Fermeture du serveur." << std::endl;
            else if (cmd == "nick") 
                std::cout << "Commande 'nick' reçue. Nouveau pseudo : " << arg1 << std::endl;
            else if (cmd == "join") 
                std::cout << "Commande 'join' reçue. Rejoindre le canal : " << arg1 << std::endl;
            else if (cmd == "register") 
                std::cout << "Commande 'register' reçue. Informations d'enregistrement : " << arg1 << " " << arg2 << std::endl;
            std::string response = "Bien reçu !";
            send(client, response.c_str(), response.size(), 0);
        } 
        else if (bytesRead == 0) 
        {
            _socketsToRemove.push_back(client);
            std::cout << "Déconnexion du client " << client << std::endl;
        } 
        else if (errno != EWOULDBLOCK && errno != EAGAIN) 
        {
            _socketsToRemove.push_back(client);
            std::cerr << "Erreur lors de la lecture du client " << client << std::endl;
        }
    }
}

int Server::start(int port) 
{
	if (createSocket())
		return (1);
	serverInfo(port);
	if (link_SocketServer())
		return (1);
	if (listenSocket())
		return (1);
    //Socket d'ecoute en mode non bloquant
    int flags = fcntl(_listenSocket, F_GETFL, 0);
    fcntl(_listenSocket, F_SETFL, flags | O_NONBLOCK);
    
    while (true)
    {
        acceptConnexions();
        manageClientMessage();
        //socketToRemove();
    }
    close(_listenSocket);
    return 0;
}
