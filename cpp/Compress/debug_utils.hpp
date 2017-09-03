//
//  debug_utils.h
//  Dig
//
//  Created by DB on 10/17/14.
//  Copyright (c) 2014 DB. All rights reserved.
//

#ifndef __debug_utils_hpp
#define __debug_utils_hpp

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#ifdef __cplusplus
	#include <iostream>
	#include <cstdarg>
	#include <string>
	#include <cstdint>

	#define PRINT_DEBUG(STR) \
		std::cout << __func__ << "(): " STR << "\n";

	#define PRINT_VAR_DEBUG(VAR) \
		std::cout << __func__ << "(): " #VAR << ": " << VAR << "\n";

	#define PRINT(STR) \
		std::cout << STR << "\n";

	#define PRINT_VAR(VAR) \
		std::cout << #VAR ": " << VAR << "\n";

	#define PRINTLN_VAR(VAR) \
		std::cout << #VAR ":\n" << VAR << "\n";

	template<int MAX_LEN=512>
	static inline std::string string_with_format(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		char buff[MAX_LEN];
		vsnprintf(buff, MAX_LEN-1, fmt, args);
		return std::string(buff);
		va_end(args);
	}

	template<typename P>
	inline int32_t pretty_ptr(P ptr) {
		return (((int64_t)ptr) << 40) >> 40;
	}


#endif

#ifdef __cplusplus
extern "C" {
#endif

// #ifdef DEBUG
//	#define clean_errno() (errno == 0 ? "None" : strerror(errno))
//	#define log_error(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
//	#define assertf(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }
// #else
// 	#define assertf(A, M, ...)
// #endif

static inline void print_var(const char* name, double val) {
	printf("%s=%g\n", name, val);
}

static inline void print(const char* str) {
	printf("%s\n", str);
}

#define DEBUGF(format, ...) \
    printf("%s(): " format "\n", __func__, ##__VA_ARGS__);

// won't work cuz we don't know size of elements for void*
//inline void print_array(const char* name, void* ar, int len) {
//	double*v = (double*) ar;
//	printf("%s: ", name);
//	for(unsigned i = 0; i < len; ++i) {
//		printf("%g ", v[i]);
//	}
//	printf("\n");
//}

#ifdef __cplusplus
}
#endif

template<class T> // dumps the bits in logical order (ie, msb always first)
inline void dumpBits(T x, bool newline=true) {
	// for (int i = 0; i < sizeof(x) ; i++) {
	for (int i = sizeof(x) - 1; i >= 0 ; i--) {
		std::cout << " ";
		for (int j = 7; j >= 0; j--) {
			uint64_t mask = ((uint64_t)1) << (8*i + j);
			uint64_t masked = mask & x;
			std::cout << (bool)masked;
		}
	}
	if (newline) { std::cout << "\n"; }
}

template<class T> // dumps the raw bits in memory order
inline void dumpEndianBits(T x, bool newline=true) {
	const uint8_t* ptr = reinterpret_cast<const uint8_t*>(&x);
	for (int i = 0; i < sizeof(x); i++) {
		std::cout << " ";
		const uint8_t byte = *(ptr + i);
		for (int j = 0; j < 8; j++) {
			uint64_t mask = ((uint8_t)1) << j;
			uint64_t masked = mask & byte;
			std::cout << (bool)masked;
		}
	}
	if (newline) { std::cout << "\n"; }
}


#endif
