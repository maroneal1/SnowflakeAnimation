/**
 * \file ViewActors.cpp
 *
 * \author Charles B. Owen
 */

#include "stdafx.h"
#include "CanadianExperience.h"
#include "ViewActors.h"

#include "DoubleBufferDC.h"
#include "MainFrm.h"
#include "Picture.h"
#include "Actor.h"

using namespace std;
using namespace Gdiplus;

/// Drawables indentation
const int Indent = 10;

/// \cond
IMPLEMENT_DYNCREATE(CViewActors, CScrollView)

BEGIN_MESSAGE_MAP(CViewActors, CScrollView)
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
/// \endcond

/** \brief Constructor */
CViewActors::CViewActors()
{

}

/** \brief Destructor */
CViewActors::~CViewActors()
{
}


/** \brief Handle the initial update for this window */
void CViewActors::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    CSize sizeTotal(0, 100);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** \brief Draw this window
* \param pDC Device context */
void CViewActors::OnDraw(CDC* pDC)
{
    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    Pen pen(Color(0, 128, 0), 1);
    graphics.DrawRectangle(&pen, 10, 150, 100, 100);

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 16);

    SolidBrush brush(Color(0, 0, 0));
    graphics.DrawString(L"Actors!",  // String to draw
        -1,         // String length, -1 means it figures it out on its own
        &font,      // The font to use
        PointF(15, 170),   // Where to draw
        &brush);    // The brush to draw the text with

    CString time = CTime::GetCurrentTime().Format("%H:%M:%S");
    graphics.DrawString(time,  // String to draw
        -1,         // String length, -1 means it figures it out on its own
        &font,      // The font to use
        PointF(15, 200),   // Where to draw
        &brush);    // The brush to draw the text with


    //CDoubleBufferDC dbDC(pDC);

    //Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    //FontFamily fontFamily(L"Arial");
    //Gdiplus::Font font(&fontFamily, 12);
    //SolidBrush brush(Color(0, 0, 0));
    //SolidBrush green(Color(0, 128, 0));

    //// Determine the text height
    //RectF size;
    //PointF origin(0.0f, 0.0f);
    //graphics.MeasureString(L"TEST", 4, &font, origin, &size);
    //mTextHeight = (int)size.Height;

    //// Y location to draw
    //int y = 0;

    //for (auto actor : *GetPicture())
    //{
    //    graphics.DrawString(actor->GetName().c_str(),  // String to draw
    //        -1,         // String length, -1 means it figures it out on its own
    //        &font,      // The font to use
    //        PointF(0, (float)y),   // Where to draw
    //        &brush);    // The brush to draw the text with

    //    y += mTextHeight;

    //    y += DrawDrawablesNames(&graphics,
    //        actor->GetRoot(), 0, y, &font, &green);
    //}


    //SetScrollSizes(MM_TEXT, CSize(150, y));

}

/** \brief Draw the name of a drawable and the names of all of the
* drawables children.
* \param graphics The graphics device to draw on
* \param drawable Pointer to the drawable to draw
* \param x The x location to draw the text (left to right)
* \param y The y location to draw the text (top to bottom)
* \param font The font to use
* \param brush The brush to use
* \returns The height of all text drawn.
*/
int CViewActors::DrawDrawablesNames(Gdiplus::Graphics *graphics, 
        std::shared_ptr<CDrawable> drawable, int x, int y,
        Gdiplus::Font *font, Gdiplus::Brush *brush)
{
    // Don't draw if no drawable
    if (drawable == nullptr)
    {
        return 0;
    }

    // Keep track of the height of what we are drawing
    int height = 0;

    // Indent 10 pixels from the parent
    x += Indent;

    // Draw the name of the drawable

    graphics->DrawString(drawable->GetName().c_str(),  // String to draw
        -1,         // String length, -1 means it figures it out on its own
        font,      // The font to use
        PointF((float)x, (float)y),   // Where to draw
        brush);    // The brush to draw the text with


    height += mTextHeight;

    for (auto child : *drawable)
    {
        height += DrawDrawablesNames(graphics, child, x, y + height,
            font, brush);
    }

    return height;
}


/** \brief Force an update of this window when the picture changes.
*/
void CViewActors::UpdateObserver()
{
    Invalidate();
	//UpdateWindow();
}


/** \brief Erase the background
*
* This is disabled to eliminate flicker
* \param pDC Device context
* \returns FALSE */
BOOL CViewActors::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}
