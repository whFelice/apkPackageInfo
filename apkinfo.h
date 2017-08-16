#ifndef __APK_INFO__
#define __APK_INFO__

#include <iostream>
#include "tsrm_win32.h"
#include <windows.h>
#include <string>
#include "strHandle.h"
#include "strRW.h"
using namespace std;
class apkinfo{
    public:
        string packageName;             //包名
        string versionCode;             //versionCode
        string versionName;             //版本名
        string sdkVersion;              //sdk版本
        string targetSdkVersion;        //目标sdk版本
        string appName;                 //app名称
        string appName_Zh_CN;           //app名称(中文)
        string launchableActivity;      //显示在桌面上的图标点击后进入的activity类名
        string iconPath;                //app图标在包中的路径


        apkinfo(string apkPath){
            getPackageInfo(apkPath);
            parsePackageInfo();
        }

        void dumpInfo(){
            cout << " - " << appName << endl
                 << " - " << appName_Zh_CN << endl
                 << " - " << packageName << endl
                 << " - " << versionCode << endl
                 << " - " << versionName << endl
                 << " - " << sdkVersion << endl
                 << " - " << targetSdkVersion << endl
                 << " - " << launchableActivity << endl
                 << " - " << iconPath << endl
                 ;
        }
    private:
        void getPackageInfo(string apkPath){
            //tools\bin\aapt.exe d badging "目标apk文件" > tools\apkinfo\info
            string cmd = "";
            cmd = "tools\\bin\\aapt.exe d badging \"" + apkPath + "\" > tools\\apkinfo\\info";
            //cout<<cmd<<endl;
            system(cmd.c_str());
        }
        void parsePackageInfo(){
            string infoText = readStr("tools\\apkinfo\\info");
            string_replace(infoText, " ","");
            packageName         = getMiddleStr(infoText,"package:name='","'");
            versionCode         = getMiddleStr(infoText,"versionCode='","'");
            versionName         = getMiddleStr(infoText,"versionName='","'");
            sdkVersion          = getMiddleStr(infoText,"sdkVersion:'","'");
            targetSdkVersion    = getMiddleStr(infoText,"targetSdkVersion:'","'");
            appName             = getMiddleStr(infoText,"application-label:'","'");
            appName_Zh_CN       = getMiddleStr(infoText,"application-label-zh_CN:'","'");
            launchableActivity  = getMiddleStr(infoText,"launchable-activity:name='","'");
            iconPath            = getMiddleStr(infoText,"icon='","'");
        }
		
};

#endif // __APK_INFO_HEAD__
