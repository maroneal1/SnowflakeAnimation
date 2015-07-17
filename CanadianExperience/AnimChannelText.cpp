#include "stdafx.h"
#include "AnimChannelText.h"
#include "Timeline.h"

using namespace std;

CAnimChannelText::CAnimChannelText()
{
}


CAnimChannelText::~CAnimChannelText()
{
}

/**
* \brief Set a keyframe
*
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
* \param text The text for the keyframe
* \param status the status of mirror
*/
void CAnimChannelText::SetKeyframe(std::wstring text, bool status)
{
	// Create a keyframe of the appropriate type
	// Telling it this channel and the angle
	shared_ptr<KeyframeText> keyframe = make_shared<KeyframeText>(this, text, status);

	// Insert it into the collection
	InsertKeyframe(keyframe);
}

/** \brief Save this keyframe to an XML node
* \param node The node we are going to be a child of
* \returns Allocated XML node.
*/
std::shared_ptr<xmlnode::CXmlNode> CAnimChannelText::KeyframeText::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CAnimChannel::Keyframe::XmlSave(node);
	itemNode->SetAttribute(L"text", mText);
	if (mMirror)
	{
		itemNode->SetAttribute(L"mirror", L"true");
	}
	else
	{
		itemNode->SetAttribute(L"mirror", L"false");
	}

	return itemNode;
}



/**
* \brief Handle loading this channel's keyframe type
* \param node keyframe tag node
*/
void CAnimChannelText::XmlLoadKeyframe(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	std::wstring text = node->GetAttributeValue(L"text", L"hello");
	bool mirror = false;
	std::wstring mirrorStatus = L"false";
	if (node->GetAttributeValue(L"mirror", mirrorStatus) != mirrorStatus)
	{
		mirror = true;
	}
	SetKeyframe(text, mirror);

}
void CAnimChannelText::Tween(double t)
{
	mText = mKeyframe1->GetText();
	mMirror = mKeyframe1->GetMirror();
}
