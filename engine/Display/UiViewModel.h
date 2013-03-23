
// UiViewModel.h
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

#pragma once

#include "../Util/MR_Types.h"
#include "Vec.h"
#include "ViewModel.h"

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
namespace Display {

/**
 * Base class for UI (2D) components.
 * @author Michael Imamura
 */
class MR_DllDeclare UiViewModel : public ViewModel
{
	typedef ViewModel SUPER;

	public:
		struct Props
		{
			enum {
				POS,
				ALIGNMENT,
				NEXT_,  ///< First index for subclasses.
			};
		};
		
		struct LayoutFlags
		{
			enum {
				UNSCALED = 0x01,  ///< Don't scale the component to the UI viewport.
				FLOATING = 0x02,  ///< Use absolute (screen-space) coordinates.
			};
		};
		typedef MR_UInt32 layoutFlags_t;

		/**
		 * Imagine the component pinned to the container with a thumbtack.
		 * The thumbtack's position is at GetPos(), and the alignment determines
		 * which corner the component hangs from.
		 */
		struct Alignment
		{
			enum alignment_t {
				NW,  ///< Northwest corner (default).
				N,  ///< North (horizontally-centered).
				NE,  ///< Northeast corner.
				E,  ///< East (vertically-centered).
				SE,  ///< Southeast corner.
				S,  ///< South (horizontally-centered).
				SW,  ///< Southwest corner.
				W,  ///< West (vertically-centered).
				CENTER,  ///< Horizontally @e and vertically centered.
			};
		};

	public:
		UiViewModel(layoutFlags_t layoutFlags=0) :
			SUPER(), pos(0, 0), alignment(Alignment::NW),
			layoutFlags(layoutFlags) { }
		virtual ~UiViewModel() { }

	public:
		/**
		 * Get the position of the component.
		 * @return The position, relative to the parent (if any).
		 * @see GetAlignment()
		 */
		const Vec2 &GetPos() const { return pos; }
		void SetPos(const Vec2 &pos);
		/// Convenience function for SetPos(const Vec2&).
		void SetPos(double x, double y) { SetPos(Vec2(x, y)); }

		/**
		 * Retrieve the alignment of the component.
		 * @return The alignment.
		 * @see UiViewModel::Alignment
		 */
		const Alignment::alignment_t GetAlignment() const { return alignment; }
		void SetAlignment(Alignment::alignment_t alignment);

		Vec2 GetAlignedPos(double w, double h) const;

		/**
		 * Retrieve the layout flags.
		 * @see UiViewModel::LayoutFlags
		 */
		layoutFlags_t GetLayoutFlags() const { return layoutFlags; }

		// Convenience functions for querying layout flags.
		layoutFlags_t IsLayoutUnscaled() const { return layoutFlags & LayoutFlags::UNSCALED; }
		layoutFlags_t IsLayoutFloating() const { return layoutFlags & LayoutFlags::FLOATING; }

	private:
		Vec2 pos;
		Alignment::alignment_t alignment;
		layoutFlags_t layoutFlags;
};

}  // namespace Display
}  // namespace HoverRace

#undef MR_DllDeclare