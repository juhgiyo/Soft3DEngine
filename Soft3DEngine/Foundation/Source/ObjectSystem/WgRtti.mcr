///////////////////////////////////////////////////////////
//                                                       //
//                    WgRtti.h                           //
//                                                       //
//  - Interface for Real Time Type Information class     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
#define WG3D_DECLARE_RTTI \
public: \
    static const Rtti TYPE; \
    virtual const Rtti& GetType () const { return TYPE; }
//----------------------------------------------------------------------------
#define WG3D_DECLARE_TEMPLATE_RTTI \
public: \
    WG3D_FOUNDATION_ITEM static const Rtti TYPE; \
    virtual const Rtti& GetType () const { return TYPE; }
//----------------------------------------------------------------------------
#define WG3D_IMPLEMENT_RTTI(nsname,classname,baseclassname) \
    const Rtti classname::TYPE(#nsname"."#classname,&baseclassname::TYPE)
//----------------------------------------------------------------------------
#define WG3D_IMPLEMENT_TEMPLATE_RTTI(nsname,classname,baseclassname) \
    template <> \
    const Rtti classname::TYPE(#nsname"."#classname,&baseclassname::TYPE)
//----------------------------------------------------------------------------

