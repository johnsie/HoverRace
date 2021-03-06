// FreeElementBase.cpp
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

#include "StdAfx.h"

#include "FreeElementBase.h"

namespace HoverRace {
namespace ObjFacTools {

FreeElementBase::FreeElementBase(const HoverRace::Util::ObjectFromFactoryId & pId) :
	HoverRace::Model::FreeElement(pId)
{
	// The task of initialising the data members is done by the superclass
	mActor = NULL;
	mCurrentSequence = 0;
	mCurrentFrame = 0;

}

FreeElementBase::~FreeElementBase()
{
}

void FreeElementBase::Render(HoverRace::VideoServices::Viewport3D *pDest, MR_SimulationTime /*pTime */ )
{
	// Compute the required rotation matrix
	HoverRace::VideoServices::PositionMatrix lMatrix;

	if(pDest->ComputePositionMatrix(lMatrix, mPosition, mOrientation, 1000 /* TODO Object ray must be precomputed at compilation */ )) {
		mActor->Draw(pDest, lMatrix, mCurrentSequence, mCurrentFrame);
	}
}

}  // namespace ObjFacTools
}  // namespace HoverRace
