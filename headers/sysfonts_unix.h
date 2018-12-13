#include <stdlib.h>
#include <string.h>
#include <fontconfig/fontconfig.h>
#include "sysfonts.h"

static int convertWeight(int fcWeight) {
    switch (fcWeight) {
        case FC_WEIGHT_THIN: return 100;
        case FC_WEIGHT_ULTRALIGHT: return 200;
        case FC_WEIGHT_LIGHT: return 300;
        case FC_WEIGHT_REGULAR: return 400;
        case FC_WEIGHT_MEDIUM: return 500;
        case FC_WEIGHT_SEMIBOLD: return 600;
        case FC_WEIGHT_BOLD: return 700;
        case FC_WEIGHT_EXTRABOLD: return 800;
        case FC_WEIGHT_ULTRABLACK: return 900;
        default: return 400;
    }
}

static int convertWidth(int fcWidth) {
    switch (fcWidth) {
        case FC_WIDTH_ULTRACONDENSED: return 1;
        case FC_WIDTH_EXTRACONDENSED: return 2;
        case FC_WIDTH_CONDENSED: return 3;
        case FC_WIDTH_SEMICONDENSED: return 4;
        case FC_WIDTH_NORMAL: return 5;
        case FC_WIDTH_SEMIEXPANDED: return 6;
        case FC_WIDTH_EXPANDED: return 7;
        case FC_WIDTH_EXTRAEXPANDED: return 8;
        case FC_WIDTH_ULTRAEXPANDED: return 9;
        default: return 5;
    }
}

static FontDescription *getDescription(FcPattern *p) {
    FcChar8 *name, *path, *family, *style;
    int weight, width, slant, spacing;

    FcPatternGetString(p, FC_POSTSCRIPT_NAME, 0, &name);
    FcPatternGetString(p, FC_FILE, 0, &path);
    FcPatternGetString(p, FC_FAMILY, 0, &family);
    FcPatternGetString(p, FC_STYLE, 0, &style);
    FcPatternGetInteger(p, FC_WEIGHT, 0, &weight);
    FcPatternGetInteger(p, FC_WIDTH, 0, &width);
    FcPatternGetInteger(p, FC_SLANT, 0, &slant);
    FcPatternGetInteger(p, FC_SPACING, 0, &spacing);

    FontDescription *desc = (FontDescription *) malloc(sizeof(FontDescription));
    desc->name = (char *) malloc(strlen((char *) name) + 1);
    strcpy(desc->name, (char *) name);
    desc->path = (char *) malloc(strlen((char *) path) + 1);
    strcpy(desc->path, (char *) path);
    desc->family = (char *) malloc(strlen((char *) family) + 1);
    strcpy(desc->family, (char *) family);
    desc->style = (char *) malloc(strlen((char *) style) + 1);
    strcpy(desc->style, (char *) style);

    desc->weight = convertWeight(weight);
    desc->width = convertWidth(width);
    desc->italic = slant == FC_SLANT_ITALIC;
    desc->monospace = spacing == FC_MONO;

    return desc;
}

static FontList *getFontList(FcFontSet *fs) {
    FontList *list = (FontList *) malloc(sizeof(FontList));
    if (fs) {
        list->length = fs->nfont;
        list->fonts = (FontDescription **) malloc(list->length * sizeof(FontDescription));
        int i;
        for (i = 0; i < list->length; i++) {
            list->fonts[i] = getDescription(fs->fonts[i]);
        }
    }
    return list;
}

static FontList *getFonts() {
    FcInit();
    FcPattern *pattern = FcPatternCreate();
    FcObjectSet *os = FcObjectSetBuild(FC_POSTSCRIPT_NAME, FC_FILE, FC_FAMILY, FC_STYLE, FC_WEIGHT, FC_WIDTH, FC_SLANT, FC_SPACING, NULL);
    FcFontSet *fs = FcFontList(NULL, pattern, os);
    FontList *list = getFontList(fs);
    FcPatternDestroy(pattern);
    FcObjectSetDestroy(os);
    FcFontSetDestroy(fs);

    return list;
}

static void freeFontDescription(FontDescription *fd) {
    if (!fd) {
        return;
    }
    free(fd->name);
    free(fd->family);
    free(fd->style);
    free(fd->path);
    free(fd);
}

static void freeFontList(FontList *fl) {
    if (!fl) {
        return;
    }
    int n = fl->length;
    int i;
    for (i = 0; i < n; i++) {
        freeFontDescription(fl->fonts[i]);
    }
    free(fl->fonts);
    free(fl);
}
