#include "configargs.h"

#define GCCPLUGIN_VERSION_MAJOR   4
#define GCCPLUGIN_VERSION_MINOR   9
#define GCCPLUGIN_VERSION_PATCHLEVEL   3
#define GCCPLUGIN_VERSION  (GCCPLUGIN_VERSION_MAJOR*1000 + GCCPLUGIN_VERSION_MINOR)

static char basever[] = "4.9.3";
static char datestamp[] = "20150529";
static char devphase[] = "release";
static char revision[] = "[ARM/embedded-4_9-branch revision 224288]";

/* FIXME plugins: We should make the version information more precise.
   One way to do is to add a checksum. */

static struct plugin_gcc_version gcc_version = {basever, datestamp,
						devphase, revision,
						configuration_arguments};
