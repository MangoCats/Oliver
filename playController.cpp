/**************************************
 * Oliver - simple script launcher    *
 * triggered by network messages.     *
 * Copyright (c) 2025 by Mike Inman   *
 * aka MangoCats, all rights reserved *
 * Free, Open Source, MIT license     *
 **************************************/

#include "playController.h"
#include "global.h"
#include <QDateTime>
#include <QJsonDocument>

PlayController::PlayController()
{ connect( this, SIGNAL(startPlayer())         , &sPlayer, SLOT(playTimerTimeout())    , Qt::QueuedConnection );
  connect( this, SIGNAL(enqueueScript(QString)), &sPlayer, SLOT(enqueueScript(QString)), Qt::QueuedConnection );
}

PlayController::~PlayController()
{}

/**
 * @brief PlayController::service - called on its own short lived thread
 * @param request - received from http server
 * @param response - sent back to http server
 */
void PlayController::service(HttpRequest& request, HttpResponse& response)
{ QDir dir( scriptsPath );
  scriptFilesMutex.lock();
  scriptFiles.clear();
  if ( dir.exists() )
    if ( !dir.isEmpty() )
      scriptFiles = dir.entryInfoList( QDir::Files | QDir::NoSymLinks, QDir::Name | QDir::IgnoreCase );
  scriptFilesMutex.unlock();

  QByteArray name = request.getPath().mid(6);  // Strip off the /play/ portion of path
  foreach ( QFileInfo fi, scriptFiles )
    if ( name == fi.fileName().toUtf8() )
      emit enqueueScript( fi.fileName() );

  // If anything has been enqueued while timer was not running, this will start the queue running
  emit startPlayer();

  // Don't generate a page for a POST request, but otherwise it's processed the same as a GET.
  if ( request.getMethod() == "POST" )
    return;

  response.setHeader("Content-Type", "text/html; charset=UTF-8");

  QByteArray body("<html>\n");
  body.append("<head>\n");
  body.append("<link rel='shortcut icon' href='/images/Oliver.png' />\n");
  body.append("<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n");
  body.append("<meta http-equiv='Cache-Control' content='no-cache, no-store, must-revalidate' />\n");
  body.append("<meta http-equiv='Pragma' content='no-cache' />\n");
  body.append("<meta http-equiv='Expires' content='0' />\n");
  body.append("<style>\n");
  body.append("table {\n");
  body.append("    border: 0px solid black;\n");
  body.append("}\n");
  body.append("table, th, td {\n");
  body.append("    padding: 5px;\n");
  body.append("}\n");
  body.append("</style>\n");
  body.append("<title>Oliver: Script Launcher</title>\n");
  body.append("</head>\n");

  body.append("<body>\n");

  body.append(QString("<H1>%1</H1>\n").arg( hostName ).toUtf8() );
  body.append(QString("<H2>%1</H2>\n").arg( QDateTime::currentDateTime().toString() ).toUtf8() );

  qint32 i = 0;
  scriptFilesMutex.lock();
  if ( scriptFiles.size() < 1 )
    body.append( QString( "No files in "+scriptsPath ).toUtf8() );
   else
    foreach ( QFileInfo fi, scriptFiles )
      body.append( playButton( fi, i++ ) );
  scriptFilesMutex.unlock();
  body.append("</body>\n");

  body.append("</html>");
  response.write(body,true);
}

/**
 * @brief PlayController::playButton
 * @param fi - file info for play button
 * @param i - index number
 * @return html for one file's play button
 */
QByteArray PlayController::playButton( QFileInfo fi, qint32 i )
{ QByteArray name  = fi.fileName().toUtf8();
  QByteArray label = labelFromFileInfo( fi ).toUtf8();
  QByteArray id    = "btn"+QString::number(i).toUtf8();
  QByteArray ba;
  ba.append( "<form action='/play/"+name+"' method='get'>\n" );
  ba.append( "  <label for='"+id+"'>"+label+"</label>\n" );
  ba.append( "  <input type='submit' id='"+id+"' value='Play'>\n" );
  ba.append( "</form>\n" );
  return ba;
}

/**
 * @brief PlayController::labelFromFileInfo
 * @param fi - file info for file to look in
 * @return label if found in the file, or the filename if not
 */
QString PlayController::labelFromFileInfo( QFileInfo fi )
{ QString name = fi.fileName();
  QFile file( fi.absoluteFilePath() );
  if ( !file.open( QIODevice::ReadOnly ) )
    return name;
  QString contents = QString::fromUtf8( file.readAll() );
  if ( !contents.contains( "#OliverName=" ) )
    return name;
  QStringList lines = contents.split( QChar('\n'), QString::SkipEmptyParts );
  foreach ( QString line, lines )
    if ( line.startsWith( "#OliverName=") )
      { return line.mid(12).trimmed();
      }
  return name;
}
