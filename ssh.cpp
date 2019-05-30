#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "ssh.h"
void free_channel(ssh_channel channel) {
	ssh_channel_send_eof(channel);
	ssh_channel_close(channel);
	ssh_channel_free(channel);
}
void error(ssh_session session) {
	fprintf(stderr, "Error: %s\n", ssh_get_error(session));
	free_session(session);
	exit(-1);
}
void free_session(ssh_session session) {
	ssh_disconnect(session);
	ssh_free(session);
}
void get_channel(ssh_session &session, ssh_channel& channel) {
	printf("Channel...\n");
	channel = ssh_channel_new(session);
	if (channel == NULL) exit(-1);

	printf("Opening...\n");
	int rc = ssh_channel_open_session(channel);
	if (rc != SSH_OK) {
		error(session);
		
	}
}

bool initialize(ssh_session &session, ssh_channel &channel) {
	int rc, port = 22;
	char buffer[1024];
	unsigned int nbytes;

	printf("Attempting to connect to the servo controller...\n");
	session = ssh_new();
	if (session == NULL) exit(-1);

	ssh_options_set(session, SSH_OPTIONS_HOST, "raspberrypi.local"); //these are just the default values I included
	ssh_options_set(session, SSH_OPTIONS_PORT, &port);
	ssh_options_set(session, SSH_OPTIONS_USER, "pi");

	printf("Connecting...\n");
	rc = ssh_connect(session);
	//Is there an error? 
	if (rc != SSH_OK) {
		error(session);
		return false;
	}

	printf("Password Autentication...\n");
	rc = ssh_userauth_password(session, NULL, "raspberry");
	if (rc != SSH_AUTH_SUCCESS) {
		error(session);
		return false;
	}

	get_channel(session, channel);
	printf("init success!\n");
	return true;


}
///--

//