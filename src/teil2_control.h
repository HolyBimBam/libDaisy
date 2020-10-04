#pragma once
#ifndef TEIL2_CONTROL_BSP_H
#define TEIL2_CONTROL_BSP_H

#include "daisy_seed.h"

namespace daisy
{
/**
    @brief Class that handles initializing all of the hardware specific to the Teil2 Control Board.
    Based on Electro Smith Daisy Pod and Patch Code.\n 
    Helper funtions are also in place to provide easy access to built-in controls and peripherals.
    
    @author HolyBimBam
    @date October 2020
*/
class Teil2Control
{
  public:
    /** Switches */
    enum Sw
    {
        BUTTON_1,    /**< ARC1 */
        BUTTON_2,    /**< ACR2 */
        BUTTON_3,    /**< Toggle1 */
        BUTTON_4,    /**< Toggle2 */
        BUTTON_LAST, /** &  */
    };

    /** Knobs */
    enum Knob
    {
        KNOB_1,    /** &  */
        KNOB_2,    /** & */
        KNOB_3,    /** &  */
        KNOB_4,    /** & */
        KNOB_5,    /** &  */
        KNOB_6,    /** & */
        KNOB_7,    /** &  */
        KNOB_8,    /** & */
        KNOB_LAST, /** & */
    };

    Teil2Control() {}
    ~Teil2Control() {}

    /** Init related stuff. */
    void Init();

    /** Wait for a bit
    \param del Time to wait in ms.
    */
    void DelayMs(size_t del);

    /** Audio Block size defaults to 48. Change it using this function before StartingAudio. 
    \param size Block size to set.
     */
    void SetAudioBlockSize(size_t size);

    /** Starts the callback
    \cb Interleaved callback function
    */
    void StartAudio(dsy_audio_callback cb);

    /** Starts the callback
    \cb multichannel callback function
    */
    void StartAudio(dsy_audio_mc_callback cb);

    /**
       Switch callback functions
       \param cb New interleaved callback function.
    */
    void ChangeAudioCallback(dsy_audio_callback cb);

    /**
       Switch callback functions
       \param cb New multichannel callback function.
    */
    void ChangeAudioCallback(dsy_audio_mc_callback cb);

    /**
       Start analog to digital conversion.
     */
    void StartAdc();

    /** Get sample rate */
    float AudioSampleRate();
    /** Get block size */
    size_t AudioBlockSize();
    /** Get callback rate */
    float AudioCallbackRate(); /** */
    /** Call at same rate as analog reads for smooth reading.*/
    void UpdateAnalogControls(); /** */
    /** & */
    float GetKnobValue(Knob k);
    /** & */
    void DebounceControls();
    /** Reset Leds*/
    void ClearLeds();
    /** Update Leds to set colors*/
    void UpdateLeds();

    /** Public Members */
    DaisySeed     seed;        /**<# */
    AnalogControl knob1,       /**< & */
        knob2,                 /**< & */
        knob3,                 /**< & */
        knob4,                 /**< & */
        knob5,                 /**< & */
        knob6,                 /**< & */
        knob7,                 /**< & */
        knob8,                 /**< & */
        *knobs[KNOB_LAST];     /**< & */
    Switch button1,            /**< & */
        button2,               /**< & */
        button3,               /**< & */
        button4,               /**< & */
        *buttons[BUTTON_LAST]; /**< & */
    Led led1,                   /**< & */
        led2;                  /**< & */

  private:
    void   InitButtons();
    void   InitLeds();
    void   InitKnobs();
    float  sample_rate_, callback_rate_;
    size_t block_size_;
};

} // namespace daisy
#endif
