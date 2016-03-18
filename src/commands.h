#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include "settings.h"

void install(struct Settings *settings);
void package(struct Settings *settings);
void library(struct Settings *settings);
void query(struct Settings *settings);

#endif
