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
FT_UInt index;
FT_Face face;

int w;
int h;

void usage (char* name)
{
    printf ("usage : %s [xlfd] [text]\n", name);
    exit (1);
}

void init_fontconfig ()
{
    config = FcInitLoadConfigAndFonts ();
    if (! config) errx (1, "failed to initialize fontconfig");
}

void init_freetype ()
{
    error = FT_Init_FreeType (&library);
    if (error) errx (2, "failed to initialize freetype library");
}

void get_file (char* name)
{
    pattern = XftXlfdParse (name, FcFalse, FcFalse);
    if (! pattern) errx (1, "failed to parse pattern");

    font = FcFontMatch (config, pattern, &result);
    if (! font) errx (1, "failed to match font");

    FcPatternGetString (font, FC_FILE, 0, &file);
    if (! file) errx (1, "failed to get font file");
}

void get_size (char* string)
{
    error = FT_New_Face (library, ((const char*) file), 0, &face);
    if (error) errx (2, "failed to open font face");

    for (int i = 0; string [i] != '\0'; i++)
    {
        index = FT_Get_Char_Index (face, string [i]);

        error = FT_Load_Glyph (face, index, FT_LOAD_DEFAULT);
        if (error) errx (2, "failed to load glyph");

        w = w + face -> glyph -> metrics.horiAdvance / 64;
    }

    h = face -> glyph -> metrics.vertAdvance / 64;
}

void cleanup ()
{
    FT_Done_FreeType (library);

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
