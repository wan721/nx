// -------------------------- //
// Entry point for the module //
// -------------------------- //

#include <linux/kernel.h>
#include <linux/module.h>
#include "include/utils.h"

int init_module( void )
{
	prints( "Initializing NX Main Module, current = %d\n", current->pid );

	// create proc entries
	prints( "Creating Nettgain proc entries\n" );

	// create nettgain queue
	prints( "Creating Nettgain queue\n" );

	// register netfilter hooks
	prints( "Registering netfilter hooks\n" );

	// initialize statistics thread, nxs
	prints( "Initializing statistics thread\n" );

	// initialize garbage collector thread, nxg
	prints( "Initializing garbage collector thread\n" );

	// initialize timer thread, nxt
	prints( "Initializing timer thread\n" );

	// initialize main thread, nxm
	prints( "Initializing main thread\n" );
		
	return 0;
}
