/**
 * @file      memory_mutex.h
 * @author    Atakan S.
 * @date      01/01/2019
 * @version   1.0
 * @brief     Mutex class for Cortex-M3/M4.
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

#ifndef _MEMORY_MUTEX_H_
#define _MEMORY_MUTEX_H_

// Includes.
#define xstr(s) str(s)
#define str(s) #s
#include xstr(MCU_INCLUDE)
#include <stdbool.h>
#include <functional>
#include "memory_semaphore.h"

// The namespace.
namespace memory_exclusive {

class Mutex : protected Semaphore {
public:
	/*
	 * @brief Constructor.
	 */
	Mutex() : Semaphore::Semaphore(1) { };

	/*
	 * @brief Locks the mutex.
	 * @param timeout Timeout callback function. Returning true means timed-out.
	 * @return true for success and false for timeout or failure.
	 */
	bool Lock(TimeoutProvider timeout);

	/*
	 * @brief Unlocks the mutex. Do not use when the mutex is not locked.
	 */
	void Unlock();

	// Use the timeout providers.
	using Semaphore::TryOnce;
	using Semaphore::TryAlways;
};

}

#endif
