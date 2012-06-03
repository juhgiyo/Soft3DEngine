///////////////////////////////////////////////////////////
//                                                       //
//             WgTCachedArrayDestructor.inl              //
//                                                       //
//  - Inlines for Generic Cached Array Destructor class  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgRenderer.h"

namespace WGSoft3D
{

// This function is separated from the other template functions to avoid a
// circular header dependency (destructor uses the Renderer class).  The
// other functions are inlined, but this file is included in the specific
// typedef'd CachedArray classes.
template <class T>
TCachedArray<T>::~TCachedArray ()
{
    // Inform all renderers using this array that it is being destroyed.
    // This allows the renderer to free up any associated resources.
    const TArray<BindInfo>& rkArray = BIArray.GetArray();
    for (int i = 0; i < rkArray.GetQuantity(); i++)
        rkArray[i].User->ReleaseArray(this);
}

}




