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
 * proc entries for application directory
 */
static struct proc_dir_entry	*BST_DelMark_proc;
static struct proc_dir_entry	*BST_Mark_proc;
static struct proc_dir_entry	*TCP_Mark_proc;
static struct proc_dir_entry	*TotalFree_proc;
static struct proc_dir_entry	*SynPiggyTo_proc;
static struct proc_dir_entry	*DataPiggyTo_proc;

/*
 * buffers for proc entries
 */
static char BST_DelMark_buf[ PROC_MAX_SIZE ];
static char BST_Mark_buf[ PROC_MAX_SIZE ];
static char TCP_Mark_buf[ PROC_MAX_SIZE ];
static char TotalFree_buf[ PROC_MAX_SIZE ];
static char SynPiggyTo_buf[ PROC_MAX_SIZE ];
static char DataPiggyTo_buf[ PROC_MAX_SIZE ];

/*
 * size of each proc buffer
 */
static unsigned long BST_DelMark_size = 0;
static unsigned long BST_Mark_size = 0;
static unsigned long TCP_Mark_size = 0;
static unsigned long TotalFree_size = 0;
static unsigned long SynPiggyTo_size = 0;
static unsigned long DataPiggyTo_size = 0;

/*
 * read operation for each proc entry
 */
int BST_DelMark_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, BST_DelMark_buf, BST_DelMark_size );
        ret = BST_DelMark_size;
    }

    return ret;
}

int BST_Mark_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
	int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, BST_Mark_buf, BST_Mark_size );
        ret = BST_Mark_size;
    }

    return ret;
}

int TCP_Mark_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, TCP_Mark_buf, TCP_Mark_size );
        ret = TCP_Mark_size;
    }

    return ret;
}

int TotalFree_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, TotalFree_buf, TotalFree_size );
        ret = TotalFree_size;
    }

    return ret;
}

int SynPiggyTo_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, SynPiggyTo_buf, SynPiggyTo_size );
        ret = SynPiggyTo_size;
    }

    return ret;
}

int DataPiggyTo_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, DataPiggyTo_buf, DataPiggyTo_size );
        ret = DataPiggyTo_size;
    }

    return ret;
}

/*
 * write operation for each proc entry
 */
int BST_DelMark_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	BST_DelMark_size = count;
    if ( BST_DelMark_size > PROC_MAX_SIZE ) {
        BST_DelMark_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( BST_DelMark_buf, buffer, BST_DelMark_size ) ) {
        return -EFAULT;
    }

    return BST_DelMark_size;
}

int BST_Mark_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	BST_Mark_size = count;
    if ( BST_Mark_size > PROC_MAX_SIZE ) {
        BST_Mark_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( BST_Mark_buf, buffer, BST_Mark_size ) ) {
        return -EFAULT;
    }

    return BST_Mark_size;
}
int TCP_Mark_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	TCP_Mark_size = count;
    if ( TCP_Mark_size > PROC_MAX_SIZE ) {
        TCP_Mark_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( TCP_Mark_buf, buffer, TCP_Mark_size ) ) {
        return -EFAULT;
    }

    return TCP_Mark_size;
}

int TotalFree_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	TotalFree_size = count;
    if ( TotalFree_size > PROC_MAX_SIZE ) {
        TotalFree_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( TotalFree_buf, buffer, TotalFree_size ) ) {
        return -EFAULT;
    }

    return TotalFree_size;
}

int SynPiggyTo_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	SynPiggyTo_size = count;
    if ( SynPiggyTo_size > PROC_MAX_SIZE ) {
        SynPiggyTo_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( SynPiggyTo_buf, buffer, SynPiggyTo_size ) ) {
        return -EFAULT;
    }

    return SynPiggyTo_size;
}

int DataPiggyTo_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
	DataPiggyTo_size = count;
    if ( DataPiggyTo_size > PROC_MAX_SIZE ) {
        DataPiggyTo_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( DataPiggyTo_buf, buffer, DataPiggyTo_size ) ) {
        return -EFAULT;
    }

    return DataPiggyTo_size;
}

int create_application_entries( struct proc_dir_entry *application_proc_dir )
{
    int ret;

    ret = 0;

	/* create BST_DelMark proc entry */
	BST_DelMark_proc               = create_proc_entry( "BST_DelMark", 0644, application_proc_dir );
    if ( !BST_DelMark_proc ) {
        prints( "cannot initialize BST_DelMark\n" );
        goto no_BST_DelMark;
    }
    BST_DelMark_proc->read_proc    = BST_DelMark_read;
    BST_DelMark_proc->write_proc   = BST_DelMark_write;
    BST_DelMark_proc->mode         = (S_IFREG | S_IRUGO);
    BST_DelMark_proc->uid          = 0;
    BST_DelMark_proc->gid          = 0;
    BST_DelMark_proc->size         = 128;

	/* create BST_Mark proc entry */
	BST_Mark_proc               = create_proc_entry( "BST_Mark", 0644, application_proc_dir );
    if ( !BST_Mark_proc ) {
        prints( "cannot initialize BST_Mark\n" );
        goto no_BST_Mark;
    }
    BST_Mark_proc->read_proc    = BST_Mark_read;
    BST_Mark_proc->write_proc   = BST_Mark_write;
    BST_Mark_proc->mode         = (S_IFREG | S_IRUGO);
    BST_Mark_proc->uid          = 0;
    BST_Mark_proc->gid          = 0;
    BST_Mark_proc->size         = 128;

	/* create TCP_Mark proc entry */
	TCP_Mark_proc               = create_proc_entry( "TCP_Mark", 0644, application_proc_dir );
    if ( !TCP_Mark_proc ) {
        prints( "cannot initialize TCP_Mark\n" );
        goto no_TCP_Mark;
    }
    TCP_Mark_proc->read_proc    = TCP_Mark_read;
    TCP_Mark_proc->write_proc   = TCP_Mark_write;
    TCP_Mark_proc->mode         = (S_IFREG | S_IRUGO);
    TCP_Mark_proc->uid          = 0;
    TCP_Mark_proc->gid          = 0;
    TCP_Mark_proc->size         = 128;

	/* create TotalFree proc entry */
	TotalFree_proc               = create_proc_entry( "TotalFree", 0644, application_proc_dir );
    if ( !TotalFree_proc ) {
        prints( "cannot initialize TotalFree\n" );
        goto no_TotalFree;
    }
    TotalFree_proc->read_proc    = TotalFree_read;
    TotalFree_proc->write_proc   = TotalFree_write;
    TotalFree_proc->mode         = (S_IFREG | S_IRUGO);
    TotalFree_proc->uid          = 0;
    TotalFree_proc->gid          = 0;
    TotalFree_proc->size         = 128;

	/* create SynPiggyTo proc entry */
	SynPiggyTo_proc               = create_proc_entry( "SynPiggyTo", 0644, application_proc_dir );
    if ( !SynPiggyTo_proc ) {
        prints( "cannot initialize SynPiggyTo\n" );
        goto no_SynPiggyTo;
    }
    SynPiggyTo_proc->read_proc    = SynPiggyTo_read;
    SynPiggyTo_proc->write_proc   = SynPiggyTo_write;
    SynPiggyTo_proc->mode         = (S_IFREG | S_IRUGO);
    SynPiggyTo_proc->uid          = 0;
    SynPiggyTo_proc->gid          = 0;
    SynPiggyTo_proc->size         = 128;

	/* create DataPiggyTo proc entry */
	DataPiggyTo_proc               = create_proc_entry( "DataPiggyTo", 0644, application_proc_dir );
    if ( !DataPiggyTo_proc ) {
        prints( "cannot initialize DataPiggyTo\n" );
        goto no_DataPiggyTo;
    }
    DataPiggyTo_proc->read_proc    = DataPiggyTo_read;
    DataPiggyTo_proc->write_proc   = DataPiggyTo_write;
    DataPiggyTo_proc->mode         = (S_IFREG | S_IRUGO);
    DataPiggyTo_proc->uid          = 0;
    DataPiggyTo_proc->gid          = 0;
    DataPiggyTo_proc->size         = 128;

	/* all is good */
    return ret;

/* some is bad */
no_DataPiggyTo:
	remove_proc_entry( "SynPiggyTo", application_proc_dir );
no_SynPiggyTo:
	remove_proc_entry( "TotalFree", application_proc_dir );
no_TotalFree:
	remove_proc_entry( "TCP_Mark", application_proc_dir );
no_TCP_Mark:
	remove_proc_entry( "BST_Mark", application_proc_dir );
no_BST_Mark:
	remove_proc_entry( "BST_DelMark", application_proc_dir );
no_BST_DelMark:
	return -ENOMEM;
}
EXPORT_SYMBOL(create_application_entries);

void remove_application_entries( struct proc_dir_entry *application_proc_dir )
{
	remove_proc_entry( "BST_DelMark", application_proc_dir );
	remove_proc_entry( "BST_Mark", application_proc_dir );
	remove_proc_entry( "TCP_Mark", application_proc_dir );
	remove_proc_entry( "TotalFree", application_proc_dir );
	remove_proc_entry( "SynPiggyTo", application_proc_dir );
	remove_proc_entry( "DataPiggyTo", application_proc_dir );
}
EXPORT_SYMBOL(remove_application_entries);
