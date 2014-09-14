#ifndef JRL_CODE_TOOL_H
#define JRL_CODE_TOOL_H

/**
    @file CodeTool.h
    @copyright jrlanglois

*/
class CodeTool
{
public:
    /** Constructor */
    CodeTool (const CodeFileList& codeFiles) noexcept;

    /** Destructor */
    virtual ~CodeTool();

    //==============================================================================
    /** */
    virtual bool canApplyToFile (const juce::File& file) const;

protected:
    //==============================================================================
    /** */
    inline const CodeFileList& getCodeFiles() const noexcept { return codeFiles; }

    /** */
    void writeLinesToStream (juce::FileOutputStream* stream,
                             juce::StringArray& lines,
                             const juce::String& lineEnding = juce::newLine);

private:
    //==============================================================================
    const CodeFileList& codeFiles;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CodeTool)
};

#endif //JRL_CODE_TOOL_H