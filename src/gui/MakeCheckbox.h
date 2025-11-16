/**
* \file MakeCheckbox.h
*
* \brief Helper function for creating ImGui checkbox widgets.
*/

#ifndef MAKE_CHECKBOX_H
#define MAKE_CHECKBOX_H

/**
* Creates a checkbox widget with consistent styling.
*
* Wraps ImGui::Checkbox with consistent styling and behavior for
* the application's GUI. The checkbox allows the user to toggle
* a boolean value on or off.
*
* @param label The label displayed next to the checkbox.
* @param value Pointer to the bool value to modify.
* @return True if the value was modified, false otherwise.
*
* @see MakeSliderFloat for slider widgets.
* @see Gui for the main GUI rendering.
*/
bool MakeCheckbox(const char* label, bool* value);

#endif
