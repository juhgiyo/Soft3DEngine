///////////////////////////////////////////////////////////
//                                                       //
//                    WgColorRGB.h                       //
//                                                       //
//  - Interface for Color RGB class                      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_COLOR_RGB_H__
#define __WG_COLOR_RGB_H__

#include "WgFoundationLIB.h"
#include "WgSystem.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM ColorRGB
{
public:
    // Construction.  The components are intended to be in the interval [0,1].
    // For accessing of colors by array index, the map is 0 = red, 1 = green,
    // and 2 = blue.
    ColorRGB ();  // initial values (0,0,0)
    ColorRGB (fixed fR, fixed fG, fixed fB);
    ColorRGB (const fixed* afTuple);
    ColorRGB (const ColorRGB& rkC);

    // member access
    operator const fixed* () const;
    operator fixed* ();

    fixed operator[] (int i) const;
    fixed& operator[] (int i);
    fixed R () const;
    fixed& R ();
    fixed G () const;
    fixed& G ();
    fixed B () const;
    fixed& B ();

    // assignment
    ColorRGB& operator= (const ColorRGB& rkC);

    // comparison
    bool operator== (const ColorRGB& rkC) const;
    bool operator!= (const ColorRGB& rkC) const;
    bool operator<  (const ColorRGB& rkC) const;
    bool operator<= (const ColorRGB& rkC) const;
    bool operator>  (const ColorRGB& rkC) const;
    bool operator>= (const ColorRGB& rkC) const;

    // arithmetic operations
    ColorRGB operator+ (const ColorRGB& rkC) const;
    ColorRGB operator- (const ColorRGB& rkC) const;
    ColorRGB operator* (const ColorRGB& rkC) const;
    ColorRGB operator* (fixed fScalar) const;

    // arithmetic updates
    ColorRGB& operator+= (const ColorRGB& rkC);
    ColorRGB& operator-= (const ColorRGB& rkC);
    ColorRGB& operator*= (const ColorRGB& rkC);
    ColorRGB& operator*= (fixed fScalar);

    // Transform the color channels to [0,1].  Clamp sets negative values to
    // zero and values larger than one to one.  ScaleByMax assumes the color
    // channels are nonnegative, finds the maximum color channel, and divides
    // all channels by that value.
    void Clamp ();
    void ScaleByMax ();

    static const ColorRGB BLACK;    // = (0,0,0) 
    static const ColorRGB WHITE;    // = (1,1,1)
    static const ColorRGB INVALID;  // = (-1,-1,-1)

private:
    // support for comparisons
    int CompareArrays (const ColorRGB& rkC) const;

    fixed m_afTuple[3];
};

WG3D_FOUNDATION_ITEM ColorRGB operator* (float fScalar, const ColorRGB& rkC);

#include "WgColorRGB.inl"

}

#endif
