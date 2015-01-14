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
 * proc entries for debug directory
 */
static struct proc_dir_entry	*debugInfo_proc;
static struct proc_dir_entry	*nackInfo_proc;
static struct proc_dir_entry	*ngTcpInfo_proc;

/*
 * buffers for proc entries
 */
static char debugInfo_buf[ 1500 ];
static char nackInfo_buf[ 1500 ];
static char ngTcpInfo_buf[ 1500 ];

/*
 * size of each proc buffer
 */
static unsigned long debugInfo_size = 0;
static unsigned long nackInfo_size = 0;
static unsigned long ngTcpInfo_size = 0;

/*
 * read operation for each proc entry
 */
int debugInfo_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, debugInfo_buf, debugInfo_size );
        ret = debugInfo_size;
    }

    return ret;
}

int nackInfo_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, nackInfo_buf, nackInfo_size );
        ret = nackInfo_size;
    }

    return ret;
}

int ngTcpInfo_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, ngTcpInfo_buf, ngTcpInfo_size );
        ret = ngTcpInfo_size;
    }

    return ret;
}

/*
 * write operation for each proc entry
 */
int debugInfo_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	debugInfo_size = count;
    if ( debugInfo_size > PROC_MAX_SIZE ) {
        debugInfo_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( debugInfo_buf, buffer, debugInfo_size ) ) {
        return -EFAULT;
    }

    return debugInfo_size;
}

int nackInfo_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	nackInfo_size = count;
    if ( nackInfo_size > PROC_MAX_SIZE ) {
        nackInfo_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( nackInfo_buf, buffer, nackInfo_size ) ) {
        return -EFAULT;
    }

    return nackInfo_size;
}

int ngTcpInfo_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	ngTcpInfo_size = count;
    if ( ngTcpInfo_size > PROC_MAX_SIZE ) {
        ngTcpInfo_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( ngTcpInfo_buf, buffer, ngTcpInfo_size ) ) {
        return -EFAULT;
    }

    return ngTcpInfo_size;
}

int create_debug_entries( struct proc_dir_entry *debug_proc_dir )
{
    int ret;

    ret = 0;

	/* create debugInfo proc entry */
	debugInfo_proc               = create_proc_entry( "debugInfo", 0644, debug_proc_dir );
    if ( !debugInfo_proc ) {
        prints( "cannot initialize debugInfo\n" );
        goto no_debugInfo;
    }
    debugInfo_proc->read_proc    = debugInfo_read;
    debugInfo_proc->write_proc   = debugInfo_write;
    debugInfo_proc->mode         = (S_IFREG | S_IRUGO);
    debugInfo_proc->uid          = 0;
    debugInfo_proc->gid          = 0;
    debugInfo_proc->size         = 128;

	/* create nackInfo proc entry */
	nackInfo_proc               = create_proc_entry( "nackInfo", 0644, debug_proc_dir );
    if ( !nackInfo_proc ) {
        prints( "cannot initialize nackInfo\n" );
        goto no_nackInfo;
    }
    nackInfo_proc->read_proc    = nackInfo_read;
    nackInfo_proc->write_proc   = nackInfo_write;
    nackInfo_proc->mode         = (S_IFREG | S_IRUGO);
    nackInfo_proc->uid          = 0;
    nackInfo_proc->gid          = 0;
    nackInfo_proc->size         = 128;

	/* create ngTcpInfo proc entry */
	ngTcpInfo_proc               = create_proc_entry( "ngTcpInfo", 0644, debug_proc_dir );
    if ( !ngTcpInfo_proc ) {
        prints( "cannot initialize ngTcpInfo\n" );
        goto no_ngTcpInfo;
    }
    ngTcpInfo_proc->read_proc    = ngTcpInfo_read;
    ngTcpInfo_proc->write_proc   = ngTcpInfo_write;
    ngTcpInfo_proc->mode         = (S_IFREG | S_IRUGO);
    ngTcpInfo_proc->uid          = 0;
    ngTcpInfo_proc->gid          = 0;
    ngTcpInfo_proc->size         = 128;

	/* all is good */
    return ret;

/* some is bad */
no_ngTcpInfo:
	remove_proc_entry( "nackInfo", debug_proc_dir );
no_nackInfo:
	remove_proc_entry( "debugInfo", debug_proc_dir );
no_debugInfo:
	return -ENOMEM;
}
EXPORT_SYMBOL( create_debug_entries );

void remove_debug_entries( struct proc_dir_entry *debug_proc_dir )
{
	remove_proc_entry( "debugInfo", debug_proc_dir );
	remove_proc_entry( "nackInfo", debug_proc_dir );
	remove_proc_entry( "ngTcpInfo", debug_proc_dir );
}
EXPORT_SYMBOL( remove_debug_entries );
