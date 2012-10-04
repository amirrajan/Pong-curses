//Standars libraries
#include <iostream>
#include <stdio.h>
#include <unistd.h>

//Networking libraries
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//Types libraries
#include <sys/types.h>
#include <stdint.h>

//Default screen size
#define columns 80
#define rows 24

#ifndef PORT
#define PORT 9999
#endif

using namespace std;

int sock;

enum direction {RIGHT, LEFT, UP, DOWN};

struct element{
	int8_t x,y;
	direction horizontal, vertical;

	void changeVer() {
		vertical = (vertical == RIGHT) ? LEFT: RIGHT;
	}
	void changeHor() {
		horizontal = (horizontal == UP) ? DOWN: UP;
	}

} ball;

struct client: public element {
	int16_t fd;
	int8_t counter;
	struct sockaddr_in addr;
	socklen_t size;

	client(): counter(0), fd(-1) { 
		size = sizeof(struct sockaddr_in);
	}
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

  if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
      perror("Unable to bind");
      exit(EXIT_FAILURE);
  }
  if (listen(sock, 2) == -1) {
      perror("Listen");
      exit(EXIT_FAILURE);
  }
 	cout << "TCPServer listening port: " << PORT << endl;

	for (int i = 0; i < 2; i++) /*Two clients*/ {
		player[i].fd = accept(sock, (struct sockaddr *)&player[i].addr, &player[i].size);
		cout << "Player:  " << i+1 << " from: " << inet_ntoa(player[i].addr.sin_addr) << endl;
	}
}

int main(int argc, const char **argv)
{
	wakeUpServer();
	while (!fin) {
		recv( keyboard input );

		if (ball.y == rows-1 || ball.y == 1) 
			ball.changeVer();

		if (ball.x >= columns-2 || ball.x <= 2) {

			ball.changeHor();
			if (ball.y == player[0].y-1 || ball.y == player[1].y-1) 
				ball.vertical = DOWN;

			else if (ball.y == player[0].y+1 || ball.y == player[1].y+1) 
				ball.vertical = UP;

			if (ball.y != player[0].y && ball.y != player[1].y){
				if (ball.x == columns-2)
					player[0].counter++; 

				else if (ball.x == 2) 
					player[1].counter++; 

				ball.x = columns/2; 
				ball.y = rows/2;
			}
		}

		ball.x = ball.horizontal ? ball.x+1 : ball.x-1;
		ball.y = ball.vertical ? ball.y+1 : ball.y-1;

		if (player[0].y <= 1) 
			player[0].y = rows-2;

		if (player[0].y >= columns-1) 
			player[0].y = 2;

		if (player[1].y <= 1) 
			player[1].y = rows-2; 

		if (player[1].y >= columns-1) 
			player[1].y = 2;

		send( all coordenates);
	}
	return EXIT_SUCCESS;
}
