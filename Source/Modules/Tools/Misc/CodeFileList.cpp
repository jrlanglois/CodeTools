#include "CodeFileList.h"

//==============================================================================
CodeFileList::CodeFileList (juce::UndoManager* um) noexcept :
    wildcards (getAllWildcards()),
    asteriskFreeWildcards (getAllWildcards().removeCharacters ("*")),
    undoManager (um)
{
}

//==============================================================================
void CodeFileList::addFile (const juce::String& filepath)
{
    if (isValid (filepath))
        files.addIfNotAlreadyThere (filepath);
}

void CodeFileList::addFile (const juce::File& file)
{
    addFile (file.getFullPathName().trim());
}

void CodeFileList::addDirectory (const juce::String& path)
{
    addDirectory (juce::File (path));
}

void CodeFileList::addDirectory (const juce::File& file)
{
    if (file.isDirectory())
    {
        juce::Array<juce::File> results;
        file.findChildFiles (results, juce::File::findFilesAndDirectories, true, wildcards);

        for (int i = results.size(); --i >= 0;)
            addDirectory (results.getReference (i)); //N.B.: Don't use addFile() - it will be a redundant check to see if the file is valid
    }
    else
    {
        addFile (file.getFullPathName());
    }
}

void CodeFileList::addFiles (const juce::StringArray& filepaths)
{
    for (int i = filepaths.size(); --i >= 0;)
        addDirectory (filepaths.strings.getUnchecked (i));

    cleanUpFileList();
}

void CodeFileList::addFiles (const juce::Array<juce::File>& files)
{
    for (int i = files.size(); --i >= 0;)
        addDirectory (files.getReference (i).getFullPathName());

    cleanUpFileList();
}

void CodeFileList::removeFile (const int index)
{
    files.remove (index);
}

void CodeFileList::cleanUpFileList()
{
}

void CodeFileList::clearFiles()
{
    //Desktops can usually handle a bit more
    //memory usage without caring about energy usage.
   #if JUCE_WINDOWS || JUCE_MAC
    files.clearQuick();
   #else
    files.clear();
   #endif
}

//==============================================================================
juce::String CodeFileList::getHeaderWildcards() noexcept
{
    return "*.h;*.hh;*.hpp;*.hxx;*.inl";
}

juce::String CodeFileList::getImplementationWildcards() noexcept
{
    return "*.c;*.cc;*.cbp;*.cpp;*.cxx;*.m;*.mm";
}

juce::String CodeFileList::getWebWildcards() noexcept
{
    return "*.htm;*.html;*.dhtml;*.xhtml;*.css;";
}

juce::String CodeFileList::getScriptWildcards() noexcept
{
    return "*.js;*.lua;*.json;*.xml;*.svg;*.xss;*.php;*.rb;*.rbw;*.pl;*.pm;*.t;*.pod";
}

juce::String CodeFileList::getAllWildcards() noexcept
{
    return getHeaderWildcards()
           + ";" + getImplementationWildcards()
           + ";" + getWebWildcards()
           + ";" + getScriptWildcards();
}

//==============================================================================
bool CodeFileList::containsFilesWithExtension (const juce::String& extension) const
{
    for (int i = files.size(); --i >= 0;)
        if (juce::File (files.getUnchecked (i)).hasFileExtension (extension))
            return true;

    return false;
}

bool CodeFileList::containsOldCStyleCodeFiles() const
{
    return containsFilesWithExtension (".c")
           || containsFilesWithExtension (".cc");
}

//==============================================================================
bool CodeFileList::isValid (const juce::File& file) const
{
    if (file.existsAsFile())
        return file.hasFileExtension (asteriskFreeWildcards);

    return false;
}

bool CodeFileList::isValid (const juce::String& filepath) const
{
    return isValid (juce::File (filepath));
}

//==============================================================================
juce::XmlElement* CodeFileList::createXmlState()
{
    juce::XmlElement* state = new juce::XmlElement ("CodeFileList");

    for (int i = getNumFiles(); --i >= 0;)
    {
        juce::XmlElement* fileState = new juce::XmlElement ("CodeFile");
        fileState->setAttribute ("Path", getFile (i).getFullPathName());

        state->prependChildElement (fileState);
    }

    return state;
}

void CodeFileList::fromXmlState (juce::XmlElement& state)
{
    clearFiles();

    if (state.getTagName() == "CodeFileList")
    {
        forEachXmlChildElementWithTagName (state, child, "CodeFile")
            addFile (child->getStringAttribute ("Path").trim());
    }
    else
    {
        jassertfalse;
    }
}

//==============================================================================
void CodeFileList::addListener (Listener* const listener)
{
    listeners.add (listener);
}

void CodeFileList::removeListener (Listener* const listener)
{
    listeners.remove (listener);
}

void CodeFileList::notifyOfChange()
{
    listeners.call (&Listener::codeFilesChanged, this);
}