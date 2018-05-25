/*
 * depends on : xft, fontconfig
 * argument : xfld name
 * returns : font path
 */

#include <err.h>
#include <X11/Xft/Xft.h>

void usage (char* name)
{
    printf ("usage : %s [font name]\n", name);
    exit (1);
}

int main (int argc, char** argv)
{
    if (argc != 2) usage (argv[0]);

    FcResult result;

    FcConfig* config = FcInitLoadConfigAndFonts ();
    if (! config)
        errx (1, "failed to initialiaze fontconfig");

    FcPattern* pattern = XftXlfdParse (argv[1], FcFalse, FcFalse);
    if (! pattern)
        errx (1, "failed to parse pattern");

    FcPattern* font = FcFontMatch (config, pattern, &result);
    if (! font)
        errx (1, "failed to open font");

    FcChar8* file = NULL;
    if (FcPatternGetString (font, FC_FILE, 0, &file) == FcResultMatch)
        printf ("%s\n", file);

    FcPatternDestroy (font);
    FcPatternDestroy (pattern);
    FcConfigDestroy (config);
    FcFini ();

    return 0;
}
