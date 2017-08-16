/*
+----------------------------------------------------------------------+
| Swoole                                                               |
+----------------------------------------------------------------------+
| This source file is subject to version 2.0 of the Apache license,    |
| that is bundled with this package in the file LICENSE, and is        |
| available through the world-wide-web at the following url:           |
| http://www.apache.org/licenses/LICENSE-2.0.html                      |
| If you did not receive a copy of the Apache2.0 license and are unable|
| to obtain it through the world-wide-web, please send a note to       |
| license@swoole.com so we can mail you a copy immediately.            |
+----------------------------------------------------------------------+
| Author: Tianfeng Han  <mikan.tenny@gmail.com>                        |
+----------------------------------------------------------------------+
*/

#include "phpx.h"
#include "strHandle.h"
#include "strRW.h"
#include "iostream"

using namespace php;
using namespace std;


void executeCMD(const char *cmd, char *result);

Array parsePackageInfo(char *infoText);

void Apk_construct(Object &_this, Args &args, Variant &retval);

void Apk_apkInfo(Object &_this, Args &args, Variant &retval);

PHPX_EXTENSION()
{
	Extension *ext = new Extension("test", "0.0.1");

	ext->onStart = [ext]
	{
		Class *apk = new Class("Apk");
		/**
		* 注册构造方法
		*/
		apk->addMethod("__construct", Apk_construct, CONSTRUCT);
		/**
		* 普通方法
		*/
		apk->addMethod(PHPX_ME(Apk, apkInfo));
		
		ext->registerClass(apk);
	};

	return ext;
}

void Apk_construct(Object &_this, Args &args, Variant &retval)
{
	_this.set("path", args[0]);
}

void Apk_apkInfo(Object &_this, Args &args, Variant &retval)
{
	string apkPath = _this.get("path").toCString();
	string cmd = "";
	string fullPath = "E:\\php-7.1.8\\aapt.exe d badging " + apkPath;
	cout << fullPath << endl;
	Array apkInfo;
	char result[1000000];
	executeCMD(fullPath.c_str(), result);
	apkInfo = parsePackageInfo(result);
	retval = apkInfo;
}

void executeCMD(const char *cmd, char *result)
{
	char buf_ps[1024];
	char ps[1024] = { 0 };
	FILE *ptr;
	strcpy(ps, cmd);
	if ((ptr = popen(ps, "r")) != NULL)
	{
		while (fgets(buf_ps, 1024, ptr) != NULL)
		{
			//         可以通过这行来获取shell命令行中的每一行的输出  
			//         printf("%s", buf_ps);  
			strcat(result, buf_ps);
			if (strlen(result)>1024)
				break;
		}
		pclose(ptr);
		ptr = NULL;
	}
	else
	{
		printf("popen %s error\n", ps);
	}
}
Array parsePackageInfo(char *infoText) {
	Array packageInfo;
	string infoString = infoText;
	string_replace(infoString, " ", "");
	packageInfo.set("packageNname", getMiddleStr(infoString, "package:name='", "'"));
	packageInfo.set("versionCode", getMiddleStr(infoString, "versionCode='", "'"));
	packageInfo.set("versionName", getMiddleStr(infoString, "versionName='", "'"));
	packageInfo.set("sdkVersion", getMiddleStr(infoString, "sdkVersion:'", "'"));
	packageInfo.set("targetSdkVersion", getMiddleStr(infoString, "targetSdkVersion:'", "'"));
	packageInfo.set("applicationLabel", getMiddleStr(infoString, "application-label:'", "'"));
	packageInfo.set("applicationLabelZhCN", getMiddleStr(infoString, "application-label-zh_CN:'", "'"));
	packageInfo.set("launchableActivityName", getMiddleStr(infoString, "launchable-activity:name='", "'"));
	packageInfo.set("icon", getMiddleStr(infoString, "icon='", "'"));
	return packageInfo;
}