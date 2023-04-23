#include <vector>
#include "MainComponent.h"

MainComponent::MainComponent()
{
    leftDecibelLevelSlider.setRange(-100, -12);
    leftDecibelLevelSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    leftDecibelLevelSlider.onValueChange = [this] {leftLevel = juce::Decibels::decibelsToGain((float) leftDecibelLevelSlider.getValue());};
    leftDecibelLevelSlider.setValue(juce::Decibels::gainToDecibels(leftLevel));
    leftLevelLabel.setText("Left noise level in dB", juce::dontSendNotification);


    addAndMakeVisible(leftDecibelLevelSlider);
    addAndMakeVisible(leftLevelLabel);

    rightDecibelLevelSlider.setRange(-100, -12);
    rightDecibelLevelSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    rightDecibelLevelSlider.onValueChange = [this] {rightLevel = juce::Decibels::decibelsToGain((float) rightDecibelLevelSlider.getValue());};
    rightDecibelLevelSlider.setValue(juce::Decibels::gainToDecibels(rightLevel));
    rightLevelLabel.setText("Right noise Level in dB", juce::dontSendNotification);

    addAndMakeVisible(rightDecibelLevelSlider);
    addAndMakeVisible(rightLevelLabel);

    setSize(600, 100);
    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    juce::String message;
    message << "preparing to play audio...\n";
    message << "samplesPerBlockExpected: " << samplesPerBlockExpected << "\n";
    message << "sampleRate: " << sampleRate;
    juce::Logger::getCurrentLogger()->writeToLog(message);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    std::vector<float> levels = {
        (float) leftLevel,
        (float) rightLevel
    };
    
    std::vector<float> levelScales = {
        (float) leftLevel * 2.0f,
        (float) rightLevel * 2.0f
    };

    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
        auto *buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {
            buffer[sample] = random.nextFloat() * levelScales[channel] - levels[channel];
        }
    }
}

void MainComponent::releaseResources()
{
    juce::Logger::getCurrentLogger()->writeToLog("Releasing audio resources");
}

void MainComponent::paint(juce::Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    leftLevelLabel.setBounds(10, 10, 90, 20);
    leftDecibelLevelSlider.setBounds(100, 10, getWidth() - 110, 20);

    rightLevelLabel.setBounds(10, 40, 90, 20);
    rightDecibelLevelSlider.setBounds(100, 40, getWidth() - 110, 20);
}
