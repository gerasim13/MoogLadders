#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DafxAudioProcessorEditor::DafxAudioProcessorEditor (DafxAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    
    setSize (380, 160);

    // Cutoff Slider
    addAndMakeVisible(cutoffSlider = new Slider("cut"));
    cutoffSlider->setSliderStyle(Slider::LinearHorizontal);
    cutoffSlider->addListener(this);
    cutoffSlider->setRange(20, 20000, 1);
    cutoffSlider->setBounds(20, 60, 340, 20);
    
    cutoffSliderLabel = new Label("", "Cutoff:");
    cutoffSliderLabel->attachToComponent(cutoffSlider, false);
    cutoffSliderLabel->setFont (Font (11.0f));
    
    // Resonance Slider 
    addAndMakeVisible(resSlider = new Slider("res"));
    resSlider->setSliderStyle(Slider::LinearHorizontal);
    resSlider->addListener(this);
    resSlider->setRange(0, 1, 0.01f);
    resSlider->setBounds(20, 100, 340, 20);
    
    resonanceSliderLabel = new Label("", "Resonance:");
    resonanceSliderLabel->attachToComponent(resSlider, false);
    resonanceSliderLabel->setFont (Font (11.0f));
    
    // Filter type selector 
    addAndMakeVisible (filterTypeSelector = new ComboBox (String::empty));
    filterTypeSelector->addListener(this);
    
    
}

DafxAudioProcessorEditor::~DafxAudioProcessorEditor()
{
}

//==============================================================================
void DafxAudioProcessorEditor::paint (Graphics& g)
{
    
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (20.0f);
    
    g.drawFittedText ("Moog Ladders", 20, 0, getWidth(), 40, Justification::left, 1);
    
    if (filterTypeSelector != nullptr) 
    {
        
        filterTypeSelector->setBounds (  160, 10, 195, 30);
        filterTypeSelector->clear();

        filterTypeSelector->addItem (("Simplified"), 1);
            filterTypeSelector->addSeparator();
        filterTypeSelector->addItem (("Stilson"), 2);
            filterTypeSelector->addSeparator();
        filterTypeSelector->addItem (("Huovilainen"), 3);
        
    }
    
}


// This is our Slider::Listener callback, when the user drags a slider.
void DafxAudioProcessorEditor::sliderValueChanged (Slider* slider)
{

    if (slider == resSlider)
    {
        // It's vital to use setParameterNotifyingHost to change any parameters that are automatable
        // by the host, rather than just modifying them directly, otherwise the host won't know
        // that they've changed.
        getProcessor()->setParameterNotifyingHost (DafxAudioProcessor::resParam,
                                                   (float) resSlider->getValue());
    }
    else if (slider == cutoffSlider)
    {
        getProcessor()->setParameterNotifyingHost (DafxAudioProcessor::cutoffParam,
                                                   (float) cutoffSlider->getValue());
    }
    
}

void DafxAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    
    if (comboBoxThatHasChanged == filterTypeSelector)
    {
        String type  = filterTypeSelector->getText(); 
        
        if (type == "Simplified") { 
            getProcessor()->setParameterNotifyingHost (DafxAudioProcessor::setSimplified, 1);
        }
        
        else if (type == "Stilson") {
            getProcessor()->setParameterNotifyingHost (DafxAudioProcessor::setStilson, 1);
        }
        
        else if (type == "Huovilainen") {
             getProcessor()->setParameterNotifyingHost (DafxAudioProcessor::setHuovilainen, 1);
        }
    }
    
    filterTypeSelector->resized(); 
}


// No buttons to handle... yet
void DafxAudioProcessorEditor::buttonClicked(Button* btn)
{
    
}


