{\rtf1\ansi\ansicpg936\cocoartf1504\cocoasubrtf820
{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;}
{\colortbl;\red255\green255\blue255;\red100\green56\blue32;\red196\green26\blue22;\red170\green13\blue145;
\red0\green0\blue0;\red92\green38\blue153;\red28\green0\blue207;\red46\green13\blue110;\red0\green116\blue0;
\red38\green71\blue75;}
{\*\expandedcolortbl;;\csgenericrgb\c39100\c22000\c12500;\csgenericrgb\c77000\c10200\c8600;\csgenericrgb\c66500\c5200\c56900;
\csgenericrgb\c0\c0\c0;\csgenericrgb\c35900\c14900\c60100;\csgenericrgb\c11000\c0\c81000;\csgenericrgb\c18100\c5200\c43100;\csgenericrgb\c0\c45600\c0;
\csgenericrgb\c14900\c27800\c29400;}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab543
\pard\tx543\pardeftab543\pardirnatural\partightenfactor0

\f0\fs22 \cf2 \CocoaLigature0 #include \cf3 <iostream>\cf2 \
#include \cf3 <opencv2/opencv.hpp>\cf2 \
#include \cf3 <math.h>\cf2 \
\cf4 using\cf5  \cf4 namespace\cf5  \cf6 std\cf5 ;\
\cf4 using\cf5  \cf4 namespace\cf5  \cf6 cv\cf5 ;\
\
\
\cf4 void\cf5  Gaussian(\cf4 const\cf5  \cf6 Mat\cf5  &input, \cf6 Mat\cf5  &output, \cf4 int\cf5  sigma)\{\
    \cf4 int\cf5  size=\cf7 0\cf5 ;\
    \cf4 double\cf5  **gaus=(\cf4 double\cf5  **) \cf8 malloc\cf5 (\cf4 sizeof\cf5 (\cf4 double\cf5 ) * size);\
    \cf4 int\cf5  center=size/\cf7 2\cf5 ;\
    \cf4 double\cf5  sum=\cf7 0\cf5 ;\
    \cf4 const\cf5  \cf4 int\cf5  PI=\cf7 3.14\cf5 ;\
    \cf4 for\cf5 (\cf4 int\cf5  i=\cf7 0\cf5 ;i<size;i++)\{\
        \cf4 for\cf5 (\cf4 int\cf5  j=\cf7 0\cf5 ;j<size;j++)\{\
            gaus[i][j]=(\cf7 1\cf5 /\cf7 2\cf5 *PI*sigma*sigma)*\cf8 exp\cf5 (-((i-center)*(i-center)+(j-center)*(j-center))/(\cf7 2\cf5 *sigma*sigma));\
            sum+=gaus[i][j];\
        \}\
    \}\
    \cf4 for\cf5 (\cf4 int\cf5  i=\cf7 0\cf5 ;i<size;i++)\{\
        \cf4 for\cf5 (\cf4 int\cf5  j=\cf7 0\cf5 ;j<size;j++)\{\
            gaus[i][j]/=sum;\
            \cf6 cout\cf5 <<gaus[i][j]<<\cf8 endl\cf5 ;\
        \}\
    \}\
\
    \cf4 for\cf5 (\cf4 int\cf5  i=\cf7 0\cf5 ;i<output.\cf6 rows\cf5 ;i++)\{\
        \cf4 for\cf5 (\cf4 int\cf5  j=center;j<output.\cf6 cols\cf5 -center;j++)\{\
            output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 0\cf5 ]=\cf7 0\cf5 ;\
            output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 1\cf5 ]=\cf7 0\cf5 ;\
            output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 2\cf5 ]=\cf7 0\cf5 ;\
            \cf4 for\cf5 (\cf4 int\cf5  k=\cf7 0\cf5 ;k<size;k++)\{\
                output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 0\cf5 ]=input.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j+k)[\cf7 0\cf5 ]*(*gaus[center+k]);\
                output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 1\cf5 ]=input.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j+k)[\cf7 1\cf5 ]*(*gaus[center+k]);\
                output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 2\cf5 ]=input.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j+k)[\cf7 2\cf5 ]*(*gaus[center+k]);\
            \}\
        \}\
    \}\
    \cf4 for\cf5 (\cf4 int\cf5  i=\cf7 0\cf5 ;i<output.\cf6 cols\cf5 ;i++)\{\
        \cf4 for\cf5 (\cf4 int\cf5  j=center;j<output.\cf6 rows\cf5 -center;j++)\{\
            output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 0\cf5 ]=\cf7 0\cf5 ;\
            output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 1\cf5 ]=\cf7 0\cf5 ;\
            output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 2\cf5 ]=\cf7 0\cf5 ;\
            \cf4 for\cf5 (\cf4 int\cf5  k=\cf7 0\cf5 ;k<size;k++)\{\
                output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 0\cf5 ]=input.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i+k,j)[\cf7 0\cf5 ]*(*gaus[center+k]);\
                output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 1\cf5 ]=input.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i+k,j)[\cf7 1\cf5 ]*(*gaus[center+k]);\
                output.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i,j)[\cf7 2\cf5 ]=input.\cf8 at\cf5 <\cf6 Vec3b\cf5 >(i+k,j)[\cf7 2\cf5 ]*(*gaus[center+k]);\
            \}\
        \}\
    \}\
    \cf8 free\cf5 (gaus);\
    \cf9 //imshow("output", output);\cf5 \
\}\
\
\cf4 int\cf5  main(\cf4 int\cf5  argc, \cf4 char\cf5  **argv)\
\{\
    \cf6 Mat\cf5  input = \cf8 imread\cf5 (\cf3 "/Users/apple/Desktop/a.png"\cf5 );\
    \cf6 Mat\cf5  output;\
    \cf8 imshow\cf5 (\cf3 "input"\cf5 , input);\
    \cf10 Gaussian\cf5 (input, output, \cf7 1\cf5 );\
    \cf8 imshow\cf5 (\cf3 "output"\cf5 , output);\
    \cf8 waitKey\cf5 ();\
    \cf4 return\cf5  \cf7 0\cf5 ;\
\}}