/* This is a small demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "tx_api.h"
#include "gx_api.h"
#include "gx_validation_utility.h"

TEST_PARAM test_parameter = {
    "guix_graphics_palette_ellipse", /* Test name */
     28, 24, 370, 402  /* Define the coordinates of the capture area.
                         In this test, we only need to capture the pixelmap
                         drawing area.  */
};

static VOID      control_thread_entry(ULONG);
int main(int argc, char ** argv)
{
    /* Parse the command line argument. */
    gx_validation_setup(argc, argv);

    /* Start ThreadX system */
    tx_kernel_enter(); 
    return(0);
}

VOID tx_application_define(void *first_unused_memory)
{

    /* Create a dedicated thread to perform various operations
       on the line drawing example. These operations simulate 
       user input. */
    gx_validation_control_thread_create(control_thread_entry);

    /* Termiante the test if it runs for more than 100 ticks */
    /* This function is not implemented yet. */
    gx_validation_watchdog_create(100);

    /* Call the actual line example routine. */
    gx_validation_application_define(first_unused_memory);

}


/* Replace the default graphics driver with the validation driver. */
#ifdef win32_graphics_driver_setup_8bit_palette  
#undef win32_graphics_driver_setup_8bit_palette  
#endif
#define win32_graphics_driver_setup_8bit_palette  gx_validation_graphics_driver_setup_8bit_palette


#ifdef WIN32
#undef WIN32
#endif

#include "gx_validation_wrapper.h"
#include "demo_guix_graphics_palette.c"

char test_comment[255];
extern GX_STUDIO_DISPLAY_INFO graphics_palette_display_table[];

GX_BOOL style_status[2] = {GX_TRUE, GX_FALSE};
INT     brush_width_value[] = {0, 1, 9, 13};
GX_RESOURCE_ID fill_pixelmap_id[] = {GX_PIXELMAP_ID_RAW, GX_PIXELMAP_ID_COMPRESSED, GX_PIXELMAP_ID_TRANSPARENT, GX_PIXELMAP_ID_CMOPRESSED_TRANSPARENT};
/* This thread simulates user input.  Its priority is lower
   than the GUIX thread, so that GUIX finishes an operation 
   before this thread is able to issue the next command. */

static VOID control_thread_entry(ULONG input)
{
int frame_id = 1;
GX_CONST GX_THEME *theme_ptr;
INT anti_aliased_index, solid_fill_index;
INT radius_index, brush_width_index;
INT compressed, transparent;

    draw_shape = ELLIPSE;

    /* Save palette info. */
    theme_ptr = graphics_palette_display_table[DISPLAY_1].theme_table[DISPLAY_1_DEFAULT_THEME];
    gx_validation_write_palette(theme_ptr -> theme_palette, theme_ptr->theme_palette_size);
    
    for(anti_aliased_index = 0; anti_aliased_index < (INT)(sizeof(style_status)/sizeof(INT)); anti_aliased_index++)
    {
        anti_aliased = style_status[anti_aliased_index];
        for(solid_fill_index = 0; solid_fill_index < (INT)(sizeof(style_status)/sizeof(INT)); solid_fill_index++)
        {
            solid_fill = style_status[solid_fill_index];
            for(pixelmap_fill = 0; pixelmap_fill < (INT)(sizeof(style_status)/sizeof(INT)); pixelmap_fill++)
            {
                for(radius_index = 5; radius_index <= 100; radius_index += 33)
                {
                    a = radius_index;
                    b = 100 - radius_index;
                    for(brush_width_index = 0; brush_width_index < (INT)(sizeof(brush_width_value)/sizeof(INT)); brush_width_index ++ )
                    {
                        brush_width = brush_width_value[brush_width_index];
                        
                        
                        sprintf(test_comment, "a:%d, b:%d, brush_width:%d, ",  a, b, brush_width);
                        
                        if(anti_aliased)
                        {
                            strcat(test_comment, "anti_aliased, ");
                        }
                        else
                        {
                            strcat(test_comment, "No anti_aliased, ");
                        }
                        
                        if(pixelmap_fill)
                        {
                            strcat(test_comment, "pixelmap fill: ");
                            
                            for(compressed = 0; compressed <= 1; compressed++)
                            {
                                for(transparent = 0; transparent <= 2; transparent+=2)
                                {
                                    pixelmap_id = compressed + transparent;
                                    
                                    if(compressed)
                                    {
                                        strcat(test_comment, "compressed: true, ");
                                    }
                                    else
                                    {
                                        strcat(test_comment, "compressed: false, ");
                                    }
                                    
                                    if(transparent)
                                    {
                                        strcat(test_comment, "transparent: true, ");
                                    }
                                    else
                                    {
                                        strcat(test_comment, "transparent: false, ");
                                    }
                                     gx_validation_set_frame_id(frame_id);
                                     
                                     gx_validation_set_frame_comment(test_comment);

                                     /* Mark the window "dirty" */
                                     gx_system_dirty_mark(pMainWin);

                                     /* Force a screen refresh. */
                                     gx_validation_screen_refresh();

                                     /* Increment frame ID */
                                     frame_id ++;
                                    
                                }    
                            }
                            
                        }
                        else
                        {
                            if(solid_fill)
                            {
                                strcat(test_comment, "Solid fill ");
                            }
                            else
                            {
                                strcat(test_comment, "No solid fill, ");
                            }
                            
                             gx_validation_set_frame_id(frame_id);
                             
                             gx_validation_set_frame_comment(test_comment);

                             /* Mark the window "dirty" */
                             gx_system_dirty_mark(pMainWin);

                             /* Force a screen refresh. */
                             gx_validation_screen_refresh();

                             /* Increment frame ID */
                             frame_id ++;
                        }

                    }
                }
            }
        }
    }


    /* Signal the end of the test case.  Verify the output. */
    gx_validation_end();

    exit(0);
}
