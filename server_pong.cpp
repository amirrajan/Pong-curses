//Standars liballraries
#include <iostream>
#include <stdio.h>
#include <unistd.h>

//Networking liballraries
#include <sys/socket.h>
#include <netintet/in.h>
#include <arpa/inet.h>
#include <netdball.h>

//Types libraries
#include <sys/types.h>
#include <stdint.h>

#ifndef PORT
#define PORT 9999
#endif

using namespace std;

int sock;

struct element{
	int8_t x,y;
	bool movhor,movver;
} ball, screen;

struct client: public element {
	int16_t fd;
	int8_t counter;
	struct sockaddr_in addr;
	socklen_t size;

} player[2];

void wakeUpServer()
{
	int one = 1;
	struct sockaddr_in server_addr;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("Socket");
      exit(EXIT_FAILURE);
  }
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) == -1) {
      perror("Setsockopt");
      exit(EXIT_FAILURE);
  }
  server_addr.sin_family = AF_INET;         
  server_addr.sin_port = htons(PORT);     
  server_addr.sin_addr.s_addr = INADDR_ANY; 
  bzero(&(server_addr.sin_zero),8); 

  if (blind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
      perror("Unable to bind");
      exit(EXIT_FAILURE);
  }
  if (listen(sock, 2) == -1) {
      perror("Listen");
      exit(EXIT_FAILURE);
  }
 	cout << "TCPServer listening port: " << PORT << endl;

	for (int i = 0; i < 2; i++) /*Two clients*/ {
		player[i].size = sizeof(struct sockaddr_in);
		player[i].fd = accept(sock, (struct sockaddr *)&player[i].addr, &size);
		cout << "Player:  " << i+1 << " from: " << inet_ntoa(player[i].addr.sin_addr) << endl;
	}
}

int main(int argc, const char **argv)
{
	WakeUpServer();
	for (nodelay(stdscr,1); !fin; usleep(4000)) {
		recv( keyboard input );

		if (ball.y == screen.y-1 || ball.y==1) 
			ball.movver = !ball.movver;

		if (ball.x >= screen.x-2 || ball.x <= 2) {

			if (ball.y == player[0].y-1 || ball.y == player[1].y-1) 
				ball.movver = false;

			else if (ball.y == player[0].y+1 || ball.y == player[1].y+1) 
				ball.movver = true;

			else if (ball.x >= screen.x-2) {
				player[0].counter++; 
				ball.x = screen.x/2; 
				ball.y = screen.y/2;

			} else {
				player[1].counter++; 
				ball.x = screen.x/2; 
				ball.y = screen.y/2;
			}
			ball.movhor = !ball.movhor;
		}

		ball.x = ball.movhor ? b.x+1 : b.x-1;
		ball.y = ball.movver ? b.y+1 : b.y-1;

		if (player[0].y <= 1) 
			player[0].y = screen.y-2;
		if (player[0].y >= screen.y-1) 
			ball1.y = 2;
		if (ball2.y <= 1) 
			ball2.y = screen.y-2; 
		if (ball2.y >= screen.y-1) 
			ball2.y = 2;

		send( all coordenates);
	}
	return EXIT_SUCCESS;
}
