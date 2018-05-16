/*
 * depends on : xft, freetype
 * argument : xfld name
 * returns : font path
 */

#include <X11/Xft/Xft.h>
#include <fontconfig/fontconfig.h>

void usage (char* name)
{
    printf ("usage : %s [font name]\n", name);
    exit (1);
}

int main (int argc, char** argv)
{
    if (argc != 2) usage (argv[0]);

    FcConfig* config = FcInitLoadConfigAndFonts ();
    if (! config) return 1;

    FcPattern* pattern = XftXlfdParse (argv[1], FcFalse, FcFalse);
    if (! pattern) return 2;

    FcResult result;
    FcPattern* font = FcFontMatch (config, pattern, &result);
    if (! font) return 3;

    FcChar8* file = NULL;
    if (FcPatternGetString (font, FC_FILE, 0, &file) == FcResultMatch)
        printf ("%s\n", file);

    /* cleanup */
    FcPatternDestroy (font);
    FcPatternDestroy (pattern);
    FcConfigDestroy (config);
    FcFini();

    return 0;
}
