/*******************************************************************
*
*  DESCRIPTION: Atomic Model Receiver
*
*  AUTHOR: Tao Zheng 
*
*  EMAIL: mailto://zhengtao@sce.carleton.ca
*
*  DATE: 15/10/2002
*
*******************************************************************/

#ifndef __RECEIVER_H
#define __RECEIVER_H

//#include <list>
#include "atomic.h"     // class Atomic

class Receiver : public Atomic
{
public:
	Receiver( const string &name = "Receiver" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	Port &out;
	Time preparationTime;
	int ackNum;
//	typedef list<Value> ElementList ;
//	ElementList elements ;

//	Time timeLeft;

};	// class Receiver

// ** inline ** // 
inline
string Receiver::className() const
{
	return "Receiver" ;
}

#endif   //__RECEIVER_H
