
// ResourceLib.h
// Loadable resource manager.
//
// Copyright (c) 2010 Michael Imamura.
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

#pragma once

#include <map>

#include "../Util/OS.h"
#include "ResActor.h"
#include "ResSprite.h"
#include "ResSound.h"

#ifdef _WIN32
#	ifdef MR_ENGINE
#		define MR_DllDeclare   __declspec( dllexport )
#	else
#		define MR_DllDeclare   __declspec( dllimport )
#	endif
#else
#	define MR_DllDeclare
#endif

namespace HoverRace {
	namespace Parcel {
		class ObjStream;
		class RecordFile;
	}
}

namespace HoverRace {
namespace ObjFacTools {

class MR_DllDeclare ResourceLib
{
	protected:
		ResourceLib() { }
	public:
		ResourceLib(const Util::OS::path_t &filename);
		~ResourceLib();

	public:
		ResBitmap * GetBitmap(int id);
		const ResActor *GetActor(int id);
		const ResSprite *GetSprite(int id);
		const ResShortSound *GetShortSound(int id);
		const ResContinuousSound *GetContinuousSound(int id);

	protected:
		Parcel::RecordFile *recordFile;

		typedef std::map<int, ResBitmap*> bitmaps_t;
		bitmaps_t bitmaps;
		typedef std::map<int, ResActor*> actors_t;
		actors_t actors;
		typedef std::map<int, ResSprite*> sprites_t;
		sprites_t sprites;
		typedef std::map<int, ResShortSound*> shortSounds_t;
		shortSounds_t shortSounds;
		typedef std::map<int, ResContinuousSound*> continuousSounds_t;
		continuousSounds_t continuousSounds;

	protected:
		static const MR_UInt32 FILE_MAGIC = 12345;
};

}  // namespace HoverRace
}  // namespace ObjFacTools

#undef MR_DllDeclare
