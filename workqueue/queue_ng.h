#ifndef _FLASH_WORKQ_H
#define _FLASH_WORKQ_H

#include <linux/wait.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>

#include <linux/wait.h>

#define UPLINK_PACKET           0x00000001
#define DOWNLINK_PACKET         0x00000002


#define MAX_PACKETS_TYPE        0x00000fff
#define IS_PACKET_TYPE(x)       x <= MAX_PACKETS_TYPE

#define TIMER_MESSAGE           0x00001000
#define SCHED_APPLICATION       0x00002000
#define SCHED_TCP               0x00003000
#define GRE_QUEUED_PACKET       0x00004000
#define SCHED_GRE               0x00005000
#define SHUTDOWN_MESSAGE        0x0fffffff
#define MESSAGE_USED            0x10000000
#define MESSAGE_USED_IGNORE     0xefffffff

#define warparound_inc(n, limit) { ++(n); if ((n) == (limit)) (n) = 0; }
#define MAX_QUEUE_ENTRIES	6000

struct msg_elements {
	unsigned long	type;
	void 			*data;
	unsigned long	seq;
};

struct flworkq_t {
	// move lock to global variable
	//struct spinlock_t	*lock;
	struct msg_elements	*elements;
	unsigned long		head;
	unsigned long		tail;
	unsigned long		qsize;
	wait_queue_head_t	wait_queue;
};

int queue_ng_create( unsigned long qsize );
void queue_ng_destroy( void );
int queue_ng_add( void *work, unsigned long type );
void queue_ng_remove( unsigned long *locType, void **locData, unsigned long *locSeq );
int queue_ng_add_itself( void *work, unsigned long type );
int queue_ng_add_timer( void *work, unsigned long type );

#endif
