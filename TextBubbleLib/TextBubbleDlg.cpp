/**
 * \file TextBubbleDlg.cpp
 *
 * \author Charles B. Owen
 */

#include "stdafx.h"
#include "TextBubbleDlg.h"
#include "afxdialogex.h"


// CTextBubbleDlg dialog

IMPLEMENT_DYNAMIC(CTextBubbleDlg, CDialogEx)


/**
 * \brief Constructor
 * \param pParent Optional parent window
 */
CTextBubbleDlg::CTextBubbleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextBubbleDlg::IDD, pParent)
    , mText(_T(""))
    , mMirror(FALSE)
{

}


/**
 * \brief Destructor
 */
CTextBubbleDlg::~CTextBubbleDlg()
{
}

/// \cond
void CTextBubbleDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDITTBTEXT, mText);
    DDX_Check(pDX, IDC_CHECKTBMIRROR, mMirror);
}
/// \endcond

BEGIN_MESSAGE_MAP(CTextBubbleDlg, CDialogEx)
END_MESSAGE_MAP()

/** \brief Set the CTextBubble object we are editing
 * \param bubble The CTextBubble object */
void CTextBubbleDlg::SetTextBubble(CTextBubble *bubble)
{
    mTextBubble = bubble;
    mText = mTextBubble->GetText().c_str();
    mMirror = mTextBubble->IsMirrored();
}

/** \brief Take the changes into the text bubble object */
void CTextBubbleDlg::Take()
{
    mTextBubble->SetText((LPCWSTR)mText);
    mTextBubble->SetMirrored(mMirror ? true : false);
}