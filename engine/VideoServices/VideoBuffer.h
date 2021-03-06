// VideoBuffer.h
// DirectDraw encapsulation module
//
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

#pragma once

#ifdef WITH_SDL
#	include <SDL/SDL.h>
#else
#	include <ddraw.h>
#endif

#include "../Util/MR_Types.h"
#include "../Util/OS.h"
#include "ColorPalette.h"

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
namespace VideoServices {

class VideoBuffer
{

	private:
		bool mFullScreen;
		int desktopWidth;
		int desktopHeight;
#	ifdef WITH_SDL
		ColorPalette::paletteEntry_t mPalette[256];
#	else
		HWND mWindow;
		HINSTANCE directDrawInst;
		GUID curMonitor;
		LPDIRECTDRAW mDirectDraw;
		LPDIRECTDRAWSURFACE mFrontBuffer;
		LPDIRECTDRAWSURFACE mBackBuffer;
		LPDIRECTDRAWPALETTE mPalette;
		LPDIRECTDRAWCLIPPER mClipper;			  // To use in windows only
		// remove if too slow
#	endif

		BOOL mSpecialWindowMode;				  // Use a 256 color mode when switching to window mode
		int mSpecialModeXRes;
		int mSpecialModeYRes;

#	ifdef WITH_SDL

#	else
		LONG mOriginalExStyle;					  // Only valid if mFullScreen
		LONG mOriginalStyle;					  // Only valid if mFullScreen
		RECT mOriginalPos;						  // Only valid if mFullScreen
#	endif

		BOOL mModeSettingInProgress;

		int mX0;								  // used only when
		int mY0;								  // displaying in a window
		int mXRes;
		int mYRes;
		int mLineLen;

		DWORD mBpp;								  // current bits per pixel
		DWORD mNativeBpp;						  // native (desktop) bits per pixel

		struct Channel
		{
			DWORD mShift;
			DWORD mSize;

			Channel() : mShift(0), mSize(0) { }

			void SetMask(DWORD mask)
			{
				// Computes the run length and shift of the block of ones in a bitmask.
				// Example: If the mask is "00011100" then mSize=3 and mShift=2.
				mShift = 0;
				mSize = 0;

				// Count the zeros on right hand side.
				while(!(mask & 1L)) {
					mask >>= 1;
					mShift++;
				}

				// Count the ones.
				while(mask & 1L) {
					mask >>= 1;
					mSize++;
				}
			}

			DWORD Pack(DWORD intensity) const
			{
				// Packs a value into the bitmask for this channel.
				intensity >>= (8 - mSize);
				intensity <<= mShift;
				return intensity;
			}
		};
		Channel mRChan, mGChan, mBChan;

		DWORD *mPackedPalette;

		MR_UInt16 *mZBuffer;
		MR_UInt8 *mBuffer;

		MR_UInt8 *mBackPalette;

		// IconMode releted functions
		BOOL mIconMode;
		//      int  mBeforeIconXRes;
		//      int  mBeforeIconYRes;

		// ColorRelated data
		double mGamma;
		double mContrast;
		double mBrightness;

		DWORD PackRGB(ColorPalette::paletteEntry_t &pal);

#	ifndef WITH_SDL
		bool InitDirectDraw(GUID *monitor, bool newFullscreen);
		BOOL ProcessCurrentBpp(const DDPIXELFORMAT & lFormat);
		void DeleteInternalSurfaces();
		void ReturnToWindowsResolution();		  //Automaticly call DeleteInternalSurfaces
#	endif

		void Flip();

	public:

		MR_DllDeclare VideoBuffer(Util::OS::wnd_t pWindow, double lGamma, double lContrast, double mBrightness);
		MR_DllDeclare ~VideoBuffer();

		// Video mode selection
		MR_DllDeclare void NotifyDesktopModeChange(int width, int height);
#	ifdef WITH_SDL
		MR_DllDeclare void NotifyWindowResChange(int width, int height, int lineLen);
#	endif
		MR_DllDeclare bool SetVideoMode();		  // In a window mode
												  // Full screen mode
		MR_DllDeclare bool SetVideoMode(int pXRes, int pYRes, GUID *monitor);
		MR_DllDeclare void EnterIconMode();
		MR_DllDeclare void ExitIconMode();
		MR_DllDeclare void AssignPalette();

#	ifndef WITH_SDL
		MR_DllDeclare BOOL TryToSetColorMode(int colorBits);
#	endif

		MR_DllDeclare BOOL IsWindowMode() const;
		MR_DllDeclare BOOL IsIconMode() const;
		MR_DllDeclare BOOL IsModeSettingInProgress() const;

		MR_DllDeclare void CreatePalette(double pGamma, double pContrast, double pBrightness);
		MR_DllDeclare void GetPaletteAttrib(double &pGamma, double &pContrast, double &pBrightness);
		MR_DllDeclare void SetBackPalette(MR_UInt8 * pPalette);

		// Buffers manipulation
		MR_DllDeclare BOOL Lock();				  // Must be called before drawing
		MR_DllDeclare void Unlock();

		// Buffer access functions
		MR_DllDeclare int GetXRes() const;
		MR_DllDeclare int GetYRes() const;
		MR_DllDeclare int GetLineLen() const;
		MR_DllDeclare int GetZLineLen() const;

		MR_DllDeclare MR_UInt8 *GetBuffer();
		MR_DllDeclare MR_UInt16 *GetZBuffer();

		MR_DllDeclare void Clear(MR_UInt8 pColor = 0);
		MR_DllDeclare void ClearZ(MR_UInt8 pDepth = -1);

		// geometry access functions
		typedef std::pair<int,int> pixelMeter_t;
		MR_DllDeclare pixelMeter_t GetPixelMeter() const;

		// 2DDrawing primitives, defined in VideoBuffer2DDraw.cpp
		MR_DllDeclare void DrawPoint(int pX, int pY, MR_UInt8 pColor);
		MR_DllDeclare void DrawLine(int pX0, int pY0, int pX1, int pY1, MR_UInt8 pColor);
		MR_DllDeclare void DrawHorizontalLine(int pY, int pX0, int pX1, MR_UInt8 pColor);

		// 2DRendering primitives, defined in VideoBuffer3DRendering.cpp

};

}  // namespace VideoServices
}  // namespace HoverRace

#undef MR_DllDeclare
