/**
* \file GuiUpdateFlags.h
*
* \brief Flags for tracking GUI-triggered resource updates.
*/

#ifndef GUI_UPDATE_FLAGS_H
#define GUI_UPDATE_FLAGS_H

/**
* \struct GuiUpdateFlags
*
* \brief Tracks which rendering resources need regeneration due to GUI changes.
*
* Contains boolean flags set by the GUI when parameters are modified that require
* expensive resource updates (e.g., regenerating textures or kernel samples).
* Updater components (SsaoUpdater, TransferFunctionTextureUpdater) monitor these
* flags and perform necessary updates, then clear the flags.
*
* This decouples the GUI from resource management and prevents unnecessary
* regeneration when parameters haven't changed.
*
* @see Gui for GUI parameter editing and flag setting.
* @see SsaoUpdater for SSAO resource regeneration based on flags.
* @see TransferFunctionTextureUpdater for transfer function texture updates.
*/
struct GuiUpdateFlags
{
    bool ssaoParametersChanged = false; /**< True if SSAO kernel size or radius changed, requiring noise texture regeneration. */
    bool transferFunctionChanged = false; /**< True if transfer function control points changed, requiring texture update. */
};

#endif
