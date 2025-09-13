#ifndef __PSF_H_
#define __PSF_H_

#define PSF1_FONT_MAGIC		0x0436

typedef struct {
	uint16_t magic;		/* magic bytes for identification */
	uint8_t mode;		/* PSF font mode */
	uint8_t char_size;	/* PSF character size */
} psf1_header_t;

#define PSF2_FONT_MAGIC		0x864AB572

typedef struct {
	uint32_t magic;			/* magic bytes to identify PSF */
	uint32_t version;		/* zero */
	uint32_t header_size;		/* offset of bitmaps in file */
	uint32_t flags;			/* 0 if there is no unicode table */
	uint32_t num_glyph;		/* number of glyphs */
	uint32_t bytes_per_glyph;	/* size of each glyph */
	uint32_t height;		/* height in pixels */
	uint32_t width;			/* width in pixels */
} psf2_t;

#endif
