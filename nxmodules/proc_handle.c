#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include "../include/utils.h"
#include "../include/proc_defs.h"

static inline ktime_t ktime_now(void)
{
    struct timespec ts;
    ktime_get_ts(&ts);

    return timespec_to_ktime(ts);
}

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "AARON LIN" );
MODULE_DESCRIPTION( "DEFAULT CONFIGURATION PARAMETERS" );

static struct proc_dir_entry	*nxmodules_proc_dir;
static struct proc_dir_entry	*bstr_proc_dir;
static struct proc_dir_entry	*application_proc_dir;
static struct proc_dir_entry	*system_proc_dir;
static struct proc_dir_entry	*misc_proc_dir;
static struct proc_dir_entry	*conf_proc_dir;
static struct proc_dir_entry	*debug_proc_dir;

/*
 * create the main proc directory and its subdirectories
 */
static int initialize_proc_directories( void )
{
	/* create the main nx module directory attached to the root directory of proc */
	nxmodules_proc_dir = proc_mkdir( PROC_MAIN_NAME, NULL );
	if ( !nxmodules_proc_dir ) {
		prints( "cannot initialize the main nx proc module\n" );
		goto no_main;
	}
	
	/* create nx module proc subdirectories in the main nx module directory */
	bstr_proc_dir = proc_mkdir( PROC_BSTR_NAME, nxmodules_proc_dir );
	if ( !bstr_proc_dir ) {
        prints( "cannot initialize the bstr proc sub directory\n" );
		goto no_bstr;
    }

	application_proc_dir = proc_mkdir( PROC_APPLICATION_NAME, nxmodules_proc_dir );
	if ( !application_proc_dir ) {
        prints( "cannot initialize the application proc sub directory\n" );
		goto no_application;
    }

	system_proc_dir = proc_mkdir( PROC_SYSTEM_NAME, nxmodules_proc_dir );
	if ( !system_proc_dir ) {
        prints( "cannot initialize the system proc sub directory\n" );
        goto no_system;
    }

	misc_proc_dir = proc_mkdir( PROC_MISC_NAME, nxmodules_proc_dir );
	if ( !misc_proc_dir ) {
		prints( "cannot initialize the misc proc sub directory\n" );
		goto no_misc;
    }

	conf_proc_dir = proc_mkdir( PROC_CONF_NAME, nxmodules_proc_dir );
	if ( !conf_proc_dir ) {
        prints( "cannot initialize the conf proc sub directory\n" );
		goto no_conf;
    }
	
	debug_proc_dir = proc_mkdir( PROC_DEBUG_NAME, nxmodules_proc_dir );
	if ( !debug_proc_dir ) {
		prints( "cannot initialize the debug proc sub directory\n" );
		goto no_debug;
	}

	/* all is good */
	prints( "All proc directories created successfully\n" );
	return 0;

/* some is bad */
no_debug:
	remove_proc_entry( PROC_CONF_NAME, nxmodules_proc_dir );
	prints( "removing the debug proc sub directory\n" );
no_conf:
	remove_proc_entry( PROC_MISC_NAME, nxmodules_proc_dir );
	prints( "removing the misc proc sub directory\n" );
no_misc:
	remove_proc_entry( PROC_SYSTEM_NAME, nxmodules_proc_dir );
	prints( "removing the system proc sub directory\n" );
no_system:
	remove_proc_entry( PROC_APPLICATION_NAME, nxmodules_proc_dir );
	prints( "removing the application proc sub directory\n" );
no_application:
	remove_proc_entry( PROC_BSTR_NAME, nxmodules_proc_dir );
	prints( "removing the bstr proc sub directory\n" );
no_bstr:
	remove_proc_entry( PROC_MAIN_NAME, NULL );
	prints( "removing the main proc sub directory\n" );
no_main:
	return -ENOMEM;
}

/*
 * remove the main proc directory and its subdirectories
 */
static void remove_proc_directories( void )
{
    /* remove subdirectories */
    remove_proc_entry( PROC_BSTR_NAME, nxmodules_proc_dir );
    remove_proc_entry( PROC_APPLICATION_NAME, nxmodules_proc_dir );
    remove_proc_entry( PROC_SYSTEM_NAME, nxmodules_proc_dir );
    remove_proc_entry( PROC_MISC_NAME, nxmodules_proc_dir );
    remove_proc_entry( PROC_CONF_NAME, nxmodules_proc_dir );
	remove_proc_entry( PROC_DEBUG_NAME, nxmodules_proc_dir );

    /* remove the main nx module */
    remove_proc_entry( PROC_MAIN_NAME, NULL );
    prints( "The main nx proc module removed.\n" );
}

/*
 *
 */
static int create_proc_entries( void )
{
	int ret;

	ret = create_bstr_entries( bstr_proc_dir );
	if ( ret < 0 ) {
		prints( "cannot create bstr entries\n" );
		goto no_bstr;
	}

	ret = create_application_entries( application_proc_dir );
    if ( ret < 0 ) {
		prints( "cannot create application entries\n" );
		goto no_application;
    }

	ret = create_system_entries( system_proc_dir );
    if ( ret < 0 ) {
		prints( "cannot create system entries\n" );
		goto no_system;
    }

	ret = create_misc_entries( misc_proc_dir );
    if ( ret < 0 ) {
		prints( "cannot create misc entries\n" );
		goto no_misc;
    }

	ret = create_conf_entries( conf_proc_dir );
    if ( ret < 0 ) {
		prints( "cannot create conf entries\n" );
		goto no_conf;
    }

	ret = create_debug_entries( debug_proc_dir );
    if ( ret < 0 ) {
        prints( "cannot create debug entries\n" );
        goto no_debug;
    }
	
	return 0;

no_debug:
	remove_proc_entry( PROC_CONF_NAME, nxmodules_proc_dir );
no_conf:
	remove_proc_entry( PROC_MISC_NAME, nxmodules_proc_dir );
no_misc:
	remove_proc_entry( PROC_SYSTEM_NAME, nxmodules_proc_dir );
no_system:
	remove_proc_entry( PROC_APPLICATION_NAME, nxmodules_proc_dir );
no_application:
	remove_proc_entry( PROC_BSTR_NAME, nxmodules_proc_dir );
no_bstr:
	return ret;
}

static void remove_proc_entries( void )
{
	remove_bstr_entries( bstr_proc_dir );
	remove_application_entries( application_proc_dir );
	remove_system_entries( system_proc_dir );
	remove_misc_entries( misc_proc_dir );
	remove_conf_entries( conf_proc_dir );
	remove_debug_entries( debug_proc_dir );
}

static int __init init_nxmodules( void )
{
	int ret;

	/* initialize proc directories */
	ret = initialize_proc_directories();

	/* initialize proc entries in each subdirectory*/
	ret = create_proc_entries();

	/* debug timer values */
	prints( "insmod time(ms) = %llu\n", ktime_to_ms( ktime_now() ) );
	return ret;
}

static void __exit cleanup_nxmodules( void )
{
	/* remove proc entries in each subdirectory */
	remove_proc_entries();

	/* remove proc directories */
	remove_proc_directories();
	prints( "rmmod time(ms) = %llu\n", ktime_to_ms( ktime_now() ) );
}

module_init( init_nxmodules );
module_exit( cleanup_nxmodules );
