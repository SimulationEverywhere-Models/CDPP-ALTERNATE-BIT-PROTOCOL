/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Rujun Hu
*
*  STUDENT#: 258902
*
*  EMAIL: rujun_hu@yahoo.ca
*
*  DATE: 16/10/2001
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "receiver.h"        // class Receiver
#include "sender.h"        // class Sender
#include "subnet.h"        // class Subnet
//#include "subnet2.h"        // class Subnet2

void MainSimulator::registerNewAtomics()
{
 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Subnet>(), "Subnet" ) ;   
	//SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Subnet2>(), "Subnet2" ) ; 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Sender>(), "Sender" ) ; 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Receiver>(), "Receiver" ) ;  } 

