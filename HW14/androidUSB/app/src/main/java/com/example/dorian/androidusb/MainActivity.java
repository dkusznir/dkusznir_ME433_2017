package com.example.dorian.androidusb;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.Button;

import org.w3c.dom.Text;

public class MainActivity extends AppCompatActivity
{

    SeekBar myControl;
    TextView myTextView;

    // New widgets for HW14
    Button button;
    TextView myTextView2;
    ScrollView myScrollView;
    TextView myTextView3;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myControl = (SeekBar) findViewById(R.id.seek1);                 // Instantiate SeekBar

        myTextView = (TextView) findViewById(R.id.textView01);          // Instantiate TextView
        myTextView.setText("Move Seek Bar to Update Values!");          // Just some random text

        myTextView2 = (TextView) findViewById(R.id.textView02);         // Instantiate TextView2

        myScrollView = (ScrollView) findViewById(R.id.ScrollView01);    // Instantiate ScrollView

        myTextView3 = (TextView) findViewById(R.id.textView03);         // Instantiate TextView3

        button = (Button) findViewById(R.id.button1);                   // Instantiate Button

        button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                myTextView2.setText("Value on click is " + myControl.getProgress());
            }
        });

        setMyControlListener();
    }

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
