
/* 
 * File:   DBusMprisProxy.cpp
 * Author: SET - nmset@yandex.com
 * License : GPL V2
 * 
 * Created on 10 décembre 2017, 22:23
 */

#include "DBusMprisProxy.h"
#include "globals.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#define FFR_PAUSE 200

bool DBusMprisProxy::m_break = true;
extern uint g_autorewind;

/**
 * Communicates over DBus to an MPRIS compliant media player.
 * @param connection
 * @param service
 */
DBusMprisProxy::DBusMprisProxy(DBus::Connection &connection, const char * service)
: DBus::ObjectProxy(connection, "/org/mpris/MediaPlayer2", service)
{
}

DBusMprisProxy::~DBusMprisProxy()
{
}

void DBusMprisProxy::FastForward(const int& step)
{
    // Let the running thread die
    this_thread::sleep_for(chrono::milliseconds(FFR_PAUSE + 1));
    m_break = false;
    thread t(DoFastForward, this, step);
    t.detach();
}

void DBusMprisProxy::Rewind(const int& step)
{
    this_thread::sleep_for(chrono::milliseconds(FFR_PAUSE + 1));
    m_break = false;
    thread t(DoRewind, this, step);
    t.detach();
}

void DBusMprisProxy::Reset()
{
    m_break = true;
}

int DBusMprisProxy::DoFastForward(DBusMprisProxy * obj, const int& step)
{
    try
    {
        while (!m_break)
        {
            obj->Seek(step); // 1 sec = 1000000
            // https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
            this_thread::sleep_for(chrono::milliseconds(FFR_PAUSE));
        }
    }
    catch (DBus::Error e)
    {
        cout << e.message() << _NL_ << e.name() << endl;
        return 1; // ???
    }
    return 0; // ???
}

int DBusMprisProxy::DoRewind(DBusMprisProxy* obj, const int& step)
{
    try
    {
        while (!m_break)
        {
            obj->Seek(-1 * step);
            this_thread::sleep_for(chrono::milliseconds(FFR_PAUSE));
        }
    }
    catch (DBus::Error e)
    {
        cout << e.message() << _NL_ << e.name() << endl;
        return 1; // ???
    }
    return 0; // ???
}

void DBusMprisProxy::AutoRewind()
{
    Seek((int64_t) g_autorewind * 1000 * -1);
}

