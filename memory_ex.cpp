/**
 * @file      exclusive_mem.cpp
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

// Includes.
#include "memory_ex.h"

// The namespace.
namespace memory_exclusive {

using namespace std;

bool MemoryEx::ReadModifyWrite_if(uint32_t &memory, MemoryModifier modifier, TimeoutProvider timeout){
	uint32_t memory_val;
	do {
		// Read the current value.
		memory_val = __LDREXW(&memory);
		
		// Call the modifier.
		if (modifier(memory_val)) {
			// Data memory barrier instruction.
			__DMB();

			// Try to write.
			if (0 == __STREXW(memory_val, &memory)) {
				// Data memory barrier instruction.
				__DMB();
            
				// Written, return success.
				return true;
			}
		}
	}
	// Check for timeout.
	while (!timeout());

	// Failure.
	return false;
}

uint32_t MemoryEx::Read(const uint32_t &memory){
	// Return the memory value directly since it is atomic.
	return memory;
}

void MemoryEx::Write(uint32_t &memory, const uint32_t value){
	// Data memory barrier instruction.
	__DMB();

	// Write the value directly since it is atomic.
	memory = value;
}

}
