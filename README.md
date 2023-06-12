# TCP Server C++
This is a TCP server implemented in C++ using the `Winsock` library (for Windows). 
The server listens on a specified port and responds to incoming connections with a predefined response.

## How It Works
1. The program initializes the `Winsock` library by calling the `WSAStartup` function. If the initialization fails, an error message is displayed, and the program exits.

2. The program creates a socket using the socket function. If the socket creation fails, an error message is displayed, and the program exits.

3. The program binds the socket to an address and port using the bind function. If the binding fails, an error message is displayed, and the program exits.

4. The program listens on the socket for incoming connections using the listen function. If the listening fails, an error message is displayed, and the program exits.

5. The program enters an infinite loop to accept and handle incoming connections.

6. When a client connects to the server, the program accepts the connection using the accept function. If the acceptance fails, an error message is displayed, and the program continues to the next iteration.

7. The program receives data from the client using the `recv` function. If the receiving fails, an error message is displayed, and the program continues to the next iteration.

8. The program initializes a `GET` request by converting the received data to a string.

9. The program prepares a response message with the content `"Hello, World!"` and sends it back to the client using the send function. If the sending fails, an error message is displayed.

10. The program closes the client socket and continues to the next iteration of the loop to accept new connections.

If the server socket is closed or an error occurs, the program exits.

## Customization
To change the listening `port`, modify the `serverAddress.sin_port` value in the main function.
To customize the response message, modify the `response` variable in the main function.

#### NOTE: Further customizations will be applied.