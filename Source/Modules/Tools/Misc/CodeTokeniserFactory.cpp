CodeTokeniserFactory::CodeTokeniserFactory() noexcept
{
    populateTokenisers();
}

//==============================================================================
juce::CodeTokeniser* CodeTokeniserFactory::getTokeniserForFile (const juce::File& file) const
{
    if (file.hasFileExtension ((CodeFileList::getHeaderWildcards() + CodeFileList::getImplementationWildcards()).removeCharacters ("*")))
    {
        return tokenisers.getUnchecked (0);
    }
    else if (file.hasFileExtension (".lua"))
    {
        return tokenisers.getUnchecked (1);
    }
    else if (file.hasFileExtension (".xml;.svg"))
    {
        return tokenisers.getUnchecked (2);
    }

    return nullptr;
}

//==============================================================================
void CodeTokeniserFactory::populateTokenisers()
{
    tokenisers.add (new juce::CPlusPlusCodeTokeniser());
    tokenisers.add (new juce::LuaTokeniser());
    tokenisers.add (new juce::XmlTokeniser());
}