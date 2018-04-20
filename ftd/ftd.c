/*
 * depends on : freetype
 * options : width / height
 * argument : path to a bitmap font
 * returns : size in pixels
 */

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

void usage (char* name)
{
    printf ("usage : %s [-wh] [font path]\n", name);
    exit (1);
}

int main (int argc, char** argv)
{
    if (argc < 3) usage (argv[0]);

    FT_Library library;
    FT_Glyph glyph;
    FT_Error error;
    FT_Face face;

    error = FT_Init_FreeType (&library);
    if (error) return 1;

    error = FT_New_Face (library, argv[2], 0, &face);
    if (error) return 2;

    int w = 0, h = 0, i = 0;

    while (w == 0) {
        error = FT_Load_Glyph (face, i, FT_LOAD_DEFAULT);
        if (error) return 3;

        error = FT_Get_Glyph (face->glyph, &glyph);
        if (error) return 4;

        h = face->glyph->metrics.height;
        w = face->glyph->metrics.width;

        i++;
    }

    FT_Done_Glyph (glyph);

    if (strncmp (argv[1], "-w", 2) == 0) printf ("%i\n", w/64);
    if (strncmp (argv[1], "-h", 2) == 0) printf ("%i\n", h/64);

    return 0;
}
