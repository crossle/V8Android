package me.crossle.v8android;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends Activity {

  static {
    System.loadLibrary("v8android");
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    nativeInit();
    String okjs = "function main() { var fo = \"HelloWorld V8 in Android\"; return fo; } \n main();";
    String result = runScript("Hello world", okjs);
    TextView textView = (TextView) findViewById(R.id.tv_hello);
    textView.setText(result);
    Log.d("V8 in Android ACTIVITY VATEDROID 'PRODUCED' RESULT", result);

  }


  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    // Inflate the menu; this adds items to the action bar if it is present.
    getMenuInflater().inflate(R.menu.main, menu);
    return true;
  }


  private native void nativeInit();

  private native String runScript(String name, String code);
}
