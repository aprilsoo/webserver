/*
 * @Author: peace901 443257245@qq.com
 * @Date: 2023-04-21 14:10:14
 * @LastEditors: peace901 443257245@qq.com
 * @LastEditTime: 2023-04-21 21:43:30
 * @FilePath: /webserver/src/server/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include<cstring>
#include<iostream>
#include<cstdio>
#include<algorithm>


#include "buffer/buffer.h"

int main(int argc, char* argv[]) {
    int port_ = 80;
    if(argc >= 2) {
     std::string q(argv[1]);
     port_ = stoi(q);
    }
    
    
}