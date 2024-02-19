#pragma once
#include <stdint.h>
#include <imgui.h>
#include <imgui_impl_3ds.h>
#include <imgui_impl_opengl2.h>

enum EClockValue
{
    CLOCK_DEFAULT = 268123480,
    CLOCK_DOWN = 268123480 / 2,
    CLOCK_UP = 268123480 * 2,
    CLOCK_LOWER = 268123480 / 3,
    CLOCK_HIGHER = 268123480 * 3,
    CLOCK_MUCHLOWER = 268123480 / 4,
    CLOCK_MUCHHIGHER = 268123480 * 4,
    CLOCK_WAYLOWER = 268123480 / 5,
    CLOCK_WAYHIGHER = 268123480 * 5,
    CLOCK_1MHZ = 268123480 / 6,
    CLOCK_MAX = 268123480 * 6,
    CLOCK_WTF = 268123480 * 8,
    NUM_CLOCK_VALUES = 12,
};

namespace UI
{
	void Initialize();
	void RestoreRenderState();
}
