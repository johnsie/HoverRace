
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = hoverrace
hoverrace_CPPFLAGS = $(HR_CPPFLAGS) -DLOCALEDIR=\"$(localedir)\"
hoverrace_CXXFLAGS = $(HR_CXXFLAGS)
hoverrace_LDADD = \
	../../engine/libhoverrace-engine.la \
	$(BOOST_FILESYSTEM_LDFLAGS) $(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LDFLAGS) $(BOOST_SYSTEM_LIBS) \
	$(BOOST_THREAD_LDFLAGS) $(BOOST_THREAD_LIBS) \
	$(LUA_LIBS) $(LUABIND_LDFLAGS) \
	$(DEPS_LIBS)
hoverrace_SOURCES = \
	StdAfx.h \
	Control/SDL/SDLInputManager.cpp \
	Control/SDL/SDLInputManager.h \
	Control/SDL/SDLKeyboard.cpp \
	Control/SDL/SDLKeyboard.h \
	Control/SDL/SDLMouse.cpp \
	Control/SDL/SDLMouse.h \
	Control/SDL/SDLPrereqs.h \
	Control/ActionPerformers.cpp \
	Control/ActionPerformers.h \
	Control/ConsoleActions.cpp \
	Control/ConsoleActions.h \
	Control/ControlAction.h \
	Control/Controller.cpp \
	Control/Controller.h \
	Control/InputHandler.h \
	Control/ObserverActions.cpp \
	Control/ObserverActions.h \
	Control/UiHandler.h \
	HoverScript/ClientScriptCore.cpp \
	HoverScript/ClientScriptCore.h \
	HoverScript/ConfigPeer.cpp \
	HoverScript/ConfigPeer.h \
	HoverScript/Console.cpp \
	HoverScript/Console.h \
	HoverScript/GamePeer.cpp \
	HoverScript/GamePeer.h \
	HoverScript/HighConsole.cpp \
	HoverScript/HighConsole.h \
	HoverScript/SessionPeer.cpp \
	HoverScript/SessionPeer.h \
	HoverScript/SysEnv.cpp \
	HoverScript/SysEnv.h \
	ClientApp.cpp \
	ClientApp.h \
	ClientSession.cpp \
	ClientSession.h \
	FolderViewer.cpp \
	FolderViewer.h \
	GameDirector.h \
	GameScene.cpp \
	GameScene.h \
	HighObserver.cpp \
	HighObserver.h \
	Observer.cpp \
	Observer.h \
	RoomList.cpp \
	RoomList.h \
	Rulebook.h \
	Scene.h \
	main.cpp \
	version.h

BUILT_SOURCES = StdAfx.h.gch
CLEANFILES = $(BUILT_SOURCES) StdAfx.h.Td StdAfx.h.d

EXTRA_DIST = \
	Game2.rc \
	StdAfx.cpp \
	icon1.ico \
	icon2.ico \
	icon3.ico

# Build the precompiled header.
StdAfx.h.gch: StdAfx.h
	$(AM_V_GEN)$(CXXCOMPILE) $(HR_CPPFLAGS) $(HR_CXXFLAGS) \
		-x c++-header \
		-MD -MP -MF StdAfx.h.Td \
		-c -o $@ $<
	mv StdAfx.h.Td StdAfx.h.d

-include StdAfx.h.d

