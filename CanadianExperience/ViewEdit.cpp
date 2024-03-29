/**
 * \file ViewEdit.cpp
 *
 * \author Charles B. Owen
 */


#include "stdafx.h"
#include "CanadianExperience.h"
#include "ViewEdit.h"

#include "DoubleBufferDC.h"
#include "MainFrm.h"
#include "Picture.h"
#include "Actor.h"

/// A scaling factor, converts mouse motion to rotation in radians
const double RotationScaling = 0.02;

using namespace std;
using namespace Gdiplus;

IMPLEMENT_DYNCREATE(CViewEdit, CScrollView)


BEGIN_MESSAGE_MAP(CViewEdit, CScrollView)
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

/** \brief Constructor */
CViewEdit::CViewEdit()
{

}

/** \brief Destructor */
CViewEdit::~CViewEdit()
{
}

/** \brief Handle initial update of the window */
void CViewEdit::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal(800, 600);
	SetScrollSizes(MM_TEXT, sizeTotal);
}


/** \brief Drawing of the window 
 * \param pDC the device context to draw on */
void CViewEdit::OnDraw(CDC* pDC)
{
    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    Gdiplus::Size size = GetPicture()->GetSize();
    SetScrollSizes(MM_TEXT, CSize(size.Width, size.Height));

    GetPicture()->Draw(&graphics);
}

/** \brief Force an update of this window when the picture changes.
*/
void CViewEdit::UpdateObserver()
{
    Invalidate();
   // UpdateWindow();
}

/** \brief Erase the background
*
* This is disabled to eliminate flicker
* \param pDC Device context
* \returns FALSE */
BOOL CViewEdit::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}



/**
 * \brief Handle a left button click
 * \param nFlags Flags that indicate status of the mouse buttons 
 * \param point The x,y location for the mouse click
 */
void CViewEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
    // Convert mouse coordinates to logical coordinates
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&point);

    mLastMouse = Gdiplus::Point(point.x, point.y);

    //
    // Did we hit anything?
    //

    std::shared_ptr<CActor> hitActor;
    std::shared_ptr<CDrawable> hitDrawable;
    for (auto actor : *GetPicture())
    {
        // Note: We do not exit when we get the first hit, since
        // we are looking at these in drawing order. Instead, we
        // keep the last hit.
        std::shared_ptr<CDrawable> drawable = actor->HitTest(Point(point.x, point.y));
        if (drawable != nullptr)
        {
            hitActor = actor;
            hitDrawable = drawable;
        }
    }

    // If we hit something determine what we do with it based on the
    // current mode.
    if (hitActor != NULL)
    {
        mSelectedActor = hitActor;
        mSelectedDrawable = hitDrawable;
    }

    __super::OnLButtonDown(nFlags, point);
}


/**
 * \brief Handle mouse movement
 * \param nFlags Flags that indicate status of the mouse buttons 
 * \param point The x,y location for the mouse
 */
/**
* \brief Handle mouse movement
* \param nFlags Flags that indicate status of the mouse buttons
* \param point The x,y location for the mouse
*/
void CViewEdit::OnMouseMove(UINT nFlags, CPoint point)
{
    // Convert mouse coordinates to logical coordinates
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&point);
    Gdiplus::Point newMouse(point.x, point.y);
    Gdiplus::Point delta = newMouse - mLastMouse;
    mLastMouse = newMouse;

    if (nFlags & MK_LBUTTON)
    {
        switch (mMainFrame->GetMode())
        {
        case CMainFrame::Move:
            if (mSelectedDrawable != nullptr)
            {
                if (mSelectedDrawable->IsMovable())
                {
                    mSelectedDrawable->Move(delta);
                }
                else
                {
                    mSelectedActor->SetPosition(mSelectedActor->GetPosition() + delta);
                }
                GetPicture()->UpdateObservers();
            }
            break;

        case CMainFrame::Rotate:
            if (mSelectedDrawable != nullptr)
            {
                mSelectedDrawable->SetRotation(mSelectedDrawable->GetRotation() + delta.Y * RotationScaling);
                GetPicture()->UpdateObservers();
            }
            break;

        default:
            break;
        }

    }
    else
    {
        mSelectedDrawable = nullptr;
        mSelectedActor = nullptr;
    }

    __super::OnMouseMove(nFlags, point);
}
