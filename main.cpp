// SPDX-License-Identifier: LGPL-3.0
#include <QCoreApplication>
#include <iostream>
#include <QDebug>

// including some headers for a test
// httpserver
#include "httplistener.h"
#include "httprequesthandler.h"
// logger
#include "logger.h"
// templateengin
#include "template.h"

int main(int argc, char *argv[])
{

    // Initialize the core application
    QCoreApplication app(argc, argv);

    // creating some objekts for a test
    stefanfrings::HttpCookie A();
    stefanfrings::Logger B();
    stefanfrings::Template C("A","B");

    qDebug() << "Done";
}


