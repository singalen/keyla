#### Users' suggestions ####

There are some suggestions at the <a href='http://mrshadow.habrahabr.ru/blog/44656/'>discussion at Habrahabr</a> (in Russian).

Summary:
  * provide a key to change layout or letter case of already written text;
  * support phrase substitution (e.g., "plz" -> "please");
  * support letter substitution (this may be useful when you don't like your keyboard layout);
  * show the layout icon next to the text cursor or the focused text entry.

#### Switching layouts using the tray icon menu ####

It's a very useful feature provided even by the Language Panel in Windows.

_Note._ Implementation isn't simple because when you click the tray icon, the active window looses focus. So a click at a hypothetical menu item will change the keyboard layout in keyla, not the layout in the window you wished.

#### Indication of the current layout on keyboard LEDs ####

It enables you to be able to figure the current layout out with your side sight.

_Note._ AFAIK, there is the only way to control LEDs on an USB keyboard from the user mode in Windows NT4 and later. This way is to simulate that a key (Caps Lock, Num Lock or Scroll Lock) was pressed. The main question is how to enable the Caps LED so that Windows won't go to the upper case mode...

If the task can't be solved for USB keyboards, it isn't worth solving for PS-2 keyboards only.