
// SdlDisplay.h
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

#ifdef WITH_SDL_PANGO
#	include <SDL_Pango.h>
#endif

#include "../UiViewModel.h"
#include "../Display.h"

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
		class Label;
	}
}

namespace HoverRace {
namespace Display {
namespace SDL {

/**
 * SDL-based software rendering.
 * @author Michael Imamura
 */
class MR_DllDeclare SdlDisplay : public Display
{
	typedef Display SUPER;
	public:
		SdlDisplay();
		virtual ~SdlDisplay();

	public:
		// ViewAttacher
		virtual void AttachView(FillBox &model);
		virtual void AttachView(Label &model);
		virtual void AttachView(ScreenFade &model);

	public:
		// Display
		virtual VideoServices::VideoBuffer &GetLegacyDisplay() const { return *legacyDisplay; }
		virtual void OnDesktopModeChanged(int width, int height);
		virtual void OnDisplayConfigChanged();
		virtual void Flip();

	private:
		void ApplyVideoMode();

	public:
		int GetScreenWidth() const { return width; }
		int GetScreenHeight() const { return height; }

#		ifdef WITH_SDL_PANGO
			/**
			 * Retrieve the shared SDL_Pango rendering context.
			 * @return The context (never @c NULL).
			 * @see SdlLabelView
			 */
			SDLPango_Context *GetPangoContext() { return pangoContext; }
#		endif

	public:
		// SDL-specific utilities.
		static SDL_Surface *CreateHardwareSurface(int w, int h);
		void DrawUiSurface(SDL_Surface *surface, const Vec2 &relPos,
			UiViewModel::layoutFlags_t layoutFlags=0);

	private:
		int width, height;
		std::unique_ptr<VideoServices::VideoBuffer> legacyDisplay;
#		ifdef WITH_SDL_PANGO
			SDLPango_Context *pangoContext;
#		endif
};

}  // namespace SDL
}  // namespace Display
}  // namespace HoverRace

#undef MR_DllDeclare