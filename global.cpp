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

#include "global.h"

              QString  scriptsPath;
              QString  hostName;
               qint32  defaultRunTime;
        QFileInfoList  scriptFiles;
               QMutex  scriptFilesMutex;
         ScriptPlayer  sPlayer;
     HttpSessionStore *sessionStore;
 StaticFileController *staticFileController;
