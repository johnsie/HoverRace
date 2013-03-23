
// MessageScene.cpp
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

#include "StdAfx.h"

#include "../../engine/Display/Display.h"
#include "../../engine/Display/Label.h"
#include "../../engine/Display/ScreenFade.h"
#include "../../engine/VideoServices/FontSpec.h"
#include "../../engine/Util/Config.h"

#include "MessageScene.h"

#define START_DURATION 500

using namespace HoverRace::Util;

namespace HoverRace {
namespace Client {

MessageScene::MessageScene(Display::Display &display,
                           GameDirector &director,
                           const std::string &title,
                           const std::string &message) :
	SUPER("Messsage (" + title + ")"),
	display(display), director(director)
{
	Config *cfg = Config::GetInstance();

	fader = new Display::ScreenFade(0xcc000000, 0.0);
	fader->AttachView(display);

	std::string fontName = cfg->GetDefaultFontName();

	titleLbl = new Display::Label(title,
		Display::UiFont(fontName, 40, Display::UiFont::BOLD),
		Display::COLOR_WHITE);
	titleLbl->AttachView(display);

	messageLbl = new Display::Label(message,
		Display::UiFont(fontName, 20), 0xffbfbfbf);
	messageLbl->AttachView(display);

	controlsLbl = new Display::Label("",
		Display::UiFont(fontName, 20, Display::UiFont::BOLD),
		Display::COLOR_WHITE);
	controlsLbl->AttachView(display);
}

MessageScene::~MessageScene()
{
	delete controlsLbl;
	delete messageLbl;
	delete titleLbl;
	delete fader;
}

void MessageScene::OnOk()
{
	//TODO: Fire "OK" event.
	director.RequestPopScene();
}

void MessageScene::OnCancel()
{
	//TODO: Fire "Cancel" event.
	director.RequestPopScene();
}

void MessageScene::AttachController(Control::InputEventController &controller)
{
	controller.AddMenuMaps();

	auto &menuOkAction = controller.actions.ui.menuOk;
	auto &menuCancelAction = controller.actions.ui.menuCancel;

	okConn = menuOkAction->Connect(std::bind(&MessageScene::OnOk, this));
	cancelConn = menuCancelAction->Connect(std::bind(&MessageScene::OnCancel, this));

	std::ostringstream oss;
	oss << '[' << controller.HashToString(menuOkAction->GetPrimaryTrigger()) <<
		"] " << menuOkAction->GetName();
	controlsLbl->SetText(oss.str());
}

void MessageScene::DetachController(Control::InputEventController &controller)
{
	cancelConn.disconnect();
	okConn.disconnect();
}

void MessageScene::Advance(Util::OS::timestamp_t tick)
{
	switch (GetPhase()) {
		case Phase::STARTING: {
			Util::OS::timestamp_t duration = GetPhaseDuration(tick);
			if (duration > START_DURATION) {
				fader->SetOpacity(1.0);
				SetPhase(Phase::RUNNING);
			}
			else {
				// Fade-in the screen fader.
				double opacity = static_cast<double>(duration) / START_DURATION;
				fader->SetOpacity(opacity);
			}
			break;
		}

		case Phase::STOPPING: {
			Util::OS::timestamp_t duration = GetPhaseDuration(tick);
			Util::OS::timestamp_t startingDuration = GetStartingPhaseTime();
			if (duration > startingDuration) {
				fader->SetOpacity(0.0);
				SetPhase(Phase::STOPPED);
			}
			else {
				// Fade-out the screen fader.
				double opacity = static_cast<double>(startingDuration - duration) / startingDuration;
				fader->SetOpacity(opacity);
			}
			break;
		}
	}
}

void MessageScene::PrepareRender()
{
	//TODO: Only update positions when screen size changes.
	Config::cfg_video_t &vidCfg = Config::GetInstance()->video;

	int leftMargin = vidCfg.xRes / 50;
	int centerH = vidCfg.yRes / 2;
	titleLbl->SetPos(Display::Vec2(leftMargin, centerH - 50));
	messageLbl->SetPos(Display::Vec2(leftMargin, centerH));
	controlsLbl->SetPos(Display::Vec2(leftMargin, vidCfg.yRes * 3 / 4));

	fader->PrepareRender();
	titleLbl->PrepareRender();
	messageLbl->PrepareRender();
	controlsLbl->PrepareRender();
}

void MessageScene::Render()
{
	fader->Render();
	if (GetPhase() != Phase::STOPPING) {
		titleLbl->Render();
		messageLbl->Render();
		controlsLbl->Render();
	}
}

}  // namespace HoverScript
}  // namespace Client