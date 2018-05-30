#include <err.h>
#include <ft2build.h>
#include <X11/Xft/Xft.h>

FcConfig* config;
FcPattern* font;
FcPattern* pattern;
FcChar8* file;
FcResult result;

FT_Library library;
FT_Error error;
FT_Face face;

int w = 0, h = 0;

void usage (char* name)
{
    printf ("usage : %s [xlfd] [text]\n", name);
    exit (1);
}

void init_fontconfig ()
{
    config = FcInitLoadConfigAndFonts ();
    if (! config)
        errx (1, "failed to initialize fontconfig");
}

void init_freetype ()
{
    error = FT_Init_FreeType (&library);
    if (error)
        errx (2, "failed to initialize freetype library");
}

void get_file (char* xfld)
{
    pattern = XftXlfdParse (xfld, FcFalse, FcFalse);
    if (! config)
        errx (1, "failed to parse xlfd pattern");

    font = FcFontMatch (config, pattern, &result);
    if (! font)
        errx (1, "failed to match font");

    FcPatternGetString (font, FC_FILE, 0, &file);
    if (! file)
        errx (1, "failed to get font file");
}

void get_size (char* string)
{
    error = FT_New_Face (library, ((const char*) file), 0, &face);
    if (error)
        errx (2, "failed to open font face");

    int i = 0, l = strlen (string);

    /* iterate until we get a valid glyph */
    while (w == 0) {
        error = FT_Load_Glyph (face, i, FT_LOAD_DEFAULT);
        if (error)
            errx (2, "failed to load glyph");

        w = face -> glyph -> metrics.horiAdvance;
        h = face -> glyph -> metrics.vertAdvance;

        i++;
    }

    /* get the right values */
    w = w / 64 * l;
    h = h / 64;
}

void cleanup ()
{
    /* freetype */
    FT_Done_FreeType (library);

    /* fontconfig */
    FcPatternDestroy (font);
    FcPatternDestroy (pattern);

    FcConfigDestroy (config);

    FcFini ();
}

int main (int argc, char** argv)
{
    if (argc != 3) usage (argv [0]);

    init_fontconfig ();
    init_freetype ();

    get_file (argv [1]);
    get_size (argv [2]);

    printf ("%i %i\n", w, h);

    cleanup ();

    return 0;
}
