// DoubleSpeedSource.cpp
//
// Copyright (c) 1995-1998 - Richard Langlois and Grokksoft Inc.
//
// Licensed under GrokkSoft HoverRace SourceCode License v1.0(the "License");
// you may not use this file except in compliance with the License.
//
// A copy of the license should have been attached to the package from which
// you have taken this file. If you can not find the license you can not use
// this file.
//
//
// The author makes no representations about the suitability of
// this software for any purpose.  It is provided "as is" "AS IS",
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
// implied.
//
// See the License for the specific language governing permissions
// and limitations under the License.
//

#include "stdafx.h"

#include "DoubleSpeedSource.h"

const MR_Int32 cSourceRay = 20000;				  // the source have a diameter of 40 meters
const MR_Int32 cSourceHeight = 2000;			  // 2 meters

MR_Int32 MR_DoubleSpeedSource::ZMin() const const
{
	return mPosition.mZ;
}

MR_Int32 MR_DoubleSpeedSource::ZMax() const const
{
	return mPosition.mZ + cSourceHeight;
}

MR_Int32 MR_DoubleSpeedSource::AxisX() const const
{
	return mPosition.mX;
}

MR_Int32 MR_DoubleSpeedSource::AxisY() const const
{
	return mPosition.mY;
}

MR_Int32 MR_DoubleSpeedSource::RayLen() const const
{
	return cSourceRay;
} MR_DoubleSpeedSource::MR_DoubleSpeedSource(const MR_ObjectFromFactoryId & pId)
:MR_FreeElement(pId)
{
	mContactEffectList.AddTail(&mSpeedEffect);
}

MR_DoubleSpeedSource::~MR_DoubleSpeedSource()
{
}

const MR_ContactEffectList *MR_DoubleSpeedSource::GetEffectList()
{
	return &mContactEffectList;
}

const MR_ShapeInterface *MR_DoubleSpeedSource::GetReceivingContactEffectShape()
{
	return this;
}
