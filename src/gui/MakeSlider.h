/**
* \file MakeSlider.h
*
* \brief Helper functions for creating ImGui slider widgets.
*/

#ifndef MAKE_SLIDER_H
#define MAKE_SLIDER_H

/**
* Creates a float slider widget with consistent styling.
*
* Wraps ImGui::SliderFloat with consistent styling and behavior for
* the application's GUI. The slider allows the user to adjust a float
* value within the specified range.
*
* @param label The label displayed next to the slider.
* @param value Pointer to the float value to modify.
* @param min Minimum allowed value.
* @param max Maximum allowed value.
* @return True if the value was modified, false otherwise.
*
* @see MakeSliderInt for integer sliders.
* @see Gui for the main GUI rendering.
*/
bool MakeSliderFloat(const char* label, float* value, float min, float max);

/**
* Creates an integer slider widget with consistent styling.
*
* Wraps ImGui::SliderInt with consistent styling and behavior for
* the application's GUI. The slider allows the user to adjust an integer
* value within the specified range.
*
* @param label The label displayed next to the slider.
* @param value Pointer to the int value to modify.
* @param min Minimum allowed value.
* @param max Maximum allowed value.
* @return True if the value was modified, false otherwise.
*
* @see MakeSliderFloat for float sliders.
* @see Gui for the main GUI rendering.
*/
bool MakeSliderInt(const char* label, int* value, int min, int max);

#endif
