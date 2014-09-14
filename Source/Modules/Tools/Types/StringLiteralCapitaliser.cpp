#include "StringLiteralCapitaliser.h"

//==============================================================================
class StringLiteralCapitaliser::CaseChangeBase
{
public:
    CaseChangeBase() noexcept { }
    virtual ~CaseChangeBase() noexcept { }

    virtual void perform (juce::String& line) noexcept = 0;

protected:
    static void parseStringLiteral (juce::String::CharPointerType& p, juce::MemoryOutputStream& out) noexcept
    {
        p = p.findEndOfWhitespace();

        if (p.getAndAdvance() == '"')
        {
            juce::String::CharPointerType start (p);

            for (;;)
            {
                const juce::juce_wchar c = *p;

                if (c == '"')
                {
                    out << juce::String (start, p);
                    ++p;
                    parseStringLiteral (p, out);
                    return;
                }

                if (c == 0)
                    break;

                if (c == '\\')
                {
                    out << juce::String (start, p);
                    ++p;
                    out << juce::String::charToString (readEscapedChar (p));
                    start = p + 1;
                }

                ++p;
            }
        }
    }

private:
    static juce::juce_wchar readEscapedChar (juce::String::CharPointerType& p)
    {
        juce::juce_wchar c = *p;

        switch (c)
        {
            case '"':
            case '\\':
            case '/':
            break;

            case 'b':
            {
                c = '\b';
            }
            break;

            case 'f':
            {
                c = '\f';
            }
            break;

            case 'n':
            {
                c = '\n';
            }
            break;

            case 'r':
            {
                c = '\r';
            }
            break;

            case 't':
            {
                c = '\t';
            }
            break;

            case 'x':
            {
                ++p;
                c = 0;

                for (int i = 4; --i >= 0;)
                {
                    const int digitValue = juce::CharacterFunctions::getHexDigitValue (*p);

                    if (digitValue < 0)
                        break;

                    ++p;
                    c = (juce::juce_wchar) ((c << 4) + digitValue);
                }
            }
            break;

            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                c = 0;

                for (int i = 4; --i >= 0;)
                {
                    const int digitValue = *p - '0';

                    if (digitValue < 0 || digitValue > 7)
                        break;

                    ++p;
                    c = (juce::juce_wchar) ((c << 3) + digitValue);
                }

            }
            break;

            default:
            break;
        }

        return c;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CaseChangeBase)
};

class StringLiteralCapitaliser::CaseChangeUpper : public CaseChangeBase
{
public:
    CaseChangeUpper() noexcept { }
    ~CaseChangeUpper() noexcept { }

    void perform (juce::String&) noexcept override
    {

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CaseChangeUpper)
};

class StringLiteralCapitaliser::CaseChangeLower : public CaseChangeBase
{
public:
    CaseChangeLower() noexcept { }
    ~CaseChangeLower() noexcept { }

    void perform (juce::String&) noexcept override
    {

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CaseChangeLower)
};

class StringLiteralCapitaliser::CaseChangeTitle : public CaseChangeBase
{
public:
    CaseChangeTitle() noexcept { }
    ~CaseChangeTitle() noexcept { }

    void perform (juce::String&) noexcept override
    {

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CaseChangeTitle)
};

class StringLiteralCapitaliser::CaseChangeSentence : public CaseChangeBase
{
public:
    CaseChangeSentence() noexcept { }
    ~CaseChangeSentence() noexcept { }

    void perform (juce::String&) noexcept override
    {

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CaseChangeSentence)
};

//==============================================================================
StringLiteralCapitaliser::StringLiteralCapitaliser (const CodeFileList& c) :
    CodeTool (c)
{
    //Case changers are added in the order of the enumeration:
    caseChangers.add (new CaseChangeUpper());
    caseChangers.add (new CaseChangeLower());
    caseChangers.add (new CaseChangeTitle());
    caseChangers.add (new CaseChangeSentence());

    caseChangers.minimiseStorageOverheads();
}

//==============================================================================
StringLiteralCapitaliser::CaseChangeBase* StringLiteralCapitaliser::getCaseChangeForStyle (const Style style) const noexcept
{
    return caseChangers.getUnchecked ((int) style);
}

void StringLiteralCapitaliser::capitalise (const juce::File& file, const Style style)
{
    if (! file.hasWriteAccess())
        return;

    //Get the lines:
    juce::StringArray lines;
    file.readLines (lines);

    //Capitalise:
    if (CaseChangeBase* const caseChanger = getCaseChangeForStyle (style))
    {
        for (int i = lines.size(); --i >= 0;)
            caseChanger->perform (lines.getReference (i));

        //Write the result back to the source file:
        juce::ScopedPointer<juce::FileOutputStream> stream (file.createOutputStream());

        if (stream != nullptr)
            writeLinesToStream (stream, lines);
    }
}

//==============================================================================
void StringLiteralCapitaliser::perform (const Style style)
{
    const CodeFileList& codeFiles = getCodeFiles();

    for (int i = codeFiles.getNumFiles(); --i >= 0;)
        capitalise (codeFiles[i], style);
}