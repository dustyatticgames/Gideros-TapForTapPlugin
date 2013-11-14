#include "gideros.h"
#include "lua.h"
#include "lauxlib.h"
#define LUA_LIB
#include <jni.h>
//this is for debugginh purpose
//and should be commented out before deployment
//you can log using
//__android_log_print(ANDROID_LOG_DEBUG, "tag", "Output String");
#include <android/log.h>
 
//some configurations of our plugin
static const char* pluginName = "tapfortapplugin";
static const char* pluginVersion = "1.0";
static const char* javaClassName = "com/giderosmobile/android/plugins/TapForTapPlugin";
 
//Store Java Environment reference
static JNIEnv *ENV;
//Store our main class, what we will use as plugin
static jclass cls;

static jmethodID jInitialize;
static jmethodID jLoadAndShowInterstitial;

static int initialize(lua_State *L)
{
	if(ENV == NULL) return 0;
	
	if(cls == NULL)
	{
		jclass tmp = ENV->FindClass(javaClassName);
		cls = (jclass)ENV->NewGlobalRef(tmp);
		if(!cls) return 0;
	}

	if(jInitialize == NULL)
	{
		jInitialize = ENV->GetStaticMethodID(cls, "initialize", "(Ljava/lang/String;)V");
		if(!jInitialize) return 0;
	}

	const char *apiKeyString = lua_tostring(L, 1);

	ENV->CallStaticObjectMethod(cls, jInitialize, ENV->NewStringUTF(apiKeyString));
	
	return 1;
}

static int loadAndShowInterstitial(lua_State *L)
{
	if(ENV == NULL) return 0;
	
	if(cls == NULL)
	{
		jclass tmp = ENV->FindClass(javaClassName);
		cls = (jclass)ENV->NewGlobalRef(tmp);
		if(!cls) return 0;
	}

	if(jLoadAndShowInterstitial == NULL)
	{
		jLoadAndShowInterstitial = ENV->GetStaticMethodID(cls, "loadAndShowInterstitial", "()V");
		if(!jLoadAndShowInterstitial) return 0;
	}

	ENV->CallStaticObjectMethod(cls, jLoadAndShowInterstitial);
	
	return 1;
}
 
 
//here we register all functions we could call from lua
//lua function name as key and C function as value
static const struct luaL_Reg funcs[] = {
  { "initialize", initialize },
  { "loadAndShowInterstitial", loadAndShowInterstitial },
  { NULL, NULL }
};
 
//here we register all the C functions for lua
//so lua engine would know they exists
LUALIB_API int luaopen_plugin(lua_State *L)
{
  luaL_register(L, pluginName, funcs);
  return 1;
}
 
//here we do all our stuff needs to be done on initialization
static void g_initializePlugin(lua_State *L)
{
    //get java environment reference
    ENV = g_getJNIEnv();
     
    //get global package object
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
     
    //put our plugin name inside with a callback to
    //registering C functions
    lua_pushcfunction(L, luaopen_plugin);
    lua_setfield(L, -2, pluginName);
 
    lua_pop(L, 2);
}
 
//and here we free everything we need to free
static void g_deinitializePlugin(lua_State *L)
{
 
}
 
//register our plugin with Gideros lib
REGISTER_PLUGIN(pluginName, pluginVersion)