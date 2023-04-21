/*
 * @Author: peace901 443257245@qq.com
 * @Date: 2023-04-21 14:16:56
 * @LastEditors: peace901 443257245@qq.com
 * @LastEditTime: 2023-04-21 21:41:28
 * @FilePath: /webserver/src/include/buffer/buffer.h
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#pragma once

#include<sys/types.h>
#include<iostream>
#include<cstdio>
#include<memory>
#include<algorithm>
#include<thread>
#include<mutex>

namespace Buffer{
 class Buffer{
  public:
   Buffer(size_t size);

   size_t Get_capacity();
   int Write(const char *data);
   // int Swrite(const char *data, ...);
   int Snwrite(size_t max_size, const char *data, ...);
   std::unique_ptr<char[]> Read();

  private:
   size_t Get_remain_size();
   size_t Get_used_size();

   std::mutex mutex;

   size_t size_;
   int st_;
   int ed_;
   bool ok_;
   std::unique_ptr<char[]> data_;

 };
}
