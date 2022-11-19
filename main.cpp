/* 
 * File:   main.cpp
 * Author: Saleem Edah-Tally - nmset@yandex.com
 * License : GPL V2
 *
 * Created on 10 décembre 2017, 16:24
 */

// Pedal controlled Media Player

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <boost/program_options.hpp>
#include "globals.h"
#include "DBusPODProxy.h"

using namespace std;
namespace po = boost::program_options;

DBusPODProxy * g_pod7Proxy;
DBus::BusDispatcher g_dispatcher;
bool g_verbose = false;
string g_backend = "";
uint g_play = 4;
uint g_fastforward = 2;
uint g_rewind = 1;
uint g_autorewind = 1500;

void signalhandler(int sn)
{
    if (g_verbose)
        cout << _("Application signaled to exit.") << endl;
    delete g_pod7Proxy;
    exit(0);
}

bool ManageParams(int argc, char** argv)
{
    try
    {
        po::options_description desc(_ABOUT_);
        desc.add_options()
                ("help,h", _("Print help messages."))
                ("backend,b", po::value<string>(&g_backend), _("Media player : vlc, dragonplayer, xmms2..."))
                ("verbose,v", _("Show some messages on stdout, namely, signaled pedal codes."))
                ("play,p", po::value<uint>(&g_play), _("Pedal code for <PLAY> - default : 4, unsigned."))
                ("fastforward,f", po::value<uint>(&g_fastforward), _("Pedal code for <FAST FORWARD> - default : 2, unsigned."))
                ("rewind,r", po::value<uint>(&g_play), _("Pedal code for <REWIND> - default : 1, unsigned."))
                ("autorewind,a", po::value<uint>(&g_autorewind), _("Automatically rewind for n milliseconds when playback stops - default : 1500, unsigned."));

        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
            if (vm.count("help"))
            {
                cout << desc << endl;
                return false;
            }
            if (!vm.count("backend"))
            {
                cout << desc << endl;
                return false;
            }
            if (g_rewind == g_play
                    || g_rewind == g_fastforward
                    || g_play == g_fastforward)
            {
                cout << _("Declared pedal codes are inconsistent. A pedal code should identify a unique action.") << endl;
                return false;
            }
            if (vm.count("verbose"))
            {
                g_verbose = true;
            }
        }
        catch (po::error& eb)
        {
            cerr << _("Error : ") << eb.what() << endl;
            return false;
        }
    }
    catch (exception& e)
    {
        cerr << _("Error : ") << e.what() << endl;
        return false;
    }
    return true;
}

bool StartPOD7Proxy()
{
    DBus::Connection bus = DBus::Connection::SessionBus();
    try
    {
        g_pod7Proxy = new DBusPODProxy(bus, "pedal.event");
        return true;
    }
    catch (DBus::Error e)
    {
        delete g_pod7Proxy;
        cout << e.message() << _NL_ << e.name() << endl;
        ;
    }
    return false;
}

int main(int argc, char** argv)
{
    setlocale (LC_ALL, "");
    bindtextdomain (_APPNAME_, "/usr/local/share/locale"); // containing fr/LC_MESSAGES/
    textdomain (_APPNAME_);
    
    if (!ManageParams(argc, argv))
        return 0;
    signal(SIGINT, signalhandler);
    signal(SIGTERM, signalhandler);
    DBus::_init_threading();
    DBus::default_dispatcher = &g_dispatcher;
    if (!StartPOD7Proxy())
    {
        cout << _("Could not listen to pedal events.") << endl;
        return 0;
    }

    // Any better way to do that ?
    while (true)
        sleep(84600);
    return 0;
}

/*
 dbusxx-introspect /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.vlc
 dbusxx-introspect /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.dragonplayer
 */
