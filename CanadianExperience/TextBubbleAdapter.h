/**
 * \file TextBubbleAdapter.h
 *
 * \author Cameron Merrill
 *
 * \brief 
 */

#pragma once
#include "Drawable.h"
#include "TextBubble.h"
#include "AnimChannelPoint.h"
#include "AnimChannelText.h"
#include "TextBubbleDlg.h"


/**
 * \brief class that encapsulates a text bubble
 */
class CTextBubbleAdapter : public CDrawable
{
public:
	CTextBubbleAdapter::CTextBubbleAdapter(const std::wstring &name);

	~CTextBubbleAdapter();
	/** \brief Default constructor disabled */
	CTextBubbleAdapter() = delete;
	/** \brief Copy constructor disabled */
	CTextBubbleAdapter(const CTextBubbleAdapter &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CTextBubbleAdapter &) = delete;
	/// \brief Getter for movable status \returns always true for this class
	bool CTextBubbleAdapter::IsMovable() { return true; }
	virtual void Draw(Gdiplus::Graphics *graphics);
	virtual bool HitTest(Gdiplus::Point pos);

	/// \brief Setter for Text Bubble's Text \param content we are setting to
	void SetContent(std::wstring content) { mTextBubble.SetText(content); }
	/// \brief Getter for content \returns mTextBubbleContent
	std::wstring GetContent() { return mTextBubble.GetText(); }


	virtual void SetTimeline(CTimeline *timeline);
	void SetKeyframe();
	void GetKeyframe();
	void CTextBubbleAdapter::SetActor(CActor *actor);
	/// \brief Getter for position channel \returns mChannel point channel
	CAnimChannelPoint *GetPositionChannel() { return &mChannel; }
	/// \brief Getter for text channel \returns mTextChannel text channel
	CAnimChannelText *GetTextChannel() { return &mTextChannel; }

	/// \brief Getter for mirror status \returns mMirror
	bool GetMirror() { return mTextBubble.GetMirror(); }
	/// \brief Setter for mirror status \param status we are setting to
	void SetMirror(bool status) { mTextBubble.SetMirrored(status); }
	void CTextBubbleAdapter::SetDialogTextBox(CTextBubbleDlg &dlg);


private:
	CTextBubble mTextBubble; ///<Our text bubble that we are encapsulating
	CAnimChannelText mTextChannel; ///<text channel for the text bubble's content
	CAnimChannelPoint mChannel; ///<point channel for position channel
	
};

