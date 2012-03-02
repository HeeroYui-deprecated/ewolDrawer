/**
 *******************************************************************************
 * @file globalMsg.cpp
 * @brief ewol drawer global message system (sources)
 * @author Edouard DUPIN
 * @date 02/03/2012
 * @par Project
 * Edn
 *
 * @par Copyright
 * Copyright 2010 Edouard DUPIN, all right reserved
 *
 *******************************************************************************
 */

#include <globalMsg.h>

////////////////////////////////////////////////////////////////////////
// Event of the gui request something :
////////////////////////////////////////////////////////////////////////
extern const char* const drawMsgGuiNew        = "draw-Msg-Gui-New";
extern const char* const drawMsgGuiOpen       = "draw-Msg-Gui-Open";
extern const char* const drawMsgGuiClose      = "draw-Msg-Gui-Close";
extern const char* const drawMsgGuiSave       = "draw-Msg-Gui-Save";
extern const char* const drawMsgGuiSaveAs     = "draw-Msg-Gui-SaveAs";

extern const char* const drawMsgGuiUndo       = "draw-Msg-Gui-Undo";
extern const char* const drawMsgGuiRedo       = "draw-Msg-Gui-Redo";

extern const char* const drawMsgGuiElementNew      = "draw-Msg-Gui-Element-new";
extern const char* const drawMsgGuiElementRemove   = "draw-Msg-Gui-Element-remove";
extern const char* const drawMsgGuiElementHideShow = "draw-Msg-Gui-Element-hide";
extern const char* const drawMsgGuiDotAdd          = "draw-Msg-Gui-Dot-Add";
extern const char* const drawMsgGuiDotRm           = "draw-Msg-Gui-Dot-Rm";
extern const char* const drawMsgGuiLinkStart       = "draw-Msg-Gui-Link-Start";
extern const char* const drawMsgGuiLinkStop        = "draw-Msg-Gui-Link-Stop";
