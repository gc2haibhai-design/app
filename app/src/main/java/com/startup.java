package com.Mrkaushikhaxor;

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.os.Process;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.text.Html;
import android.util.Base64;
import android.util.Log;
import android.text.Html;
import android.widget.Toast;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Handler;
import android.provider.Settings;
import android.text.Html;
import android.view.Gravity;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.view.View;
import android.widget.Toast;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.File;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import android.util.Log;
import android.app.AlertDialog;
import android.content.DialogInterface;

import com.Mrkaushikhaxor.*;

public class startup {
	
    private static final String TAG = "Mod Menu";
    public static String cacheDir;

    public static void Start(final Context context) {
        Toast.makeText(context, (Html.fromHtml("<font face='bold'> <font color='#000000'>Modded By - @Mrkaushikhaxor</font></font>")), Toast.LENGTH_LONG).show();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && !Settings.canDrawOverlays(context)) {
            context.startActivity(new Intent("android.settings.action.MANAGE_OVERLAY_PERMISSION",
                                             Uri.parse("package:" + context.getPackageName())));
                    } else {
            Handler handler = new Handler();
            handler.postDelayed(new Runnable() {
                    @Override
                                public void run() {
				                context.startService(new Intent(context, Injector.class));
                                    
                    }
                }, 2500);
        }

        
    }
    

    private static void writeToFile(String name, String base64) {
        File file = new File(cacheDir + name);
        try {
            if (!file.exists()) {
                file.createNewFile();
            }
            FileOutputStream fos = new FileOutputStream(file);
            byte[] decode = Base64.decode(base64, 0);
            fos.write(decode);
            fos.close();
        } catch (Exception e) {
            Log.e(TAG, e.getMessage());
        }
    }
}

