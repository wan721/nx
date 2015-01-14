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
 * proc entries for bstr directory
 */
static struct proc_dir_entry	*ConnectRetries_proc;
static struct proc_dir_entry	*ConnectTimeout_proc;
static struct proc_dir_entry	*DisorderTime_proc;
static struct proc_dir_entry	*HoleReportTime_proc;
static struct proc_dir_entry	*IdleTimeout_proc;
static struct proc_dir_entry	*KeepAliveInterval_proc;
static struct proc_dir_entry	*KeepAliveTimeout_proc;
static struct proc_dir_entry	*MaxConnections_proc;
static struct proc_dir_entry	*MaxRxBwSlot_proc;
static struct proc_dir_entry	*NackTimeout_proc;
static struct proc_dir_entry	*PeerIp_proc;
static struct proc_dir_entry	*ResendTimeout_proc;
static struct proc_dir_entry	*RxBufSize_proc;
static struct proc_dir_entry	*RxBufTimeout_proc;
static struct proc_dir_entry	*RxBwSize_proc;
static struct proc_dir_entry	*RxBwTimeout_proc;
static struct proc_dir_entry	*SendRetries_proc;
static struct proc_dir_entry	*TxBufSize_proc;
static struct proc_dir_entry	*TxBwSize_proc;
static struct proc_dir_entry	*TxBwSlot_proc;
static struct proc_dir_entry	*ReOpenTimeout_proc;
static struct proc_dir_entry	*showAllBstrEntries_proc;

/*
 * buffers for proc entries
 */
static char ConnectRetries_buf[ PROC_MAX_SIZE ];
static char ConnectTimeout_buf[ PROC_MAX_SIZE ];
static char DisorderTime_buf[ PROC_MAX_SIZE ];
static char HoleReportTime_buf[ PROC_MAX_SIZE ];
static char IdleTimeout_buf[ PROC_MAX_SIZE ];
static char KeepAliveInterval_buf[ PROC_MAX_SIZE ];
static char KeepAliveTimeout_buf[ PROC_MAX_SIZE ];
static char MaxConnections_buf[ PROC_MAX_SIZE ];
static char MaxRxBwSlot_buf[ PROC_MAX_SIZE ];
static char NackTimeout_buf[ PROC_MAX_SIZE ];
static char PeerIp_buf[ PROC_MAX_SIZE ];
static char ResendTimeout_buf[ PROC_MAX_SIZE ];
static char RxBufSize_buf[ PROC_MAX_SIZE ];
static char RxBufTimeout_buf[ PROC_MAX_SIZE ];
static char RxBwSize_buf[ PROC_MAX_SIZE ];
static char RxBwTimeout_buf[ PROC_MAX_SIZE ];
static char SendRetries_buf[ PROC_MAX_SIZE ];
static char TxBufSize_buf[ PROC_MAX_SIZE ];
static char TxBwSize_buf[ PROC_MAX_SIZE ];
static char TxBwSlot_buf[ PROC_MAX_SIZE ];
static char ReOpenTimeout_buf[ PROC_MAX_SIZE ];
static char showAllBstrEntries_buf[ PROC_MAX_SIZE ];

/*
 * size of each proc buffer
 */
static unsigned long ConnectRetries_size = 0;
static unsigned long ConnectTimeout_size = 0;
static unsigned long DisorderTime_size = 0;
static unsigned long HoleReportTime_size = 0;
static unsigned long IdleTimeout_size = 0;
static unsigned long KeepAliveInterval_size = 0;
static unsigned long KeepAliveTimeout_size = 0;
static unsigned long MaxConnections_size = 0;
static unsigned long MaxRxBwSlot_size = 0;
static unsigned long NackTimeout_size = 0;
static unsigned long PeerIp_size = 0;
static unsigned long ResendTimeout_size = 0;
static unsigned long RxBufSize_size = 0;
static unsigned long RxBufTimeout_size = 0;
static unsigned long RxBwSize_size = 0;
static unsigned long RxBwTimeout_size = 0;
static unsigned long SendRetries_size = 0;
static unsigned long TxBufSize_size = 0;
static unsigned long TxBwSize_size = 0;
static unsigned long TxBwSlot_size = 0;
static unsigned long ReOpenTimeout_size = 0;
static unsigned long showAllBstrEntries_size = 0;

/*
 * read operation for each proc entry
 */
int ConnectRetries_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, ConnectRetries_buf, ConnectRetries_size );
        ret = ConnectRetries_size;
    }

    return ret;
}

int ConnectTimeout_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, ConnectTimeout_buf, ConnectTimeout_size );
        ret = ConnectTimeout_size;
    }

    return ret;
}

int DisorderTime_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, DisorderTime_buf, DisorderTime_size );
        ret = DisorderTime_size;
    }

    return ret;
}

int HoleReportTime_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, HoleReportTime_buf, HoleReportTime_size );
        ret = HoleReportTime_size;
    }

    return ret;
}

int IdleTimeout_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, IdleTimeout_buf, IdleTimeout_size );
        ret = IdleTimeout_size;
    }

    return ret;
}

int KeepAliveInterval_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, KeepAliveInterval_buf, KeepAliveInterval_size );
        ret = KeepAliveInterval_size;
    }

    return ret;
}

int KeepAliveTimeout_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, KeepAliveTimeout_buf, KeepAliveTimeout_size );
        ret = KeepAliveTimeout_size;
    }

    return ret;
}

int MaxConnections_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, MaxConnections_buf, MaxConnections_size );
        ret = MaxConnections_size;
    }

    return ret;
}

int MaxRxBwSlot_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, MaxRxBwSlot_buf, MaxRxBwSlot_size );
        ret = MaxRxBwSlot_size;
    }

    return ret;
}

int NackTimeout_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, NackTimeout_buf, NackTimeout_size );
        ret = NackTimeout_size;
    }

    return ret;
}

int PeerIp_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, PeerIp_buf, PeerIp_size );
        ret = PeerIp_size;
    }

    return ret;
}

int ResendTimeout_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, ResendTimeout_buf, ResendTimeout_size );
        ret = ResendTimeout_size;
    }

    return ret;
}

int RxBufSize_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, RxBufSize_buf, RxBufSize_size );
        ret = RxBufSize_size;
    }

    return ret;
}

int RxBufTimeout_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, RxBufTimeout_buf, RxBufTimeout_size );
        ret = RxBufTimeout_size;
    }

    return ret;
}

int RxBwSize_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, RxBwSize_buf, RxBwSize_size );
        ret = RxBwSize_size;
    }

    return ret;
}

int RxBwTimeout_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, RxBwTimeout_buf, RxBwTimeout_size );
        ret = RxBwTimeout_size;
    }

    return ret;
}

int SendRetries_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, SendRetries_buf, SendRetries_size );
        ret = SendRetries_size;
    }

    return ret;
}

int TxBufSize_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, TxBufSize_buf, TxBufSize_size );
        ret = TxBufSize_size;
    }

    return ret;
}

int TxBwSize_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, TxBwSize_buf, TxBwSize_size );
        ret = TxBwSize_size;
    }

    return ret;
}

int TxBwSlot_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, TxBwSlot_buf, TxBwSlot_size );
        ret = TxBwSlot_size;
    }

    return ret;
}

int ReOpenTimeout_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, ReOpenTimeout_buf, ReOpenTimeout_size );
        ret = ReOpenTimeout_size;
    }

    return ret;
}

int showAllBstrEntries_read( char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data )
{
    int ret;

    if ( offset > 0 ) {
        ret = 0;
    } else {
        memcpy( buffer, showAllBstrEntries_buf, showAllBstrEntries_size );
        ret = showAllBstrEntries_size;
    }

    return ret;
}

/*
 * write operation for each proc entry
 */
int ConnectRetries_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    ConnectRetries_size = count;
    if ( ConnectRetries_size > PROC_MAX_SIZE ) {
        ConnectRetries_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( ConnectRetries_buf, buffer, ConnectRetries_size ) ) {
        return -EFAULT;
    }

    return ConnectRetries_size;
}

int ConnectTimeout_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    ConnectTimeout_size = count;
    if ( ConnectTimeout_size > PROC_MAX_SIZE ) {
        ConnectTimeout_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( ConnectTimeout_buf, buffer, ConnectTimeout_size ) ) {
        return -EFAULT;
    }

    return ConnectTimeout_size;
}

int DisorderTime_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    DisorderTime_size = count;
    if ( DisorderTime_size > PROC_MAX_SIZE ) {
        DisorderTime_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( DisorderTime_buf, buffer, DisorderTime_size ) ) {
        return -EFAULT;
    }

    return DisorderTime_size;
}

int HoleReportTime_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    HoleReportTime_size = count;
    if ( HoleReportTime_size > PROC_MAX_SIZE ) {
        HoleReportTime_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( HoleReportTime_buf, buffer, HoleReportTime_size ) ) {
        return -EFAULT;
    }

    return HoleReportTime_size;
}

int IdleTimeout_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    IdleTimeout_size = count;
    if ( IdleTimeout_size > PROC_MAX_SIZE ) {
        IdleTimeout_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( IdleTimeout_buf, buffer, IdleTimeout_size ) ) {
        return -EFAULT;
    }

    return IdleTimeout_size;
}

int KeepAliveInterval_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    KeepAliveInterval_size = count;
    if ( KeepAliveInterval_size > PROC_MAX_SIZE ) {
        KeepAliveInterval_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( KeepAliveInterval_buf, buffer, KeepAliveInterval_size ) ) {
        return -EFAULT;
    }

    return KeepAliveInterval_size;
}

int KeepAliveTimeout_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    KeepAliveTimeout_size = count;
    if ( KeepAliveTimeout_size > PROC_MAX_SIZE ) {
        KeepAliveTimeout_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( KeepAliveTimeout_buf, buffer, KeepAliveTimeout_size ) ) {
        return -EFAULT;
    }

    return KeepAliveTimeout_size;
}

int MaxConnections_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    MaxConnections_size = count;
    if ( MaxConnections_size > PROC_MAX_SIZE ) {
        MaxConnections_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( MaxConnections_buf, buffer, MaxConnections_size ) ) {
        return -EFAULT;
    }

    return MaxConnections_size;
}

int MaxRxBwSlot_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    MaxRxBwSlot_size = count;
    if ( MaxRxBwSlot_size > PROC_MAX_SIZE ) {
        MaxRxBwSlot_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( MaxRxBwSlot_buf, buffer, MaxRxBwSlot_size ) ) {
        return -EFAULT;
    }

    return MaxRxBwSlot_size;
}

int NackTimeout_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    NackTimeout_size = count;
    if ( NackTimeout_size > PROC_MAX_SIZE ) {
        NackTimeout_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( NackTimeout_buf, buffer, NackTimeout_size ) ) {
        return -EFAULT;
    }

    return NackTimeout_size;
}

int PeerIp_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    PeerIp_size = count;
    if ( PeerIp_size > PROC_MAX_SIZE ) {
        PeerIp_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( PeerIp_buf, buffer, PeerIp_size ) ) {
        return -EFAULT;
    }

    return PeerIp_size;
}

int ResendTimeout_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    ResendTimeout_size = count;
    if ( ResendTimeout_size > PROC_MAX_SIZE ) {
        ResendTimeout_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( ResendTimeout_buf, buffer, ResendTimeout_size ) ) {
        return -EFAULT;
    }

    return ResendTimeout_size;
}

int RxBufSize_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    RxBufSize_size = count;
    if ( RxBufSize_size > PROC_MAX_SIZE ) {
        RxBufSize_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( RxBufSize_buf, buffer, RxBufSize_size ) ) {
        return -EFAULT;
    }

    return RxBufSize_size;
}

int RxBufTimeout_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    RxBufTimeout_size = count;
    if ( RxBufTimeout_size > PROC_MAX_SIZE ) {
        RxBufTimeout_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( RxBufTimeout_buf, buffer, RxBufTimeout_size ) ) {
        return -EFAULT;
    }

    return RxBufTimeout_size;
}

int RxBwSize_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    RxBwSize_size = count;
    if ( RxBwSize_size > PROC_MAX_SIZE ) {
        RxBwSize_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( RxBwSize_buf, buffer, RxBwSize_size ) ) {
        return -EFAULT;
    }

    return RxBwSize_size;
}

int RxBwTimeout_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    RxBwTimeout_size = count;
    if ( RxBwTimeout_size > PROC_MAX_SIZE ) {
        RxBwTimeout_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( RxBwTimeout_buf, buffer, RxBwTimeout_size ) ) {
        return -EFAULT;
    }

    return RxBwTimeout_size;
}

int SendRetries_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    SendRetries_size = count;
    if ( SendRetries_size > PROC_MAX_SIZE ) {
        SendRetries_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( SendRetries_buf, buffer, SendRetries_size ) ) {
        return -EFAULT;
    }

    return SendRetries_size;
}

int TxBufSize_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    TxBufSize_size = count;
    if ( TxBufSize_size > PROC_MAX_SIZE ) {
        TxBufSize_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( TxBufSize_buf, buffer, TxBufSize_size ) ) {
        return -EFAULT;
    }

    return TxBufSize_size;
}

int TxBwSize_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    TxBwSize_size = count;
    if ( TxBwSize_size > PROC_MAX_SIZE ) {
        TxBwSize_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( TxBwSize_buf, buffer, TxBwSize_size ) ) {
        return -EFAULT;
    }

    return TxBwSize_size;
}

int TxBwSlot_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    TxBwSlot_size = count;
    if ( TxBwSlot_size > PROC_MAX_SIZE ) {
        TxBwSlot_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( TxBwSlot_buf, buffer, TxBwSlot_size ) ) {
        return -EFAULT;
    }

    return TxBwSlot_size;
}

int ReOpenTimeout_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    ReOpenTimeout_size = count;
    if ( ReOpenTimeout_size > PROC_MAX_SIZE ) {
        ReOpenTimeout_size = PROC_MAX_SIZE;
    }

    if ( copy_from_user( ReOpenTimeout_buf, buffer, ReOpenTimeout_size ) ) {
        return -EFAULT;
    }

    return ReOpenTimeout_size;
}

int showAllBstrEntries_write( struct file *file, const char *buffer, unsigned long count, void *data )
{
    showAllBstrEntries_size = count;
    if ( showAllBstrEntries_size > 1500 ) {
        showAllBstrEntries_size = 1500;
    }

    if ( copy_from_user( showAllBstrEntries_buf, buffer, showAllBstrEntries_size ) ) {
        return -EFAULT;
    }

    return showAllBstrEntries_size;
}

int create_bstr_entries( struct proc_dir_entry *bstr_proc_dir )
{
	int ret;

	ret = 0;

	/* create ConnectRetries entry */
    ConnectRetries_proc		= create_proc_entry( "ConnectRetries", 0644, bstr_proc_dir );
    if ( !ConnectRetries_proc ) {
        prints( "cannot initialize ConnectRetries\n" );
        goto no_ConnectRetries;
    }
    ConnectRetries_proc->read_proc    	= ConnectRetries_read;
    ConnectRetries_proc->write_proc   	= ConnectRetries_write;
    ConnectRetries_proc->mode         	= (S_IFREG | S_IRUGO);
    ConnectRetries_proc->uid          	= 0;
    ConnectRetries_proc->gid          	= 0;
    ConnectRetries_proc->size         	= 128;

	/* create ConnectTimeout entry */
	ConnectTimeout_proc     = create_proc_entry( "ConnectTimeout", 0644, bstr_proc_dir );
	if ( !ConnectTimeout_proc ) {
		prints( "cannot initialize ConnectTimeout\n" );
		goto no_ConnectTimeout;
	}
	ConnectTimeout_proc->read_proc      = ConnectTimeout_read;
	ConnectTimeout_proc->write_proc     = ConnectTimeout_write;
	ConnectTimeout_proc->mode           = (S_IFREG | S_IRUGO);
	ConnectTimeout_proc->uid            = 0;
	ConnectTimeout_proc->gid            = 0;
	ConnectTimeout_proc->size           = 128;

	/* create DisorderTime entry */
	DisorderTime_proc     = create_proc_entry( "DisorderTime", 0644, bstr_proc_dir );
	if ( !DisorderTime_proc ) {
		prints( "cannot initialize DisorderTime\n" );
		goto no_DisorderTime;
	}
	DisorderTime_proc->read_proc      = DisorderTime_read;
	DisorderTime_proc->write_proc     = DisorderTime_write;
	DisorderTime_proc->mode           = (S_IFREG | S_IRUGO);
	DisorderTime_proc->uid            = 0;
	DisorderTime_proc->gid            = 0;
	DisorderTime_proc->size           = 128;

	/* create HoleReportTime entry */
	HoleReportTime_proc     = create_proc_entry( "HoleReportTime", 0644, bstr_proc_dir );
	if ( !HoleReportTime_proc ) {
		prints( "cannot initialize HoleReportTime\n" );
		goto no_HoleReportTime;
	}
	HoleReportTime_proc->read_proc      = HoleReportTime_read;
	HoleReportTime_proc->write_proc     = HoleReportTime_write;
	HoleReportTime_proc->mode           = (S_IFREG | S_IRUGO);
	HoleReportTime_proc->uid            = 0;
	HoleReportTime_proc->gid            = 0;
	HoleReportTime_proc->size           = 128;

	/* create IdleTimeout entry */
	IdleTimeout_proc     = create_proc_entry( "IdleTimeout", 0644, bstr_proc_dir );
	if ( !IdleTimeout_proc ) {
		prints( "cannot initialize IdleTimeout\n" );
		goto no_IdleTimeout;
	}
	IdleTimeout_proc->read_proc      = IdleTimeout_read;
	IdleTimeout_proc->write_proc     = IdleTimeout_write;
	IdleTimeout_proc->mode           = (S_IFREG | S_IRUGO);
	IdleTimeout_proc->uid            = 0;
	IdleTimeout_proc->gid            = 0;
	IdleTimeout_proc->size           = 128;

	/* create KeepAliveInterval entry */
	KeepAliveInterval_proc     = create_proc_entry( "KeepAliveInterval", 0644, bstr_proc_dir );
	if ( !KeepAliveInterval_proc ) {
		prints( "cannot initialize KeepAliveInterval\n" );
		goto no_KeepAliveInterval;
	}
	KeepAliveInterval_proc->read_proc      = KeepAliveInterval_read;
	KeepAliveInterval_proc->write_proc     = KeepAliveInterval_write;
	KeepAliveInterval_proc->mode           = (S_IFREG | S_IRUGO);
	KeepAliveInterval_proc->uid            = 0;
	KeepAliveInterval_proc->gid            = 0;
	KeepAliveInterval_proc->size           = 128;

	/* create KeepAliveTimeout entry */
	KeepAliveTimeout_proc     = create_proc_entry( "KeepAliveTimeout", 0644, bstr_proc_dir );
	if ( !KeepAliveTimeout_proc ) {
		prints( "cannot initialize KeepAliveTimeout\n" );
		goto no_KeepAliveTimeout;
	}
	KeepAliveTimeout_proc->read_proc      = KeepAliveTimeout_read;
	KeepAliveTimeout_proc->write_proc     = KeepAliveTimeout_write;
	KeepAliveTimeout_proc->mode           = (S_IFREG | S_IRUGO);
	KeepAliveTimeout_proc->uid            = 0;
	KeepAliveTimeout_proc->gid            = 0;
	KeepAliveTimeout_proc->size           = 128;

	/* create MaxConnections entry */
	MaxConnections_proc     = create_proc_entry( "MaxConnections", 0644, bstr_proc_dir );
	if ( !MaxConnections_proc ) {
		prints( "cannot initialize MaxConnections\n" );
		goto no_MaxConnections;
	}
	MaxConnections_proc->read_proc      = MaxConnections_read;
	MaxConnections_proc->write_proc     = MaxConnections_write;
	MaxConnections_proc->mode           = (S_IFREG | S_IRUGO);
	MaxConnections_proc->uid            = 0;
	MaxConnections_proc->gid            = 0;
	MaxConnections_proc->size           = 128;

	/* create MaxRxBwSlot entry */
	MaxRxBwSlot_proc     = create_proc_entry( "MaxRxBwSlot", 0644, bstr_proc_dir );
	if ( !MaxRxBwSlot_proc ) {
		prints( "cannot initialize MaxRxBwSlot\n" );
		goto no_MaxRxBwSlot;
	}
	MaxRxBwSlot_proc->read_proc      = MaxRxBwSlot_read;
	MaxRxBwSlot_proc->write_proc     = MaxRxBwSlot_write;
	MaxRxBwSlot_proc->mode           = (S_IFREG | S_IRUGO);
	MaxRxBwSlot_proc->uid            = 0;
	MaxRxBwSlot_proc->gid            = 0;
	MaxRxBwSlot_proc->size           = 128;

	/* create NackTimeout entry */
	NackTimeout_proc     = create_proc_entry( "NackTimeout", 0644, bstr_proc_dir );
	if ( !NackTimeout_proc ) {
		prints( "cannot initialize NackTimeout\n" );
		goto no_NackTimeout;
	}
	NackTimeout_proc->read_proc      = NackTimeout_read;
	NackTimeout_proc->write_proc     = NackTimeout_write;
	NackTimeout_proc->mode           = (S_IFREG | S_IRUGO);
	NackTimeout_proc->uid            = 0;
	NackTimeout_proc->gid            = 0;
	NackTimeout_proc->size           = 128;

	/* create PeerIp entry */
	PeerIp_proc     = create_proc_entry( "PeerIp", 0644, bstr_proc_dir );
	if ( !PeerIp_proc ) {
		prints( "cannot initialize PeerIp\n" );
		goto no_PeerIp;
	}
	PeerIp_proc->read_proc      = PeerIp_read;
	PeerIp_proc->write_proc     = PeerIp_write;
	PeerIp_proc->mode           = (S_IFREG | S_IRUGO);
	PeerIp_proc->uid            = 0;
	PeerIp_proc->gid            = 0;
	PeerIp_proc->size           = 128;

	/* create ResendTimeout entry */
	ResendTimeout_proc     = create_proc_entry( "ResendTimeout", 0644, bstr_proc_dir );
	if ( !ResendTimeout_proc ) {
		prints( "cannot initialize ResendTimeout\n" );
		goto no_ResendTimeout;
	}
	ResendTimeout_proc->read_proc      = ResendTimeout_read;
	ResendTimeout_proc->write_proc     = ResendTimeout_write;
	ResendTimeout_proc->mode           = (S_IFREG | S_IRUGO);
	ResendTimeout_proc->uid            = 0;
	ResendTimeout_proc->gid            = 0;
	ResendTimeout_proc->size           = 128;

	/* create RxBufSize entry */
	RxBufSize_proc     = create_proc_entry( "RxBufSize", 0644, bstr_proc_dir );
	if ( !RxBufSize_proc ) {
		prints( "cannot initialize RxBufSize\n" );
		goto no_RxBufSize;
	}
	RxBufSize_proc->read_proc      = RxBufSize_read;
	RxBufSize_proc->write_proc     = RxBufSize_write;
	RxBufSize_proc->mode           = (S_IFREG | S_IRUGO);
	RxBufSize_proc->uid            = 0;
	RxBufSize_proc->gid            = 0;
	RxBufSize_proc->size           = 128;

	/* create RxBufTimeout entry */
	RxBufTimeout_proc     = create_proc_entry( "RxBufTimeout", 0644, bstr_proc_dir );
	if ( !RxBufTimeout_proc ) {
		prints( "cannot initialize RxBufTimeout\n" );
		goto no_RxBufTimeout;
	}
	RxBufTimeout_proc->read_proc      = RxBufTimeout_read;
	RxBufTimeout_proc->write_proc     = RxBufTimeout_write;
	RxBufTimeout_proc->mode           = (S_IFREG | S_IRUGO);
	RxBufTimeout_proc->uid            = 0;
	RxBufTimeout_proc->gid            = 0;
	RxBufTimeout_proc->size           = 128;

	/* create RxBwSize entry */
	RxBwSize_proc     = create_proc_entry( "RxBwSize", 0644, bstr_proc_dir );
	if ( !RxBwSize_proc ) {
		prints( "cannot initialize RxBwSize\n" );
		goto no_RxBwSize;
	}
	RxBwSize_proc->read_proc      = RxBwSize_read;
	RxBwSize_proc->write_proc     = RxBwSize_write;
	RxBwSize_proc->mode           = (S_IFREG | S_IRUGO);
	RxBwSize_proc->uid            = 0;
	RxBwSize_proc->gid            = 0;
	RxBwSize_proc->size           = 128;

	/* create RxBwTimeout entry */
	RxBwTimeout_proc     = create_proc_entry( "RxBwTimeout", 0644, bstr_proc_dir );
	if ( !RxBwTimeout_proc ) {
		prints( "cannot initialize RxBwTimeout\n" );
		goto no_RxBwTimeout;
	}
	RxBwTimeout_proc->read_proc      = RxBwTimeout_read;
	RxBwTimeout_proc->write_proc     = RxBwTimeout_write;
	RxBwTimeout_proc->mode           = (S_IFREG | S_IRUGO);
	RxBwTimeout_proc->uid            = 0;
	RxBwTimeout_proc->gid            = 0;
	RxBwTimeout_proc->size           = 128;

	/* create SendRetries entry */
	SendRetries_proc     = create_proc_entry( "SendRetries", 0644, bstr_proc_dir );
	if ( !SendRetries_proc ) {
		prints( "cannot initialize SendRetries\n" );
		goto no_SendRetries;
	}
	SendRetries_proc->read_proc      = SendRetries_read;
	SendRetries_proc->write_proc     = SendRetries_write;
	SendRetries_proc->mode           = (S_IFREG | S_IRUGO);
	SendRetries_proc->uid            = 0;
	SendRetries_proc->gid            = 0;
	SendRetries_proc->size           = 128;

	/* create TxBufSize entry */
	TxBufSize_proc     = create_proc_entry( "TxBufSize", 0644, bstr_proc_dir );
	if ( !TxBufSize_proc ) {
		prints( "cannot initialize TxBufSize\n" );
		goto no_TxBufSize;
	}
	TxBufSize_proc->read_proc      = TxBufSize_read;
	TxBufSize_proc->write_proc     = TxBufSize_write;
	TxBufSize_proc->mode           = (S_IFREG | S_IRUGO);
	TxBufSize_proc->uid            = 0;
	TxBufSize_proc->gid            = 0;
	TxBufSize_proc->size           = 128;

	/* create TxBwSize entry */
	TxBwSize_proc     = create_proc_entry( "TxBwSize", 0644, bstr_proc_dir );
	if ( !TxBwSize_proc ) {
		prints( "cannot initialize TxBwSize\n" );
		goto no_TxBwSize;
	}
	TxBwSize_proc->read_proc      = TxBwSize_read;
	TxBwSize_proc->write_proc     = TxBwSize_write;
	TxBwSize_proc->mode           = (S_IFREG | S_IRUGO);
	TxBwSize_proc->uid            = 0;
	TxBwSize_proc->gid            = 0;
	TxBwSize_proc->size           = 128;

	/* create TxBwSlot entry */
	TxBwSlot_proc     = create_proc_entry( "TxBwSlot", 0644, bstr_proc_dir );
	if ( !TxBwSlot_proc ) {
		prints( "cannot initialize TxBwSlot\n" );
		goto no_TxBwSlot;
	}
	TxBwSlot_proc->read_proc      = TxBwSlot_read;
	TxBwSlot_proc->write_proc     = TxBwSlot_write;
	TxBwSlot_proc->mode           = (S_IFREG | S_IRUGO);
	TxBwSlot_proc->uid            = 0;
	TxBwSlot_proc->gid            = 0;
	TxBwSlot_proc->size           = 128;

	/* create ReOpenTimeout entry */
	ReOpenTimeout_proc     = create_proc_entry( "ReOpenTimeout", 0644, bstr_proc_dir );
	if ( !ReOpenTimeout_proc ) {
		prints( "cannot initialize ReOpenTimeout\n" );
		goto no_ReOpenTimeout;
	}
	ReOpenTimeout_proc->read_proc      = ReOpenTimeout_read;
	ReOpenTimeout_proc->write_proc     = ReOpenTimeout_write;
	ReOpenTimeout_proc->mode           = (S_IFREG | S_IRUGO);
	ReOpenTimeout_proc->uid            = 0;
	ReOpenTimeout_proc->gid            = 0;
	ReOpenTimeout_proc->size           = 128;

	/* create showAllBstrEntries entry */
	showAllBstrEntries_proc     = create_proc_entry( "showAllBstrEntries", 0644, bstr_proc_dir );
	if ( !showAllBstrEntries_proc ) {
		prints( "cannot initialize showAllBstrEntries\n" );
		goto no_showAllBstrEntries;
	}
	showAllBstrEntries_proc->read_proc      = showAllBstrEntries_read;
	showAllBstrEntries_proc->write_proc     = showAllBstrEntries_write;
	showAllBstrEntries_proc->mode           = (S_IFREG | S_IRUGO);
	showAllBstrEntries_proc->uid            = 0;
	showAllBstrEntries_proc->gid            = 0;
	showAllBstrEntries_proc->size           = 1500;

	/* all is good */
	return ret;

/* some is bad */
no_showAllBstrEntries:
	remove_proc_entry( "ReOpenTimeout", bstr_proc_dir );
no_ReOpenTimeout:
	remove_proc_entry( "TxBwSlot", bstr_proc_dir );
no_TxBwSlot:
	remove_proc_entry( "TxBwSize", bstr_proc_dir );
no_TxBwSize:
	remove_proc_entry( "TxBufSize", bstr_proc_dir );
no_TxBufSize:
	remove_proc_entry( "SendRetries", bstr_proc_dir );
no_SendRetries:
	remove_proc_entry( "RxBwTimeout", bstr_proc_dir );
no_RxBwTimeout:
	remove_proc_entry( "RxBwSize", bstr_proc_dir );
no_RxBwSize:
	remove_proc_entry( "RxBufTimeout", bstr_proc_dir );
no_RxBufTimeout:
	remove_proc_entry( "RxBufSize", bstr_proc_dir );
no_RxBufSize:
	remove_proc_entry( "ResendTimeout", bstr_proc_dir );
no_ResendTimeout:
	remove_proc_entry( "PeerIp", bstr_proc_dir );
no_PeerIp:
	remove_proc_entry( "NackTimeout", bstr_proc_dir );
no_NackTimeout:
	remove_proc_entry( "MaxRxBwSlot", bstr_proc_dir );
no_MaxRxBwSlot:
	remove_proc_entry( "MaxConnections", bstr_proc_dir );
no_MaxConnections:
	remove_proc_entry( "KeepAliveTimeout", bstr_proc_dir );
no_KeepAliveTimeout:
	remove_proc_entry( "KeepAliveInterval", bstr_proc_dir );
no_KeepAliveInterval:
	remove_proc_entry( "IdleTimeout", bstr_proc_dir );
no_IdleTimeout:
	remove_proc_entry( "HoleReportTime", bstr_proc_dir );
no_HoleReportTime:
	remove_proc_entry( "DisorderTime", bstr_proc_dir );
no_DisorderTime:
	remove_proc_entry( "ConnectTimeout", bstr_proc_dir );
no_ConnectTimeout:
	remove_proc_entry( "ConnectRetries", bstr_proc_dir );
no_ConnectRetries:
	return -ENOMEM;
}
EXPORT_SYMBOL(create_bstr_entries);

void remove_bstr_entries( struct proc_dir_entry *bstr_proc_dir )
{
	/* remove ConnectRetries proc entry */
    remove_proc_entry( "ConnectRetries", bstr_proc_dir );
	/* remove ConnectTimeout proc entry */
    remove_proc_entry( "ConnectTimeout", bstr_proc_dir );
	/* remove DisorderTime proc entry */
    remove_proc_entry( "DisorderTime", bstr_proc_dir );
	/* remove HoleReportTime proc entry */
    remove_proc_entry( "HoleReportTime", bstr_proc_dir );
	/* remove IdleTimeout proc entry */
    remove_proc_entry( "IdleTimeout", bstr_proc_dir );
	/* remove KeepAliveInterval proc entry */
    remove_proc_entry( "KeepAliveInterval", bstr_proc_dir );
	/* remove KeepAliveTimeout proc entry */
    remove_proc_entry( "KeepAliveTimeout", bstr_proc_dir );
	/* remove MaxConnections proc entry */
    remove_proc_entry( "MaxConnections", bstr_proc_dir );
	/* remove MaxRxBwSlot proc entry */
    remove_proc_entry( "MaxRxBwSlot", bstr_proc_dir );
	/* remove NackTimeout proc entry */
    remove_proc_entry( "NackTimeout", bstr_proc_dir );
	/* remove PeerIp proc entry */
    remove_proc_entry( "PeerIp", bstr_proc_dir );
	/* remove ResendTimeout proc entry */
    remove_proc_entry( "ResendTimeout", bstr_proc_dir );
	/* remove RxBufSize proc entry */
    remove_proc_entry( "RxBufSize", bstr_proc_dir );	
	/* remove RxBufTimeout proc entry */
    remove_proc_entry( "RxBufTimeout", bstr_proc_dir );
	/* remove RxBwSize proc entry */
    remove_proc_entry( "RxBwSize", bstr_proc_dir );
	/* remove RxBwTimeout proc entry */
    remove_proc_entry( "RxBwTimeout", bstr_proc_dir );
	/* remove SendRetries proc entry */
    remove_proc_entry( "SendRetries", bstr_proc_dir );
	/* remove TxBufSize proc entry */
    remove_proc_entry( "TxBufSize", bstr_proc_dir );
	/* remove TxBwSize proc entry */
    remove_proc_entry( "TxBwSize", bstr_proc_dir );
	/* remove TxBwSlot proc entry */
    remove_proc_entry( "TxBwSlot", bstr_proc_dir );
	/* remove ReOpenTimeout proc entry */
    remove_proc_entry( "ReOpenTimeout", bstr_proc_dir );
	/* remove showAllBstrEntries proc entry */
    remove_proc_entry( "showAllBstrEntries", bstr_proc_dir );
}
EXPORT_SYMBOL(remove_bstr_entries);
