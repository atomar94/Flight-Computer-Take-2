/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <stdlib.h>
#include <strings.h>
#include <sys/wait.h>	/* for the waitpid() system call */
#include <signal.h>	/* signal name macros, and the kill() prototype */
#include <errno.h>
#include <arpa/inet.h> //inet addr

#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream> //read and write
#include <utility> //pair

#include "http_req.h"
#include "http_res.h"
#include "server.h"

using namespace std;

bool TESTING = false; //false for debug info, true for submission info

void error(std::string msg)
{
    perror(msg.c_str());
    //exit(1);
}


pair<string, string> Server::read_request(int portnum)
{
    int pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        //error on socket
        error("Error on Socket.");
        close(sockfd);
        return pair<string, string>("", "");
    }
    int optval = 1; //so we can set the value of SO_REUSEADDR to 1
    //so after we close the socket it is released immediately
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    memset((char *) &serv_addr, 0, sizeof(serv_addr));	
    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_addr.s_addr = inet_addr("10.10.10.3");
    serv_addr.sin_port = htons(portnum);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
    { 
        error("ERROR on binding");
        close(sockfd);
        return pair<string, string>("","");
    }
    if(listen(sockfd,5) != 0)    //5 simultaneous connection at most
    {
       error("Listen had an error");
       close(sockfd);
       return pair<string, string>("","");
    }

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
    {
        printf("Error on Accept: %s, %d", strerror(errno), errno);
        close(sockfd);
        close(newsockfd);
        return pair<string, string>("","");
    }
    int n;
    char buffer[512];
  	memset(buffer, 0, 512);	//reset memory
      
 	  //read client's message
    n = read(newsockfd,buffer,511);
   	if (n < 0)
    {
        close(sockfd);
        close(newsockfd);
        error("error on client read.");
        return pair<string, string>("","");
    }
    string stdstr = buffer;
    HTTP_Req req(stdstr);

    send_response(""); //send an empty response.
    close(sockfd);
    close(newsockfd);
    return pair<string, string>(req.get_type(), req.get_path());
}

void Server::send_response(string msg)
{
    HTTP_Res res;
    string response = res.form_res_pkt(msg);
    write(newsockfd, response.c_str(), response.length());
    close(newsockfd); 
    close(sockfd);
} 

