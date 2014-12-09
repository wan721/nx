// -------------------------- //
// Entry point for the module //
// -------------------------- //

#include <linux/kernel.h>
#include <linux/module.h>
#include "../include/utils.h"
#include "../workqueue/queue_ng.h"

int init_module( void )
{
	int ret = 0;
	int test = 1;

	unsigned long locType = 0;
	unsigned int *locData;
	unsigned long locSeq = 0;

	prints( "Initializing NX Main Module, current = %d\n", current->pid );

	// create proc entries
	prints( "Creating Nettgain proc entries\n" );

	// create nettgain queue
	prints( "Creating Nettgain queue\n" );
	ret = queue_ng_create( MAX_QUEUE_ENTRIES );

	// try adding something to test interface
	ret = queue_ng_add( &test, UPLINK_PACKET );
	prints( "after add, ret = %d\n", ret );
	
	queue_ng_remove( &locType, (void **)&locData, &locSeq );
	prints( "locType: %lu, locData: %d, *locData: %d, locSeq: %lu\n", locType, (int) locData, *locData, locSeq );

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
