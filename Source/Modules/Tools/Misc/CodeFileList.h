#ifndef JRL_CODE_FILE_LIST_H
#define JRL_CODE_FILE_LIST_H

/**
    @file CodeFileList.h
    @copyright jrlanglois


*/
class CodeFileList
{
public:
    /** Constructor

        @param[in] undoManager
    */
    CodeFileList (juce::UndoManager* undoManager = nullptr) noexcept;

    //==============================================================================
    /** */
    int getNumFiles() const { return files.size(); }

    /** Returns one of the code file paths from the array.

        If the index is out-of-range, an empty string is returned.

        Obviously the reference returned shouldn't be stored for later use, as the
        string it refers to may disappear when the array changes.
    */
    juce::String operator[] (int index) const noexcept { return files[index].getFullPathName(); }

    /** */
    const juce::File& getFile (int index) const noexcept { return files.getReference (index); }

    /** */
    const juce::Array<juce::File>& getFiles() const noexcept { return files; }

    //==============================================================================
    /** @note Does not matter if the file(s) exists or not */
    void addFile (const juce::String& path);
    void addFile (const juce::File& file);

    /** */
    void addDirectory (const juce::String& path);
    /** */
    void addDirectory (const juce::File& file);

    /** */
    void addFiles (const juce::StringArray& filepaths);
    /** */
    void addFiles (const juce::Array<juce::File>& files);

    /** */
    void removeFile (int index);

    /** */
    void clearFiles();

    //==============================================================================
    /** */
    bool containsFilesWithExtension (const juce::String& extension) const;

    /** */
    bool containsOldCStyleCodeFiles() const;

    //==============================================================================
    /** */
    static juce::String getHeaderWildcards() noexcept;

    /** */
    static juce::String getImplementationWildcards() noexcept;

    /** */
    static juce::String getWebWildcards() noexcept;

    /** */
    static juce::String getScriptWildcards() noexcept;

    /** */
    static juce::String getAllWildcards() noexcept;

    //==============================================================================
    /** */
    juce::XmlElement* createXmlState();

    /** */
    void fromXmlState (juce::XmlElement& state);

    //==============================================================================
    class Listener
    {
    public:
        virtual ~Listener() { }

        /** */
        virtual void codeFilesChanged (CodeFileList* list) = 0;
    };

    /** */
    void addListener (Listener* listener);

    /** */
    void removeListener (Listener* listener);

private:
    //==============================================================================
    juce::Array<juce::File> files;
    const juce::String wildcards;
    juce::UndoManager* undoManager;
    juce::ListenerList<Listener> listeners;

    //==============================================================================
    /** */
    bool isValid (const juce::String& filepath);

    /** */
    void cleanUpFileList();

    /** */
    void notifyOfChange();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CodeFileList)
};

#endif //JRL_CODE_FILE_LIST_H