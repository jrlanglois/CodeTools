/**
    @file JRLTools.h
    @copyright jrlanglois

    This is the master module header for the various tools.

    @note Please keep the inclusions alphabetically sorted!
*/
#ifndef JRL_TOOLS_H
#define JRL_TOOLS_H

#include "../Core/JRLCore.h"

#ifndef JRL_CODE_FILE_LIST_COMPONENT_H
 #include "Components/CodeFileListComponent.h"
#endif //JRL_CODE_FILE_LIST_COMPONENT_H

#ifndef JRL_LINE_ENDINGS_CONVERTER_COMPONENT_H
 #include "Components/LineEndingsConverterComponent.h"
#endif //JRL_LINE_ENDINGS_CONVERTER_COMPONENT_H

#ifndef JRL_MODULARISER_COMPONENT_H
 #include "Components/ModulariserComponent.h"
#endif //JRL_MODULARISER_COMPONENT_H

#ifndef JRL_TABS_TO_SPACES_COMPONENT_H
 #include "Components/TabsToSpacesComponent.h"
#endif //JRL_TABS_TO_SPACES_COMPONENT_H

#ifndef JRL_TOOL_COMPONENT_H
 #include "Components/ToolComponent.h"
#endif //JRL_TOOL_COMPONENT_H

#ifndef JRL_TRAILING_WHITESPACE_CLEANER_COMPONENT_H
 #include "Components/TrailingWhitespaceCleanerComponent.h"
#endif //JRL_TRAILING_WHITESPACE_CLEANER_COMPONENT_H

#ifndef JRL_CODE_FILE_LIST_H
 #include "Misc/CodeFileList.h"
#endif //JRL_CODE_FILE_LIST_H

#ifndef JRL_CODE_TOKENISER_FACTORY_H
 #include "Misc/CodeTokeniserFactory.h"
#endif

#ifndef JRL_CODE_TOOL_H
 #include "Types/CodeTool.h"
#endif //JRL_CODE_TOOL_H

#ifndef JRL_LINE_ENDINGS_CONVERTER_H
 #include "Types/LineEndingsConverter.h"
#endif //JRL_LINE_ENDINGS_CONVERTER_H

#ifndef JRL_MODULARISER_H
 #include "Types/Modulariser.h"
#endif //JRL_MODULARISER_H

#ifndef JRL_STRING_LITERAL_CAPITALISER_H
 #include "Types/StringLiteralCapitaliser.h"
#endif //JRL_STRING_LITERAL_CAPITALISER_H

#ifndef JRL_TABS_TO_SPACES_H
 #include "Types/TabsToSpaces.h"
#endif //JRL_TABS_TO_SPACES_H

#ifndef JRL_TRAILING_WHITESPACE_CLEANER_H
 #include "Types/TrailingWhitespaceCleaner.h"
#endif //JRL_TRAILING_WHITESPACE_CLEANER_H

#endif //JRL_TOOLS_H