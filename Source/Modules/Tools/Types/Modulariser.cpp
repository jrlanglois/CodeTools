#include "Modulariser.h"

Modulariser::Modulariser (const CodeFileList& c) :
    CodeTool (c)
{
}

//==============================================================================
void Modulariser::saveTo (const juce::File& destinationFolder,
                          const juce::String& sourceFolderToRemove,
                          const juce::String& moduleName,
                          const juce::String& headerGuard,
                          const juce::String& desiredNamespace)
{
    const CodeFileList& codeFiles = getCodeFiles();
    const int numFiles = codeFiles.getNumFiles();

    if (numFiles > 0
        && moduleName.isNotEmpty()
        && headerGuard.isNotEmpty())
    {
        const juce::String moduleNameToUse (moduleName.trim());
        const juce::String headerGuardToUse (headerGuard.toUpperCase().trim());
        const juce::String namespaceToUse (desiredNamespace.trim());
        const juce::String headerWildcards (codeFiles.getHeaderWildcards().removeCharacters ("*"));
        const juce::String implementationWildcards (codeFiles.getImplementationWildcards().removeCharacters ("*"));

        const juce::File moduleHeader (destinationFolder.getFullPathName() + "/" + moduleNameToUse + ".h");
        moduleHeader.deleteFile();
        moduleHeader.create();

        const bool endsWithSlash = sourceFolderToRemove.endsWith ("/") || sourceFolderToRemove.endsWith ("\\");
        const int numPathCharsToRemove = sourceFolderToRemove.length() - (endsWithSlash ? 1 : 0);

        juce::String spacer;

        {
            int numSpaces = desiredNamespace.isEmpty() ? 0 : 4;

            while (--numSpaces >= 0)
                spacer += " ";
        }

        { //Write the header file contents:
            juce::String data;

            data << "#ifndef " << headerGuardToUse << juce::newLine
                 << "#define " << headerGuardToUse << juce::newLine
                 << juce::newLine << juce::newLine << juce::newLine;

            if (namespaceToUse.isNotEmpty())
            {
                data << "namespace " << namespaceToUse << juce::newLine
                     << "{" << juce::newLine;
            }

            for (int i = 0; i < numFiles; ++i)
            {
                const juce::File file (codeFiles[i]);

                if (file.hasFileExtension (headerWildcards))
                {
                    juce::ScopedPointer<juce::FileInputStream> guardFinder (file.createInputStream());
                    jassert (guardFinder != nullptr);

                    const juce::String code (guardFinder->readString());
                    const int startIndex = code.indexOf ("#ifndef ") + 8;
                    const int endIndex = startIndex + code.substring (startIndex).indexOf ("\n");

                    const juce::String guard (code.substring (startIndex, endIndex)
                                                  .trim()
                                                  .removeCharacters (juce::newLine)
                                                  .removeCharacters ("\n")
                                                  .removeCharacters ("\r"));

                    juce::String fileShort = file.getFullPathName()
                                                 .replaceCharacters ("\\", "/")
                                                 .replaceSection (0, numPathCharsToRemove, juce::String::empty);

                    if (fileShort.startsWith ("/"))
                        fileShort = fileShort.substring (1);

                    data << spacer << "#ifndef " << guard << juce::newLine
                         << spacer << "    #include \"" << fileShort << "\"" << juce::newLine
                         << spacer << "#endif //" << guard << juce::newLine;

                    if (i != (numFiles - 1))
                        data << juce::newLine;
                }
            }

            if (namespaceToUse.isNotEmpty())
                data << "}" << juce::newLine;

            data << juce::newLine;
            data << "#endif //" << headerGuardToUse;

            juce::ScopedPointer<juce::FileOutputStream> stream (moduleHeader.createOutputStream());
            stream->writeText (data, false, false);
        }

        const juce::File moduleCPP (destinationFolder.getFullPathName() + "/" + moduleNameToUse + ".cpp");
        moduleCPP.deleteFile();
        moduleCPP.create();

        { //Write the CPP file contents:
            juce::String data (juce::String::empty);

            data << "#include \"" << moduleNameToUse << ".h\"" << juce::newLine;
            data << juce::newLine;

            if (namespaceToUse.isNotEmpty())
            {
                data << "namespace " << namespaceToUse << juce::newLine;
                data << "{" << juce::newLine;
            }

            for (int i = 0; i < numFiles; ++i)
            {
                const juce::File file (codeFiles[i]);

                if (file.hasFileExtension (implementationWildcards))
                {
                    juce::String fileShort = file.getFullPathName()
                                                 .replaceCharacters ("\\", "/")
                                                 .replaceSection (0, numPathCharsToRemove, juce::String::empty);

                    if (fileShort.startsWith ("/"))
                        fileShort = fileShort.substring (1);

                    data << spacer << "#include \"" << fileShort << "\"";

                    if (i != (numFiles - 1))
                        data << juce::newLine;
                }
            }

            if (namespaceToUse.isNotEmpty())
                data << "}";

            juce::ScopedPointer<juce::FileOutputStream> stream (moduleCPP.createOutputStream());
            stream->writeText (data, false, false);
        }
    }
}