#include <Foundation/Foundation.h>
#include <CoreText/CoreText.h>
#include "sysfonts.h"

static int convertWeight(float weight) {
    if (weight <= -0.8f) return 100;
    if (weight <= -0.6f) return 200;
    if (weight <= -0.4f) return 300;
    if (weight <= -0.0f) return 400;
    if (weight <= 0.25f) return 500;
    if (weight <= 0.35f) return 600;
    if (weight <= 0.4f) return 700;
    if (weight <= 0.6f) return 800;
    return 900;
}

static int convertWidth(float unit) {
    if (unit < 0) {
        return 1 + (1 + unit) * 4;
    }
    return 5 + unit * 4;
}

static FontList *getFonts() {
    static CTFontCollectionRef collection = NULL;
    if (collection == NULL) {
        collection = CTFontCollectionCreateFromAvailableFonts(NULL);
    }

    NSArray *matches = (NSArray *) CTFontCollectionCreateMatchingFontDescriptors(collection);
    FontList *fl = (FontList *) malloc(sizeof(FontList));
    fl->length = matches->count;
    fl->fonts = (FontDescription **) malloc(matches->count * sizeof(FontDescription));
    // TODO
}

// TODO: going to need OSXCross and maybe https://gist.github.com/steeve/6905542 to test cross-compilation
