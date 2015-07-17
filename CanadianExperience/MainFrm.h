/**
 * \file MainFrm.h
 *
 * \author 
 *
 * \brief The program main frame.
 */

#pragma once
#include "ViewEdit.h"
#include "ViewTimeline.h"
#include "ViewActors.h"

#include <memory>

class CPicture;

/** \brief Program main frame */
class CMainFrame : public CFrameWndEx
{
	
public:
	CMainFrame();

    /** \brief Enumerations for the possible manipulation modes */
    enum MotionModes { Move, Rotate };

    /** \brief The selected manipulation mode 
     * \returns Currently selected manipulation mode */
    MotionModes GetMode() const { return mMode; }
	void ChangeText(std::wstring str);


protected: 
	DECLARE_DYNAMIC(CMainFrame)

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCToolBar     m_wndToolBar;
	CMFCStatusBar   m_wndStatusBar;
	CSplitterWnd    mWndSplitter;

private:
    void Initialize();

    /// The timeline window
    CViewTimeline  *mViewTimeline;

    /// The editing window
    CViewEdit      *mViewEdit;

    /// The actors window
    CViewActors    *mViewActors;

    /// The current manipulation mode
    MotionModes mMode = Move;

    /// The picture object we are viewing/editing
    std::shared_ptr<CPicture> mPicture;
	long long mLastTime;    ///< Last time we read the timer
	double mTimeFreq;       ///< Rate the timer updates

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnEditMove();
    afx_msg void OnUpdateEditMove(CCmdUI *pCmdUI);
    afx_msg void OnEditRotate();
    afx_msg void OnUpdateEditRotate(CCmdUI *pCmdUI);
    afx_msg void OnEditTimelineproperties();
	afx_msg void OnEditEditHarold();
	afx_msg void OnEditEditSparty();

};


