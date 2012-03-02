/**
 *******************************************************************************
 * @file globalMsg.h
 * @brief ewol drawer global message system (header)
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
 
#ifndef __GLOBAL_MSG_H__
#define __GLOBAL_MSG_H__


// new list of edn event generic : 
////////////////////////////////////////////////////////////////////////
// Event of the gui request something :
////////////////////////////////////////////////////////////////////////
	extern const char* const drawMsgGuiNew;        // data : ""
	extern const char* const drawMsgGuiOpen;       // data : ""
	extern const char* const drawMsgGuiClose;      // data : ""
	extern const char* const drawMsgGuiSave;       // data : ""
	extern const char* const drawMsgGuiSaveAs;     // data : ""
	
	extern const char* const drawMsgGuiUndo;       // data : ""
	extern const char* const drawMsgGuiRedo;       // data : ""
	
	extern const char* const drawMsgGuiElementNew;
	extern const char* const drawMsgGuiElementRemove;
	extern const char* const drawMsgGuiElementHideShow;
	extern const char* const drawMsgGuiDotAdd;
	extern const char* const drawMsgGuiDotRm;
	extern const char* const drawMsgGuiLinkStart;
	extern const char* const drawMsgGuiLinkStop;

#endif

