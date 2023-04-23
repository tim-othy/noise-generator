#pragma once

#include <JuceHeader.h>
#include "DecibelSlider.h"

class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    juce::Random random;

    DecibelSlider leftDecibelLevelSlider;
    juce::Label leftLevelLabel;
    float leftLevel = 0.0f;

    DecibelSlider rightDecibelLevelSlider;
    juce::Label rightLevelLabel;
    float rightLevel = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
