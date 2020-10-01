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

#ifndef __SUBNET_H
#define __SUBNET_H

#include "atomic.h"     // class Atomic


/** forward declarations **/
class Distribution ;

class Subnet : public Atomic
{
public:
	Subnet( const string &name = "Subnet" );					//Default constructor
	~Subnet();
	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	Port &out;
	//Time preparationTime;
	int packet;
	int index;
	Distribution * dist;
	
	Distribution &distribution()
		{return *dist;}

};	// class Subnet

// ** inline ** // 
inline
string Subnet::className() const
{
	return "Subnet" ;
}

#endif   //__SUBNET_H
