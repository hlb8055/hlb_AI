#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   MessageDispatcher.h
//
//  Desc:   A message dispatcher. Manages messages of the type Telegram.
//          Instantiated as a singleton.
//
//
//------------------------------------------------------------------------
#include "common/message/Telegram.h"


class BaseEntity;

//to make code easier to read
const float SEND_MSG_IMMEDIATELY = 0.0f;
const int NO_ADDITIONAL_INFO   = 0;
const int SENDER_ID_IRRELEVANT = -1;


class MessageDispatcher
{
public:
    static MessageDispatcher* instance();

    //send a message to another agent. Receiving agent is referenced by ID.
    void dispatchMsg(float delay,
                                       int sender,
                                       int receiver,
                                       int msg,
                                       void* extraInfo);

    //send out any delayed messages. This method is called each time through   
    //the main game loop.
    void dispatchMsgDelay();

private:  
    MessageDispatcher(){}

    //copy ctor and assignment should be private
    MessageDispatcher(const MessageDispatcher&);
    MessageDispatcher& operator=(const MessageDispatcher&);  
    
    //this method is utilized by DispatchMsg or DispatchDelayedMessages.
    //This method calls the message handling member function of the receiving
    //entity, pReceiver, with the newly created telegram
    void execute(BaseEntity* pReceiver, const Telegram& msg);
    
    //a std::priority_queue is used as the container for the delayed messages
    //because of the benefit of automatic sorting and avoidance
    //of duplicates. Messages are sorted by their dispatch time.
    std::priority_queue<Telegram> m_delayQueue;    
    
};



#endif