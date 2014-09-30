ModulariserComponent::ModulariserComponent (const CodeFileList& codeFiles) :
    ToolComponent (TRANS ("Modulariser"), codeFiles)
{
    addTextButton (btnGenerate, TRANS ("Generate"), TRANS ("Generates a module at the specified folder."));
    addTextButton (btnBrowse, TRANS ("Browse") + "...", TRANS ("Browse for a path to specify as the destination folder."));

    addLabel (lblAdditionalHeaders, TRANS ("Additional Headers:"), TRANS ("Comma separated, wrapped with either <> or \"\"."));
    addLabel (lblModuleFilename, TRANS ("Module Name:") + ":", TRANS ("Will be the name for header and CPP files."));
    addLabel (lblHeaderGuard, TRANS ("Header Guard") + ":", TRANS ("Will be the header file\'s include guard."));
    addLabel (lblNamespace, TRANS ("Namespace") + ":", TRANS ("Optional.\n\nWill wrap the headers and source files with the namespace name."));
    addLabel (lblDestinationFolder,
              TRANS ("Destination Folder") + ":",
              TRANS ("Folder that will contain the newly created module file for the listed files.")
              + "\n\n" + TRANS ("If the folder does not exist, it will be created.")
              + "\n\n" + TRANS ("If the folder contains files with the same name, they will be overwritten!"));

    addTextEditor (txtAdditionalHeaders, juce::String::empty, lblAdditionalHeaders.getTooltip());
    addTextEditor (txtModuleFilename, TRANS ("MyModule"), lblModuleFilename.getTooltip());
    addTextEditor (txtHeaderGuard, TRANS ("MYMODULE_H"), lblHeaderGuard.getTooltip());
    addTextEditor (txtNamespace, juce::String::empty, lblNamespace.getTooltip());
    addTextEditor (txtDestinationFolder, juce::String::empty, lblDestinationFolder.getTooltip());

    addAndMakeVisible (&btnGenerate);
    addAndMakeVisible (&btnBrowse);
}

//==============================================================================
void ModulariserComponent::resized()
{
    const int width         = getWidth();
    const int height        = getHeight();
    const int margin        = getMarginSize();
    const int buttonWidth   = getDefaultButtonWidth();
    const int itemHeight    = getItemHeight();
    const int labelWidth    = getLargestLabelTextWidth();

    positionLabels (margin, margin, labelWidth, itemHeight, margin);

    {
        const int x = labelWidth + margin;
        const int boxWidth = width - x - margin;

        txtModuleFilename.setBounds (x, lblModuleFilename.getY(), boxWidth, itemHeight);
        txtHeaderGuard.setBounds (x, lblHeaderGuard.getY(), boxWidth, itemHeight);
        txtNamespace.setBounds (x, lblNamespace.getY(), boxWidth, itemHeight);
        txtDestinationFolder.setBounds (x, lblDestinationFolder.getY(), boxWidth - margin - buttonWidth, itemHeight);
    }

    btnGenerate.setBounds (width - buttonWidth - margin,
                           height - itemHeight - margin,
                           buttonWidth,
                           itemHeight);

    btnBrowse.setBounds (txtDestinationFolder.getRight() + margin,
                         txtDestinationFolder.getY(),
                         buttonWidth,
                         itemHeight);
}

void ModulariserComponent::buttonClicked (juce::Button* const button)
{
    if (button == &btnGenerate)
    {
        const juce::String destFolder (txtDestinationFolder.getText().trim());
        const juce::String moduleName (juce::File::createLegalFileName (txtModuleFilename.getText().trim()));
        const juce::String headerGuard (juce::File::createLegalFileName (txtHeaderGuard.getText().trim()));
        const juce::String namespaceName (juce::File::createLegalFileName (txtNamespace.getText().trim()));

        if (juce::File::isAbsolutePath (destFolder))
        {
            if (moduleName.isNotEmpty()
                && headerGuard.isNotEmpty())
            {
                Modulariser (getCodeFiles()).saveTo (juce::File (destFolder),
                                                     juce::String::empty,
                                                     moduleName,
                                                     headerGuard,
                                                     namespaceName);
            }
        }
        else
        {
            juce::AlertWindow::showMessageBox (juce::AlertWindow::WarningIcon,
                                               TRANS ("Invalid destination folder!"),
                                               TRANS ("The path must be valid to have a place for generating files!"),
                                               "OK");

            txtDestinationFolder.setText (juce::File::getSpecialLocation (juce::File::SpecialLocationType::userDesktopDirectory).getFullPathName()
                                          + "/" + TRANS ("GeneratedModules") + "/");
        }
    }
    else if (button == &btnBrowse)
    {
        juce::FileChooser chooser (TRANS ("Select a folder that will contain the generated module files."));

        if (chooser.browseForDirectory())
        {
            const juce::File folder (chooser.getResult());

            txtDestinationFolder.setText (folder.getFullPathName().trim(), juce::sendNotification);
        }
    }
}