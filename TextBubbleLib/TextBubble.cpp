/**
 * \file TextBubble.cpp
 *
 * \author Charles B. Owen
 */

#include "stdafx.h"
#include "TextBubble.h"

#include  <sstream>

#include <iostream>

using namespace std;
using namespace Gdiplus;

//! The maximum width in pixels for a line of text
const int MaxWidth = 200;

//! Locations of the text area of the bubble - left
const double Left = 14.0 / 256.0;

//! Right location of the text bubble area
const double Right = 242.0 / 256.0;

//! Top location of the text bubble area
const double Top = 16.0 / 128.0;

//! Bottom location of the text bubble area
const double Bottom = 88.0 / 128.0;

//! Location of the tip of the bubble: x
const double TipX = 106.0 / 256.0;

//! Location of the tip of the bubble: y
const double TipY = 125.0 / 128.0;


/*! \brief Constructor for our text bubble class.  
 *
 * Loads the image file and creates a font to use.
 */
CTextBubble::CTextBubble()
{
    mBubble = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"TextBubbleLib/cartoon_bubble.png"));
    if (mBubble->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/cartoon_bubble.png");
    }

    // Create the font we will use
    FontFamily fontFamily(L"Arial");
    mFont = make_unique<Gdiplus::Font>(&fontFamily, 16.0f, 0, Unit::UnitPixel);
}


/*! \brief Destructor...
*/
CTextBubble::~CTextBubble()
{
}



/*! \brief Draw the text bubble.
* \param graphics The device context to draw on
*/
void CTextBubble::DrawMe(Gdiplus::Graphics *graphics)
{
    // Anytime the string is updated, we have to recompute the lines on the screen
    if (mNewString)
    {
        NewString(graphics);
    }

    // An empty text bubble is not drawn at all.
    if (mSplitText.empty())
        return;


    // Determine where the bitmap will appear on the screen.
    int x = int(mPosition.X - (mBubbleWid * (mMirror ? 1 - TipX : TipX)));
    int y = int(mPosition.Y - (mBubbleHit * TipY));

    if (mMirror)
    {
        graphics->DrawImage(mBubble.get(), x + mBubbleWid, y, -mBubbleWid, mBubbleHit);
    }
    else
    {
        graphics->DrawImage(mBubble.get(), x, y, mBubbleWid, mBubbleHit);
    }

    int ty = int(y + Top * mBubbleHit);
    for (auto line : mSplitText)
    {
        RectF rect;
        graphics->MeasureString(line.c_str(), -1, mFont.get(), PointF(0, 0), &rect);
        int w = (int)rect.Width;
        int h = (int)rect.Height;

        SolidBrush brush(Color::White);
        graphics->DrawString(line.c_str(), -1, mFont.get(), PointF(float(x + mBubbleWid / 2 - w / 2), (float)ty), &brush);

        ty += h;
    }

}


/*! \brief Determines if a point is inside the text bubble.
* \param x X location to test
* \param y Y location to test
* \returns true if point is inside the text bubble.
*/
bool CTextBubble::IsPointInside(int x, int y)
{
    // An empty text bubble is not drawn at all.
    if (mSplitText.empty())
        return false;

    // Determine where the bitmap will appear on the screen.
    x -= int(mPosition.X - (mBubbleWid * (mMirror ? 1 - TipX : TipX)));
    y -= int(mPosition.Y - (mBubbleHit * TipY));

    if (x < 0 || y < 0 || x >= mBubbleWid || y >= mBubbleHit)
        return false;

    // Test to see if x, y are in the drawn part of the image
    auto format = mBubble->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // Determine the location on the image prior to scaling
        int testX = x * mBubble->GetWidth() / mBubbleWid;
        int testY = y * mBubble->GetHeight() / mBubbleHit;

        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mBubble->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;
    }
}



/*! \brief Handle when we get a new string.
*
* We have to break it into lines of no more than
* a defined length in pixels and make the text bubble
* the correct size.
* \param graphics The graphics device we draw on
*/
void CTextBubble::NewString(Gdiplus::Graphics *graphics)
{
    mNewString = false;
    mSplitText.clear();


    // A stream to read the text from
    wstringstream str(mText);

    // A string to write text into
    wstring line;

    int hit = 0;
    int maxwid = 1;

    //
    // Pull one word at a time and add to a line
    // until we are too wide.
    //

    while (!str.eof())
    {
        wstring word;
        str >> word;

        // Is our line empty? If so, just add the word
        if (line.empty())
        {
            line = word.c_str();
        }
        else
        {
            // The line is not empty. See how long this would
            // make the line in pixels.
            wstring line2 = line + L" " + word.c_str();
            RectF rect;
            graphics->MeasureString(line2.c_str(), -1, mFont.get(), PointF(0, 0), &rect);
           // dc->GetTextExtent(line2, &w, &h);
            if (rect.Width <= MaxWidth)
            {
                line = line2;
            }
            else
            {
                // Add to our height and determine the maximum width
                graphics->MeasureString(line.c_str(), -1, mFont.get(), PointF(0, 0), &rect);
                hit += (int)rect.Height;
                if (rect.Width > maxwid)
                    maxwid = (int)rect.Width;

                mSplitText.push_back(line);
                line = word.c_str();
            }
        }
    }

    // Any remaining text left in line
    if (!line.empty())
    {
        RectF rect;
        graphics->MeasureString(line.c_str(), -1, mFont.get(), PointF(0, 0), &rect);
        hit += (int)rect.Height;
        if (rect.Width > maxwid)
            maxwid = (int)rect.Width;

        mSplitText.push_back(line);
    }

    if (mSplitText.empty())
    {
        return;
    }

    // What size does the image need to be?
    mBubbleWid = int(double(maxwid / (Right - Left)));
    mBubbleHit = int(double(hit / (Bottom - Top)));
}

/*! \brief Set the text we draw in the text bubble.
* \param str The new string to set as the text
*/
void CTextBubble::SetText(const std::wstring &str)
{
    mText = str;
    mNewString = true;
}


