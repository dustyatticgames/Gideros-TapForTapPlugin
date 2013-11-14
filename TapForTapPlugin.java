package com.giderosmobile.android.plugins;

import android.util.Log;

import android.app.Activity;

import com.tapfortap.AppWall;
import com.tapfortap.Banner;
import com.tapfortap.Interstitial;
import com.tapfortap.Interstitial.InterstitialListener;
import com.tapfortap.TapForTap;

/**
 * Gideros plugin which calls Tap for Tap libraries.
 * Place this file in your "[Exported Project]\src\com\giderosmobile\android\plugins" directory.
 */
public class TapForTapPlugin {
    private static Activity currentActivity;
    private static InterstitialListener interstitialListener;

    public static void onCreate(Activity activity) {
        currentActivity = activity;

        // Create a basic InterstitialListener
        interstitialListener = new InterstitialListener() {
            public void interstitialOnReceive(Interstitial interstitial) {
                interstitial.show();
            }

            public void interstitialOnFail(Interstitial interstitial, String reason, Throwable throwable) {
            }

            public void interstitialOnShow(Interstitial interstitial) {
            }

            public void interstitialOnTap(Interstitial interstitial) {
            }

            public void interstitialOnDismiss(Interstitial interstitial) {
            }
        };
    }

    public static void initialize(String apiKey) {
        TapForTap.initialize(currentActivity, apiKey);
    }

    /**
     * Load an Interstitial, the InterstitialListener will automatically show it when loaded.
     */
    public static void loadAndShowInterstitial() {
        Interstitial interstitial = Interstitial.create(currentActivity.getApplicationContext(), interstitialListener);
        interstitial.load();
    }

    public static void onStart() {
    }

    public static void onResume() {
    }

    public static void onPause() {
    }

    public static void onStop() {
    }

    public static void onDestroy() {
    }
}
