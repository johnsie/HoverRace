
// HighObserver.h
// Header for global HUD.
//
// Copyright (c) 2009 Michael Imamura.
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

namespace HoverRace {
namespace VideoServices {
	struct Font;
	class MultipartText;
	class NumericGlyphs;
	class StaticText;
}
}

class MR_2DViewPort;
class MR_ClientSession;
class MR_VideoBuffer;

/**
 * A global HUD that sits on top of everything else.
 *
 * Unlike the regular Observer, which has one per split-screen player, 
 * there is only one HighObserver that fills the entire screen.
 * The main purpose is to display messages which would otherwise be repeated
 * (in tiny text) in each split screen.
 *
 * @author Michael Imamura
 */
class HighObserver
{
	public:
		HighObserver();
		~HighObserver();

	private:
		void RenderStats(const MR_ClientSession *session);
	public:
		void Render(MR_VideoBuffer *dest, const MR_ClientSession *session);

	private:
		MR_2DViewPort *viewport;
		HoverRace::VideoServices::Font *statsFont; ///< Font used for stats HUD text.
		HoverRace::VideoServices::NumericGlyphs *statsNumGlyphs;
		HoverRace::VideoServices::MultipartText *fpsTxt;
};
