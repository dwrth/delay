cmake_minimum_required(VERSION 3.15)

project(Delay VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add JUCE as a subdirectory with explicit binary directory
add_subdirectory(/Users/davidwerth/Developer/audio/JUCE ${CMAKE_BINARY_DIR}/JUCE EXCLUDE_FROM_ALL)

# Create the plugin
juce_add_plugin(Delay
    VERSION "1.0.0"
    COMPANY_NAME "dwrth"
    PLUGIN_MANUFACTURER_CODE "Madw"
    PLUGIN_CODE "Dlay"
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "DeutscheBahn"
    DESCRIPTION "International Rail Delay"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    VST3_CATEGORIES Delay Fx
)

# Generate JUCE header
juce_generate_juce_header(Delay)

# Add source files
target_sources(Delay
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
        Source/Parameters.cpp
        Source/RotaryKnob.cpp
        Source/LookAndFeel.cpp
)

# Update include directories to include JuceLibraryCode
target_include_directories(Delay
    PRIVATE
        Source
        ${CMAKE_CURRENT_BINARY_DIR}/JuceLibraryCode
)

# Link with JUCE modules
target_link_libraries(Delay
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_dsp
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
