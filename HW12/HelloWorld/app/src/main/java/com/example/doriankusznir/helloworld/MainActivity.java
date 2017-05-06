package com.example.doriankusznir.helloworld;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity
{
    SeekBar myControl;
    TextView myTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myControl = (SeekBar) findViewById(R.id.seek1);             // Instantiate SeekBar

        myTextView = (TextView) findViewById(R.id.textView01);      // Instantiate TextView
        myTextView.setText("Move Seek Bar to Update Values!");      // Just some random text

        setMyControlListener();

    }

    // Function to detect when the slider is used.
    private void setMyControlListener()
    {
        myControl.setOnSeekBarChangeListener(new OnSeekBarChangeListener()
        {

            int progressChanged = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser)
            {
                progressChanged = progress;
                myTextView.setText("The value is " + progress);

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar)
            {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar)
            {

            }
        });
    }
}


