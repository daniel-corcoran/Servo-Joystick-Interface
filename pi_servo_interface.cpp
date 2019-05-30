
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string>

#include "ssh.h"


double getPanAngle() {

}
double getTiltAngle() {

}
void zero(ssh_session session, ssh_channel channel) {
	int rc;
	char buffer[1024];
	unsigned int nbytes;
	printf("Executing remote command...\n");
	ssh_channel_request_exec(channel, "cd servo; sudo python pantilt.py 90 0 ");



	//printf("Error at checkpoint\n");

	printf("Received:\n");
	nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);

	while (nbytes > 0) {
		fwrite(buffer, 1, nbytes, stdout);
		nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
	}

	printf("servo is at zero\n");
	//ssh_channel_request_exec(channel, "sudo python pantilt.py 90 90 ");


}
void assign(ssh_session session, ssh_channel channel, int pan, int tilt) {
	std::string command = "cd servo; sudo python pantilt.py " + std::to_string(pan) + " " + std::to_string(tilt);
	const char* cstr = command.c_str();
	int rc;
	char buffer[1024];
	unsigned int nbytes;
	//printf("Executing remote command...\n");
	ssh_channel_request_exec(channel, cstr);



	//printf("Error at checkpoint\n");

	printf("Received:\n");
	nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);


	printf("checkpoint\n");


}
int main() {





	ssh_session session;
	ssh_channel channel;

	initialize(session, channel);
	zero(session, channel);
	printf("check1");
	//free_channel(channel);
	free_channel(channel);
	sf::Joystick::update();
	while (sf::Joystick::isConnected(2)) {
		//event handler loop for main sequence

		std::cout << sf::Joystick::getAxisPosition(2, sf::Joystick::Y) << std::endl;
		double pan_value = (sf::Joystick::getAxisPosition(2, sf::Joystick::X) + 100) * 0.9;
		double tilt_value = (sf::Joystick::getAxisPosition(2, sf::Joystick::Y) + 100) * 0.9;
		sf::Joystick::update();
		//Sleep(200);


		get_channel(session, channel);
		assign(session, channel, pan_value, tilt_value);
		free_channel(channel);


	}
	//free_channel(channel);
	free_session(session);

	return 0;
}

