/**
 * @file      exclusive_mem.h
 * @author    Atakan S.
 * @date      01/01/2019
 * @version   1.0
 * @brief     Exclusive memory access for Cortex-M3/M4.
 *
 * @copyright Copyright (c) 2018 Atakan SARIOGLU ~ www.atakansarioglu.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 */

#ifndef _EXCLUSIVE_MEM_H_
#define _EXCLUSIVE_MEM_H_

// Includes.
#define xstr(s) str(s)
#define str(s) #s
#include xstr(MCU_INCLUDE)
#include <stdbool.h>
#include <functional>

// The namespace.
namespace memory_exclusive {

/*
 * @brief Timeout function handle that takes no parameters and returns true when timed-out.
 */
typedef std::function<bool ()> TimeoutProvider;

/*
 * @brief Function that takes 32bit value, modifies it and returns true if modified.
 */
typedef std::function<bool (uint32_t&)> MemoryModifier;

class MemoryEx {
public:
	/*
	 * @brief Exclusive read followed by conditional modify-write operation.
	 * @param memory The memory area for exclusive access.
	 * @param modifier Function takes current value and modifies if necessary.
	 * @param timeout Timeout callback function. Returning true means timed-out.
	 * @return true for success and false for timeout or failure.
	 */
	static bool ReadModifyWrite_if(uint32_t &memory, MemoryModifier modifier, TimeoutProvider timeout);

	/*
	 * @brief Direct read operation.
	 * @param memory The memory area for exclusive access.
	 * @return the value.
	 */
	static uint32_t Read(const uint32_t &memory);

	/*
	 * @brief Direct write operation followed by memory barrier/fence operation.
	 * @param memory The memory area for exclusive access.
	 * @param value The value to write.
	 */
	static void Write(uint32_t &memory, const uint32_t value);

private:
	/*
	 * @brief Private constructor.
	 */
	MemoryEx();

	/*
	 * @brief Private destructor.
	 */
	~MemoryEx();
};

}

#endif
