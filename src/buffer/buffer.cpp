/*
 * @Author: peace901 443257245@qq.com
 * @Date: 2023-04-21 14:40:44
 * @LastEditors: peace901 443257245@qq.com
 * @LastEditTime: 2023-04-21 21:43:44
 * @FilePath: /webserver/src/buffer/buffer.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "../include/buffer/buffer.h"

#include<iostream>
#include<cstdio>
#include<cstring>
#include<stdarg.h>

namespace Buffer{
 Buffer::Buffer(size_t size) {
  if (size <= 0 ) { return; }
  ok_ = false;
  size_ = size;

  data_ = std::make_unique<char[]>(size);
  
  st_ = 0;
  ed_ = 0;
  ok_ = true;
 }

 auto Buffer::Get_capacity() -> size_t { return size_; }

 auto Buffer::Get_used_size() -> size_t { return st_<= ed_ ? ed_-st_ : ed_+size_-st_; }

 auto Buffer::Get_remain_size() -> size_t { return size_-Get_used_size(); }



 auto Buffer::Write(const char *data) -> int {
  std::unique_lock<std::mutex> lock(mutex);
  if(!ok_) { return -2; }
  if (data == nullptr) { return -1; }

  size_t len = strlen(data);
  if (len == 0U) { return 0; }

  if (Get_remain_size() < len) { return -1; }
 
  int ll = std::min(len, size_-ed_);
  memcpy(data_.get()+ed_,data,ll);
  ed_ = ed_+ll >= size_ ? ed_+ll-size_ : ed_+ll;

  if (ll < len) {
   len -= ll;
   memcpy(data_.get(),data+ll,len);
   ed_ += len;
  }
  
  return len;
 }




 auto Buffer::Snwrite(size_t max_size, const char *data, ...) -> int {
  if(!ok_) { return -2; }
  if(data == nullptr) { return -1; }
  va_list vptr;
  va_start(vptr,data);
  size_t len = vsnprintf(data_.get(),0,data,vptr);
  va_end(vptr);
  if (len == 0) { return 0; }
  if (len > max_size) { return -1; }

  std::unique_ptr<char[]> tmp = std::make_unique<char[]>(len+1);
  memset(tmp.get(),0,len+1);
  
  va_start(vptr,data);
  vsnprintf(tmp.get(),len+1,data,vptr);
  va_end(vptr);

  return Write(tmp.get());
 }




 auto Buffer::Read() -> std::unique_ptr<char[]> {
  if(!ok_) { return nullptr; }
  if(st_ == ed_) { return nullptr; }
  std::unique_lock<std::mutex> lock(mutex);

  int len = Get_remain_size();
  std::unique_ptr<char[]> tmp = std::make_unique<char[]>(len+1);
  memset(tmp.get(),0,len+1);
  if(st_ < ed_){
   memcpy(tmp.get(), data_.get()+st_, len);
  } else {
   memcpy(tmp.get(), data_.get()+ed_, len-ed_);
   memcpy(tmp.get()+len-ed_, data_.get(), st_+1);
  }
  st_ = 0;
  ed_ = 0;
  return std::move(tmp);
 }

}

