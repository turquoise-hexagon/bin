/*
 * depends on : freetype
 * argument : path to a bitmap font
 * returns : pixel width
 */

#include <ft2build.h>
#include FT_FREETYPE_H

void usage (char* name)
{
    printf ("usage : %s [font path]\n", name);
    exit (1);
}

int main (int argc, char** argv)
{
    if (argc < 2) usage (argv[0]);

    FT_Library library;
    FT_Error error;
    FT_Face face;

    error = FT_Init_FreeType (&library);
    if (error) return 1;

    error = FT_New_Face (library, argv[1], 0, &face);
    if (error) return 2;

    FT_Set_Pixel_Sizes (face, 0, 10);
    FT_GlyphSlot slot = face->glyph;

    int i = 0, width = 0;

    while (width == 0) {
        error = FT_Load_Glyph (face, i, FT_LOAD_DEFAULT);
        if (error) return 3;

        width = slot->advance.x;
        i++;
    }

    printf ("%i\n", width/64);

    return 0;
}
