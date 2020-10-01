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

/** include files **/
#include "sender.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: Sender
* Description: 
********************************************************************/
Sender::Sender( const string &name )
: Atomic( name )
, controlIn( addInputPort( "controlIn" ) )
, ackIn( addInputPort( "ackIn" ) )
, dataOut( addOutputPort( "dataOut" ) )
, packetSent( addOutputPort( "packetSent" ) )
, ackReceived( addOutputPort( "ackReceived" ) )
, preparationTime( 0, 0, 10, 0 )
, timeout(0, 0, 20, 0)
{	alt_bit = 0;
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
	
	string time2( MainSimulator::Instance().getParameter( description(), "timeout" ) ) ;

	if( time2 != "" )
		timeout = time2 ;	
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Sender::initFunction()
{
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Sender::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == controlIn  && this->state() == passive)
	{	totalPacketNum = static_cast < int > (msg.value());
		if (totalPacketNum > 0)	
		{	packetNum = 1;
			ack = false;
			sending = true;
			alt_bit = packetNum % 2;	//set initial alt_bit
			holdIn(active, preparationTime ); 
		}
	}
	if( msg.port() == ackIn  && this->state() == active)
	{	
		if (alt_bit == static_cast < int > (msg.value()))
		{	ack = true;
			sending = false;
			holdIn(active, Time::Zero) ;
			
		}
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Sender::internalFunction( const InternalMessage & )
{	if (ack)
	{	if (packetNum < totalPacketNum)
		{	packetNum ++;
			ack = false;
		   alt_bit = (alt_bit + 1) % 2;
		   sending = true;
			holdIn( active, preparationTime );
			
		}
		else
			passivate();
	}	
	else
	{	if (sending )
		{	sending = false;
			holdIn(active, timeout);
		}
		else
		{	sending = true;
			holdIn( active, preparationTime );
		
		}	
	}
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Sender::outputFunction( const InternalMessage &msg )
{	if (sending)
	{	sendOutput( msg.time(), dataOut, packetNum * 10 + alt_bit ) ;
		sendOutput(	msg.time(), packetSent, packetNum ) ;
		
	}
	else 
	{	if (ack)
		  sendOutput( msg.time(), ackReceived, alt_bit ) ;	
	}		
	return *this ;
}
