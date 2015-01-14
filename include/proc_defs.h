#define PROC_MAIN_NAME			"nxmodules"
#define PROC_BSTR_NAME			"bstr"
#define PROC_APPLICATION_NAME	"application"
#define PROC_SYSTEM_NAME		"system"
#define PROC_MISC_NAME			"misc"
#define PROC_CONF_NAME			"conf"
#define PROC_DEBUG_NAME			"debug"

#define PROC_MAX_SIZE			128

extern int create_bstr_entries( struct proc_dir_entry *bstr_proc_dir );
extern int create_application_entries( struct proc_dir_entry *application_proc_dir );
extern int create_system_entries( struct proc_dir_entry *system_proc_dir );
extern int create_misc_entries( struct proc_dir_entry *misc_proc_dir );
extern int create_conf_entries( struct proc_dir_entry *conf_proc_dir );
extern int create_debug_entries( struct proc_dir_entry *debug_proc_dir );

extern void remove_bstr_entries( struct proc_dir_entry *bstr_proc_dir );
extern void remove_application_entries( struct proc_dir_entry *application_proc_dir );
extern void remove_system_entries( struct proc_dir_entry *system_proc_dir );
extern void remove_misc_entries( struct proc_dir_entry *misc_proc_dir );
extern void remove_conf_entries( struct proc_dir_entry *conf_proc_dir );
extern void remove_debug_entries( struct proc_dir_entry *debug_proc_dir );
