#include <linux/slab.h>
#include <linux/skbuff.h>
#include "../include/utils.h"
#include "queue_ng.h"
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/wait.h>

static unsigned long 	num_elements;
struct flworkq_t		*ngqueue;
static DEFINE_SPINLOCK( ngqueue_lock );
static unsigned long	NGQueueDown;
unsigned long			queueOverWritePacket;
unsigned long			queueOverWriteEvents;

// ==============================
// creates the main program queue which includes entries for both
// packets and timing elements
// ==============================
int queue_ng_create( unsigned long qsize )
{
	unsigned int	index = 0;
	int 			ret = 0;

	num_elements = 0;
	
	if ( !qsize ) {
		return ( -EINVAL );
	}
	
	ngqueue = (struct flworkq_t *) kmalloc( sizeof( struct flworkq_t ), GFP_KERNEL );
	if ( !ngqueue ) {
		return ( -ENOMEM );
	}

	memset( ngqueue, 0, sizeof( struct flworkq_t ) );
	ngqueue->qsize = qsize;
	init_waitqueue_head( &ngqueue->wait_queue );	
	
	prints( "lock queue access\n" );

	spin_lock( &ngqueue_lock );	
	ngqueue->elements = (struct msg_elements *) kmalloc( qsize * sizeof( struct msg_elements ), GFP_KERNEL );
	if ( !ngqueue->elements ) {
		kfree( ngqueue );
		return ( -ENOMEM );
	}
	while ( index < qsize ) {
		ngqueue->elements[ index ].data = NULL;
		ngqueue->elements[ index ].type = MESSAGE_USED;
		index++;
	}
	NGQueueDown = 0;
	queueOverWritePacket = 0;
	queueOverWriteEvents = 0;
	prints( "unlock queue access\n" );
	spin_unlock( &ngqueue_lock );

	prints( "created nettgain queue of size %lu\n", qsize );

	return ret;
}

void queue_ng_destroy( void )
{
	unsigned int	count;
	unsigned int	freeCount;
	unsigned int	justCount;

	count = queueOverWritePacket = freeCount = justCount = 0;

	// look for packets just arrived
	if ( ngqueue->head != ngqueue->tail )
	{
		prints( "ngqueue not empty, there maybe packets just arrived, clean them out...\n" );
		while ( count < MAX_QUEUE_ENTRIES ) {
			if ( (ngqueue->elements[ count ].type & MESSAGE_USED) != MESSAGE_USED ) {
				justCount++;
			}
			if ( IS_PACKET_TYPE( (ngqueue->elements[ count ].type) ) ) {
				prints( "free skb at count: %d\n", count );
				freeCount++;
				kfree_skb( (struct sk_buff *) ngqueue->elements[count].data );
			}
			count++;
		}
	}

	prints("freeCount: %d, justCount: %d, NGSyncQueue->head: %lu, NGSyncQueue->tail: %lu\n",
            freeCount, justCount, ngqueue->head, ngqueue->tail );

	kfree( ngqueue->elements );
	kfree( ngqueue );
}

int queue_ng_add( void *work, unsigned long type )
{
	unsigned long temp = 0;
	
	spin_lock( &ngqueue_lock );
	temp = ngqueue->head;
	warparound_inc( temp, ngqueue->qsize );
	if ( (ngqueue->elements[ temp ].type & MESSAGE_USED) != MESSAGE_USED ) {
		prints( "Add:  Tail %lu Head %lu \n", ngqueue->head, ngqueue->tail );
		queueOverWriteEvents++;
		if ( IS_PACKET_TYPE( (ngqueue->elements[ temp ].type) ) ) {
			queueOverWritePacket++;
			kfree_skb( (struct sk_buff *) ngqueue->elements[temp].data );
		}
	}
	ngqueue->elements[ temp ].type &= MESSAGE_USED_IGNORE;
	ngqueue->elements[ temp ].type |= type;
	ngqueue->elements[ temp ].data = work;
	ngqueue->elements[ temp ].seq = temp;
	ngqueue->head = temp;
	spin_unlock( &ngqueue_lock );
	
	//wake_up( &ngqueue->wait_queue );
	if ( num_elements >= 0 ) {
		num_elements++;
	}
	
	return ( 0 );
}

void queue_ng_remove( unsigned long *locType, void **locData, unsigned long *locSeq )
{
	unsigned int temp_tail = 0;
	int rc_wait = 0;

	prints( "before wait, ngqueue->head = %lu, ngqueue->tail = %lu\n", ngqueue->head, ngqueue->tail );
	rc_wait = wait_event_interruptible( ngqueue->wait_queue, ngqueue->head != ngqueue->tail );
	prints( "after wait, ngqueue->head = %lu, ngqueue->tail = %lu\n", ngqueue->head, ngqueue->tail );

	if ( rc_wait == -ERESTARTSYS ) {
		prints( "wait returns -ERESTARTSYS ( %d )\n", rc_wait );
		return;
	}

	spin_lock( &ngqueue_lock );
	warparound_inc( ngqueue->tail, ngqueue->qsize );
	temp_tail = ngqueue->tail;
	*locType = ngqueue->elements[ temp_tail ].type;
	*locData = ngqueue->elements[ temp_tail ].data;
	*locSeq = ngqueue->elements[ temp_tail ].seq;
	ngqueue->elements[ ngqueue->tail ].type |= MESSAGE_USED;
	spin_unlock( &ngqueue_lock );

	if ( num_elements >= 0 ) {
		num_elements--;
	}
}

int queue_ng_add_itself( void *work, unsigned long type )
{
	unsigned long temp;

	spin_lock( &ngqueue_lock );
	temp = ngqueue->head;
	warparound_inc( temp, ngqueue->qsize );
	if ( (ngqueue->elements[ temp ].type & MESSAGE_USED) != MESSAGE_USED ) {
		queueOverWriteEvents++;
		if ( IS_PACKET_TYPE( (ngqueue->elements[ temp ].type) ) ) {
			queueOverWritePacket++;
			kfree_skb( (struct sk_buff *) ngqueue->elements[temp].data );
		}
	}
	ngqueue->elements[ temp ].type &= MESSAGE_USED_IGNORE;
	ngqueue->elements[ temp ].type |= type;
	ngqueue->elements[ temp ].data = work;
	ngqueue->elements[ temp ].seq = temp;
	ngqueue->head = temp;
	spin_unlock( &ngqueue_lock );

	return ( 0 );
}

int queue_ng_add_timer( void *work, unsigned long type )
{
	unsigned int temp;

	spin_lock( &ngqueue_lock );
	temp = ngqueue->head;
	warparound_inc( temp, ngqueue->qsize );
	if ( (ngqueue->elements[ temp ].type & MESSAGE_USED) != MESSAGE_USED ) {
        queueOverWriteEvents++;
        if ( IS_PACKET_TYPE( (ngqueue->elements[ temp ].type) ) ) {
            queueOverWritePacket++;
            kfree_skb( (struct sk_buff *) ngqueue->elements[temp].data );
        }
    }
	ngqueue->elements[ temp ].type &= MESSAGE_USED_IGNORE;
	ngqueue->elements[ temp ].type |= type;
	ngqueue->elements[ temp ].data = work;
	ngqueue->elements[ temp ].seq = temp;
	ngqueue->head = temp;
	spin_unlock( &ngqueue_lock );

	//wake_up( &ngqueue->wait_queue );

	return ( 0 );
}
