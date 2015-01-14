// -------------------------- //
// Entry point for the module //
// -------------------------- //

#include <linux/sys.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
#include "../include/utils.h"
#include "../workqueue/queue_ng.h"

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "AARON LIN" );
MODULE_DESCRIPTION( "NETTGAIN MAIN MODULE" );

static inline ktime_t ktime_now(void)
{
    struct timespec ts;
    ktime_get_ts(&ts);

    return timespec_to_ktime(ts);
}

static int __init nx_init( void )
{
	int ret = 0;
	int test = 3;

	unsigned long locType = 0;
	unsigned int *locData;
	unsigned long locSeq = 0;

	prints( "======= Initializing NX Main Module, current = %d, time(ms) = %llu =======\n", current->pid, ktime_to_ms( ktime_now() ) );

	// create proc entries : moved to nxmodules
	prints( "Creating Nettgain proc entries : moved to nxmodules\n" );

	// create nettgain queue
	prints( "Creating Nettgain queue\n" );
	ret = queue_ng_create( MAX_QUEUE_ENTRIES );

	// try adding something to test interface
	// add something to the queue
	ret = queue_ng_add( &test, DOWNLINK_PACKET );
	prints( "after add, ret = %d\n", ret );
	
	// add timer to the queue
	ret = queue_ng_add_timer( &test, TIMER_MESSAGE );
	prints( "after add timer, ret = %d\n", ret );

	// add itself to the queue
	ret = queue_ng_add_itself( &test, UPLINK_PACKET );
	prints( "after add itself, ret = %d\n", ret );

	// the remove it from the queue
	// [ note ] there seems to be a problem when trying to remove something from the queue when it's empty,
	//          needs to put some error handling there.
	// need to branch on cpu type, 32-bit or 64-bit
	queue_ng_remove( &locType, (void **)&locData, &locSeq );
	prints( "locType: %lu, locData: %u, *locData: %d, locSeq: %lu\n", locType, /*(u64)*/ (unsigned int) locData, *locData, locSeq );

	queue_ng_remove( &locType, (void **)&locData, &locSeq );
	prints( "locType: %lu, locData: %u, *locData: %d, locSeq: %lu\n", locType, /*(u64)*/ (unsigned int) locData, *locData, locSeq );

	queue_ng_remove( &locType, (void **)&locData, &locSeq );
	prints( "locType: %lu, locData: %u, *locData: %d, locSeq: %lu\n", locType, /*(u64)*/ (unsigned int) locData, *locData, locSeq );

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

module_init( nx_init );
