# ft_irc

## 🧠 Internet Relay Chat Server

### 📌 Summary

The goal of this project is to implement a fully functioning **IRC (Internet Relay Chat) server** in **C++98**. You will connect to your server using a real IRC client (IRSSI).

IRC is a text-based communication protocol that enables real-time messaging through channels (groups) and private messaging.

---

## ✅ Features

- Connect multiple IRC clients simultaneously using non-blocking sockets.
- Authentication using a password.
- Join, leave, and message IRC channels.
- Private messaging between clients.
- Channel operators with advanced permissions.
- Full command parsing.

---

## ⚙️ Installation

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/your_username/ft_irc.git](https://github.com/Man-shaa/ft_irc)
   cd ft_irc

---

## 🚀 Usage

./ircserv \<port\> \<password\>

---

## 🛠 Supported Commands

PASS <password>: Authenticate with the server

NICK <nickname>: Set client nickname

USER <username> 0 * :<realname>: Set username

JOIN <#channel>: Join a channel

KICK <#channel> <user>: (operator) Kick user

INVITE <user> <#channel>: (operator) Invite user

MODE <#channel> <modes> [params]: (operator) Set channel modes

TOPIC <#channel> [:<topic>]: View or set (operator) channel topic

PART <#channel>: Leave a channel

NOTICE <targets> <message>: Sends a notice to the target, used by the bot

PRIVMSG <target> :<message>: Send private or channel messages

KILL <nick> <reason>: (operator) Terminates a nickname’s connection from the network

OPER [<nick> [<password>]]: Grants the IRC operator status.

PING <nick>: Sends a PING request to a nickname; this is used to find out the latency on the network.


  Channel Modes

+i: Invite-only channel

+t: Topic can be changed only by operators

+k: Channel password (key)

+o: Operator privilege

+l: User limit for the channel

## 🏅 Bonus Features

📁 File transfers (DCC Send and DCC Get)

🤖 IRC Bot (?help)

## 📜 Documentation

https://irssi.org/documentation/
https://modern.ircdocs.horse/
