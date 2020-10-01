/*******************************************************************
*
*  DESCRIPTION: Atomic Model Sender
*
*  AUTHOR: Tao Zheng 
*
*  EMAIL: mailto://zhengtao@sce.carleton.ca
*
*  DATE: 15/10/2002
*
*******************************************************************/

#ifndef __SENDER_H
#define __SENDER_H


#include "atomic.h"     // class Atomic

class Sender : public Atomic
{
public:
	Sender( const string &name = "Sender" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &controlIn;
	const Port &ackIn;
	Port &dataOut;
	Port &packetSent;	
	Port &ackReceived;
	Time preparationTime;
	Time timeout;
	bool ack;
	int packetNum;
	int totalPacketNum;
	int alt_bit;
	bool sending;
//	typedef list<Value> ElementList ;
//	ElementList elements ;

//	Time timeLeft;

};	// class Sender

// ** inline ** // 
inline
string Sender::className() const
{
	return "Sender" ;
}

#endif   //__SENDER_H
