/* 
 * File:   globals.h
 * Author: Saleem Edah-Tally - nmset@yandex.com
 * License : GPL V2
 *
 * Created on 10 décembre 2017, 20:27
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <libintl.h>
#include <string>
using namespace std;

//https://www.labri.fr/perso/fleury/posts/programming/a-quick-gettext-tutorial.html
#define _(STRING) gettext(STRING)

#define _APPNAME_ "PMP7" // Pedal control for Media Player
#define _APP_DESCRIPTION_ "Controls media playback by foot pedal"
#define _VERSION_ "2"
#define _AUTHOR_ "Saleem Edah-Tally - nmset@yandex.com"
#define _ABOUT_ string(_APPNAME_) + string(" - version ") + string(_VERSION_) \
        + string(" - ") + string(_APP_DESCRIPTION_) + _DOT_ \
        + string("\nAuthor : ") + string(_AUTHOR_) \
        + string("\nLicense : GPL v2")

#define _DOT_ "."
#define _SPACE_ " "
#define _COMMA_ ","
#define _COLON_ ":"
#define _NL_ "\n"

#endif /* GLOBALS_H */

