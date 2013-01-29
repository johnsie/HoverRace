// TrackCompiler.h
//
// Copyright (c) 2013 Michael Imamura.
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

#pragma once

#include "../Util/MR_Types.h"
#include "../Util/OS.h"
#include "TrackCompilationLog.h"

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
	}
}

namespace HoverRace {
namespace MazeCompiler {

/**
 * Compiles the standard textual track format (usually generated by HoverCAD).
 * @author Michael Imamura
 */
class MR_DllDeclare TrackCompiler
{
	public:
		TrackCompiler(const TrackCompilationLogPtr &log, const Util::OS::path_t &outputFilename);
		~TrackCompiler() {}

	public:
		void Compile(const Util::OS::path_t &inputFilename) const;
		void Compile(std::istream &in) const;

	private:
		void CreateHeader(std::istream &in, Parcel::ObjStream &pDestination) const;
		static void AddBackgroundImage(std::istream &in, Parcel::ObjStream &pDestination);
		
		static std::string FormatStr(const char *pSrc);

		static MR_UInt8 *PCXRead(FILE *pFile, int &pXRes, int &pYRes);
		static MR_UInt8 *LoadBitmap(FILE *pFile);
		static MR_UInt8 *LoadPalette(FILE *pFile);

	private:
		Util::OS::path_t outputFilename;
		TrackCompilationLogPtr log;
};

}  // namespace MazeCompiler
}  // namespace HoverRace

#undef MR_DllDeclare
