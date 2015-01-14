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
 * proc entries for misc directory
 */
static struct proc_dir_entry	*NGVersion_proc;
static struct proc_dir_entry	*EnableGreSupport_proc;
static struct proc_dir_entry	*DisableBstIdleTimeout_proc;

/*
 * buffers for proc entries
 */
static char NGVersion_buf[ PROC_MAX_SIZE ];
static char EnableGreSupport_buf[ PROC_MAX_SIZE ];
static char DisableBstIdleTimeout_buf[ PROC_MAX_SIZE ];

/*
 * size of each proc buffer
 */
static unsigned long NGVersion_size = 0;
static unsigned long EnableGreSupport_size = 0;
static unsigned long DisableBstIdleTimeout_size = 0;

/*
 * read operation for each proc entry
 */
int NGVersion_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, NGVersion_buf, NGVersion_size );
        ret = NGVersion_size;
    }

    return ret;
}

int EnableGreSupport_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, EnableGreSupport_buf, EnableGreSupport_size );
        ret = EnableGreSupport_size;
    }

    return ret;
}

int DisableBstIdleTimeout_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, DisableBstIdleTimeout_buf, DisableBstIdleTimeout_size );
        ret = DisableBstIdleTimeout_size;
    }

    return ret;
}

/*
 * write operation for each proc entry
 */
int NGVersion_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	NGVersion_size = count;
    if ( NGVersion_size > PROC_MAX_SIZE ) {
        NGVersion_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( NGVersion_buf, buffer, NGVersion_size ) ) {
        return -EFAULT;
    }

    return NGVersion_size;
}

int EnableGreSupport_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	EnableGreSupport_size = count;
    if ( EnableGreSupport_size > PROC_MAX_SIZE ) {
        EnableGreSupport_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( EnableGreSupport_buf, buffer, EnableGreSupport_size ) ) {
        return -EFAULT;
    }

    return EnableGreSupport_size;
}

int DisableBstIdleTimeout_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	DisableBstIdleTimeout_size = count;
    if ( DisableBstIdleTimeout_size > PROC_MAX_SIZE ) {
        DisableBstIdleTimeout_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( DisableBstIdleTimeout_buf, buffer, DisableBstIdleTimeout_size ) ) {
        return -EFAULT;
    }

    return DisableBstIdleTimeout_size;
}

int create_misc_entries( struct proc_dir_entry *misc_proc_dir )
{
    int ret;

    ret = 0;

	/* create NGVersion proc entry */
    NGVersion_proc               = create_proc_entry( "NGVersion", 0644, misc_proc_dir );
    if ( !NGVersion_proc ) {
        prints( "cannot initialize NGVersion\n" );
        goto no_NGVersion;
    }
    NGVersion_proc->read_proc    = NGVersion_read;
    NGVersion_proc->write_proc   = NGVersion_write;
    NGVersion_proc->mode         = (S_IFREG | S_IRUGO);
    NGVersion_proc->uid          = 0;
    NGVersion_proc->gid          = 0;
    NGVersion_proc->size         = 128;

	/* create EnableGreSupport proc entry */
    EnableGreSupport_proc               = create_proc_entry( "EnableGreSupport", 0644, misc_proc_dir );
    if ( !EnableGreSupport_proc ) {
        prints( "cannot initialize EnableGreSupport\n" );
        goto no_EnableGreSupport;
    }
    EnableGreSupport_proc->read_proc    = EnableGreSupport_read;
    EnableGreSupport_proc->write_proc   = EnableGreSupport_write;
    EnableGreSupport_proc->mode         = (S_IFREG | S_IRUGO);
    EnableGreSupport_proc->uid          = 0;
    EnableGreSupport_proc->gid          = 0;
    EnableGreSupport_proc->size         = 128;

	/* create DisableBstIdleTimeout proc entry */
    DisableBstIdleTimeout_proc               = create_proc_entry( "DisableBstIdleTimeout", 0644, misc_proc_dir );
    if ( !DisableBstIdleTimeout_proc ) {
        prints( "cannot initialize DisableBstIdleTimeout\n" );
        goto no_DisableBstIdleTimeout;
    }
    DisableBstIdleTimeout_proc->read_proc    = DisableBstIdleTimeout_read;
    DisableBstIdleTimeout_proc->write_proc   = DisableBstIdleTimeout_write;
    DisableBstIdleTimeout_proc->mode         = (S_IFREG | S_IRUGO);
    DisableBstIdleTimeout_proc->uid          = 0;
    DisableBstIdleTimeout_proc->gid          = 0;
    DisableBstIdleTimeout_proc->size         = 128;

	/* all is good */
    return ret;

/* some is bad */
no_DisableBstIdleTimeout:
	remove_proc_entry( "EnableGreSupport", misc_proc_dir );
no_EnableGreSupport:
	remove_proc_entry( "NGVersion", misc_proc_dir );
no_NGVersion:
	return -ENOMEM;
}
EXPORT_SYMBOL(  create_misc_entries );

void remove_misc_entries( struct proc_dir_entry *misc_proc_dir )
{
	remove_proc_entry( "NGVersion", misc_proc_dir );
	remove_proc_entry( "EnableGreSupport", misc_proc_dir );
	remove_proc_entry( "DisableBstIdleTimeout", misc_proc_dir );
}
EXPORT_SYMBOL( remove_misc_entries );
