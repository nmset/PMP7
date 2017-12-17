/* 
 * File:   DBusPODProxy.h
 * Author: SET - nmset@yandex.com
 * License : GPL V2
 *
 * Created on 10 décembre 2017, 18:51
 */

#ifndef DBUSPODPROXY_H
#define DBUSPODPROXY_H

#include "pod_proxy.hpp"

/**
 * Listen to DBus pedal events from application POD7.
 * It creates an DBus proxy for an MPRIS compliant media player
 * that will react to pedal events.
 */

class DBusPODProxy : public pedal::event_proxy,
public DBus::IntrospectableProxy,
public DBus::ObjectProxy
{
public:
    /**
     * 
     * @param connection
     * @param service : pedal.event, from application POD7.
     */
    DBusPODProxy(DBus::Connection &connection, const char * service);
    virtual ~DBusPODProxy();

    /**
     * 
     * @param code : sent by a pedal event
     */
    void OnPedalEvent(const int32_t& code) override;

    /**
     * Enters the DBus loop in a detached thread
     * @return 
     */
    static int Entry();

private:

};

#endif /* DBUSPODPROXY_H */

