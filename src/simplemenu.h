/*
  Copyright (c) 2007 Paolo Capriotti <p.capriotti@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
*/

#ifndef SIMPLEMENU_H
#define SIMPLEMENU_H

#include <QObject>

#include "clientnetworkdialog.h"

class WelcomeScreen;
class Controller;
class SeaView;
class Button;
class QTcpSocket;
class Entity;
class Protocol;
class Wpa;

class SimpleMenu : public QObject
{
Q_OBJECT
    WelcomeScreen* m_screen;

    Button* m_server_btn;
    Button* m_client_btn;

    Protocol* m_protocol;
    QString m_nickname;

    enum State
    {
        READY,
        DONE_SERVER,
        DONE_CLIENT
    } m_state;

    Entity* m_player1;
    Entity* m_player2;
    ClientNetworkDialog dialog;
    Wpa *wpa;

    void finalize(State, const QString& nick, QTcpSocket* socket = 0);
public:
    SimpleMenu(QWidget* parent, WelcomeScreen* screen);

    void setupController(Controller* controller, Entity* old_opponent,
                         SeaView* sea, bool ask = false);

    Entity* player(int p) { return p == 0 ? m_player1 : m_player2; }

    static const char* iconServer;
    static const char* iconClient;
public slots:
    void createServer();
    void createClient();
    void gameAbort();
private slots:
    void connectToHost(bool go);
signals:
    void done();
};

#endif // SIMPLEMENU_H
