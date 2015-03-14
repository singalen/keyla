To localize keyla, you need to: (1) download source files, (2) translate them and (3) send changes to me. I (4) look at the translation, (5) add it to the project and (6) recompile the program. If the installer is already translated into the same language, I (7) increase keyla's version and (8) upload the new version to the site.

Download the resource files ([one](http://keyla.googlecode.com/svn/trunk/keyla/res/resource.rc), [two](http://keyla.googlecode.com/svn/trunk/layoutHookDll/resource.rc)) and for each of them do the following.

#### 1. Preparation ####

Copy any language section and paste it into the end of the file. For example, if you would like to create a translation based on the English-language one, copy the piece from

`// === english resources ======================================================`

to

`// === russian resources ======================================================`

(excluding the last line).

#### 2. Specifying the language ####

Change the comment in the top of the section and the language name. For example, if you are translating into Ukrainian, instead of

`// === english resources ======================================================`

`LANGUAGE LANG_ENGLISH,SUBLANG_DEFAULT`

use

`// === ukrainian resources=====================================================`

`LANGUAGE LANG_UKRAINIAN,SUBLANG_DEFAULT`

#### 3. Version information ####

Version information is located under the following comment:

`// ------- version info -------------------------------------------------------`

Find a piece of code looking like

`BLOCK "StringFileInfo"`

`BEGIN`

`BLOCK "040904b0"`

and replace the first four digits to the code of the language you are translating into excluding the beginning _0x_.

> The list of codes can be found at [this MSDN page](http://msdn.microsoft.com/en-us/library/ms776294(VS.85).aspx). If the page is not found, please [search](http://search.msdn.microsoft.com/) for "Language Identifier Constants and Strings".

Find **in entire file** the instructions beginning with `VALUE "Translation"` and append to their parameter list the language code and `1200` separating them with commas. In this case _0x_ should be preserved.

Translate all the strings from within the section that take the second place in the parameter list near a `VALUE` keyword.

#### 4. Dialog boxes ####

Information about the dialog boxes is located under the following comment:

`// ------- dialogs ------------------------------------------------------------`

A dialog box is described with a piece of code like the following:

`... DIALOG ...`

`...`

`BEGIN`

`...`

`END`

You have to translate the string located in the code block bounded with `BEGIN` and `END` where all dialog box controls are described. The beginning and the end of the description of a control are indicated with indentation.

The description contains a keyword and a comma-separated parameter list. If the first parameter is a string, you have to translate this string. Otherwise, you have nothing to do with the control.

#### 5. Menus ####

Information about menus are located under the following comment:

`// ------- menus --------------------------------------------------------------`

Each menu is described with a piece of code like the following:

`... MENU`

`BEGIN`

`...`

`END`

You have to translate all the strings located within the block bounded with `BEGIN` and `END`.

#### 6. String table ####

String table is located under the following comment:

`// ------- string table -------------------------------------------------------`

It is described with a piece of code like the following:

`STRINGTABLE`

`BEGIN`

`...`

`END`

You have to translate all the strings located within the block bounded with `BEGIN` and `END`.

#### 7. Sending back the results ####

Please [write an issue](http://code.google.com/p/keyla/issues/entry) and attach the changed resources file. If you don't have a Google account, send the file directly to me (earshinov at gmail dot com) with subject "Keyla localization".