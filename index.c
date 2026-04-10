#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main() {
    // 1. Create a socket (get a "communication handle")
    int server_fd = socket(AF_INET,SOCK_STREAM,0);
    if (server_fd == -1) {
        perror("socket failed");
        return 1;
    }

    // 2. Define the address (where you want to listen)
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind the socket to that address
    //bind(server_fd, address);

    // 4. Start listening for connections
    //listen(server_fd, backlog_limit);

    // 5. Wait for a client to connect (BLOCKS here)
    //client_fd = accept(server_fd);

    // ---- CONNECTION ESTABLISHED ----

    // 6. Create a buffer to hold incoming data
    //buffer = some byte array;

    // 7. Read data from the client
    //bytes_read = read(client_fd, buffer);

    // 8. Print what you received
    //print(buffer);

    // 9. (Optional for now) Send a response
    //write(client_fd, "some response");

    // 10. Close the client connection
    //close(client_fd);

    // 11. Close the server (for now, later you'll loop)
    //close(server_fd);

    return 0;
}