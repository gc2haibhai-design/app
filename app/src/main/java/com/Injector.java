package com.Mrkaushikhaxor;

import android.app.ProgressDialog;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.content.res.ColorStateList;
import android.content.res.Resources;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.graphics.Point;
import android.graphics.Typeface;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.os.IBinder;
import android.util.Base64;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;
import com.Mrkaushikhaxor.FileUtil;
import com.Mrkaushikhaxor.RUtils;


import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Timer;
import java.util.TimerTask;
import android.widget.ToggleButton;
public class Injector
extends Service {
    final LinearLayout[] contentLayouts;
    float density;
    int dpi;
    RelativeLayout g_iconLayout;
    LinearLayout g_mainLayout;
    final LinearLayout[] layoutParents;
    boolean resetAvailable;
    int scanThread;
    int screenHeight;
    int screenWidth;
    SharedPreferences sp;
	String rebrand = " ";
		
	String jodop = "[ Mr Kaushik Haxor ]        ";
	
    static Context ctx;
    final ScrollView[] scrollLayouts;
    int selectedTab;
    final FrameLayout[] tabLayouts;
    int type;
    WindowManager windowManager;
    static boolean execs = false;
	static boolean count = false;
    private RelativeLayout relativeLayout;
    final String[] TABS;
	SharedPreferences configPrefs;
	String bgColor="#1b1a17";
    String colorBtnBlue="#ffffff";
	String colorBtnNormal = "#f44336";
    String time;
    TextView timerTV;
    Switch switch_;
	CheckBox save;
    EditText mail, pass, email;
    Button init;
	Button b1;
	private final String PASS = "PASS";
  //  private Prefs prefs;
    private Timer _timer = new Timer();
	private TimerTask tier;
	public static GradientDrawable drawable(int radius, String color, int stroke, String strokeColor) {
		GradientDrawable drawable = new GradientDrawable();
		drawable.setCornerRadius(radius);
		drawable.setColor(Color.parseColor(color));
		drawable.setStroke(stroke, Color.parseColor(strokeColor));
		return drawable;
	}
	

    public Injector() {
        String[] arrstring = new String[]{"Player World", "Item's", "Vehicle", "Aimbot", "Extras", "Settings", "Info"};
        this.TABS = arrstring;
        this.tabLayouts = new FrameLayout[arrstring.length];
        this.scrollLayouts = new ScrollView[arrstring.length];
        this.layoutParents = new LinearLayout[arrstring.length];
        this.contentLayouts = new LinearLayout[arrstring.length];
        this.resetAvailable = false;
        this.selectedTab = 0;
        this.scanThread = 1;
    }
    private void AddToggle(Object object,String name, CompoundButton.OnCheckedChangeListener onCheckedChangeListener) {
        switch_ = new Switch((Context)this);
		Typeface Type2 = Typeface.createFromAsset(getAssets(),"fonts/MK4.TTF"); 
		switch_.setTypeface(Type2);	
		switch_.setText(name);
        switch_.setTextColor(Color.GREEN);
		switch_.setTextSize(17);
		switch_.setPadding(dp(4), dp(4), dp(4), dp(4));
		switch_.setOnCheckedChangeListener(onCheckedChangeListener);
        switch_.setLayoutParams((ViewGroup.LayoutParams)new LinearLayout.LayoutParams(-1, -1));
        ColorStateList buttonStates = new ColorStateList(
			new int[][]{
				new int[]{-android.R.attr.state_enabled},
				new int[]{android.R.attr.state_checked},
				new int[]{}
			},
			new int[]{
				Color.BLUE,
				Color.parseColor(colorBtnBlue),
				Color.parseColor("#ECECEC")
			}
		);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			switch_.getThumbDrawable().setTintList(buttonStates);
			switch_.getTrackDrawable().setTintList(buttonStates);
		}

        if (object instanceof ViewGroup) {
            ((ViewGroup)object).addView((View)switch_);
            return;
        }
        if (object instanceof Integer) {
            this.layoutParents[(Integer)object].addView((View)switch_);
        }
        }

    void AddButton(Object object, String string, int n, int n2, View.OnClickListener onClickListener) {
        LinearLayout linearLayout = new LinearLayout((Context)this);
        linearLayout.setOrientation(1);
        linearLayout.setLayoutParams((ViewGroup.LayoutParams)new LinearLayout.LayoutParams(n, n2));
        linearLayout.setPadding(this.convertSizeToDp(15.0f), this.convertSizeToDp(15.0f), this.convertSizeToDp(15.0f), this.convertSizeToDp(15.0f));
        linearLayout.setGravity(17);
        Button button = new Button((Context)this);
        button.setText((CharSequence)string);
        button.setTextColor(-1);
        button.setOnClickListener(onClickListener);
        button.setLayoutParams((ViewGroup.LayoutParams)new LinearLayout.LayoutParams(-1, -1));
        GradientDrawable gradientDrawable = new GradientDrawable();
        gradientDrawable.setColor(Color.parseColor("#FF343434"));//Color.argb((int)255, (int)63, (int)63, (int)63));
        gradientDrawable.setStroke(2, Color.argb((int)255, (int)0, (int)0, (int)0));
        button.setBackground((Drawable)gradientDrawable);
        linearLayout.addView((View)button);
        if (object instanceof ViewGroup) {
            ((ViewGroup)object).addView((View)linearLayout);
            return;
        }
        if (object instanceof Integer) {
            this.layoutParents[(Integer)object].addView((View)linearLayout);
        }
    }
    
    void AddCheckbox(Object object, String string, CompoundButton.OnCheckedChangeListener onCheckedChangeListener) {
        CheckBox checkBox = new CheckBox((Context)this);
        checkBox.setText((CharSequence)string);
        checkBox.setTextColor(Color.GREEN);
		Typeface Type2 = Typeface.createFromAsset(getAssets(),"fonts/MK4.TTF"); 
		checkBox.setTypeface(Type2);
		checkBox.setTextSize(17);
        checkBox.setOnCheckedChangeListener(onCheckedChangeListener);
		setCheckBoxColor(checkBox, Color.parseColor(colorBtnBlue), Color.parseColor(colorBtnBlue));
        checkBox.setLayoutParams((ViewGroup.LayoutParams)new LinearLayout.LayoutParams(-2, -2));

        if (object instanceof ViewGroup) {
            ((ViewGroup)object).addView((View)checkBox);
            return;
        }
        if (object instanceof Integer) {
            this.layoutParents[(Integer)object].addView((View)checkBox);
        }
    }



	public void setCheckBoxColor(CheckBox checkBox, int uncheckedColor, int checkedColor) {
		ColorStateList colorStateList = new ColorStateList(
			new int[][] {
				new int[] { -android.R.attr.state_checked }, // unchecked
				new int[] {  android.R.attr.state_checked }  // checked
			},
			new int[] {
				uncheckedColor,
				checkedColor
			}
		);
		checkBox.setButtonTintList(colorStateList);


    }

    void AddFloatSeekbar(Object object, String string, final int n, int n2, int n3, final String string2, final String string3, final SeekBar.OnSeekBarChangeListener onSeekBarChangeListener) {
        int n4 = n3;
        LinearLayout linearLayout = new LinearLayout((Context)this);
        linearLayout.setLayoutParams((ViewGroup.LayoutParams)new LinearLayout.LayoutParams(-1, -2));
        linearLayout.setOrientation(0);
        TextView textView = new TextView((Context)this);
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(string);
        stringBuilder.append(":");
        textView.setText((CharSequence)stringBuilder.toString());
        textView.setTextSize(1, 12.5f);
        textView.setPadding(this.convertSizeToDp(10.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(10.0f), this.convertSizeToDp(5.0f));
        textView.setTextColor(-1);
        textView.setLayoutParams((ViewGroup.LayoutParams)new RelativeLayout.LayoutParams(-2, -2));
        textView.setGravity(3);
        SeekBar seekBar = new SeekBar((Context)this);
        seekBar.setMax(n2);
        if (Build.VERSION.SDK_INT >= 26) {
            seekBar.setMin(n);
            seekBar.setProgress(n);
        }
        if (Build.VERSION.SDK_INT >= 21) {
            seekBar.setThumbTintList(ColorStateList.valueOf((int)-1));
            seekBar.setProgressTintList(ColorStateList.valueOf((int)-1));
        }
        seekBar.setPadding(this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f));
        final TextView textView2 = new TextView((Context)this);
        StringBuilder stringBuilder2 = new StringBuilder();
        stringBuilder2.append(string2);
        stringBuilder2.append(String.valueOf((float)((float)n / 10.0f)));
        stringBuilder2.append(string3);
        textView2.setText((CharSequence)stringBuilder2.toString());
        textView2.setGravity(5);
        textView2.setTextSize(1, 12.5f);
        textView2.setLayoutParams((ViewGroup.LayoutParams)new RelativeLayout.LayoutParams(-1, -2));
        textView2.setPadding(this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f));
        textView2.setTextColor(-1);
        if (n4 != 0) {
            if (n4 < n) {
                n4 = n;
            }
            if (n4 > n2) {
                n4 = n2;
            }
            StringBuilder stringBuilder3 = new StringBuilder();
            stringBuilder3.append(string2);
            stringBuilder3.append((float)n4 / (float)n2);
            stringBuilder3.append(string3);
            textView2.setText((CharSequence)stringBuilder3.toString());
            seekBar.setProgress(n4);
        }
        SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2 = new SeekBar.OnSeekBarChangeListener(){

            public void onProgressChanged(SeekBar seekBar, int n2, boolean bl) {
                SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2;
                if (n2 < n) {
                    n2 = n;
                    seekBar.setProgress(n2);
                }
                if ((onSeekBarChangeListener2 = onSeekBarChangeListener) != null) {
                    onSeekBarChangeListener2.onProgressChanged(seekBar, n2, bl);
                }
                TextView textView = textView2;
                StringBuilder stringBuilder = new StringBuilder();
                stringBuilder.append(string2);
                stringBuilder.append(String.valueOf((float)((float)n2 / 10.0f)));
                stringBuilder.append(string3);
                textView.setText((CharSequence)stringBuilder.toString());
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
                SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2 = onSeekBarChangeListener;
                if (onSeekBarChangeListener2 != null) {
                    onSeekBarChangeListener2.onStartTrackingTouch(seekBar);
                }
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
                SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2 = onSeekBarChangeListener;
                if (onSeekBarChangeListener2 != null) {
                    onSeekBarChangeListener2.onStopTrackingTouch(seekBar);
                }
            }
        };
        seekBar.setOnSeekBarChangeListener(onSeekBarChangeListener2);
        linearLayout.addView((View)textView);
        linearLayout.addView((View)textView2);
        if (object instanceof ViewGroup) {
            ((ViewGroup)object).addView((View)linearLayout);
            ((ViewGroup)object).addView((View)seekBar);
            return;
        }
        if (object instanceof Integer) {
            this.layoutParents[(Integer)object].addView((View)linearLayout);
            this.layoutParents[(Integer)object].addView((View)seekBar);
        }
    }

    void AddRadioButton(Object object, String[] arrstring, int n, RadioGroup.OnCheckedChangeListener onCheckedChangeListener) {
        RadioGroup radioGroup = new RadioGroup((Context)this);
        RadioButton[] arrradioButton = new RadioButton[arrstring.length];
        radioGroup.setOrientation(1);
        for (int i = 0; i < arrstring.length; ++i) {
            arrradioButton[i] = new RadioButton((Context)this);
            if (i == n) {
                arrradioButton[i].setChecked(true);
            }
            arrradioButton[i].setPadding(this.convertSizeToDp(10.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(10.0f), this.convertSizeToDp(5.0f));
            arrradioButton[i].setText((CharSequence)arrstring[i]);
            arrradioButton[i].setTextSize(1, 12.5f);
            arrradioButton[i].setId(i);
            arrradioButton[i].setGravity(5);
            arrradioButton[i].setTextColor(-1);
            setRadioButtonColor(arrradioButton[i],Color.parseColor(colorBtnBlue),Color.parseColor(colorBtnBlue));
            radioGroup.addView((View)arrradioButton[i]);
        }
        radioGroup.setOnCheckedChangeListener(onCheckedChangeListener);
        radioGroup.setLayoutParams((ViewGroup.LayoutParams)new RelativeLayout.LayoutParams(-1, -2));
        if (object instanceof ViewGroup) {
            ((ViewGroup)object).addView((View)radioGroup);
            return;
        }
        if (object instanceof Integer) {
            this.layoutParents[(Integer)object].addView((View)radioGroup);
        }
    }
    
    public void setRadioButtonColor(RadioButton checkBox, int uncheckedColor, int checkedColor) {
        ColorStateList colorStateList = new ColorStateList(
            new int[][] {
                new int[] { -android.R.attr.state_checked }, // unchecked
                new int[] {  android.R.attr.state_checked }  // checked
            },
            new int[] {
                uncheckedColor,
                checkedColor
            }
        );
        checkBox.setButtonTintList(colorStateList);
	}

    void AddSeekbar(Object object, String string, final int n, int n2, int n3, final String string2, final String string3, final SeekBar.OnSeekBarChangeListener onSeekBarChangeListener) {
        int n4 = n3;
        LinearLayout linearLayout = new LinearLayout((Context)this);
        linearLayout.setLayoutParams((ViewGroup.LayoutParams)new LinearLayout.LayoutParams(-1, -2));
        linearLayout.setOrientation(0);
        TextView textView = new TextView((Context)this);
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(string);
        stringBuilder.append(":");
        textView.setText((CharSequence)stringBuilder.toString());
        textView.setTextSize(1, 12.5f);
        textView.setPadding(this.convertSizeToDp(10.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(10.0f), this.convertSizeToDp(5.0f));
        textView.setTextColor(-1);
        textView.setLayoutParams((ViewGroup.LayoutParams)new RelativeLayout.LayoutParams(-2, -2));
        textView.setGravity(3);
        SeekBar seekBar = new SeekBar((Context)this);
        seekBar.setMax(n2);
        if (Build.VERSION.SDK_INT >= 26) {
            seekBar.setMin(n);
            seekBar.setProgress(n);
        }
        if (Build.VERSION.SDK_INT >= 21) {
            seekBar.setThumbTintList(ColorStateList.valueOf((int)-1));
            seekBar.setProgressTintList(ColorStateList.valueOf((int)-1));
        }
        seekBar.setPadding(this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f));
        final TextView textView2 = new TextView((Context)this);
        StringBuilder stringBuilder2 = new StringBuilder();
        stringBuilder2.append(string2);
        stringBuilder2.append(n);
        stringBuilder2.append(string3);
        textView2.setText((CharSequence)stringBuilder2.toString());
        textView2.setGravity(5);
        textView2.setTextSize(1, 12.5f);
        textView2.setLayoutParams((ViewGroup.LayoutParams)new RelativeLayout.LayoutParams(-1, -2));
        textView2.setPadding(this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f));
        textView2.setTextColor(-1);
        if (n4 != 0) {
            if (n4 < n) {
                n4 = n;
            }
            if (n4 > n2) {
                n4 = n2;
            }
            StringBuilder stringBuilder3 = new StringBuilder();
            stringBuilder3.append(string2);
            stringBuilder3.append(n4);
            stringBuilder3.append(string3);
            textView2.setText((CharSequence)stringBuilder3.toString());
            seekBar.setProgress(n4);
        }
        SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2 = new SeekBar.OnSeekBarChangeListener(){

            public void onProgressChanged(SeekBar seekBar, int n2, boolean bl) {
                SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2;
                if (n2 < n) {
                    n2 = n;
                    seekBar.setProgress(n2);
                }
                if ((onSeekBarChangeListener2 = onSeekBarChangeListener) != null) {
                    onSeekBarChangeListener2.onProgressChanged(seekBar, n2, bl);
                }
                TextView textView = textView2;
                StringBuilder stringBuilder = new StringBuilder();
                stringBuilder.append(string2);
                stringBuilder.append(n2);
                stringBuilder.append(string3);
                textView.setText((CharSequence)stringBuilder.toString());
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
                SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2 = onSeekBarChangeListener;
                if (onSeekBarChangeListener2 != null) {
                    onSeekBarChangeListener2.onStartTrackingTouch(seekBar);
                }
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
                SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2 = onSeekBarChangeListener;
                if (onSeekBarChangeListener2 != null) {
                    onSeekBarChangeListener2.onStopTrackingTouch(seekBar);
                }
            }
        };
        seekBar.setOnSeekBarChangeListener(onSeekBarChangeListener2);
        linearLayout.addView((View)textView);
        linearLayout.addView((View)textView2);
        if (object instanceof ViewGroup) {
            ((ViewGroup)object).addView((View)linearLayout);
            ((ViewGroup)object).addView((View)seekBar);
            return;
        }
        if (object instanceof Integer) {
            this.layoutParents[(Integer)object].addView((View)linearLayout);
            this.layoutParents[(Integer)object].addView((View)seekBar);
        }
    }
    
    void AddSeekbar2(Object data, String text, int min, int max, int value, final String prefix, final String suffix, final SeekBar.OnSeekBarChangeListener listener) {
        LinearLayout linearLayout = new LinearLayout(this);
        linearLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        linearLayout.setOrientation(LinearLayout.HORIZONTAL);

        TextView textV = new TextView(this);
        textV.setText(text + ":");
        textV.setTextSize(convertSizeToDp(6.f));
        textV.setPadding(15, 15, 15, 15);
        textV.setTextColor(Color.WHITE);
        textV.setLayoutParams(new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        textV.setGravity(Gravity.LEFT);

        SeekBar seekBar = new SeekBar(this);
        seekBar.setMax(max);
        if (Build.VERSION.SDK_INT >= 26) {
            seekBar.setMin(min);
            seekBar.setProgress(min);
        }
        if (Build.VERSION.SDK_INT >= 21) {
            seekBar.setThumbTintList(ColorStateList.valueOf(Color.parseColor(colorBtnBlue)));
            seekBar.setProgressTintList(ColorStateList.valueOf(Color.parseColor(colorBtnBlue)));
        }
        seekBar.setPadding(20, 15, 20, 15);

        final TextView textValue = new TextView(this);
        textValue.setText(prefix + min + suffix);
        textValue.setGravity(Gravity.RIGHT);
        textValue.setTextSize(convertSizeToDp(6.f));
        textValue.setLayoutParams(new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        textValue.setPadding(20, 15, 20, 15);
        textValue.setTextColor(Color.WHITE);

        final int minimValue = min;
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
                @Override
                public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                    if (progress < minimValue) {
                        progress = minimValue;
                        seekBar.setProgress(progress);
                    }

                    if (listener != null) listener.onProgressChanged(seekBar, progress, fromUser);
                    textValue.setText(prefix + progress + suffix);
                }

                @Override
                public void onStartTrackingTouch(SeekBar seekBar) {
                    if (listener != null) listener.onStartTrackingTouch(seekBar);
                }

                @Override
                public void onStopTrackingTouch(SeekBar seekBar) {
                    if (listener != null) listener.onStopTrackingTouch(seekBar);
                }
            });

        if (value != 0) {
            if (value < min)
                value = min;
            if (value > max)
                value = max;

            textValue.setText(prefix + value + suffix);
            seekBar.setProgress(value);
        }

        linearLayout.addView(textV);
        linearLayout.addView(textValue);

        if (data instanceof Integer) {
            layoutParents[(Integer) data].addView(linearLayout);
            layoutParents[(Integer) data].addView(seekBar);
        } else if (data instanceof ViewGroup) {
            ((ViewGroup) data).addView(linearLayout);
            ((ViewGroup) data).addView(seekBar);
        }
    }
    
    void AddText(Object object, String string, String string2) {
        TextView textView = new TextView((Context)this);
        textView.setText(string);
        textView.setTextColor(Color.parseColor((String)string2));
        textView.setPadding(dp(4), dp(1), dp(1), dp(1));
        textView.setTextSize(14);

        if (object instanceof ViewGroup) {
            ((ViewGroup)object).addView((View)textView);
            return;
        }
        if (object instanceof Integer) {
            this.layoutParents[(Integer)object].addView((View)textView);
        }
    }

    int convertSizeToDp(float f) {
        return Math.round((float)TypedValue.applyDimension((int)1, (float)f, (DisplayMetrics)this.getResources().getDisplayMetrics()));
    }

    public IBinder onBind(Intent intent) {
        return null;
    }

    void AddSeekbarng(Object object, String string, final int n, int n2, int n3, final String string2, final String string3, final SeekBar.OnSeekBarChangeListener onSeekBarChangeListener) {
        int n4 = n3;
        LinearLayout linearLayout = new LinearLayout((Context)this);
        linearLayout.setLayoutParams((ViewGroup.LayoutParams)new LinearLayout.LayoutParams(-1, -2));
        linearLayout.setOrientation(0);
        TextView textView = new TextView((Context)this);
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(string);
        stringBuilder.append(":");
        textView.setText((CharSequence)stringBuilder.toString());
        textView.setTextSize(1, 12.5f);
        textView.setPadding(this.convertSizeToDp(10.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(10.0f), this.convertSizeToDp(5.0f));
        textView.setTextColor(-1);
        textView.setLayoutParams((ViewGroup.LayoutParams)new RelativeLayout.LayoutParams(-2, -2));
        textView.setGravity(3);
        SeekBar seekBar = new SeekBar((Context)this);
        seekBar.setMax(n2);
        if (Build.VERSION.SDK_INT >= 26) {
            seekBar.setMin(n);
            seekBar.setProgress(n);
        }
        if (Build.VERSION.SDK_INT >= 21) {
            seekBar.setThumbTintList(ColorStateList.valueOf((int)-1));
            seekBar.setProgressTintList(ColorStateList.valueOf((int)-1));
        }
        seekBar.setPadding(this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f));
        final TextView textView2 = new TextView((Context)this);
        StringBuilder stringBuilder2 = new StringBuilder();
        stringBuilder2.append(string2);
        stringBuilder2.append(n);
        stringBuilder2.append(string3);
        textView2.setText((CharSequence)stringBuilder2.toString());
        textView2.setGravity(5);
        textView2.setTextSize(1, 12.5f);
        textView2.setLayoutParams((ViewGroup.LayoutParams)new RelativeLayout.LayoutParams(-1, -2));
        textView2.setPadding(this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f), this.convertSizeToDp(15.0f), this.convertSizeToDp(5.0f));
        textView2.setTextColor(-1);
        if (n4 != 0) {
            if (n4 < n) {
                n4 = n;
            }
            if (n4 > n2) {
                n4 = n2;
            }
            StringBuilder stringBuilder3 = new StringBuilder();
            stringBuilder3.append(string2);
            stringBuilder3.append(n4);
            stringBuilder3.append(string3);
            textView2.setText((CharSequence)stringBuilder3.toString());
            seekBar.setProgress(n4);
        }
        SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2 = new SeekBar.OnSeekBarChangeListener(){

            public void onProgressChanged(SeekBar seekBar, int n2, boolean bl) {
                SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2;
                if (n2 < n) {
                    n2 = n;
                    seekBar.setProgress(n2);
                }
                if ((onSeekBarChangeListener2 = onSeekBarChangeListener) != null) {
                    onSeekBarChangeListener2.onProgressChanged(seekBar, n2, bl);
                }
                TextView textView = textView2;
                StringBuilder stringBuilder = new StringBuilder();
                stringBuilder.append(string2);
                stringBuilder.append(n2);
                stringBuilder.append(string3);
                textView.setText(stringBuilder.toString());
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
                SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2 = onSeekBarChangeListener;
                if (onSeekBarChangeListener2 != null) {
                    onSeekBarChangeListener2.onStartTrackingTouch(seekBar);
                }
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
                SeekBar.OnSeekBarChangeListener onSeekBarChangeListener2 = onSeekBarChangeListener;
                if (onSeekBarChangeListener2 != null) {
                    onSeekBarChangeListener2.onStopTrackingTouch(seekBar);
                }
            }
        };
        seekBar.setOnSeekBarChangeListener(onSeekBarChangeListener2);
        linearLayout.addView((View)textView);
        linearLayout.addView((View)textView2);
        if (object instanceof ViewGroup) {
            ((ViewGroup)object).addView((View)linearLayout);
            ((ViewGroup)object).addView((View)seekBar);
            return;
        }
        if (object instanceof Integer) {
            this.layoutParents[(Integer)object].addView((View)linearLayout);
            this.layoutParents[(Integer)object].addView((View)seekBar);
        }
    }
    
    static boolean getConfig(String key){
        SharedPreferences sp=ctx.getSharedPreferences("espValue",Context.MODE_PRIVATE);
        return  sp.getBoolean(key,false);
    }
	private int convertDipToPixels(float f) {
        return (int) ((f * getResources().getDisplayMetrics().density) + 0.5f);
    }
	
	
    public void onCreate() {

        System.loadLibrary("Mrkaushikhaxor");
 
        ctx=this;
        final LinearLayout linearLayout;
        windowManager = (WindowManager) getSystemService(WINDOW_SERVICE);
        final Point point = new Point();
        windowManager.getDefaultDisplay().getRealSize(point);
        screenWidth = point.x;
        screenHeight = point.y;
        dpi = Resources.getSystem().getDisplayMetrics().densityDpi;
        density = Resources.getSystem().getDisplayMetrics().density;
        final int n = convertSizeToDp(220.0f);//220
        final int n2 = convertSizeToDp(150.0f);//160
        g_mainLayout = linearLayout = new LinearLayout((Context)this);
        linearLayout.setLayoutParams((ViewGroup.LayoutParams)new LinearLayout.LayoutParams(-1, -1));
        linearLayout.setBackgroundColor(Color.parseColor("#000000"));//Color.argb(255,35,44,44));
		linearLayout.setOrientation(linearLayout.VERTICAL);
		GradientDrawable fm2 = new GradientDrawable();
		fm2.setColor(Color.parseColor("#000000"));
		fm2.setCornerRadius(10);
		linearLayout.setBackground(fm2);
		LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(-1, this.convertSizeToDp(30.0f));
		lp.setMargins(20,15,20,10);
		GradientDrawable fm = new GradientDrawable();
		fm.setColor(Color.parseColor("#FF0000"));
		fm.setCornerRadius(10);
		fm.setStroke(3,Color.WHITE);
        Integer n3 = 1;
        linearLayout.setOrientation(1);
        int n4 = convertSizeToDp(30.0f);
        LinearLayout frameLayout=new LinearLayout(this);
        frameLayout.setOrientation(LinearLayout.HORIZONTAL);
        frameLayout.setGravity(Gravity.CENTER);
		frameLayout.setClickable(true);
        frameLayout.setFocusable(true);
        frameLayout.setFocusableInTouchMode(true);
	    frameLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,n4));
		frameLayout.setBackground(fm);
		TextView textView = new TextView(this);
	    textView.setText(jodop);
		Typeface Type2 = Typeface.createFromAsset(getAssets(),"fonts/code.ttf"); 
		textView.setTypeface(Type2);
		Typeface Type = Typeface.createFromAsset(getAssets(),"fonts/jost.ttf"); 
        textView.setGravity(Gravity.CENTER_HORIZONTAL);
        textView.setTextColor(Color.WHITE);
        textView.setTextSize(14.0f);

        final Button button = new Button(this);
        button.setText((CharSequence)"");
	    button.setTextSize(1, 8.0f);
        button.setBackgroundColor(Color.TRANSPARENT);//Color.argb(255, 35,144,144));//BTN CLOSE
        button.setX(n - dpi / 5.5f);
        button.setLayoutParams(new RelativeLayout.LayoutParams((int)((dpi / 5.5f)), n4));
        frameLayout.addView(button);
		TextView cls = new TextView(this);
		cls.setText("X");
		cls.setGravity(Gravity.RIGHT);
		cls.setTextColor(Color.GRAY);
		cls.setPadding(convertSizeToDp(0.0f),convertSizeToDp(0.0f),convertSizeToDp(5.0f),convertSizeToDp(0.0f));

		cls.setLayoutParams(new RelativeLayout.LayoutParams((int)((dpi / 5.5f)), n4));
		cls.setX(n - dpi / 3.5f);

		
		final LinearLayout main = new LinearLayout(this);
		main.setOrientation(linearLayout.HORIZONTAL);
		main.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		//main.setBackgroundColor(Color.WHITE);
		
		
		final LinearLayout horbar = new LinearLayout(this);
	    horbar.setLayoutParams(new LinearLayout.LayoutParams(dp(130),LinearLayout.LayoutParams.MATCH_PARENT));
		horbar.setBackgroundColor(Color.parseColor("#303030"));
		horbar.setOrientation(LinearLayout.VERTICAL);
		final LinearLayout vbar = new LinearLayout(this);
		vbar.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		//vbar.setBackgroundColor(Color.parseColor("#303030"));
		final ScrollView hrscroll = new ScrollView(this);
		hrscroll.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		hrscroll.setHorizontalScrollBarEnabled(false);
		final LinearLayout scrollbg = new LinearLayout(this);
		scrollbg.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		scrollbg.setGravity(Gravity.CENTER_HORIZONTAL);
		scrollbg.setOrientation(LinearLayout.VERTICAL);
	
		GradientDrawable tabson = new GradientDrawable();
		tabson.setColor(Color.parseColor("#524E4E"));
		tabson.setCornerRadius(5);
		
		GradientDrawable sl = new GradientDrawable();
		sl.setColor(Color.GREEN);
		sl.setCornerRadius(dp(50));
    	final LinearLayout ball = new LinearLayout(this);
		LayoutParams params2 = new LayoutParams(dp(6),dp(6));
		params2.setMargins(dp(10), dp(0), 0, dp(0));
		ball.setLayoutParams(params2);
		ball.setBackground(sl);
		ball.setGravity(Gravity.RIGHT);
		
		
		final LinearLayout ballc = new LinearLayout(this);
	  ballc.setLayoutParams(params2);
		ballc.setBackground(sl);
		ballc.setGravity(Gravity.RIGHT);
		
		final LinearLayout balle = new LinearLayout(this);
		balle.setLayoutParams(params2);
		balle.setBackground(sl);
		balle.setGravity(Gravity.RIGHT);
		final LinearLayout balls = new LinearLayout(this);
		balls.setLayoutParams(params2);
		balls.setBackground(sl);
		balls.setGravity(Gravity.RIGHT);
		final LinearLayout balla = new LinearLayout(this);
		balla.setLayoutParams(params2);
		balla.setBackground(sl);
		balla.setGravity(Gravity.RIGHT);
		
		final LinearLayout tabBypass = new LinearLayout(this);
		
		LayoutParams params = new LayoutParams(dp(120),dp(40));
		params.setMargins(0, dp(5), 0, dp(0));
		tabBypass.setLayoutParams(params);
		tabBypass.setBackground(tabson);
		tabBypass.setOrientation(LinearLayout.HORIZONTAL);
		tabBypass.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.CENTER_VERTICAL);
		
		
		
	   TextView txtb = new TextView(this);
		txtb.setText("Antiban");
		txtb.setTypeface(Type);
		txtb.setTextSize(12);
		txtb.setShadowLayer(10,1,1,Color.BLACK);
		txtb.setTextColor(Color.WHITE);
		
		
		final LinearLayout tabesp = new LinearLayout(this);
		tabesp.setLayoutParams(params);
		tabesp.setBackground(tabson);
		tabesp.setOrientation(LinearLayout.HORIZONTAL);
		tabesp.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.CENTER_VERTICAL);

		TextView txte = new TextView(this);
		txte.setText("Esp");
		txte.setTypeface(Type);
		txte.setTextSize(12);
		txte.setShadowLayer(10,1,1,Color.BLACK);
		txte.setTextColor(Color.WHITE);
		
		final LinearLayout tabCheat = new LinearLayout(this);
		tabCheat.setLayoutParams(params);
		tabCheat.setBackground(tabson);
		tabCheat.setOrientation(LinearLayout.HORIZONTAL);
		tabCheat.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.CENTER_VERTICAL);

		TextView txtc = new TextView(this);
		txtc.setText("Cheats");
		txtc.setTypeface(Type);
		txtc.setTextSize(12);
		txtc.setTextColor(Color.WHITE);
		txtc.setShadowLayer(10,1,1,Color.BLACK);
		final LinearLayout tabSettings = new LinearLayout(this);
		tabSettings.setLayoutParams(params);
		tabSettings.setBackground(tabson);
		tabSettings.setOrientation(LinearLayout.HORIZONTAL);
		tabSettings.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.CENTER_VERTICAL);

		TextView txts = new TextView(this);
		txts.setText("Settings");
		txts.setTypeface(Type);
		txts.setTextSize(12);
		txts.setShadowLayer(10,1,1,Color.BLACK);
		txts.setTextColor(Color.WHITE);
		
		final LinearLayout tabAcc = new LinearLayout(this);
		tabAcc.setLayoutParams(params);
		tabAcc.setBackground(tabson);
		tabAcc.setOrientation(LinearLayout.HORIZONTAL);
		tabAcc.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.CENTER_VERTICAL);

		TextView txta = new TextView(this);
		txta.setText("Account");
		txta.setTypeface(Type);
		txta.setTextSize(12);
		txta.setShadowLayer(10,1,1,Color.BLACK);
		txta.setTextColor(Color.WHITE);
		
		final ScrollView sc = new ScrollView(this);
		sc.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
	
		final LinearLayout container = new LinearLayout(this);
		container.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		container.setOrientation(LinearLayout.VERTICAL);
		container.setGravity(Gravity.CENTER_HORIZONTAL);
		
		final LinearLayout layoutBypass = new LinearLayout(this);
		layoutBypass.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		layoutBypass.setOrientation(LinearLayout.VERTICAL);
		
		
		final LinearLayout layoutEsp = new LinearLayout(this);
		layoutEsp.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		layoutEsp.setOrientation(LinearLayout.VERTICAL);
		
		LayoutParams tabparam2 = new LayoutParams(dp(100),dp(40));
	
		
		final LinearLayout layoutCheat = new LinearLayout(this);
		layoutCheat.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		layoutCheat.setOrientation(LinearLayout.VERTICAL);
		
		final LinearLayout layoutSet = new LinearLayout(this);
		layoutSet.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		layoutSet.setOrientation(LinearLayout.VERTICAL);

		final LinearLayout layoutAcc = new LinearLayout(this);
		layoutAcc.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		layoutAcc.setOrientation(LinearLayout.VERTICAL);

		
	
		
		linearLayout.addView(frameLayout);
		linearLayout.addView(main);
		frameLayout.addView(textView);
		main.addView(vbar);
		hrscroll.addView(scrollbg);
		vbar.addView(sc);
		sc.addView(container);
		container.addView(layoutBypass);
		scrollbg.addView(tabBypass);
	
        LinearLayout linearLayout2 = new LinearLayout(this);
        linearLayout2.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
        Integer n5 = 0;
        linearLayout2.setOrientation(0);
        final LinearLayout linearLayout3 = new LinearLayout(this);
        linearLayout3.setLayoutParams(new LinearLayout.LayoutParams((int)(n / 3.0f), -1));
        linearLayout3.setBackgroundColor(Color.parseColor("#1b1a17"));//Color.argb(255,35,88,88));
        linearLayout3.setOrientation(0);
        linearLayout2.addView(linearLayout3);
        ScrollView scrollView = new ScrollView(this);
        scrollView.setLayoutParams(new RelativeLayout.LayoutParams(-1, -2));
        linearLayout3.addView(scrollView);
        LinearLayout linearLayout4 = new LinearLayout(this);
        linearLayout4.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
        linearLayout4.setOrientation(1);

        scrollView.addView(linearLayout4);
        LinearLayout linearLayout5 = new LinearLayout(this);
        linearLayout5.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
        linearLayout5.setBackgroundColor(Color.parseColor("#1b1a17"));//Color.argb(255,35,111,111));
        linearLayout5.setOrientation(1);
        linearLayout2.addView(linearLayout5);
        int n6 = 0;
        do {
            int n7 = TABS.length;
            TextView textView2 = textView;
            if (n6 >= n7) break;
            scrollLayouts[n6] = new ScrollView(this);
            ScrollView scrollView2 = scrollLayouts[n6];
            LinearLayout linearLayout6 = linearLayout2;
            scrollView2.setLayoutParams(new RelativeLayout.LayoutParams(-1, -2));
            layoutParents[n6] = new LinearLayout(this);
            layoutParents[n6].setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
            layoutParents[n6].setBackgroundColor(Color.parseColor("#1b1a17"));//Color.argb(255,35,111,111));// BG MENU FITURE
            layoutParents[n6].setOrientation(1);
            scrollLayouts[n6].addView(layoutParents[n6]);
            contentLayouts[n6] = new LinearLayout(this);
            contentLayouts[n6].setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
            contentLayouts[n6].setBackgroundColor(Color.parseColor("#1b1a17"));//Color.argb(255,35,111,111)); //BG MENU ALL
            contentLayouts[n6].setOrientation(1);
            if (n6 != 0) {
                contentLayouts[n6].setVisibility(8);
            }
            contentLayouts[n6].addView(scrollLayouts[n6]);
            linearLayout5.addView(contentLayouts[n6]);
            tabLayouts[n6] = new FrameLayout(this);
            tabLayouts[n6].setLayoutParams(new LinearLayout.LayoutParams(-1, this.convertSizeToDp(40.0f)));
            TextView textView3 = new TextView(this);
            textView3.setText(TABS[n6]);
            textView3.setGravity(17);
            textView3.setTextColor(-1);
            textView3.setTypeface(null, 1);
            int n8 = convertSizeToDp(5.0f);
            int n9 = convertSizeToDp(5.0f);
            LinearLayout linearLayout7 = linearLayout5;
            int n10 = convertSizeToDp(5.0f);
            int n11 = n4;
            textView3.setPadding(n8, n9, n10, convertSizeToDp(5.0f));
            textView3.setTextSize(1, 15.0f);
            tabLayouts[n6].addView((View)textView3);
            GradientDrawable gradientDrawable = new GradientDrawable();
            gradientDrawable.setColor(Color.parseColor("#1b1a17"));//
            if (n6 == 0) {
				gradientDrawable.setColor(Color.parseColor("#202020"));
                gradientDrawable.setStroke(4, Color.parseColor("#2196f3"));
            } else {
                gradientDrawable.setStroke(0, Color.parseColor("#ff0000"));//
            }
            this.tabLayouts[n6].setBackground((Drawable)gradientDrawable);
            linearLayout4.addView((View)this.tabLayouts[n6]);
            final int n12 = n6;
            this.tabLayouts[n6].setOnClickListener(new View.OnClickListener(){

                    public void onClick(View view) {
                        contentLayouts[selectedTab].setVisibility(8);
                        GradientDrawable gradientDrawable = new GradientDrawable();
                        gradientDrawable.setColor(Color.parseColor("#1b1a17"));
                        gradientDrawable.setStroke(0, Color.rgb(255, 0, 0));
                        tabLayouts[selectedTab].setBackground(gradientDrawable);
                        GradientDrawable gradientDrawable2 = new GradientDrawable();
                        gradientDrawable2.setColor(Color.parseColor("#202020"));
                        gradientDrawable2.setStroke(4, Color.parseColor("#2196f3"));
                        tabLayouts[n12].setBackground(gradientDrawable2);
                        contentLayouts[n12].setVisibility(0);
                        selectedTab = n12;
                    }
                });
            ++n6;
            linearLayout5 = linearLayout7;
            linearLayout2 = linearLayout6;
            textView = textView2;
            n4 = n11;
        } while (true);
        this.type = Build.VERSION.SDK_INT >= 26 ? 2038 : 2002;
  
		final WindowManager.LayoutParams layoutParams = new WindowManager.LayoutParams(n, n2, this.type, 520, -3);
        layoutParams.x = 150;//150
        layoutParams.y = 100;//150
        layoutParams.gravity = 51;
        frameLayout.setOnTouchListener(new View.OnTouchListener(){
                float deltaX;
                float deltaY;
                float maxX;
                float maxY;
                float newX;
                float newY;
                float pressedX;
                float pressedY;
                public boolean onTouch(View view, MotionEvent motionEvent) {
                    float f,f2,f3,f4;
                    int n = motionEvent.getActionMasked();
                    if (n == 0) {
                        this.deltaX = (float)layoutParams.x - motionEvent.getRawX();
                        this.deltaY = (float)layoutParams.y - motionEvent.getRawY();
                        this.pressedX = motionEvent.getRawX();
                        this.pressedY = motionEvent.getRawY();
                        return false;
                    }
                    if (n != 1) {
                        float f5;
                        float f6;
                        if (n != 2) {
                            return false;
                        }
                        this.newX = motionEvent.getRawX() + deltaX;
                        this.newY = motionEvent.getRawY() + deltaY;
                        this.maxX = point.x - linearLayout.getWidth();
                        this.maxY = f6 = (point.y - linearLayout.getHeight());
                        float f7 = newX;
                        if (!(f7 < 0.0f || f7 > maxX || (f5 = newY) < 0.0f || f5 > f6)) {
                            linearLayout.setAlpha(1.0f);
                        } else {
                            linearLayout.setAlpha(0.5f);
                        }
                        layoutParams.x = (int)newX;
                        layoutParams.y = (int)newY;
                        windowManager.updateViewLayout(linearLayout,layoutParams);
                        return false;
                    }
                    maxX = point.x - linearLayout.getWidth();
                    maxY = point.y - linearLayout.getHeight();
                    if (newX < 0.0f) {
                        newX = 0.0f;
                    }
                    if ((f = newX) > (f4 = maxX)) {
                        newX = f4;
                    }
                    if (newY < 0.0f) {
                        newY = 0.0f;
                    }
                    if ((f3 = newY) > (f2 = maxY)) {
                        newY = (int)f2;
                    }
                    layoutParams.x = (int)newX;
                    layoutParams.y = (int)newY;
                    windowManager.updateViewLayout(linearLayout,layoutParams);
                    linearLayout.setAlpha(1.0f);
                    return true;
                }
            });
    
		this.g_iconLayout = relativeLayout = new RelativeLayout((Context)this);
        relativeLayout.setLayoutParams((ViewGroup.LayoutParams)new RelativeLayout.LayoutParams(-2, -2));
        ImageView imageView = new ImageView((Context)this);
        imageView.setLayoutParams(new ViewGroup.LayoutParams(this.convertSizeToDp(40.0f), this.convertSizeToDp(40.0f)));
        relativeLayout.addView((View)imageView);
        byte[] arrby = Base64.decode(Icon(), 0);
        imageView.setImageBitmap(BitmapFactory.decodeByteArray((byte[])arrby, (int)0, (int)arrby.length));
			
		final WindowManager.LayoutParams layoutParams2 = new WindowManager.LayoutParams(-2, -2,type, 8, -3);
        layoutParams2.gravity = 51;
        layoutParams2.x = 0;
        layoutParams2.y = 0;
        relativeLayout.setVisibility(8);
        windowManager.addView(relativeLayout,layoutParams2);
        windowManager.addView(linearLayout,layoutParams);
        relativeLayout.setOnTouchListener(new View.OnTouchListener(){
                float deltaX;
                float deltaY;
                float newX;
                float newY;
                float pressedX;
                float pressedY;

                public boolean onTouch(View view, MotionEvent motionEvent) {
                    int n = motionEvent.getActionMasked();
                    if (n != 0) {
                        if (n != 1) {
                            if (n != 2) {
                                return false;
                            }
                            newX = motionEvent.getRawX() + deltaX;
                            newY = motionEvent.getRawY() + deltaY;
                            float f = screenWidth - view.getWidth();
                            float f2 = screenHeight - view.getHeight();
                            if (newX < 0.0f) {
                                newX = 0.0f;
                            }
                            if (newX > f) {
                                newX = f;
                            }
                            if (newY < 0.0f) {
                                newY = 0.0f;
                            }
                            if (newY > f2) {
                                newY = f2;
                            }
                            layoutParams2.x = (int)newX;
                            layoutParams2.y = (int)newY;
                            windowManager.updateViewLayout(relativeLayout,layoutParams2);
                            return false;
                        }
                        int n2 = (int)(motionEvent.getRawX() - pressedX);
                        int n3 = (int)(motionEvent.getRawY() - pressedY);
                        if (n2 == 0 && n3 == 0) {
                 /*  off   */    linearLayout.setVisibility(0);
                           relativeLayout.setVisibility(8);
                        }
                        return true;
                    }
                    this.deltaX = layoutParams2.x - motionEvent.getRawX();
                    this.deltaY = layoutParams2.y - motionEvent.getRawY();
                    this.pressedX = motionEvent.getRawX();
                    this.pressedY = motionEvent.getRawY();
                    return false;
                }
            });
       textView.setOnClickListener(new View.OnClickListener(){
                public void onClick(View view) {
                    linearLayout.setVisibility(8);
                    relativeLayout.setVisibility(0);
                }
            });
		
		linearLayout.setVisibility(8);
		relativeLayout.setVisibility(0);
		
	//    AddText(layoutBypass, "             ＡＮＴＩＣＨＥＡＴ", "#FFFFFF");
	    AddText(layoutBypass,"Your Device Info : " + Build.MODEL, "#FFFFFF");
	    

		AddText(layoutBypass, "    [ Don't Use Main Id | GG BRUTAL ]", "#FFFFFF");	
	

		AddToggle(layoutBypass, "AIMBOT 300", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack1(2324,isChecked);
					Toast.makeText(getApplicationContext(), "AIMBOT 100m Set", Toast.LENGTH_SHORT).show(); 
                }
            });
			
		AddToggle(layoutBypass, "Bullet Track", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack2(2325,isChecked);
					Toast.makeText(getApplicationContext(), "BULLET TRACK ACTIVATED", Toast.LENGTH_SHORT).show(); 
                }
            });

		AddToggle(layoutBypass, "X - EFFECT", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack3(2326,isChecked);
					Toast.makeText(getApplicationContext(), "X EFFECT ACTIVATED", Toast.LENGTH_SHORT).show(); 
                }
            });

		AddToggle(layoutBypass, "X - EFFECT RGB", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack4(2327,isChecked);
					Toast.makeText(getApplicationContext(), " RGB X EFFECT ACTIVATED", Toast.LENGTH_SHORT).show(); 
                }
            });

		AddToggle(layoutBypass, "SMALL CROSS", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack5(2328,isChecked);
					Toast.makeText(getApplicationContext(), "SMALL CROSS ACTIVE", Toast.LENGTH_SHORT).show(); 
                }
            });	

		AddToggle(layoutBypass, "RGB CROSS", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack6(2329,isChecked);
					Toast.makeText(getApplicationContext(), "RGB SMALL CROSS ACTIVE", Toast.LENGTH_SHORT).show(); 
                }
            });	

		AddToggle(layoutBypass, "FAST LANDING", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack7(2330,isChecked);
					Toast.makeText(getApplicationContext(), "FAST PARACHUTE ACTIVATED", Toast.LENGTH_SHORT).show(); 
                }
            });	

		AddToggle(layoutBypass, "EXTRA ZOOM", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack8(2331,isChecked);
					Toast.makeText(getApplicationContext(), "SCOPE EXTRA ZOOM", Toast.LENGTH_SHORT).show(); 
                }
            });

		AddToggle(layoutBypass, "MAGIC BULLET", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack9(2332,isChecked);
					Toast.makeText(getApplicationContext(), "Magic Bullet", Toast.LENGTH_SHORT).show(); 
                }
            });	

		AddToggle(layoutBypass, "Small Aim", new CompoundButton.OnCheckedChangeListener(){
                public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                    Hack10(2333,isChecked);
					Toast.makeText(getApplicationContext(), "Small Aim", Toast.LENGTH_SHORT).show(); 
                }
            });	

		AddToggle(layoutBypass, "SHOW MENU", new CompoundButton.OnCheckedChangeListener(){
				public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
					Hack11(2334,isChecked);
					Toast.makeText(getApplicationContext(), " Active", Toast.LENGTH_SHORT).show(); 
				}
			});		
			
	}

		
		
    private void  setValue(String key,boolean b) {
        SharedPreferences sp=this.getSharedPreferences("espValue",Context.MODE_PRIVATE);
        SharedPreferences.Editor ed= sp.edit();
        ed.putBoolean(key,b);
        ed.apply();

    }
	public static void delete(String path){
        File dir = new File(path);
        if (dir.isDirectory())
        {
            String[] children = dir.list();
            for (int i = 0; i < children.length; i++)
            {
                new File(dir, children[i]).delete();
            }
        }
    }
    public int onStartCommand(Intent intent, int n, int n2) {
        return 2;
    }
    public static interface OnListChoosedListener {
        public void onChoosed(int var1);
    }
    public native void SettingValue(int setting_code,boolean value);
    public native void Hack(int setting_code,boolean jboolean1);
	public native void Hack1(int setting_code,boolean jboolean1);
	public native void Hack2(int setting_code,boolean jboolean1);
	public native void Hack3(int setting_code,boolean jboolean1);
	public native void Hack4(int setting_code,boolean jboolean1);
	public native void Hack5(int setting_code,boolean jboolean1);
    public native void Hack6(int setting_code,boolean jboolean1);
	public native void Hack7(int setting_code,boolean jboolean1);
	public native void Hack8(int setting_code,boolean jboolean1);
	public native void Hack9(int setting_code,boolean jboolean1);
	public native void Hack10(int setting_code,boolean jboolean1);
	public native void Hack11(int setting_code,boolean jboolean1);
	/*public native void Hack12(int setting_code,boolean jboolean1);
	public native void Hack13(int setting_code,boolean jboolean1);
	public native void Hack14(int setting_code,boolean jboolean1);
	public native void Hack15(int setting_code,boolean jboolean1);
	public native void Hack16(int setting_code,boolean jboolean1);
	public native void Hack17(int setting_code,boolean jboolean1);
	public native void Hack18(int setting_code,boolean jboolean1);
	public native void Hack19(int setting_code,boolean jboolean1);
	public native void Hack20(int setting_code,boolean jboolean1);*/
    public native void Protection(int setting_code,boolean jboolean1);
    static native void Switch(int i, boolean k);
       private native String Icon();
    private native String IconClose();
    
	private int dp(int i) {
        return (int) TypedValue.applyDimension(1, (float) i, getResources().getDisplayMetrics());
    }
	private void setImageFromAssets(ImageView image,String name){
        AssetManager assetManager=getBaseContext().getAssets();
        try{
            InputStream inputStream=assetManager.open(name);
            image.setImageDrawable(Drawable.createFromStream(inputStream,null));
        } catch (IOException e){
            Toast.makeText(this,"Error could not load image from assets folder \n"+e.getMessage(),Toast.LENGTH_SHORT).show();
        }
	}
		    public void onTaskRemoved(Intent intent) {
        stopSelf();
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        super.onTaskRemoved(intent);
   }
   
}


