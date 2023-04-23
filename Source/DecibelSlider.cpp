#include "DecibelSlider.h"

double DecibelSlider::getValueFromText(const juce::String& text) {
    auto minusInfinityDb = -100.0;
    auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim();

    return decibelText.equalsIgnoreCase("-INF") ? minusInfinityDb : decibelText.getDoubleValue();
}

juce::String DecibelSlider::getTextFromValue(double value) {
    return juce::Decibels::toString(value);
}
