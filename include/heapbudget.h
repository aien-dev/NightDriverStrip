#pragma once

//+--------------------------------------------------------------------------
//
// File:        heapbudget.h
//
// NightDriverStrip - (c) 2023 Plummer's Software LLC.  All Rights Reserved.
//
// This file is part of the NightDriver software project.
//
//    NightDriver is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    NightDriver is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Nightdriver.  It is normally found in copying.txt
//    If not, see <https://www.gnu.org/licenses/>.
//
//
// Description:
//
//   Helpers that size allocation budgets from the same kind of memory the
//   allocation will actually be taken from.
//
// History:     Oct-2026
//
//---------------------------------------------------------------------------

#include <cstdint>
#include <esp_heap_caps.h>

// FreeInternalBytes8Bit
//
// Free bytes that an ordinary byte-addressed internal allocation can use, i.e. what
// psram_allocator<T> falls back to on a board without PSRAM (MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT).
//
// ESP.getFreeHeap() is not the same number: it counts MALLOC_CAP_INTERNAL only, which on the
// original ESP32 also includes the IRAM heap. That memory is 32-bit access only and is never
// handed out for an 8-bit request, so budgeting against it overstates what can be allocated.

inline uint32_t FreeInternalBytes8Bit()
{
    return static_cast<uint32_t>(heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT));
}
