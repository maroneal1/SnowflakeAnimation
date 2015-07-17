/**
 * \file Snowfall.h
 *
 * \author Cameron Miles Merrill
 *
 * \brief Handler class for Snowfall
 */

#pragma once
#include <vector>
#include <memory>
#include "Snowflake.h"
#include "SnowflakeLinkedList.h"


/**
 * \brief Class that handles operations involving snowfall
 */
class CSnowfall
{
public:
	CSnowfall();
	virtual ~CSnowfall();
	void CSnowfall::AddSnowflake(std::shared_ptr<CSnowflake> snowflake);
	void CSnowfall::Update(double elapsed);
	void CSnowfall::Draw(Gdiplus::Graphics *graphics);

private:
	/// Singly Linked list for Active Snowflakes
	std::shared_ptr<CSnowflakeLinkedList> mActiveSnowflakes;
	/// Singly linked list for inactive snowflakes
	std::shared_ptr<CSnowflakeLinkedList> mInactiveSnowflakes;
};

