{\rtf1\ansi\ansicpg936\cocoartf1504\cocoasubrtf820
{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;}
{\colortbl;\red255\green255\blue255;\red100\green56\blue32;\red196\green26\blue22;\red0\green0\blue0;
\red92\green38\blue153;\red28\green0\blue207;\red46\green13\blue110;\red170\green13\blue145;\red38\green71\blue75;
\red0\green116\blue0;}
{\*\expandedcolortbl;;\csgenericrgb\c39100\c22000\c12500;\csgenericrgb\c77000\c10200\c8600;\csgenericrgb\c0\c0\c0;
\csgenericrgb\c35900\c14900\c60100;\csgenericrgb\c11000\c0\c81000;\csgenericrgb\c18100\c5200\c43100;\csgenericrgb\c66500\c5200\c56900;\csgenericrgb\c14900\c27800\c29400;
\csgenericrgb\c0\c45600\c0;}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab543
\pard\tx543\pardeftab543\pardirnatural\partightenfactor0

\f0\fs22 \cf2 \CocoaLigature0 #include \cf3 <iostream>\cf2 \
#include \cf3 <string>\cf2 \
#include \cf3 <list>\cf2 \
#include \cf3 <vector>\cf2 \
#include \cf3 <map>\cf2 \
#include \cf3 <stack>\cf2 \
\cf4 \
\cf2 #include \cf3 <opencv2/imgproc/imgproc.hpp>\cf2 \
#include \cf3 <opencv2/highgui/highgui.hpp>\cf2 \
\cf5 cv\cf4 ::\cf5 Scalar\cf4  GetRandomColor()\
\{\
    \cf5 uchar\cf4  r = \cf6 255\cf4  * (\cf7 rand\cf4 ()/(\cf6 1.0\cf4  + \cf2 RAND_MAX\cf4 ));\
    \cf5 uchar\cf4  g = \cf6 255\cf4  * (\cf7 rand\cf4 ()/(\cf6 1.0\cf4  + \cf2 RAND_MAX\cf4 ));\
    \cf5 uchar\cf4  b = \cf6 255\cf4  * (\cf7 rand\cf4 ()/(\cf6 1.0\cf4  + \cf2 RAND_MAX\cf4 ));\
    \cf8 return\cf4  \cf5 cv\cf4 ::\cf5 Scalar\cf4 (b,g,r) ;\
\}\
\
\
\cf8 void\cf4  LabelColor(\cf8 const\cf4  \cf5 cv\cf4 ::\cf5 Mat\cf4 & _labelImg, \cf5 cv\cf4 ::\cf5 Mat\cf4 & _colorLabelImg)\
\{\
    \cf8 if\cf4  (_labelImg.\cf7 empty\cf4 () ||\
        _labelImg.\cf7 type\cf4 () != \cf2 CV_32SC1\cf4 )\
    \{\
        \cf8 return\cf4  ;\
    \}\
    \
    \cf5 std\cf4 ::\cf5 map\cf4 <\cf8 int\cf4 , \cf5 cv\cf4 ::\cf5 Scalar\cf4 > colors ;\
    \
    \cf8 int\cf4  rows = _labelImg.\cf5 rows\cf4  ;\
    \cf8 int\cf4  cols = _labelImg.\cf5 cols\cf4  ;\
    \
    _colorLabelImg.\cf7 release\cf4 () ;\
    _colorLabelImg.\cf7 create\cf4 (rows, cols, \cf2 CV_8UC3\cf4 ) ;\
    _colorLabelImg = \cf5 cv\cf4 ::\cf5 Scalar\cf4 ::\cf7 all\cf4 (\cf6 0\cf4 ) ;\
    \
    \cf8 for\cf4  (\cf8 int\cf4  i = \cf6 0\cf4 ; i < rows; i++)\
    \{\
        \cf8 const\cf4  \cf8 int\cf4 * data_src = (\cf8 int\cf4 *)_labelImg.\cf7 ptr\cf4 <\cf8 int\cf4 >(i) ;\
        \cf5 uchar\cf4 * data_dst = _colorLabelImg.\cf7 ptr\cf4 <\cf5 uchar\cf4 >(i) ;\
        \cf8 for\cf4  (\cf8 int\cf4  j = \cf6 0\cf4 ; j < cols; j++)\
        \{\
            \cf8 int\cf4  pixelValue = data_src[j] ;\
            \cf8 if\cf4  (pixelValue > \cf6 1\cf4 )\
            \{\
                \cf8 if\cf4  (colors.\cf7 count\cf4 (pixelValue) <= \cf6 0\cf4 )\
                \{\
                    colors[\cf7 pixelValue\cf4 ] = \cf9 icvprGetRandomColor\cf4 () ;\
                \}\
                \cf5 cv\cf4 ::\cf5 Scalar\cf4  color = colors[\cf7 pixelValue\cf4 ] ;\
                *data_dst++   = color[\cf6 0\cf4 ] ;\
                *data_dst++ = color[\cf6 1\cf4 ] ;\
                *data_dst++ = color[\cf6 2\cf4 ] ;\
            \}\
            \cf8 else\cf4 \
            \{\
                data_dst++ ;\
                data_dst++ ;\
                data_dst++ ;\
            \}\
        \}\
    \}\
\}\
\
\cf8 void\cf4  CcaBySeedFill(\cf8 const\cf4  \cf5 cv\cf4 ::\cf5 Mat\cf4 & _binImg, \cf5 cv\cf4 ::\cf5 Mat\cf4 & _lableImg)\
\{\
    \cf8 if\cf4  (_binImg.\cf7 empty\cf4 () ||\
        _binImg.\cf7 type\cf4 () != \cf2 CV_8UC1\cf4 )\
    \{\
        \cf8 return\cf4  ;\
    \}\
    \
    _lableImg.\cf7 release\cf4 () ;\
    _binImg.\cf7 convertTo\cf4 (_lableImg, \cf2 CV_32SC1\cf4 ) ;\
    \
    \cf8 int\cf4  label = \cf6 1\cf4  ;  \cf10 // start by 2\cf4 \
    \
    \cf8 int\cf4  rows = _binImg.\cf5 rows\cf4  - \cf6 1\cf4  ;\
    \cf8 int\cf4  cols = _binImg.\cf5 cols\cf4  - \cf6 1\cf4  ;\
    \cf8 for\cf4  (\cf8 int\cf4  i = \cf6 1\cf4 ; i < rows-\cf6 1\cf4 ; i++)\
    \{\
        \cf8 int\cf4 * data= _lableImg.\cf7 ptr\cf4 <\cf8 int\cf4 >(i) ;\
        \cf8 for\cf4  (\cf8 int\cf4  j = \cf6 1\cf4 ; j < cols-\cf6 1\cf4 ; j++)\
        \{\
            \cf8 if\cf4  (data[j] == \cf6 1\cf4 )\
            \{\
                \cf5 std\cf4 ::\cf5 stack\cf4 <\cf5 std\cf4 ::\cf5 pair\cf4 <\cf8 int\cf4 ,\cf8 int\cf4 >> neighborPixels ;\
                neighborPixels.\cf7 push\cf4 (\cf5 std\cf4 ::\cf5 pair\cf4 <\cf8 int\cf4 ,\cf8 int\cf4 >(i,j)) ;     \cf10 // pixel position: <i,j>\cf4 \
                ++label ;  \cf10 // begin with a new label\cf4 \
                \cf8 while\cf4  (!neighborPixels.\cf7 empty\cf4 ())\
                \{\
                    \cf10 // get the top pixel on the stack and label it with the same label\cf4 \
                    \cf5 std\cf4 ::\cf5 pair\cf4 <\cf8 int\cf4 ,\cf8 int\cf4 > curPixel = neighborPixels.\cf7 top\cf4 () ;\
                    \cf8 int\cf4  curX = curPixel.\cf5 first\cf4  ;\
                    \cf8 int\cf4  curY = curPixel.\cf5 second\cf4  ;\
                    _lableImg.\cf7 at\cf4 <\cf8 int\cf4 >(curX, curY) = label ;\
                    \
                    \cf10 // pop the top pixel\cf4 \
                    neighborPixels.\cf7 pop\cf4 () ;\
                    \
                    \cf10 // push the 4-neighbors (foreground pixels)\cf4 \
                    \cf8 if\cf4  (_lableImg.\cf7 at\cf4 <\cf8 int\cf4 >(curX, curY-\cf6 1\cf4 ) == \cf6 1\cf4 )\
                    \{\cf10 // left pixel\cf4 \
                        neighborPixels.\cf7 push\cf4 (\cf5 std\cf4 ::\cf5 pair\cf4 <\cf8 int\cf4 ,\cf8 int\cf4 >(curX, curY-\cf6 1\cf4 )) ;\
                    \}\
                    \cf8 if\cf4  (_lableImg.\cf7 at\cf4 <\cf8 int\cf4 >(curX, curY+\cf6 1\cf4 ) == \cf6 1\cf4 )\
                    \{\cf10 // right pixel\cf4 \
                        neighborPixels.\cf7 push\cf4 (\cf5 std\cf4 ::\cf5 pair\cf4 <\cf8 int\cf4 ,\cf8 int\cf4 >(curX, curY+\cf6 1\cf4 )) ;\
                    \}\
                    \cf8 if\cf4  (_lableImg.\cf7 at\cf4 <\cf8 int\cf4 >(curX-\cf6 1\cf4 , curY) == \cf6 1\cf4 )\
                    \{\cf10 // up pixel\cf4 \
                        neighborPixels.\cf7 push\cf4 (\cf5 std\cf4 ::\cf5 pair\cf4 <\cf8 int\cf4 ,\cf8 int\cf4 >(curX-\cf6 1\cf4 , curY)) ;\
                    \}\
                    \cf8 if\cf4  (_lableImg.\cf7 at\cf4 <\cf8 int\cf4 >(curX+\cf6 1\cf4 , curY) == \cf6 1\cf4 )\
                    \{\cf10 // down pixel\cf4 \
                        neighborPixels.\cf7 push\cf4 (\cf5 std\cf4 ::\cf5 pair\cf4 <\cf8 int\cf4 ,\cf8 int\cf4 >(curX+\cf6 1\cf4 , curY)) ;\
                    \}\
                \}\
            \}  \
        \}  \
    \}  \
\}  \
\
\cf8 int\cf4  main(\cf8 int\cf4  argc, \cf8 char\cf4 ** argv)\
\{\
    \cf5 cv\cf4 ::\cf5 Mat\cf4  binImage = \cf5 cv\cf4 ::\cf7 imread\cf4 (\cf3 "/Users/apple/Desktop/a.png"\cf4 , \cf6 0\cf4 ) ;\
    \cf5 cv\cf4 ::\cf7 threshold\cf4 (binImage, binImage, \cf6 50\cf4 , \cf6 1\cf4 , \cf7 CV_THRESH_BINARY_INV\cf4 ) ;\
    \
    \cf10 // connected component labeling\cf4 \
    \cf5 cv\cf4 ::\cf5 Mat\cf4  labelImg ;\
    \cf9 CcaBySeedFill\cf4 (binImage, labelImg) ;\
    \
    \cf10 // show result\cf4 \
    \cf5 cv\cf4 ::\cf5 Mat\cf4  grayImg ;\
    labelImg *= \cf6 10\cf4  ;\
    labelImg.\cf7 convertTo\cf4 (grayImg, \cf2 CV_8UC1\cf4 ) ;\
    \cf5 cv\cf4 ::\cf7 imshow\cf4 (\cf3 "labelImg"\cf4 , grayImg) ;\
    \
    \cf5 cv\cf4 ::\cf5 Mat\cf4  colorLabelImg ;\
    \cf9 LabelColor\cf4 (labelImg, colorLabelImg) ;\
    \cf5 cv\cf4 ::\cf7 imshow\cf4 (\cf3 "colorImg"\cf4 , colorLabelImg) ;\
    \cf5 cv\cf4 ::\cf7 waitKey\cf4 (\cf6 0\cf4 ) ;\
    \
  \cf10   return 0 ;\cf4 \
\}}