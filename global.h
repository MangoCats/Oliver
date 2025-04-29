/**************************************
 * Oliver - simple script launcher    *
 * triggered by network messages.     *
 * Copyright (c) 2025 by Mike Inman   *
 * aka MangoCats, all rights reserved *
 * Free, Open Source, MIT license     *
 *                                    *
 * Webserver code adapted from the    *
 * Stefan Frings project.             *
 **************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "scriptPlayer.h"
#include <QMutex>

/** Where the script files are kept */
extern QString scriptsPath;

/** How long a script is given to run before launching another */
extern qint32 defaultRunTime;

/** List of available script files, updated with each new page load */
extern QFileInfoList scriptFiles;
extern        QMutex scriptFilesMutex;

/** Single sound player to serve all the HTTP based requests */
extern ScriptPlayer sPlayer;

extern QString hostName;

using namespace stefanfrings;

/**
  Global objects that are shared by multiple source files
  of this project.
*/

/** Storage for session cookies */
extern  HttpSessionStore* sessionStore;

/** Controller for static files */
extern  StaticFileController* staticFileController;

#endif // GLOBAL_H
