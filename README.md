aHoverRace
=========

<http://www.hoverrace.com/>

**This is the _unstable_ branch of HoverRace.**
The current stable branch is: [1.24](https://github.com/HoverRace/HoverRace/tree/1.24)

HoverRace is an online racing game originally written by Grokksoft in the mid-1990s. After Grokksoft stopped maintaining the game in the late 1990s, HoverRace was abandonware for a number of years before the original developer, Richard Langlois, opened up the source code to the public. Since then, development has been ongoing to bring HoverRace into the 21st century.

Features
--------

 * Fast, free, and fun!
 * Single-player and multiplayer (split-screen and internet).
 * Hundreds of user-created tracks available for download.

Portability
-----------

HoverRace currently runs on Windows (7 or later) and modern Linux distributions.  Other platforms including mobile may be supported in the future.

Links
-----

Download and play the latest release: <http://www.hoverrace.com/>

Project hosted at GitHub: <https://github.com/HoverRace/HoverRace/>

Source documentation: <http://hoverrace.github.io/API/>

HoverRace wiki: <https://github.com/HoverRace/HoverRace/wiki>

Building on Windows (Version 2.1J on Visual Studio 2015 - New Documentation - updated 21/02/2020) 
-----

IMPORTANT: The project in this repository doesn't have a Visual Studio solution file, or project files. So we will need to generate them using CMake. We also need the Boot Libraries. Don't click build in Visual Studio until the following tasks are completed:

Download the boost libraries from http://sourceforge.net/projects/boost/files/boost-binaries/1.59.0/boost_1_59_0-msvc-14.0-32.exe/download
 
Run the exe and install it

Download the latest version of Cmake for Windows (known to work with Cmake 3.1) from https://cmake.org/download/ and install that. It's a Windows front end, you you wont have to do any command line magic.

Clone this repository to your computer whatever way you want ("Open/Clone from Github" in Visual Studio works ok for this, but dont bother buidling it just yet... There's no solution file or project files anyway. You could also use a git client to do this, but that's up to you)

If you've cloned it in  Visual Studio, now close Visual Studio. Changing files outside of Visual Studio makes it go bezerk.

Now fire up Cmake and enter the following details:

Where is the source code?  Wherever you cloned the github to eg: C:/Users/johnise/Source/Repos/HoverRace 

Where to build the Binaries? This is where a brand spanking new set of Visual Studio project will go.  You can decide this. The .sln file for the project will be created there. Put it in your favourite place to keep Visual Studio projects. I would recommend putting it in a completely new folder somewhere.

Now click the "Add entry" button to create the following two settings:

BOOST_INCLUDEDIR (string) - Typically, the root of your Boost installation (e.g. "C:\local\boost_1_59")
BOOST_LIBRARYDIR (string) - Where the 32-bit Boost libraries were installed (e.g. "C:\local\boost_1_59\lib32-msvc-14.0")


Click 'Configure' and when the box somes up asking for some more settings, just leave it with the default settings

When that has finished, click 'Generate'. This will create the Sln file in the folder that you choose for "Where to build the binaries". Open the solution  in that folder and you should have a Visual Studio project that builds normally.



Developing on Windows (1.24 New Documentation - Visual Studio 2019)
-----

1.24 compiles directly in Visual Studio without need for CMake. There are some things you'll need to do though:

Make sure Visual Studio is installed with the MFC C++ Components for X86 and 64 bit. This can be done at install time  or by using add/remove programs and use the "change" option. Particularly with VS2019 you want to be looking at the 142 version of of these components. 

Download and isntall the necessary boost library binaries.
https://sourceforge.net/projects/boost/files/boost-binaries/1.72.0/

Msvc-142 works with VS2019, you'll notice there are no 32 bit versions. We'll be compiling in 64-bitif that works

Clone the 1.24 of branch of this project from github in Visual Studio and open the sln in visual studio

Click View->Other Windows->Property Manager in Visual Studio to show the properties managers

Select all the projects in the properting manager yousing shift and the arrow keys after clicking one of them

Right click and click "properties"


On the left tab of the window that comes up select VC++ directories

Add your boost folder into "include directories". Make sure you click "apply" when you do this.

Add your lib64-msvc-14.2 folder to "Library directories" and also click apply

On the top main menu in visual studio change the debug and release from 32 bit to 64 bit for each project.

Try building the project. If you get typinfo.h errors try changing typeinfo.h to typeinfo in the code (typeinfo.h references are deprecated)


I'm having some issues with Luabind at the moment which has some known incompatibilties with later versions of boost. I'm going to try replacing luabind in the game source with a newer version of luabind which supposedely has the fix applied. If that works then I'll update the code and delete this part of the instructions.

Note to self. This is the version of luabind that supposedly has the fix applied (Files are in luabind folder in that repo and should be placed in include/luabind in the folder you installed the source code into)
https://github.com/rpavlik/luabind


Next issue is the calls to dialogboxparamW. On 32 bit this worked, but now that we are doing 64 bit we need to change the return type. Bool is an alias for a 32 bit int, but in 64 bit we need it to be a 64 bit int, so really we need to be returning an int_pr instead of a bool. See possible solution in stackoverflow

https://stackoverflow.com/questions/31113172/transformation-of-c-code-from-32-bit-to-64-bit

https://docs.microsoft.com/en-gb/windows/win32/api/winuser/nc-winuser-dlgproc?redirectedfrom=MSDN


***Change retun type of the dlgProc from BOOL whateeever what ever to INT_PTR**
****Also in the functiin itself make sure the BOOL return whatever is changed to an INT_PTR
***And in the .h file for the dialog you also need to change the type from Bool to INT_PTR


Developing on Windows (2.0 Old Documentation)
-----

This is preliminary documentation for HoverRace 2.0 using CMake. For the stable (1.24) branch, see: Windows Development Environment

Supported compilers on Windows
We currently support Visual Studio 2015 (aka Visual Studio 14.0), including the free Community edition.

Visual Studio 2015
Dependencies
Tools
CMake - 3.1 or later.
Libraries
Boost - Any version 1.54 or later is supported.
Boost 1.59 Installer (32-bit for Visual Studio 2015)
Running CMake
On Windows, we use CMake to generate the Visual Studio project files. CMake comes with a GUI for running CMake, installed as "CMake (cmake-gui)" in the Start menu.

Set Where is the source code to the folder where you cloned the HoverRace repository (e.g. "C:\Projects\HoverRace")
Set Where to build the binaries to a new folder. This can be anywhere you like.
For each of the following settings, click on the "Add Entry" button to add a new configuration entry:
BOOST_INCLUDEDIR (string) - Typically, the root of your Boost installation (e.g. "C:\Libraries\boost_1_59")
BOOST_LIBRARYDIR (string) - Where the 32-bit Boost libraries were installed (e.g. "C:\Libraries\boost_1_59\lib32-msvc-14.0")
Press the "Configure" button. When prompted for a generator, select the Visual Studio version being used, with the "Use default native compilers" option:
Visual Studio 2015:
CMake 3.1 or later: Visual Studio 14
If everything went well, press the "Generate" button to generate the project files.
You will now have a "hoverrace.sln" file in the destination directory which you can open with Visual Studio. It contains all of the projects necessary to build HoverRace.

Note: To run HoverRace from Visual Studio, right-click on the "HoverRace" project in the Solution Explorer and select "Set as Default".

CMake on Windows tips
Close Visual Studio when regenerating project files
If CMake (e.g. via cmake-gui) regenerates the project files while the projects are open, Visual Studio will ask to reload the project files. This seems useful, but doing so closes all of the opened files and changes the per-project tab colors (if using an extension like VS Power Tools).

Skip the CMake project check on every build
If you're running CMake manually (which is only really needed if adding / removing source files), then having CMake run automatically during each build is just slowing things down.

Set the CMAKE_SUPPRESS_REGENERATION (BOOL) configuration entry to true to skip this step from being generated in the project files.

Crank up the compiler warning level
We default to a reasonably-high warning level (/W3), but you can enable an even higher warning level by enabling the HR_EXTRA_WARNINGS configuration entry.

This option is off by default since we don't guarantee that we compile cleanly at that level.
