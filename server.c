// Remote Shell Project
// Name: Renaisa Wahed, Priska Mohunsingh
// Server code

 #include <unistd.h>
 #include <stdio.h> //this file contains declarations used in most input and output
 #include <sys/socket.h> //this file contains definitions of a number of data types used in system calls.
 #include <stdlib.h>
 #include <netinet/in.h> //This file contains constants and structures needed for internet domain addresses. 
 #include <string.h>
 #define PORT 8080 
 int main(int argc, char const *argv[])
  {
      int server_fd, new_socket, valread; //server_fd and new_socket are file descriptors, these would store the values returned     by the socket system call and accepted by system call.  
      struct sockaddr_in address; //this struct is from the netinet/in.h library. 
      int opt = 1;
      int addrlen = sizeof(address);
      char buffer[1024] = {0}; //this would read characters from the socket into this buffer.
      const char *hello = "Hello from server";
  
      // Creating socket file descriptor 
      if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
      {
          perror("socket failed"); // we use perror when a system call fails and it daisplays a message about the error on a stde    rr, then it will abort the program. 
          exit(EXIT_FAILURE);
      }
  
     // Forcefully attaching socket to the port 8080 
     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                   &opt, sizeof(opt)))
     {
         perror("setsockopt");
         exit(EXIT_FAILURE);
     }
     address.sin_family = AF_INET;
     address.sin_addr.s_addr = INADDR_ANY;
     address.sin_port = htons( PORT );
 
     // Forcefully attaching socket to the port 8080 
     if (bind(server_fd, (struct sockaddr *)&address,
                                   sizeof(address))<0)
     {
         perror("bind failed");
         exit(EXIT_FAILURE);
     }
     if (listen(server_fd, 3) < 0)
     {
          perror("listen");
         exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                        (socklen_t*)&addrlen))<0)
     {
         perror("accept");
         exit(EXIT_FAILURE);
     }
     valread = read( new_socket , buffer, 1024);
     printf("%s\n",buffer );
     send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
     return 0;
   }
