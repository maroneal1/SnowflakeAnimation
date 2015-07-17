/**
 * \file Snowfall.cpp
 *
 * \author Cameron Miles Merrill
 */

#include "stdafx.h"
#include "Snowfall.h"
#include "Snowflake.h"
#include <memory>

using namespace std;
using namespace Gdiplus;
///Max value for amount snowflakes to be emitted
const double MaxEmission = 10;


/**
 * \brief brief constructor, create the active and inactive lists
 */
CSnowfall::CSnowfall()
{
	mActiveSnowflakes = std::make_shared < CSnowflakeLinkedList >();
	mInactiveSnowflakes = std::make_shared < CSnowflakeLinkedList >();
}


/**
 * \brief destructor
 */
CSnowfall::~CSnowfall()
{
}


/**
 * \brief Add snowflake to the system
 * \param snowflake we are adding
 */
void CSnowfall::AddSnowflake(std::shared_ptr<CSnowflake> snowflake)
{
	mInactiveSnowflakes->Add(snowflake);
}


/**
 * \brief Draw the system
 * \param graphics we are drawing with
 */
void CSnowfall::Draw(Gdiplus::Graphics *graphics)
{
	SolidBrush brush(Color::White);
	if (mActiveSnowflakes->GetHead() != nullptr)
	{
		auto snowflake = mActiveSnowflakes->GetHead();
		while (snowflake->Next() != nullptr)
		{
			snowflake->Draw(graphics, brush);
			snowflake = snowflake->Next();
		}
		snowflake->Draw(graphics, brush);
	}
}


/**
 * \brief Update the snowfall system
 * \param elapsed time since last draw
 */
void CSnowfall::Update(double elapsed)
{
	// Add a random amount of snowflakes to the active list from inactive
	int emissionRate = (int) round(((double) rand() / RAND_MAX) * MaxEmission);
	for (int i = 0; i < emissionRate; i++)
	{
		// make sure we aren't trying to add nullptrptr
		if (mInactiveSnowflakes->GetHead() != nullptr)
		{
			mActiveSnowflakes->Add(mInactiveSnowflakes->pop());
		}
	}

	

	if (mActiveSnowflakes->GetHead() != nullptr)
	{
		while (mActiveSnowflakes->GetHead()->IsBottom())
		{
			//Check if the first value in the list is out of bounds
			//adjust as necessary
			auto snowflake = mActiveSnowflakes->GetHead();
			mActiveSnowflakes->SetStart(snowflake->Next());
			mInactiveSnowflakes->Add(snowflake);
		}

		// dont perform operations on nullptr
		if (mActiveSnowflakes->GetHead() != nullptr)
		{
			auto snowflake = mActiveSnowflakes->GetHead();
			// iterate over the list
			while (snowflake->Next() != nullptr)
			{
				snowflake->Update(elapsed);
				if (snowflake->Next()->IsBottom())
				{
					//if next snowflake in list is bottom, remove it
					auto removedSnowflake = snowflake->Next();
					// set this snowflake->next to next()->next()
					snowflake->SetNext(snowflake->Next()->Next());
					mInactiveSnowflakes->Add(removedSnowflake);
				}
				if (snowflake->Next() != nullptr)
				{
					snowflake = snowflake->Next();
				}
			}
			snowflake->Update(elapsed);
		}
	}
}

