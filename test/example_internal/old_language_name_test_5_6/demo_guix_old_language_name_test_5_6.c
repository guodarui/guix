/* This is a small demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "gx_api.h"
#include "old_language_name_test_5_6_resources.h"
#include "old_language_name_test_5_6_specifications.h"


extern UINT win32_graphics_driver_setup_24xrgb(GX_DISPLAY *display);
GX_WINDOW_ROOT *root;

/*****************************************************************************/
/* Application entry.                                                        */
/*****************************************************************************/
int main(int argc, char ** argv)
{
  tx_kernel_enter();
  return(0);
}

/*****************************************************************************/
/* Function called by ThreadX startup to define initial system               */
/*****************************************************************************/
VOID tx_application_define(void *first_unused_memory)
{
    /* Initialize GUIX.  */
    gx_system_initialize();

    gx_studio_display_configure(DISPLAY_1, win32_graphics_driver_setup_24xrgb,
        LANGUAGE_BAMANANKAN, DISPLAY_1_THEME_1, &root);

    /* create the window screen */
    gx_studio_named_widget_create("window", (GX_WIDGET*)root, GX_NULL);

    /* Show the root window to make it and patients screen visible.  */
    gx_widget_show(root);

    /* start the GUIX thread */
    gx_system_start();
}
