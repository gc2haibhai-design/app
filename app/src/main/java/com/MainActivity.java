package com.Mrkaushikhaxor;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {
	static{   
	System.loadLibrary("Mrkaushikhaxor");

    }
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        startup.Start(this);
    }
}
