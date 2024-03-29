/**
 * \file ViewTop.h
 *
 * \author Charles B. Owen
 *
 * \brief Class for the top of the screen view.
 *
 * You should not have to change this file.
 */

#pragma once

#include "ViewEdit.h"
#include "ViewActors.h"

/**
 * \brief Top of the screen view.
 *
 * This class creates a view that contains a splitter so we can split
 * the top window horizontally.
 */
class CViewTop : public CView
{
	DECLARE_DYNCREATE(CViewTop)

protected:
	CViewTop();           // protected constructor used by dynamic creation
	virtual ~CViewTop();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

    /** \brief Get the ViewEdit window 
     * \returns Pointer to ViewEdit window */
    CViewEdit *GetViewEdit() { return (CViewEdit *)mWndSplitter.GetPane(0, 1); }

    /** \brief Get the ViewActors window
    * \returns Pointer to ViewActors window */
    CViewActors *GetViewActors() { return (CViewActors *)mWndSplitter.GetPane(0, 0); }

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
    /// The nested splitter window
    CSplitterWnd mWndSplitter;
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
};


