/*******************************************************************
*
*  DESCRIPTION: Atomic Model Subnet
*
*  AUTHOR: Tao Zheng 
*
*  EMAIL: mailto://zhengtao@sce.carleton.ca
*
*  DATE: 15/10/2002
*
*******************************************************************/

/** include files **/
#include "subnet.h"      // class Subnet
#include "message.h"    // class ExternalMessage, InternalMessage
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )
#include <stdlib.h>
 
/** public functions **/

/*******************************************************************
* Function Name: Subnet
* Description: 
********************************************************************/
Subnet::Subnet( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
//, preparationTime( 0, 0, 3, 0 )
{	index = 1;
	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

		MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Subnet::initFunction()
{
	this-> passivate();
	//packet = 0; 
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Subnet::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in )
	{	index ++;
		packet = static_cast < int > (msg.value());
		//Time t(fabs(this->distribution().get()));
		holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) );
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Subnet::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Subnet::outputFunction( const InternalMessage &msg )
{	if ((double)rand() / (double) RAND_MAX  < 0.95)
		sendOutput( msg.time(), out, packet ) ;
	return *this ;
}

Subnet::~Subnet()
{
	delete dist;
}
