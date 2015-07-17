/**
 * \file AnimChannelText.h
 *
 * \author Cameron Merrill
 *
 * \brief Class for a Text Channel
 */

#pragma once
#include "AnimChannel.h"

/**
 * \brief Channel class for Text, extension of CAnimChannel
 */
class CAnimChannelText : public CAnimChannel
{
public:
	CAnimChannelText();
	virtual ~CAnimChannelText();
	/// \brief Getter for text \returns Channel Text
	std::wstring GetText() { return mText; }
	/**
	* \brief class for text keyframes, holds text and mirror status
	*/
	class KeyframeText : public Keyframe
	{
	public:
		/** \brief Constructor
		* \param channel The channel we are for
		* \param str The animation text for the keyframe 
		* \param mirror the mirror status for the keyframe 
		*/
		KeyframeText(CAnimChannelText *channel, std::wstring str, bool mirror) :
			Keyframe(channel), mChannel(channel), mText(str), mMirror(mirror) {}

		/** \brief Default constructor disabled */
		KeyframeText() = delete;
		/** \brief Copy constructor disabled */
		KeyframeText(const KeyframeText &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const KeyframeText &) = delete;

		/// \brief The keyframe text
		/// \return The keyframe text
		std::wstring GetText() { return mText; }
		/// \brief Getter for keyframe mirror status
		/// \return mMirror status
		bool GetMirror() { return mMirror; }

		/** \brief Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** \brief Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** \brief Use this keyframe as the angle */
		virtual void UseOnly() override { mChannel->mText = mText; mChannel->mMirror = mMirror; }

		virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);
	private:
		/// The keyframe point
		std::wstring mText = L"";
		/// The channel this keyframe is associated with
		CAnimChannelText *mChannel;
		/// Mirror for this keyframe
		bool mMirror;
	};
	void SetKeyframe(std::wstring text, bool status);
	/// \brief Tween function for text channel \param t amount we are adjusting by
	void Tween(double t);
	/// \brief Getter for Mirror \returns mMirror mirror status
	bool GetMirror() { return mMirror; }
protected:
	virtual void XmlLoadKeyframe(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
private:
	std::wstring mText; ///<text for this channel
	bool mMirror; ///< mirror status for this channel
	/// The first angle keyframe
	KeyframeText *mKeyframe1 = nullptr;

	/// The second angle keyframe
	KeyframeText *mKeyframe2 = nullptr;
};

