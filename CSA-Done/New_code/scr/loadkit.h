#ifndef _LOADKIT
#define _LOADKIT
#include<stdio.h>
#include<stdlib.h>
#include"BaseClass.h"
class loadkit
{
	public:
		loadkit(const char * file);
		~loadkit();
		i32 loadi64(i64 & value);
		i32 loadu64(u64 & value);
		i32 loadi32(i32 & value);
		i32 loadu32(u32 & value);
		i32 loadi16(i16 & value);
		i32 loadu16(u16 & value);

		i32 loadi64array(i64 * value,i32 len);
		i32 loadu64array(u64 * value,i32 len);
		i32 loadi32array(i32 * value,i32 len);
		i32 loadu32array(u32 * value,i32 len);
		i32 loadi16array(i16 * value,i32 len);
		i32 loadu16array(u16 * value,i32 len);

		void close();
	private:
		FILE * r;
};
#endif


