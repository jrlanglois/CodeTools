CodeFileListComponent::CodeFileListComponent()
{
    fileListBox.setColour (juce::ListBox::outlineColourId, juce::Colours::white.withAlpha (0.5f));
    fileListBox.setColour (juce::ListBox::textColourId, juce::Colours::white);
    fileListBox.setColour (juce::ListBox::backgroundColourId, juce::Colours::transparentBlack);
    fileListBox.setMultipleSelectionEnabled (true);
    fileListBox.setModel (this);

    addAndMakeVisible (&fileListBox);
}

//==============================================================================
void CodeFileListComponent::clearFiles()
{
    if (codeFiles.getNumFiles() > 0)
    {
        juce::AlertWindow window ("Clear the files?",
                                  "Are you sure you want to clear all the code files?",
                                  juce::AlertWindow::InfoIcon);

        enum Results { Yes = 0, No };

        window.addButton ("Yes", Yes);
        window.addButton ("No", No);

        if (window.runModalLoop() == Yes)
        {
            codeFiles.clearFiles();
            fileListBox.updateContent();
        }
    }
}

//==============================================================================
void CodeFileListComponent::resized()
{
    fileListBox.setBounds (0, 0, getWidth(), getHeight());
}

//=============================================================================
bool CodeFileListComponent::isInterestedInFileDrag (const juce::StringArray& /*files*/)
{
    return true; //Accept all files. Any invalid ones will be filtered later...
}

void CodeFileListComponent::filesDropped (const juce::StringArray& incomingFiles, const int, const int)
{
    codeFiles.addFiles (incomingFiles);
    fileListBox.updateContent();

    setColour (juce::ListBox::outlineColourId, juce::Colours::white.withAlpha (0.5f));

    grabKeyboardFocus();
}

void CodeFileListComponent::fileDragEnter (const juce::StringArray&, const int, const int)
{
    setColour (juce::ListBox::outlineColourId, juce::Colours::red.withAlpha (0.5f));
}

void CodeFileListComponent::fileDragExit (const juce::StringArray&)
{
    setColour (juce::ListBox::outlineColourId, juce::Colours::white.withAlpha (0.5f));
}

//=============================================================================
void CodeFileListComponent::deleteKeyPressed (const int)
{
    const juce::SparseSet<int> selectedRows (fileListBox.getSelectedRows());

    for (int i = selectedRows.size(); --i >= 0;)
        codeFiles.removeFile (selectedRows[i]);

    fileListBox.setSelectedRows (juce::SparseSet<int>());
    fileListBox.updateContent();
}

void CodeFileListComponent::backgroundClicked (const juce::MouseEvent&)
{
    fileListBox.setSelectedRows (juce::SparseSet<int>());
}

int CodeFileListComponent::getNumRows()
{
    return codeFiles.getNumFiles();
}

void CodeFileListComponent::paintListBoxItem (const int rowNumber,
                                              juce::Graphics& g,
                                              const int width, const int height,
                                              const bool isRowSelected)
{
    if (isRowSelected)
    {
        g.fillAll (juce::Colours::white.darker());
        g.setColour (juce::Colours::white.darker().contrasting());
    }
    else
    {
        g.setColour (fileListBox.findColour (juce::ListBox::textColourId));
    }

    g.setFont (height * 0.7f);

    g.drawText (codeFiles[rowNumber],
                5, 0, width, height,
                juce::Justification::centredLeft, false);

    const float h = (float) height;
    const float w = (float) width;
    const float offset = 5.0f;
    const float thickness = 0.25f;

    g.setColour (juce::Colours::lightgrey);

    g.drawLine (offset, h - thickness,
                w - (offset * 2.0f), h - thickness,
                thickness);
}