#include <linux/kernel.h>
#include <linux/module.h>

#include "include/utils.h"

void cleanup_module( void )
{
	prints( "Exiting NX Main Module, current = %d\n", current->pid );
	// stop main thread
	prints( "stopping main thread\n" );
	// stop timer thread
	prints( "stopping timer thread\n" );
	// stop garbage collector thread
	prints( "stopping garbage collector thread\n" );
	// stop statistics thread
	prints( "stopping statistics thread\n" );
	// unregister netfilter hooks
    prints( "unregistering netfilter hooks\n" );
	// stop nettgain queue
	prints( "stoping nettgain queue\n" );
	// remove nettgain queue
    prints( "removing nettgain queue\n" );
	// release miscellaneous memory items
	prints( "releasing miscellaneous memory items\n" );
	// remove proc entries
	prints( "removing proc entries\n" );

	return ( (void) 0 );
}
