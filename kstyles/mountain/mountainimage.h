/* Mountain Style for KDE3 */
#ifndef __mountain_image_h__
#define __mountain_image_h__

struct MountainEmbedImage {
  bool haveAlpha;
  int width;
  int height;
  int id;
  const unsigned char* data;
};

extern MountainEmbedImage* MountainGetDbImage(int id);
extern void MountainDbCleanup();

enum MountainTileType {
  MountainTileTL = 0,
  MountainTileTC = 1,
  MountainTileTR = 2,
  MountainTileCL = 3,
  MountainTileCC = 4,
  MountainTileCR = 5,
  MountainTileRL = 6,
  MountainTileRC = 7,
  MountainTileRR = 8,
  MountainTileSeparator = 16,
  MountainSlider1 = 32,
  MountainSlider2 = 48,
  MountainSlider3 = 64,
  MountainSlider4 = 80,
  MountainGroove1 = 96,
  MountainGroove2 = 112,
};

#endif /* __mountain_image_h__ */
