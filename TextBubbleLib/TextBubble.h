/** \file TextBubble.h
*
* \brief This class implements a basic text bubble control.
*
* \author Charles B. Owen
* \version 1.00 10-28-2010 Original development in wxWidgets
* \version 2.00 10-28-2014 MFC version
*/

#pragma once

#include <string>
#include <vector>
#include <memory>

/// \cond
#ifdef TEXTBUBBLE_DLL
#define TBEXPORT __declspec( dllexport )
#else
#define TBEXPORT __declspec( dllimport )
#endif
/// \endcond

/*! \brief Basic text bubble support class
*/
class TBEXPORT CTextBubble
{
public:
    CTextBubble();
    virtual ~CTextBubble();

    /** \brief Copy constructor disabled */
    CTextBubble(const CTextBubble &) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CTextBubble &) = delete;

    void DrawMe(Gdiplus::Graphics *graphics);
    bool IsPointInside(int x, int y);

    /** \brief Get the text from the bubble
    * \returns Current bubble text string
    */
    std::wstring GetText() const { return mText; }

    void SetText(const std::wstring &str);

    /** \brief Get the mirror status for the text bubble
    * \returns True if text bubble is mirrored
    */
    bool GetMirror() const { return mMirror; }

    /*! \brief Set the text bubble mirror status
    * \param m Set true if text bubble is mirrored
    */
    void SetMirrored(bool m) { mMirror = m;  mNewString = true; }

    /** \brief Get the text bubble mirror status 
     * \returns true if mirrored */
    bool IsMirrored() { return mMirror;  }

    /** \brief Set the bubble position
    * \param x X location
    * \param y Y location
    */
    void SetBubblePosition(int x, int y) { mPosition = Gdiplus::Point(x, y); }

    /*! \brief Get the bubble X position
    * \returns X position
    */
    int GetX() const { return mPosition.X; }

    /*! \brief Get the bubble Y position
    * \returns Y position
    */
    int GetY() const { return mPosition.Y; }

private:
    void NewString(Gdiplus::Graphics *graphics);

    bool     mMirror = false;       ///< Should we mirror the text box?
    std::wstring mText;             ///< The unadulterated text
    Gdiplus::Point  mPosition= Gdiplus::Point(200, 200);    ///< Position for the tip of the text bubble

    bool     mNewString = true;     ///< Set true when the string changes

    std::unique_ptr<Gdiplus::Bitmap> mBubble; ///< Text bubble image
    int      mBubbleWid = 0;        ///< Width to draw the bubble
    int      mBubbleHit = 0;        ///< Height to draw the bubble

    //! The array of string objects that holds the split text
    std::vector<std::wstring> mSplitText;

    std::unique_ptr<Gdiplus::Font> mFont;   ///< The font we will use
};
