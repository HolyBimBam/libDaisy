#include "teil2_control.h"

#ifndef SAMPLE_RATE
#define SAMPLE_RATE DSY_AUDIO_SAMPLE_RATE
#endif


#define SW_1_PIN 1
#define SW_2_PIN 2
#define SW_3_PIN 3
#define SW_4_PIN 4

#define LED_1_PIN 5
#define LED_2_PIN 6

#define KNOB_1_PIN 15
#define KNOB_2_PIN 16
#define KNOB_3_PIN 17
#define KNOB_4_PIN 18
#define KNOB_5_PIN 19
#define KNOB_6_PIN 20
#define KNOB_7_PIN 21
#define KNOB_8_PIN 22



using namespace daisy;


void Teil2Control::Init()
{
    // Set Some numbers up for accessors.
    sample_rate_   = SAMPLE_RATE; // TODO add configurable SR to libdaisy audio.
    block_size_    = 48;
    callback_rate_ = (sample_rate_ / static_cast<float>(block_size_));
    
    // Initialize the hardware.
    seed.Configure();
    seed.Init();
    dsy_tim_start();
    InitButtons();
    InitLeds();
    InitKnobs();
    SetAudioBlockSize(block_size_);
}

void Teil2Control::DelayMs(size_t del)
{
    dsy_tim_delay_ms(del);
}

void Teil2Control::StartAudio(dsy_audio_callback cb)
{
    seed.StartAudio(cb);
}

void Teil2Control::StartAudio(dsy_audio_mc_callback cb)
{
    seed.StartAudio(cb);
}

void Teil2Control::ChangeAudioCallback(dsy_audio_callback cb)
{
    seed.ChangeAudioCallback(cb);
}

void Teil2Control::ChangeAudioCallback(dsy_audio_mc_callback cb)
{
    seed.ChangeAudioCallback(cb);
}

void Teil2Control::SetAudioBlockSize(size_t size)
{
    block_size_    = size;
    callback_rate_ = (sample_rate_ / static_cast<float>(block_size_));
    dsy_audio_set_blocksize(DSY_AUDIO_INTERNAL, block_size_);
}

float Teil2Control::AudioSampleRate()
{
    return sample_rate_;
}

size_t Teil2Control::AudioBlockSize()
{
    return block_size_;
}

float Teil2Control::AudioCallbackRate()
{
    return callback_rate_;
}

void Teil2Control::StartAdc()
{
    seed.adc.Start();
}

void Teil2Control::UpdateAnalogControls()
{
    for(int i=0; i<KNOB_LAST; i++){
        knobs[i].Process();
    }
}

float Teil2Control::GetKnobValue(Knob k)
{
    size_t idx;
    idx = k < KNOB_LAST ? k : KNOB_1;
    return knobs[idx].Value();
}

void Teil2Control::DebounceControls()
{
    button1.Debounce();
    button2.Debounce();
    button3.Debounce();
    button4.Debounce();
}

void Teil2Control::ClearLeds()
{ 
    led1.Set(0.0f);
    led2.Set(0.0f);
}

void Teil2Control::UpdateLeds()
{
    led1.Update();
    led2.Update();
}

void Teil2Control::InitButtons()
{
    /*
    button1.Init(seed.GetPin(SW_1_PIN), callback_rate_, TYPE_TOGGLE, POLARITY_NORMAL, PULL_UP);
    button2.Init(seed.GetPin(SW_2_PIN), callback_rate_, TYPE_TOGGLE, POLARITY_NORMAL, PULL_UP);
    button3.Init(seed.GetPin(SW_3_PIN), callback_rate_, TYPE_MOMENTARY, POLARITY_NORMAL, PULL_UP);
    button4.Init(seed.GetPin(SW_4_PIN), callback_rate_, TYPE_MOMENTARY, POLARITY_NORMAL, PULL_UP);
*/
    button1.Init(seed.GetPin(SW_1_PIN), callback_rate_);
    button2.Init(seed.GetPin(SW_2_PIN), callback_rate_);
    button3.Init(seed.GetPin(SW_3_PIN), callback_rate_);
    button4.Init(seed.GetPin(SW_4_PIN), callback_rate_);

    buttons[BUTTON_1] = &button1;
    buttons[BUTTON_2] = &button2;
    buttons[BUTTON_3] = &button3;
    buttons[BUTTON_4] = &button4;
}

void Teil2Control::InitLeds()
{
    dsy_gpio_pin led1Pin, led2Pin;

    led1Pin = seed.GetPin(LED_1_PIN);
    led2Pin = seed.GetPin(LED_2_PIN);
    led1.Init(led1Pin, true);
    led2.Init(led2Pin, true);

    ClearLeds();
    UpdateLeds();
}

void Teil2Control::InitKnobs()
{
    // Configure the ADC channels using the desired pin
    AdcChannelConfig knob_init[KNOB_LAST];
    knob_init[KNOB_1].InitSingle(seed.GetPin(KNOB_1_PIN));
    knob_init[KNOB_2].InitSingle(seed.GetPin(KNOB_2_PIN));
    knob_init[KNOB_3].InitSingle(seed.GetPin(KNOB_3_PIN));
    knob_init[KNOB_4].InitSingle(seed.GetPin(KNOB_4_PIN));
    knob_init[KNOB_5].InitSingle(seed.GetPin(KNOB_5_PIN));
    knob_init[KNOB_6].InitSingle(seed.GetPin(KNOB_6_PIN));
    knob_init[KNOB_7].InitSingle(seed.GetPin(KNOB_7_PIN));
    knob_init[KNOB_8].InitSingle(seed.GetPin(KNOB_8_PIN));    
    
    
    // Initialize with the knob init struct w/ 2 members
    // Set Oversampling to 32x
    seed.adc.Init(knob_init, KNOB_LAST);


    // Initialize AnalogControls, with flip set to true
    for(size_t i = 0; i < KNOB_LAST; i++)
    {
        knobs[i].Init(seed.adc.GetPtr(i), callback_rate_, true);
    }

}
