/**
 * @file      memory_semaphore.cpp
 * @author    Atakan S.
 * @date      01/01/2019
 * @version   1.0
 * @brief     Semaphore class for Cortex-M3/M4.
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
#include "memory_semaphore.h"

// The namespace.
namespace memory_exclusive {

using namespace std;

bool Semaphore::GiveCounting(const uint32_t maxCount, function<bool ()> timeout) {
	// Pass lambda function that checks if the value is less than the limit then increases it.
	return MemoryEx::ReadModifyWrite_if(m_memory, [maxCount](uint32_t& val) {return (val++ < maxCount);}, timeout);
}

bool Semaphore::Give(function<bool ()> timeout) {
	// Call counting semaphore giver with unity count.
	return GiveCounting(1, timeout);
}

bool Semaphore::Take(function<bool ()> timeout){
	// Pass lambda function that checks if the value is not zero then decreases it.
	return MemoryEx::ReadModifyWrite_if(m_memory, [](uint32_t& val) {return (0 < val--);}, timeout);
}

}
