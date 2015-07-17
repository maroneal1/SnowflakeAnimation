/**
 * \file TextBubbleDlg.h
 *
 * \author Charles B. Owen
 *
 * \brief A dialog box class for editing the text bubble contents
 */

#pragma once

#include "resource.h"
#include "TextBubble.h"


/**
 * \brief A dialog box class for editing the text bubble contents
 *
 * To use this class, given a pointer pTextBubble to a CTextBubble
 * object, use the following code:
 *
 * \code
 *     // Create the dialog box object
 *     CTextBubbleDlg dlg;
 *
 *     // Tell it about the text bubble
 *     dlg.SetTextBubble(pTextBubble);
 *     if (dlg.DoModal() == IDOK)
 *     {
 *         // Take the changes to the text bubble
 *         dlg.Take();
 *     }
 * \endcode
 *
 * Your code will probably use a different value than pTextBubble. If
 * the text bubble is a member variable, it might be &mTextBubble, for
 * example.
 */
class TBEXPORT CTextBubbleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextBubbleDlg)

public:
	CTextBubbleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTextBubbleDlg();

    void SetTextBubble(CTextBubble *bubble);
    void Take();

// Dialog Data
	enum { IDD = IDD_TEXTBUBBLEDLG };

protected:
    /// \cond
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    /// \endcond

	DECLARE_MESSAGE_MAP()

private:
    CTextBubble *mTextBubble = nullptr;     ///< The text bubble we are editing
    CString mText;
    BOOL mMirror;
};
