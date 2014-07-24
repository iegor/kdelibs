/* A small utility to generate embedded images for Mountain, especially structured for easy recoloring */

#include <iostream>
#include <string.h>
#include <math.h>

/* Qt */
#include <qfileinfo.h>
#include <qimage.h>
#include <qmap.h>
#include <qregexp.h>
#include <qtextstream.h>
#include <qvaluevector.h>

/* KDE */
#include <kimageeffect.h>

//NOTE: Use of old-style header is intentional for portability. See revisions 1.6 and 1.7
//Force-touch-embedded-revision: 2

/* Mountain */
#include "mountainimage.h"

using std::cout;
using std::cerr;

/*
  Need to generate something like this:
  TargetColorAlpha, GreyAdd, SrcAlpha;

  so that one can do (R*T+GreyAdd, G*T+GreyAdd, B*T+GreyAdd, SrcAlpha) as pixel values
*/

int evalSuffix(QString suffix) {
  if(suffix == "-tl") { return 0; }
  if(suffix == "-tc") { return 1; }
  if(suffix == "-tr") { return 2; }
  if(suffix == "-cl") { return 3; }
  if(suffix == "-cc") { return 4; }
  if(suffix == "-cr") { return 5; }
  if(suffix == "-bl") { return 6; }
  if(suffix == "-bc") { return 7; }
  if(suffix == "-br") { return 8; }
  if(suffix == "-separator") { return MountainTileSeparator; }
  if(suffix == "-slider1") { return MountainSlider1; }
  if(suffix == "-slider2") { return MountainSlider2; }
  if(suffix == "-slider3") { return MountainSlider3; }
  if(suffix == "-slider4") { return MountainSlider4; }
  if(suffix == "-groove1") { return MountainGroove1; }
  if(suffix == "-groove2") { return MountainGroove2; }
  if(suffix == "-1") { return 1; }
  if(suffix == "-2") { return 2; }
  if(suffix == "-3") { return 3; }
  return -1;
}


int main(int argc, char** argv) {
  if(argc < 2) { return 0; }

  QValueVector<MountainEmbedImage> images;

  cout << "#include <qintdict.h>\n\n";
  cout << "#include \"mountainimage.h\"\n\n";

  QMap<QString, int> assignID;
  int nextID = 0;

  for(int c = 1; c < argc; c++) {

    QImage input(argv[c]);

    QFileInfo fi(argv[c]);
    QString s = fi.baseName();

    MountainEmbedImage image;

    int pos;

    QString id = s;

    int readJustID = 0;

    if((pos = s.findRev("-")) != -1) {
      int suffix = evalSuffix(s.mid(pos));
      if(suffix != -1) {
        id = s.mid(0, pos);
        readJustID = suffix;
      }
    }

    if(!assignID.contains(id)) {
      assignID[id] = nextID;
      nextID += 256;
    }

    s.replace("-", "_");

    if(s.contains("button")) { KImageEffect::contrastHSV(input); }

    int fullID = assignID[id] + readJustID; //Subwidget..

    bool highlights = true;
    bool shadows  = true;

    float gamma    = 1.0;
    int brightAdj = 0;

    if(s.contains("toolbar") || s.contains("tab-top-active") || s.contains("menubar")) {
      //highlights = false;
      gamma    = 1 / 1.25f;
      //brightAdj = 10;
      shadows = false;
    }

    if(s.contains("scrollbar") && s.contains("groove")) {
      //highlights = false;
      //gamma = 1.5;
      shadows = false;
    }
    //brightAdj = -10;

    if(s.contains("scrollbar") && s.contains("slider")) {
      //highlights = false;
      gamma = 1 / 0.7f;
      //shadows = false;
    }


    if(s.contains("menuitem")) {
      //highlights = false;
      gamma = 1 / 0.6f;
      //shadows = false;
    }

    image.width   = input.width();
    image.height = input.height();
    image.id         = fullID;
    image.data     = reinterpret_cast<unsigned char*>(strdup(s.latin1()));

    bool reallySolid = true;

    int pixCount = 0;
    int pixSolid = 0;

    cout << "static const unsigned char " << s.latin1() << "[]={\n";

    Q_UINT32* read  = reinterpret_cast< Q_UINT32* >(input.bits());
    int size = input.width() * input.height();

    for(int pos = 0; pos < size; pos++) {
      QRgb basePix = (QRgb) * read;

      if(qAlpha(basePix) != 255)
      { reallySolid = false; }
      else
      { pixSolid++; }

      pixCount++;
      read++;
    }

    image.haveAlpha = !reallySolid;

    images.push_back(image);

    read  = reinterpret_cast< Q_UINT32* >(input.bits());
    for(int pos = 0; pos < size; pos++) {
      QRgb basePix = (QRgb) * read;
      //cout<<(r*destAlpha.alphas[pos])<<"\n";
      //cout<<(int)destAlpha.alphas[pos]<<"\n";
      QColor clr(basePix);
      int h, s, v;
      clr.hsv(&h, &s, &v);

      v = qGray(basePix);

      int targetColorAlpha = 0 , greyAdd = 0;
      //int srcAlpha = qAlpha(basePix);

      if(s > 0 || v > 128) {
        //Non-shadow
        float fv = v / 255.0;
        fv = pow(fv, gamma);
        v = int(255.5 * fv);


        if(s < 17 && highlights) { //A bit of a highligt..
          float effectPortion = (16 - s) / 15.0;
          greyAdd             = (int)(v / 4.0 * effectPortion * 1.2);
          targetColorAlpha = v - greyAdd;
        } else {
          targetColorAlpha = v;//(int)(fv*255);
          greyAdd              = 0;
        }
      } else {
        if(shadows) {
          targetColorAlpha = 0;
          greyAdd              = v;
        } else {
          targetColorAlpha = v;//(int)(fv*255);
          greyAdd              = 0;
        }
      }

      greyAdd += brightAdj;

      if(reallySolid)
      { cout << targetColorAlpha << "," << greyAdd << ","; }
      else
      { cout << targetColorAlpha << "," << greyAdd << "," << qAlpha(basePix) << ","; }
      //cout<<qRed(basePix)<<","<<qGreen(basePix)<<","<<qBlue(basePix)<<","<<qAlpha(basePix)<<",";

      if(pos % 8 == 7)
      { cout << "\n"; }

      read++;
    }

    cerr << s.latin1() << ":" << pixSolid << "/" << pixCount << "(" << reallySolid << ")\n";

    cout << !reallySolid << "\n";

    cout << "};\n\n";
  }

  cout << "static const MountainEmbedImage  image_db[] = {\n";

  for(unsigned int c = 0; c < images.size(); c++) {
    cout << "\t{ " << (images[c].haveAlpha ? "true" : "false") << "," << images[c].width << ", " << images[c].height
        << ", " << images[c].id << ", " << (char *)images[c].data << "}," << "\n";
  }
  cout << "\t{0, 0, 0, 0, 0}\n";
  cout << "};\n\n";

  cout << "class MountainImageDb\n";
  cout << "{\n";
  cout << "public:\n";
  cout << "\tstatic MountainImageDb* getInstance()\n";
  cout << "\t{\n";
  cout << "\t\tif (!instance) instance = new MountainImageDb;\n";
  cout << "\t\treturn instance;\n";
  cout << "\t}\n\n";
  cout << "\tstatic void release()\n";
  cout << "\t{\n";
  cout << "\t\tdelete instance;\n";
  cout << "\t\tinstance=0;\n";
  cout << "\t}\n\n";
  cout << "\tMountainEmbedImage* getImage(int id)\n";
  cout << "\t{\n";
  cout << "\t\treturn images[id];\n";
  cout << "\t}\n\n";
  cout << "private:\n";
  cout << "\tMountainImageDb():images(503)\n";
  cout << "\t{\n";
  cout << "\t\tfor (int c=0; image_db[c].width; c++)\n";
  cout << "\t\t\timages.insert(image_db[c].id, &image_db[c]);\n";
  cout << "\t}\n";
  cout << "\tstatic MountainImageDb* instance;\n";
  cout << "\tQIntDict<MountainEmbedImage> images;\n";
  cout << "};\n\n";
  cout << "MountainImageDb* MountainImageDb::instance = 0;\n\n";

  cout << "MountainEmbedImage* MountainGetDbImage(int id)\n";
  cout << "{\n";
  cout << "\treturn MountainImageDb::getInstance()->getImage(id);\n";
  cout << "}\n\n";

  cout << "void MountainDbCleanup()\n";
  cout << "{\n";
  cout << "\t\tMountainImageDb::release();\n";
  cout << "}\n";

  QFile file("mountainrc.h");
  file.open(IO_WriteOnly);
  QTextStream ts(&file);
  ts << "#ifndef __mountain_rc_h__\n";
  ts << "#define __mountain_rc_h__\n";

  ts << "enum MountainWidget {\n";
  for(QMap<QString, int>::iterator i = assignID.begin(); i != assignID.end(); ++i) {
    QString name = "mountain_" + i.key();
    name.replace("-", "_");
    ts << "\t" << name << " = " << i.data() << ",\n";
  }
  ts << "\tmountain_last\n";
  ts << "};\n";

  ts << "#endif /* __mountain_rc_h__ */\n";

  return 0;
}
