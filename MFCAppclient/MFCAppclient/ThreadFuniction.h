/**************************************
 *FILE          :T:\car\MFCAppclient\MFCAppclient\ThreadFuniction.h
 *AUTHOR        :707wk
 *ORGANIZATION  :GT-Soft Studio
 *LAST-MODIFIED :2016/6/24 13:53:47
 *TARGET        :C/C++
 *EMAIL         :gtsoft_wk@foxmail.com
 *LOGO          :
               #########                       
              ############                     
              #############                    
             ##  ###########                   
            ###  ###### #####                  
            ### #######   ####                 
           ###  ########## ####                
          ####  ########### ####               
        #####   ###########  #####             
       ######   ### ########   #####           
       #####   ###   ########   ######         
      ######   ###  ###########   ######       
     ######   #### ##############  ######      
    #######  ##################### #######     
    #######  ##############################    
   #######  ###### ################# #######   
   #######  ###### ###### #########   ######   
   #######    ##  ######   ######     ######   
   #######        ######    #####     #####    
    ######        #####     #####     ####     
     #####        ####      #####     ###      
      #####       ###        ###      #        
        ##       ####        ####              
***************************************/

#if !defined(_THREADFUNICTION_)
#define _THREADFUNICTION_

#include "StdAfx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

DWORD WINAPI ThreadPoll(LPVOID pParam);

#endif

