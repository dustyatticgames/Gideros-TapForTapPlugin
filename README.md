Gideros-TapForTapPlugin
=======================

This is a very basic implementation of a Tap for Tap plugin for Gideros.

Thanks to Arturs Sosins at http://appcodingeasy.com/ for providing great tutoral to make a Gideros plugin.

See more here: http://appcodingeasy.com/Gideros-Mobile/Creating-plugins-for-Android-in-Gideros

Currently I've only implemented what I've needed which is showing interstitial ads but I'm hoping others will help flesh out some more functionality.

To use:

First, you'll need to put the Tap for Tap SDK into your exported project.

This includes copying their SDK jar file to your "[Exported Project]\libs" and modifying "[Exported Project]\AndroidManifest.xml".

See https://tapfortap.com/doc/android/integration for detailed instructions.


Then, modify your "[Exported Project]\src\com\giderosmobile\android\[Exported Project]Activity.java"

Adding System.loadLibrary("tapfortapplugin"); after System.loadLibrary("lfs"); 

Adding "com.giderosmobile.android.plugins.TapForTapPlugin" to the externalClasses array.


Copy the  "Gideros-TapForTapPlugin\TapForTapPlugin.java" file to your exported Gideros project folder "[Exported Project]\src\com\giderosmobile\android\plugins"


Next, copy "Gideros-TapForTapPlugin\TapForTapPlugin\libs\armeabi\libtapfortapplugin.so" and Gideros-TapForTapPlugin\TapForTapPlugin\libs\armeabi-v7a\libtapfortapplugin.so" to their respective folders in "[Exported Project]\libs"


Now you should be able to call your plugin from Gideros:


if (application:getDeviceInfo() == "Android") then
    require("tapfortapplugin");
    tapfortapplugin.initialize("putyourtapfortapapikeyhere");
    tapfortapplugin.loadAndShowInterstitial();
end

