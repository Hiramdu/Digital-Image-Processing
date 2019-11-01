{\rtf1\ansi\ansicpg936\cocoartf1504\cocoasubrtf820
{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;\f1\fnil\fcharset134 PingFangSC-Regular;}
{\colortbl;\red255\green255\blue255;\red100\green56\blue32;\red196\green26\blue22;\red170\green13\blue145;
\red0\green0\blue0;\red92\green38\blue153;\red46\green13\blue110;\red28\green0\blue207;\red0\green116\blue0;
}
{\*\expandedcolortbl;;\csgenericrgb\c39100\c22000\c12500;\csgenericrgb\c77000\c10200\c8600;\csgenericrgb\c66500\c5200\c56900;
\csgenericrgb\c0\c0\c0;\csgenericrgb\c35900\c14900\c60100;\csgenericrgb\c18100\c5200\c43100;\csgenericrgb\c11000\c0\c81000;\csgenericrgb\c0\c45600\c0;
}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab543
\pard\tx543\pardeftab543\pardirnatural\partightenfactor0

\f0\fs22 \cf2 \CocoaLigature0 #include \cf3 <iostream>\cf2 \
#include \cf3 <opencv2/opencv.hpp>\cf2 \
#include \cf3 <opencv2/highgui/highgui.hpp>\cf2 \
#include \cf3 <opencv/cvaux.hpp>\cf2 \
#include \cf3 <fstream>\cf2 \
\cf4 using\cf5  \cf4 namespace\cf5  \cf6 std\cf5 ;\
\
\cf4 int\cf5  main(\cf4 int\cf5  argc, \cf4 char\cf5 ** argv)\
\{\
    \cf4 int\cf5  i;\
    \cf6 IplImage\cf5 * src = \cf7 cvLoadImage\cf5 (\cf3 "/Users/apple/Desktop/a.png"\cf5 , \cf8 1\cf5  );\
    \cf6 IplImage\cf5 * imgChannel[\cf8 4\cf5 ] = \{ \cf8 0\cf5 , \cf8 0\cf5 , \cf8 0\cf5 , \cf8 0\cf5  \};\
    \cf6 IplImage\cf5 * dst = \cf7 cvCreateImage\cf5 ( \cf7 cvGetSize\cf5 ( src ), \cf2 IPL_DEPTH_8U\cf5 , \cf8 3\cf5  );\
    \
    \cf4 if\cf5 ( src )\
    \{\
        \cf4 for\cf5 ( i = \cf8 0\cf5 ; i < src -> \cf6 nChannels\cf5 ; i++ )\
        \{\
            imgChannel[i] = \cf7 cvCreateImage\cf5 ( \cf7 cvGetSize\cf5 ( src ), \cf2 IPL_DEPTH_8U\cf5 , \cf8 1\cf5  );  \cf9 //
\f1 \'d2\'aa\'c7\'f3\'b5\'a5\'cd\'a8\'b5\'c0\'cd\'bc\'cf\'f1\'b2\'c5\'c4\'dc\'d6\'b1\'b7\'bd\'cd\'bc\'be\'f9\'ba\'e2\'bb\'af
\f0 \cf5 \
        \}\
        \cf9 //
\f1 \'cd\'a8\'b5\'c0\'b7\'d6\'c0\'eb
\f0 \cf5 \
        \cf7 cvSplit\cf5 ( src, imgChannel[\cf8 0\cf5 ], imgChannel[\cf8 1\cf5 ], imgChannel[\cf8 2\cf5 ], imgChannel[\cf8 3\cf5 ] );\cf9 //BGRA\cf5 \
        \cf4 for\cf5 ( i = \cf8 0\cf5 ; i < dst -> \cf6 nChannels\cf5 ; i++ )\
        \{\
            \cf9 //
\f1 \'d6\'b1\'b7\'bd\'cd\'bc\'be\'f9\'ba\'e2\'bb\'af\'a3\'ac\'d4\'ad\'ca\'bc\'cd\'bc\'cf\'f1\'ba\'cd\'c4\'bf\'b1\'ea\'cd\'bc\'cf\'f1\'b1\'d8\'d0\'eb\'ca\'c7\'b5\'a5\'cd\'a8\'b5\'c0
\f0 \cf5 \
            \cf7 cvEqualizeHist\cf5 ( imgChannel[i], imgChannel[i] );\
        \}\
        \
        \cf9 //
\f1 \'cd\'a8\'b5\'c0\'d7\'e9\'ba\'cf
\f0 \cf5 \
        \cf7 cvMerge\cf5 ( imgChannel[\cf8 0\cf5 ], imgChannel[\cf8 1\cf5 ], imgChannel[\cf8 2\cf5 ], imgChannel[\cf8 3\cf5 ], dst );\
        \cf7 cvNamedWindow\cf5 ( \cf3 "src"\cf5 , \cf8 1\cf5  );\
        \cf7 cvShowImage\cf5 ( \cf3 "src"\cf5 , src );\
        \cf7 cvNamedWindow\cf5 ( \cf3 "Equalize"\cf5 , \cf8 1\cf5  );\
        \cf7 cvShowImage\cf5 ( \cf3 "Equalize"\cf5 , dst );\
        \
        \cf7 cvWaitKey\cf5 (\cf8 0\cf5 );\
        \cf9 //
\f1 \'ca\'cd\'b7\'c5\'d7\'ca\'d4\'b4
\f0 \cf5 \
        \cf4 for\cf5 ( i = \cf8 0\cf5 ; i < src -> \cf6 nChannels\cf5 ; i++ )\
        \{\
            \cf4 if\cf5 ( imgChannel[i] )\
            \{\
                \cf7 cvReleaseImage\cf5 ( &imgChannel[i] );\
                \cf9 //imgChannel[i] = 0;\cf5 \
            \}\
        \}\
        \cf7 cvReleaseImage\cf5 ( &dst );\
    \}\
    \
    \cf4 return\cf5  \cf8 0\cf5 ;\
\}\
}