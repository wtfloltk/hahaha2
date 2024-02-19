#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <iostream> 

#include <3ds.h>
#include <GL/picaGL.h>


#include "Config/ConfigOptions.h"
#include "Core/Cheats.h"
#include "Core/CPU.h"
#include "Core/CPU.h"
#include "Core/Memory.h"
#include "Core/PIF.h"
#include "Core/RomSettings.h"
#include "Core/Save.h"
#include "Debug/DBGConsole.h"
#include "Debug/DebugLog.h"
#include "Graphics/GraphicsContext.h"
#include "HLEGraphics/TextureCache.h"
#include "Input/InputManager.h"
#include "Interface/RomDB.h"
#include "System/SystemInit.h"
#include "Test/BatchTest.h"

#include "UI/UserInterface.h"
#include "UI/RomSelector.h"

#include "System/IO.h"
#include "Interface/Preferences.h"
#include "Utility/Profiler.h"
#include "System/Thread.h"
#include "Base/Path.h"

#include "Utility/Timer.h"
#include "RomFile/RomFile.h"
#include "Utility/MemoryCTR.h"

bool isN3DS = false;
bool shouldQuit = false;

EAudioPluginMode enable_audio = APM_ENABLED_ASYNC;

#ifdef DAEDALUS_LOG
void log2file(const char *format, ...) {
	__gnuc_va_list arg;
	int done;
	va_start(arg, format);
	char msg[512];
	done = vsprintf(msg, format, arg);
	va_end(arg);
	snprintf(msg, sizeof(msg),  "%s\n", msg);
	FILE *log = fopen("sdmc:/DaedalusX64.log", "a+");
	if (log != NULL) {
		fwrite(msg, 1, strlen(msg), log);
		fclose(log);
	}
}
#endif

static void CheckDSPFirmware()
{
	FILE *firmware = fopen("sdmc:/3ds/dspfirm.cdc", "rb");

	if(firmware != NULL)
	{
		fclose(firmware);
		return;
	}

	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);

	printf("DSP Firmware not found!\n\n");
	printf("Press START to exit\n");

	while(aptMainLoop())
	{
		hidScanInput();

		if(hidKeysDown() == KEY_START)
			exit(1);
	}
}

static void Initialize()
{
	CheckDSPFirmware();
	
	_InitializeSvcHack();

	romfsInit();
	
	APT_CheckNew3DS(&isN3DS);
	osSetSpeedupEnable(true);
	
	gfxInit(GSP_BGR8_OES, GSP_BGR8_OES, true);

	if(isN3DS)
		gfxSetWide(true);
	
	pglInitEx(0x080000, 0x040000);

	UI::Initialize();

	System_Init();
}


void HandleEndOfFrame()
{
	shouldQuit = !aptMainLoop();
	
	if (shouldQuit)
	{
		CPU_Halt("Exiting");
	}
}

extern u32 __ctru_heap_size;

int main(int argc, char* argv[])
{
	char fullpath[512];

	Initialize();
	
	while(shouldQuit == false)
	{
	
	// Set the default path

	std::string rom = UI::DrawRomSelector();
	std::filesystem::path RomPath = baseDir / "Roms" / std::string(rom);

	System_Open(RomPath.string().c_str());
	CPU_Run();
	System_Close();
	}
	
	System_Finalize();
	pglExit();

	return 0;
}
