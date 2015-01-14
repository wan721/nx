#ifndef _COMMON_CONFIG_H
#define _COMMON_CONFIG_H

#define min( x, y )			(( x > y ) ? y : x)
#define HTONL(addr)			(addr =  ( (((ULONG)(addr) & 0x000000FF)<<24) | \
                            	(((ULONG)(addr) & 0x0000FF00)<<8)  | \
                            	(((ULONG)(addr) & 0x00FF0000)>>8)  | \
                             	(((ULONG)(addr) & 0xFF000000)>>24)))

typedef struct
{
	unsigned long			memory_pool;
	unsigned long			local_ip;
	unsigned long			peer_ip;
	unsigned long			max_connections;				/* maximum number of server connections */
	unsigned long			rx_buf_size; 					/* rx window */
	unsigned long 			rx_bw_size;						/* rx window */
	unsigned long			tx_buf_size;					/* tx window, taking into account from the first lost packet */
	unsigned long			tx_bw_size;						/* tx window, taking into account of only unacked packets */
	unsigned long			connect_retries;				/* how many bst connections retried */
	unsigned long			connect_timeout;				/* how many miliseconds waited for connection respond */
	unsigned long			send_retries;					/* maximum packet retries times: if reached or more, close bst connection */
	unsigned long			resend_timeout;					/* resend unacked packets after this milliseconds */
	unsigned long			rx_buf_timeout;					/* send ack after this miliseconds, even if rx_window not full */
	unsigned long			rx_bw_timeout;					/* send ack after this miliseconds, even fo rx_window not full */
	unsigned long			disorder_time;
	unsigned long			hole_report_time;
	unsigned long			nack_timeout;
	unsigned long			idle_timeout;
	unsigned long			keep_alive_interval;
	unsigned long			keep_alive_timeout;				/* close bst connection if keep alive not arrived for this milliseconds */
	unsigned long			tx_time_slot;					/* for compatibility with the FG RTG */
	unsigned long			tx_bw_slot;
	unsigned long			max_rx_bw_slot;
	unsigned long			reopen_to;
	unsigned long			non_bst_bw;
	unsigned long			prv_bst_hw_mark;				/* needed for FG RTG compatibility */
	unsigned long			prv_bst_lw_mark;				/* needed for FG RTG compatibility */
	unsigned long			per_flow_hi_mark				/* needed for FG RTG compatibility */
	unsigned long			bstr_flags;
	unsigned long			ng_version;
	unsigned long			spare_var1;
    unsigned long           spare_var2;
    unsigned long           spare_var3;
    unsigned long           spare_var4;
    unsigned long           spare_var5;
    unsigned long           spare_var6;
    unsigned long           spare_var7;
    unsigned long           spare_var8;
    unsigned long           spare_var9;
    unsigned long           spare_var10;
} bstr_config;

typedef struct {
	unsigned long ip_addr;
	unsigned long in_joint_ip;
	unsigned long ip_mask;
	unsigned long def_gw;
} route_struct;

typedef struct
{
	bstr_config init;
	unsigned long  kind_of_srv;
} bst_struct;

typedef struct
{
	unsigned long bst_hw_mark;
	unsigned long bst_lw_mark;
	unsigned long bst_del_ack_hw_mark;
	unsigned long bst_del_ack_lw_mark;
	unsigned long tcp_hw_mark;
	unsigned long tcp_lw_mark;
	unsigned long tcp_drop_mark;
	unsigned long total_free_high;
	unsigned long total_free_lo;
	unsigned long syn_piggy_to;
	unsigned long data_piggy_to;
} appl_struct;

typedef struct
{
	unsigned long tcp_conn_number;
	unsigned long bst_conn_number;
	unsigned long remote_syn;
	unsigned long transparent_level;
	unsigned long mtu;
} system_struct;

typedef struct 
{
	unsigned long enable_gre_support;
	unsigned long disable_bst_idle_timeout;
} misc_struct;

/******* Compression ******/

#define MAX_COMPR_TABLE_SIZE	20
#define MAX_DATA_NAME			9

#define COMPR_NO				0
#define COMPR_ZLIB_NO_DICT		1
#define COMPR_ZLIB_DICT_HTML	2
#define COMPR_JPEG				3

typedef struct
{
	char			data_name[ MAX_DATA_NAME ];
	unsigned char	compress_method;
} compr_data_descr;

typedef struct
{
	unsigned char		use_compression;
	unsigned char		ftp_jpeg_quality;
	unsigned char 		http_qpeg_quality;
	unsigned char 		other_protocols_jpeg_quality;
	unsigned char 		compress_unrecognized_data;
	unsigned char   	ftp_table_size;
	unsigned char   	http_table_size;
	compr_data_descr	ftp_table[ MAX_COMPR_TABLE_SIZE ];
	compr_data_descr	http_table[ MAX_COMPR_TABLE_SIZE ];
} compression_struct;

#endif // _COMMON_CONFIG_H
