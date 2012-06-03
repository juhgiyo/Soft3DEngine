///////////////////////////////////////////////////////////
//                                                       //
//                    WgColorRGBA.h                      //
//                                                       //
//  - Interface for Color RGBA class                     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_COLOR_RGBA_H__
#define __WG_COLOR_RGBA_H__


#include "WgFoundationLIB.h"
#include "WgSystem.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM ColorRGBA
{
public:
    // Construction.  The components are intended to be in the interval [0,1].
    // For accessing of colors by array index, the map is 0 = red, 1 = green,
    // 2 = blue, and 3 = alpha.
    ColorRGBA ();  // initial values (0,0,0,0)
    ColorRGBA (fixed fR, fixed fG, fixed fB, fixed fA);
    ColorRGBA (const fixed* afTuple);
    ColorRGBA (const ColorRGBA& rkC);

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
    fixed A () const;
    fixed& A ();

    // assignment
    ColorRGBA& operator= (const ColorRGBA& rkC);

    // comparison
    bool operator== (const ColorRGBA& rkC) const;
    bool operator!= (const ColorRGBA& rkC) const;
    bool operator<  (const ColorRGBA& rkC) const;
    bool operator<= (const ColorRGBA& rkC) const;
    bool operator>  (const ColorRGBA& rkC) const;
    bool operator>= (const ColorRGBA& rkC) const;

    // arithmetic operations
    ColorRGBA operator+ (const ColorRGBA& rkC) const;
    ColorRGBA operator- (const ColorRGBA& rkC) const;
    ColorRGBA operator* (const ColorRGBA& rkC) const;
    ColorRGBA operator* (fixed fScalar) const;

    // arithmetic updates
    ColorRGBA& operator+= (const ColorRGBA& rkC);
    ColorRGBA& operator-= (const ColorRGBA& rkC);
    ColorRGBA& operator*= (const ColorRGBA& rkC);
    ColorRGBA& operator*= (fixed fScalar);

    // Transform the color channels to [0,1].  Clamp sets negative values to
    // zero and values larger than one to one.  ScaleByMax assumes the color
    // channels are nonnegative, finds the maximum RGB channel, and divides
    // all RGB channels by that value.  The alpha channel is clamped to [0,1].
    void Clamp ();
    void ScaleByMax ();

    static const ColorRGBA BLACK;   // = (0,0,0,1) 
    static const ColorRGBA WHITE;   // = (1,1,1,1)
    static const ColorRGBA INVALID; // = (-1,-1,-1,-1)

private:
    // support for comparisons
    int CompareArrays (const ColorRGBA& rkC) const;

    fixed m_afTuple[4];
};

WG3D_FOUNDATION_ITEM ColorRGBA operator* (fixed fScalar, const ColorRGBA& rkC);

#include "WgColorRGBA.inl"

}

#endif
