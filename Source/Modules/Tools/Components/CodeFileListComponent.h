#ifndef JRL_CODE_FILE_LIST_COMPONENT_H
#define JRL_CODE_FILE_LIST_COMPONENT_H

#include "../Misc/CodeFileList.h"

/**
    @file CodeFileListComponent.h
    @copyright jrlanglois

*/
class CodeFileListComponent : public juce::Component,
                              public juce::FileDragAndDropTarget,
                              private juce::ListBoxModel
{
public:
    /** Constructor */
    CodeFileListComponent();

    //==============================================================================
    /** Clear all the code files, if there are any */
    void clearFiles();

    /** Get a reference to the list of code files */
    const CodeFileList& getCodeFiles() const noexcept { return codeFiles; }

    /** Get a list of the selected code files */
    juce::StringArray getSelectedCodeFiles();

    //==============================================================================
    class Listener
    {
        virtual ~Listener() { }

        virtual void numberOfCodeFilesChanged (int lastAmount, int newAmount) = 0;
    };

    void addListener (Listener* listener);
    void removeListener (Listener* listener);

    //==============================================================================
    /** @internal */
    void resized() override;
    /** @internal */
    bool isInterestedInFileDrag (const juce::StringArray& files) override;
    /** @internal */
    void filesDropped (const juce::StringArray& files, int x, int y) override;
    /** @internal */
    void fileDragEnter (const juce::StringArray& files, int x, int y) override;
    /** @internal */
    void fileDragExit (const juce::StringArray& files) override;
    /** @internal */
    void deleteKeyPressed (int lastRowSelected) override;
    /** @internal */
    void backgroundClicked (const juce::MouseEvent& e) override;
    /** @internal */
    int getNumRows() override;
    /** @internal */
    void paintListBoxItem (int rowNumber,
                           juce::Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override;

private:
    //==============================================================================
    juce::ListenerList<Listener> listeners;
    CodeFileList codeFiles;
    juce::ListBox fileListBox;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CodeFileListComponent)
};

#endif //JRL_CODE_FILE_LIST_COMPONENT_H