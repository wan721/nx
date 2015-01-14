#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#include <linux/string.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/semaphore.h>

#include "../include/utils.h"
#include "../include/proc_defs.h"

/*
 * proc entries for conf directory
 */
static struct proc_dir_entry	*finished_proc;
static struct proc_dir_entry	*watchdog_proc;

/*
 * buffers for proc entries
 */
static char finished_buf[ PROC_MAX_SIZE ];
static char watchdog_buf[ PROC_MAX_SIZE ];

/*
 * size of each proc buffer
 */
static unsigned long finished_size = 0;
static unsigned long watchdog_size = 0;

/*
 * read operation for each proc entry
 */
int finished_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

	if ( offset > 0 ) {
		ret = 0;
	} else {
		memcpy( buffer, finished_buf, finished_size );
		ret = finished_size;
	}

	return ret;
}

int watchdog_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, watchdog_buf, watchdog_size );
        ret = watchdog_size;
    }

    return ret;
}

/*
 * write operation for each proc entry
 */
int finished_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	finished_size = count;
	if ( finished_size > PROC_MAX_SIZE ) {
		finished_size = PROC_MAX_SIZE;
	}

	if ( copy_from_user( finished_buf, buffer, finished_size ) ) {
		return -EFAULT;
	}
	
	return finished_size;
}

/*
 * write operation for each proc entry
 */
int watchdog_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    watchdog_size = count;
    if ( watchdog_size > PROC_MAX_SIZE ) {
        watchdog_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( watchdog_buf, buffer, watchdog_size ) ) {
        return -EFAULT;
    }
    
    return watchdog_size;
}

int create_conf_entries( struct proc_dir_entry *conf_proc_dir )
{
    int ret = 0;

	/* create finished proc entry */
	finished_proc 				= create_proc_entry( "finished", 0644, conf_proc_dir );
	if ( !finished_proc ) {
		prints( "cannot initialize finished\n" );
		goto no_finished;
	}
	finished_proc->read_proc	= finished_read;
	finished_proc->write_proc	= finished_write;
	finished_proc->mode			= (S_IFREG | S_IRUGO);
	finished_proc->uid			= 0;
	finished_proc->gid			= 0;
	finished_proc->size			= 128;

	/* create watchdog proc entry */
	watchdog_proc               = create_proc_entry( "watchdog", 0644, conf_proc_dir );
    if ( !watchdog_proc ) {
        prints( "cannot initialize watchdog\n" );
        goto no_watchdog;
    }
	watchdog_proc->read_proc	= watchdog_read;
	watchdog_proc->write_proc	= watchdog_write;
	watchdog_proc->mode			= (S_IFREG | S_IRUGO);
	watchdog_proc->uid			= 0;
	watchdog_proc->gid			= 0;
	watchdog_proc->size			= 128;

	/* all is well */	
    return ret;

/* some is bad */
no_watchdog:
	remove_proc_entry( "finished", conf_proc_dir );
no_finished:
	return -ENOMEM;
}
EXPORT_SYMBOL(create_conf_entries);

void remove_conf_entries( struct proc_dir_entry *conf_proc_dir )
{
	/* remove watchdog proc entry */
	remove_proc_entry( "watchdog", conf_proc_dir );
	/* remove finished proc entry */
	remove_proc_entry( "finished", conf_proc_dir );
}
EXPORT_SYMBOL(remove_conf_entries);
