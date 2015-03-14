To localize the installer, you need to: (1) download source files, (2) translate them and (3) send changes to me. I (4) look at the translation, (5) add it to the project and (6) recompile the program. If the program's interface is already translated into the same language, I (7) increase keyla's version and (8) upload the new version to the site.

#### 1. Preparation ####

First, download [the NSIS script](http://keyla.googlecode.com/svn-history/r34/trunk/NSIS%20installer/keyla.nsi).

Second, select an `*`.nsh file from [the "languages" folder](http://code.google.com/p/keyla/source/browse/trunk/?r=34#trunk/NSIS%20installer/languages) corresponding to the translation you would like to refer while creating your own one. To download the file click on its name and select "View raw file" on the next page.

#### 2. Adding your language ####

The corresponding NSIS instruction looks like the following:

`!insertmacro MUI_LANGUAGE "<Language>"`,

where `<Language>` is the language's name. All such instructions are located in a list in the NSIS script. Search for `MUI_LANGUAGE` to find them. Add the new instruction to the end of the list. For example:

`!insertmacro MUI_LANGUAGE "Ukrainian"`

#### 3. Include the `*`.nsh file ####

Initially, rename the `*`.nsh file you have downloaded. For example, file for the Unkrainian translation should be named "ukrainian.nsh".

NSIS instruction for inclusion looks like the following:

`!include "<path\to\file.nsh>"`

They are all located in a list in the NSIS script. Search for `english.nsh` to find them. Add the new instruction to the end of the list. For example,

`!include "languages\ukrainian.nsh"`

#### 4. Version information ####

Version information is located in the NSIS script under the following comment:

`; Languages`

Parts of the version information are added with the `ViAddVersionKey` instruction. They are grouped by language. Copy any of the groups to the end of the list and change it.

First, change the constant that looks like `${LANG_<LANGUAGE>}`. For example, if you are translating into Ukrainian, change it to `${LANG_UKRAINIAN}`.

Second, translate the instructions. If an instruction contains two strings, the second one should be translated. Do not touch other strings.

#### 5. Translate the `*`.nsh file ####

Change the `${LANG_<LANGUAGE>}` constant in the same way. Then translate all strings.

#### 6. Sending back the results ####

Please [write an issue](http://code.google.com/p/keyla/issues/entry) and attach all the files. If you don't have a Google account, send the files directly to me (earshinov at gmail dot com) with subject "Keyla installer localization".

You can put the files into an archive if you wish. You don't have to lay out the files into folders.