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
    socklen_t size = sizeof(address);

    // 3. Bind the socket to that address
    bind(server_fd, (struct sockaddr*)&address, size);//int bind(int, const struct sockaddr *, socklen_t)

    // 4. Start listening for connections
    listen(server_fd, 3);//listen(int socket, int backlog); man listen for more

    // 5. Wait for a client to connect (BLOCKS here)
    int client_fd = accept(server_fd, (struct sockaddr *__restrict__)&address, &size);//int accept(int, struct sockaddr *__restrict__, socklen_t *__restrict__)

    // ---- CONNECTION ESTABLISHED ----

    // 6. Create a buffer to hold incoming data
    char buffer[1024];

    // 7. Read data from the client
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));

    // 8. Print what you received
    if (bytes_read < 0) {
    perror("read failed");
    return 1;
    }
    buffer[bytes_read] = '\0'; // manually null terminate
    printf("%s\n", buffer);

    // 9. Send a response
    char response[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "\r\n"
    "<h1>Hello world!</h1>";
    size_t response_size = sizeof(response) - 1; // -1 gets rid of null terminator
    write(client_fd, response, response_size);//ssize_t write(int __fd, const void *__buf, size_t __nbyte)

    // 10. Close the client connection
    close(client_fd);

    // 11. Close the server (for now, later you'll loop)
    close(server_fd);

    return 0;
}