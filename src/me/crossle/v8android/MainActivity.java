/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
    String url = "hello v8 pk";
    String okjs = "function main(url) { var fo = \"HelloWorld V8 in Android\"; return url; }";
    String result = runScript(okjs, "main", url);
    TextView textView = (TextView) findViewById(R.id.tv_hello);
    textView.setText(result);
    Log.d("V8Android", result);

    Log.e("V8Android", getApplicationInfo().nativeLibraryDir);

  }


  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    // Inflate the menu; this adds items to the action bar if it is present.
    getMenuInflater().inflate(R.menu.main, menu);
    return true;
  }

  private native String runScript(String code, String function, String url);
}
