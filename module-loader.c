#include <stdio.h>
#include <dlfcn.h>
#include "module.h"

static const char *modules[] = {
	"libpktio-loop.so",
	"libpktio-socket.so",
	"libscheduler-default.so",
	 NULL};

extern void dynamic_module_loader(void)
{
	void *handler = NULL;
	const char **name = NULL;

	module_loader_start();

	/* Use RTLD_NOW to avoid lazy resolution, since typically
	 * modules do not have external references at all.
	 */
	for (name = &modules[0]; *name != NULL; name++) {
		handler = dlopen(*name, RTLD_NOW | RTLD_GLOBAL);
		if (handler != NULL)
			module_install_dso(handler);
		else
			module_abandon_dso();
	}

	module_loader_end();
}
