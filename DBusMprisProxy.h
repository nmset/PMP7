/* 
 * File:   DBusMprisProxy.h
 * Author: SET - nmset@yandex.com
 * License : GPL V2
 *
 * Created on 10 décembre 2017, 22:23
 */

#ifndef DBUSMPRISPROXY_H
#define DBUSMPRISPROXY_H

#include "mpris_proxy.hpp"

#define FFR_STEP 5000000 // Fast forward and rewind by 5 secs
#define FFR_STEP_QUICK 50000000 // 50 secs

/**
 * Sends DBus commands to an MPRIS compliant media player.
 * @param connection
 * @param service
 */

class DBusMprisProxy : public org::mpris::MediaPlayer2::Player_proxy,
public DBus::IntrospectableProxy,
public DBus::ObjectProxy
{
public:
    /**
     * 
     * @param connection
     * @param service : pedal.event, from application POD7.
     */
    DBusMprisProxy(DBus::Connection &connection, const char * service);
    virtual ~DBusMprisProxy();

    /**
     * Advances the media position by step milliseconds,
     * pausing 200 milliseconds between steps.
     * Runs in a detached thread. 
     * @param step
     */
    void FastForward(const int& step);
    /**
     * Moves back the media position by step milliseconds,
     * pausing 200 milliseconds between steps.
     * Runs in a detached thread.
     */
    void Rewind(const int& step);
    /**
     * Sets a flag that allows running threads to end.
     */
    void Reset();
    /**
     * Rewinds specified milliseconds before starting playback.
     * An unavoidable feature for transcriptionists.
     */
    void AutoRewind();
private:
    /**
     * Flag controlling thread lifetime.
     */
    static bool m_break;
    static int DoFastForward(DBusMprisProxy * obj, const int& step);
    static int DoRewind(DBusMprisProxy * obj, const int& step);
};

#endif /* DBUSMPRISPROXY_H */

