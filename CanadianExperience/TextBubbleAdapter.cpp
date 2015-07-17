#include "stdafx.h"
#include "TextBubbleAdapter.h"
#include "Timeline.h"
#include "Actor.h"
#include "TextBubbleDlg.h"


/**
 * \brief deconstructor
 */
CTextBubbleAdapter::~CTextBubbleAdapter()
{
}


/**
 * \brief Draw function for text bubble
 * \param graphics we drawing with
 */
void CTextBubbleAdapter::Draw(Gdiplus::Graphics *graphics)
{
	//Gdiplus::Point pos = GetPosition();
	//mTextBubble.SetBubblePosition(pos.X, pos.Y);
	mTextBubble.SetBubblePosition(mPlacedPosition.X, mPlacedPosition.Y);  ///< !!!!!
	mTextBubble.DrawMe(graphics);
}


/**
 * \brief constructor
 * \param name for drawable
 */
CTextBubbleAdapter::CTextBubbleAdapter(const std::wstring &name) : CDrawable(name)
{

}


/**
 * \brief hit test for text bubble adapter
 * \param pos we are testing
 * \returns true if inside 
 */
bool CTextBubbleAdapter::HitTest(Gdiplus::Point pos)
{
	return mTextBubble.IsPointInside(pos.X, pos.Y);
}

/** \brief Set a keyframe on an actor.
*/
void CTextBubbleAdapter::SetKeyframe()
{
	mChannel.SetKeyframe(GetPosition());
	mTextChannel.SetKeyframe(mTextBubble.GetText(), mTextBubble.GetMirror());
}

/** brief Get a keyframe for an actor.
*/
void CTextBubbleAdapter::GetKeyframe()
{
	if (mChannel.IsValid())
	{
		SetPosition(mChannel.GetPoint());
	}
	if (mTextChannel.IsValid())
	{
		SetContent(mTextChannel.GetText());
		SetMirror(mTextChannel.GetMirror());
	}

}

/**
* \brief Set the timeline. The tells the channel the timeline
* \param timeline Timeline to set
*/
void CTextBubbleAdapter::SetTimeline(CTimeline *timeline)
{
	CDrawable::SetTimeline(timeline);

	timeline->AddChannel(&mChannel);
	timeline->AddChannel(&mTextChannel);
}

/**
 * \brief setter for our actor
 * \param actor we are setting to
 */
void CTextBubbleAdapter::SetActor(CActor *actor)
{
	CDrawable::SetActor(actor);

	mTextChannel.SetName(actor->GetName() + L":" + GetName() + L":text");
	mChannel.SetName(actor->GetName() + L":" + GetName() + L":position");
}

/**
 * \brief class for setting and getting the dialog text box
 */
void CTextBubbleAdapter::SetDialogTextBox(CTextBubbleDlg &dlg)
{
	dlg.SetTextBubble(&mTextBubble);
}