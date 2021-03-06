#ifndef __PLUGINPROCESSOR_H_91A1C9AF__
#define __PLUGINPROCESSOR_H_91A1C9AF__

#include "../JuceLibraryCode/JuceHeader.h"

#include "LadderFilter.h"
#include "Stilson.h" 
#include "Huovilainen.h"
#include "SimplifiedMoog.h"


class DafxAudioProcessor : public AudioProcessor {
    
public:
    
    //==============================================================================
    DafxAudioProcessor();
    ~DafxAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    
    void changeFilterType(int); 
    void changeFilterResonance(float);
    void changeFilterCutoff(float); 
    
    int filterType; 
  
    enum Parameters
    {
        resParam = 0,
        cutoffParam,
        setStilson,
        setHuovilainen,
        setSimplified, 
        totalNumParams
    };
    
    float resonance;
    float cutoff; 
    
    Array<LadderFilter*> MoogLadder; 
    
private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DafxAudioProcessor);
};

#endif  // __PLUGINPROCESSOR_H_91A1C9AF__
