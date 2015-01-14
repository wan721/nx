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
 * proc entries for system directory
 */
static struct proc_dir_entry	*RemoteSyn_proc;
static struct proc_dir_entry	*TCP_ConnNumber_proc;
static struct proc_dir_entry	*TransparentLevel_proc;
static struct proc_dir_entry	*BST_MTU_proc;

/*
 * buffers for proc entries
 */
static char RemoteSyn_buf[ PROC_MAX_SIZE ];
static char TCP_ConnNumber_buf[ PROC_MAX_SIZE ];
static char TransparentLevel_buf[ PROC_MAX_SIZE ];
static char BST_MTU_buf[ PROC_MAX_SIZE ];

/*
 * size of each proc buffer
 */
static unsigned long RemoteSyn_size = 0;
static unsigned long TCP_ConnNumber_size = 0;
static unsigned long TransparentLevel_size = 0;
static unsigned long BST_MTU_size = 0;

/*
 * read operation for each proc entry
 */
int RemoteSyn_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, RemoteSyn_buf, RemoteSyn_size );
        ret = RemoteSyn_size;
    }

    return ret;
}

int TCP_ConnNumber_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, TCP_ConnNumber_buf, TCP_ConnNumber_size );
        ret = TCP_ConnNumber_size;
    }

    return ret;
}

int TransparentLevel_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, TransparentLevel_buf, TransparentLevel_size );
        ret = TransparentLevel_size;
    }

    return ret;
}

int BST_MTU_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, BST_MTU_buf, BST_MTU_size );
        ret = BST_MTU_size;
    }

    return ret;
}

/*
 * write operation for each proc entry
 */
int RemoteSyn_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	RemoteSyn_size = count;
    if ( RemoteSyn_size > PROC_MAX_SIZE ) {
        RemoteSyn_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( RemoteSyn_buf, buffer, RemoteSyn_size ) ) {
        return -EFAULT;
    }

    return RemoteSyn_size;
}

int TCP_ConnNumber_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	TCP_ConnNumber_size = count;
    if ( TCP_ConnNumber_size > PROC_MAX_SIZE ) {
        TCP_ConnNumber_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( TCP_ConnNumber_buf, buffer, TCP_ConnNumber_size ) ) {
        return -EFAULT;
    }

    return TCP_ConnNumber_size;
}

int TransparentLevel_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	TransparentLevel_size = count;
    if ( TransparentLevel_size > PROC_MAX_SIZE ) {
        TransparentLevel_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( TransparentLevel_buf, buffer, TransparentLevel_size ) ) {
        return -EFAULT;
    }

    return TransparentLevel_size;
}

int BST_MTU_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	BST_MTU_size = count;
    if ( BST_MTU_size > PROC_MAX_SIZE ) {
        BST_MTU_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( BST_MTU_buf, buffer, BST_MTU_size ) ) {
        return -EFAULT;
    }

    return BST_MTU_size;
}

int create_system_entries( struct proc_dir_entry *system_proc_dir )
{
    int ret;

    ret = 0;

	/* create RemoteSyn proc entry */
	RemoteSyn_proc				= create_proc_entry( "RemoteSyn", 0644, system_proc_dir );
    if ( !RemoteSyn_proc ) {
        prints( "cannot initialize RemoteSyn\n" );
        goto no_RemoteSyn;
    }
    RemoteSyn_proc->read_proc	= RemoteSyn_read;
    RemoteSyn_proc->write_proc	= RemoteSyn_write;
    RemoteSyn_proc->mode		= (S_IFREG | S_IRUGO);
    RemoteSyn_proc->uid			= 0;
    RemoteSyn_proc->gid			= 0;
    RemoteSyn_proc->size		= 128;

	/* create TCP_ConnNumber proc entry */
	TCP_ConnNumber_proc					= create_proc_entry( "TCP_ConnNumber", 0644, system_proc_dir );
    if ( !TCP_ConnNumber_proc ) {
        prints( "cannot initialize TCP_ConnNumber\n" );
        goto no_TCP_ConnNumber;
    }
    TCP_ConnNumber_proc->read_proc		= TCP_ConnNumber_read;
    TCP_ConnNumber_proc->write_proc		= TCP_ConnNumber_write;
    TCP_ConnNumber_proc->mode			= (S_IFREG | S_IRUGO);
    TCP_ConnNumber_proc->uid			= 0;
    TCP_ConnNumber_proc->gid			= 0;
    TCP_ConnNumber_proc->size			= 128;

	/* create TransparentLevel proc entry */
	TransparentLevel_proc				= create_proc_entry( "TransparentLevel", 0644, system_proc_dir );
    if ( !TransparentLevel_proc ) {
        prints( "cannot initialize TransparentLevel\n" );
        goto no_TransparentLevel;
    }
    TransparentLevel_proc->read_proc	= TransparentLevel_read;
    TransparentLevel_proc->write_proc	= TransparentLevel_write;
    TransparentLevel_proc->mode			= (S_IFREG | S_IRUGO);
    TransparentLevel_proc->uid			= 0;
    TransparentLevel_proc->gid			= 0;
    TransparentLevel_proc->size			= 128;

	/* create BST_MTU proc entry */
	BST_MTU_proc               			= create_proc_entry( "BST_MTU", 0644, system_proc_dir );
    if ( !BST_MTU_proc ) {
        prints( "cannot initialize BST_MTU\n" );
        goto no_BST_MTU;
    }
    BST_MTU_proc->read_proc    = BST_MTU_read;
    BST_MTU_proc->write_proc   = BST_MTU_write;
    BST_MTU_proc->mode         = (S_IFREG | S_IRUGO);
    BST_MTU_proc->uid          = 0;
    BST_MTU_proc->gid          = 0;
    BST_MTU_proc->size         = 128;

	/* all is good */
    return ret;

/* some is bad */
no_BST_MTU:
	remove_proc_entry( "TransparentLevel", system_proc_dir );
no_TransparentLevel:
	remove_proc_entry( "TCP_ConnNumber", system_proc_dir );
no_TCP_ConnNumber:
	remove_proc_entry( "RemoteSyn", system_proc_dir );
no_RemoteSyn:
	return -ENOMEM;
}
EXPORT_SYMBOL( create_system_entries );

void remove_system_entries( struct proc_dir_entry *system_proc_dir )
{
	remove_proc_entry( "RemoteSyn", system_proc_dir );
	remove_proc_entry( "TCP_ConnNumber", system_proc_dir );
	remove_proc_entry( "TransparentLevel", system_proc_dir );
	remove_proc_entry( "BST_MTU", system_proc_dir );
}
EXPORT_SYMBOL( remove_system_entries );
