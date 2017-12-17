
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusxx__pod_proxy_hpp__PROXY_MARSHAL_H
#define __dbusxx__pod_proxy_hpp__PROXY_MARSHAL_H

#include <dbus-c++/dbus.h>
#include <cassert>

namespace pedal {

class event_proxy
: public ::DBus::InterfaceProxy
{
public:

    event_proxy()
    : ::DBus::InterfaceProxy("pedal.event")
    {
        connect_signal(event_proxy, OnPedalEvent, _OnPedalEvent_stub);
    }

public:

    /* properties exported by this interface */
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */
    void Quit()
    {
        ::DBus::CallMessage call;
        call.member("Quit");
        ::DBus::Message ret = invoke_method (call);
    }


public:

    /* signal handlers for this interface
     */
    virtual void OnPedalEvent(const int32_t& code) = 0;

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
    void _OnPedalEvent_stub(const ::DBus::SignalMessage &sig)
    {
        ::DBus::MessageIter ri = sig.reader();

        int32_t code;
        ri >> code;
        OnPedalEvent(code);
    }
};

} 
#endif //__dbusxx__pod_proxy_hpp__PROXY_MARSHAL_H