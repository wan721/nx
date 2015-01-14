#include <linux/kernel.h>
#include <linux/module.h>

#include "../include/utils.h"
#include "../workqueue/queue_ng.h"

static inline ktime_t ktime_now(void)
{
    struct timespec ts;
    ktime_get_ts(&ts);

    return timespec_to_ktime(ts);
}

static void __exit nx_cleanup( void )
{
	prints( "Exiting NX Main Module, current = %d, time(ms) = %llu\n", current->pid, ktime_to_ms( ktime_now() ) );
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
	queue_ng_destroy();
	// release miscellaneous memory items
	prints( "releasing miscellaneous memory items\n" );
	// remove proc entries : moved to nxmodules
	prints( "removing proc entries : moved to nxmodules\n" );
	prints( "=======\n" );

	return ( (void) 0 );
}

module_exit( nx_cleanup );
