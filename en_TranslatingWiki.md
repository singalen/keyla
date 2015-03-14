In order to edit wiki, you'll need to first get a local copy. Use a Subversion client as described [here](http://code.google.com/p/keyla/source/checkout) with that difference that you should use `http://keyla.googlecode.com/svn/wiki/` instead of `http://keyla.googlecode.com/svn/trunk/`.

Once you've got a local copy, select the translation which you will refer to while creating your own one. Copy the files corresponding to that translation and change prefixes in file names. For example, if you'd like to create an Urkainian translation based on the Russian one, copy all the files which name starts with _ru_ and rename them by replacing _ru_ with _uk_.

Now translate the contents of the files. You can use an ordinary plain text editor.

While translating, leave Wiki special symbols unchanged. Description of these symbols can be found at [the WikiSyntax page](http://code.google.com/p/support/wiki/WikiSyntax) at Google Code.

After you finish translating please [write an issue](http://code.google.com/p/keyla/issues/entry) and attach an archive containing the files you created. If you don't have a Google account, send the files directly to me (earshinov at gmail dot com) with subject "Keyla Wiki localization".