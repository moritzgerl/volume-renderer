/**
* \file DisplayProperties.h
*
* \brief Display and debug visualization state for the application.
*/

#ifndef DISPLAY_PROPERTIES_H
#define DISPLAY_PROPERTIES_H

/**
* \struct DisplayProperties
*
* \brief Stores flags for controlling debug visualization modes.
*
* Contains boolean flags that control which debug visualizations are displayed
* in the rendering output. Modified by keyboard input via InputHandler and used
* by render passes to determine which content to display.
*
* Currently supports toggling the SSAO map visualization, which displays the raw
* ambient occlusion values instead of the final composited image.
*
* @see InputHandler for keyboard input handling that modifies these flags.
* @see RenderPass for using display properties to control rendering output.
* @see Storage for centralized display properties storage.
*/
struct DisplayProperties
{
    bool showSsaoMap; /**< If true, displays the SSAO map instead of the final composited image. */
};

#endif
