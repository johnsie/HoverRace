
// TrackList.h
// Sorted list of track headers.
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

#include "TrackEntry.h"

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
		class TrackBundle;
		typedef std::shared_ptr<TrackBundle> TrackBundlePtr;
	}
}

namespace HoverRace {
namespace Model {

class MR_DllDeclare TrackList
{
	public:
		TrackList();

	public:
		void Reload(Parcel::TrackBundlePtr trackBundle);

		/** Clear the list of available tracks. */
		void Clear() { tracks.clear(); }
		bool IsEmpty() const { return tracks.empty(); }

		TrackEntryPtr &operator[](int i) { return tracks[i]; }

	private:
		typedef std::vector<TrackEntryPtr> tracks_t;
	public:
		typedef tracks_t::iterator iterator;
		typedef tracks_t::const_iterator const_iterator;
		typedef TrackEntryPtr value_type;

		iterator begin() { return tracks.begin(); }
		iterator end() { return tracks.end(); }
		const_iterator begin() const { return tracks.begin(); }
		const_iterator end() const { return tracks.end(); }

	private:
		tracks_t tracks;
};

}  // namespace Model
}  // namespace HoverRace

#undef MR_DllDeclare
