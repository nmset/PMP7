/* 
 * File:   DBusPODProxy.cpp
 * Author: Saleem Edah-Tally - nmset@yandex.com
 * License : GPL V2
 * 
 * Created on 10 décembre 2017, 18:51
 */

#include "DBusPODProxy.h"
#include "globals.h"
#include <iostream>
#include <thread>
using namespace std;

#include "DBusMprisProxy.h"

DBusMprisProxy * g_MprisProxy;
extern string g_backend;
extern uint g_rewind;
extern uint g_fastforward;
extern uint g_play;
extern bool g_verbose;

/**
 * Controls playback of an MPRIS compliant media player.
 * @param connection
 * @param service
 */
DBusPODProxy::DBusPODProxy(DBus::Connection &connection, const char * service)
: DBus::ObjectProxy(connection, "/pedal/event", service)
{
    thread t(Entry);
    t.detach();
    string mpris_service("org.mpris.MediaPlayer2.");
    mpris_service += g_backend;
    g_MprisProxy = new DBusMprisProxy(connection, mpris_service.c_str());
}

DBusPODProxy::~DBusPODProxy()
{
    DBus::default_dispatcher->leave();
    delete g_MprisProxy;
}

void DBusPODProxy::OnPedalEvent(const int32_t& code)
{
    if (g_verbose)
        cout << code << endl;
    try
    {
        // Stop evenything whenever a pedal whenever occurs
        g_MprisProxy->Reset();
        g_MprisProxy->Pause();
        // switch case does not compile here
        if ((uint) code == g_rewind)
        {
            g_MprisProxy->Rewind(FFR_STEP);
        }
        else if ((uint) code == g_rewind + g_play)
        {
            g_MprisProxy->Rewind(FFR_STEP_QUICK);
        }
        else if ((uint) code == g_fastforward)
        {
            g_MprisProxy->FastForward(FFR_STEP);
        }
        else if ((uint) code == g_fastforward + g_play)
        {
            g_MprisProxy->FastForward(FFR_STEP_QUICK);
        }
        else if ((uint) code == g_play)
        {
            g_MprisProxy->AutoRewind();
            g_MprisProxy->Play();
        }
        else
        {
            g_MprisProxy->Reset();
            g_MprisProxy->Pause();
        }

    }
    catch (DBus::Error e)
    {
        cout << e.message() << _NL_ << e.name() << endl;
    }
}

int DBusPODProxy::Entry()
{
    DBus::default_dispatcher->enter(); // IS BLOCKING
    return 0;
}
