#define CACHED_METRICS  0x10
#define CACHED_BITMAP   0x01
#define CACHED_PIXMAP   0x02

#define TTF_STYLE_NORMAL        0x00
#define TTF_STYLE_BOLD          0x01
#define TTF_STYLE_ITALIC        0x02
#define TTF_STYLE_UNDERLINE     0x04

/* Handy routines for converting from fixed point */
#define FT_FLOOR(X)     ((X & -64) / 64)
#define FT_CEIL(X)      (((X + 63) & -64) / 64)
    
typedef struct _TTF_Font TTF_Font;

#define DROIDSANSMONO_SIZE 118640

extern char DroidSansMono_ttf[DROIDSANSMONO_SIZE];

