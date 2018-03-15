package edu.ufl.cise.os.p2;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.EditText;
import android.app.Activity;
import android.view.View;

public class P2Activity extends Activity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_p2);

        // Example of a call to a native method
        TextView contents = findViewById(R.id.contentsLabel);
        contents.setText(stringFromJNI());

    }

    protected void onLoadClick(View view){
        TextView contents = findViewById(R.id.contentsLabel);
        EditText filenameBox = findViewById(R.id.filenameBox);
        String filename = filenameBox.getText().toString();
        String toSet;
        try {
            toSet = stringFromFile(filename);
        }
        catch(Exception e){
            toSet = "File not found!";
        }
        contents.setText(toSet);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String stringFromFile(String filename);
}
