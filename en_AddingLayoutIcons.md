To add icons for the X language do the following:

  * [Download](http://www.famfamfam.com/lab/icons/flags/) and extract the flag icons.

  * Select an icon which you consider to suite with the X language best of all.

  * Make a grayscale version of the icon. Most of image editors can do it. The grayscale icon will be used when keyla is disabled.

  * Convert the icons from PNG to ICO. You can use the [ConvertIcon](http://converticon.com/) site.

  * Go to the program directory (_"C:\Program Files\keyla"_ by default) and put the icons to the _"icons"_ folder.

  * Find X at [this MSDN page](http://msdn.microsoft.com/en-us/library/ms776294(VS.85).aspx).

> If the page is not found, [search](http://search.msdn.microsoft.com/) for _"Language Identifier Constants and Strings"_.

  * There is a hexadecimal number in the column to the left from the language name (e.g., _0x0419_ for Russian). Remove _0x_ and leading zeroes (one will get _419_ for Russian). Rename the original icon leaving the extension (the original icon for Russian is named _419.ico_). Rename the grayscale icon in the same way, but add _grayscale_ to the end of the file name (the grayscale icon for Russian is named _419\_grayscale.ico_).

  * Done. You do not need to restart keyla. Just switch keyboard layout several times.

  * Please [write an issue](http://code.google.com/p/keyla/issues/entry) and attach the icons. If you do not have a Google account, send the file directly to me (earshinov at gmail dot com) with subject "Keyla layout icons for the X language" replacing X with the actual language name.
