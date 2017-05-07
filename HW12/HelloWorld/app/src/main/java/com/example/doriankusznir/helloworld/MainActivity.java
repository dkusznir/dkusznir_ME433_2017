package com.example.doriankusznir.helloworld;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.Button;

public class MainActivity extends AppCompatActivity
{
    public static final int INC_AMOUNT = 5;
    SeekBar myControl;
    TextView myTextView;
    Button increase;
    Button decrease;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myControl = (SeekBar) findViewById(R.id.seek1);             // Instantiate SeekBar

        myTextView = (TextView) findViewById(R.id.textView01);      // Instantiate TextView
        myTextView.setText("Move Seek Bar to Update Values!");      // Just some random text

        increase = (Button) findViewById(R.id.increaseButton);      // Instantiate Increase Button
        increase.setText("Increase");
        decrease = (Button) findViewById(R.id.decreaseButton);      // Instantiate Decrease Button
        decrease.setText("Decrease");

        setMyControlListener();
        setIncrease();
        setDecrease();

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

    private void setIncrease()
    {
        increase.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                myControl.setProgress(myControl.getProgress() + INC_AMOUNT);
            }
        });
    }

    private void setDecrease()
    {
        decrease.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                myControl.setProgress(myControl.getProgress() - INC_AMOUNT);
            }
        });
    }

}


