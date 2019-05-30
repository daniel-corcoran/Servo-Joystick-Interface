#pragma once
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
bool initialize(ssh_session &session, ssh_channel &channel);
void free_session(ssh_session session);
void free_channel(ssh_channel channel);
void get_channel(ssh_session& session, ssh_channel& channel);