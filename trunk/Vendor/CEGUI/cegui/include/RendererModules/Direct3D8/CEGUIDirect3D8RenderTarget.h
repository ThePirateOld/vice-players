/***********************************************************************
    filename:   CEGUIDirect3D8RenderTarget.h
    created:    Thu Aug 19 2010
    author:     Justin "ReGeX" Snyder
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2009 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#ifndef _CEGUIDirect3D8RenderTarget_h_
#define _CEGUIDirect3D8RenderTarget_h_

#include "CEGUIDirect3D8Renderer.h"
#include "../../CEGUIRenderTarget.h"
#include "../../CEGUIRect.h"
#include <d3dx8.h>

#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable : 4251)
#endif

// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
    Intermediate Direct3D8 implementation of a RenderTarget.
*/
class Direct3D8_GUIRENDERER_API Direct3D8RenderTarget : public virtual RenderTarget
{
public:
    //! Constructor
    Direct3D8RenderTarget(Direct3D8Renderer& owner);

    // implement parts of RenderTarget interface
    void draw(const GeometryBuffer& buffer);
    void draw(const RenderQueue& queue);
    void setArea(const Rect& area);
    const Rect& getArea() const;
    void activate();
    void deactivate();
    void unprojectPoint(const GeometryBuffer& buff,
                        const Vector2& p_in, Vector2& p_out) const;

protected:
    //! helper that initialises the cached matrix
    void updateMatrix() const;
    //! helper to initialise the D3DVIEWPORT8 \a vp for this target.
    void setupViewport(D3DVIEWPORT8& vp) const;

    //! Direct3D8Renderer that created this object
    Direct3D8Renderer& d_owner;
    //! Direct3DDevice9 interface obtained from our owner.
    LPDIRECT3DDEVICE8 d_device;
    //! holds defined area for the RenderTarget
    Rect d_area;
    //! projection / view matrix cache
    mutable D3DXMATRIX d_matrix;
    //! true when d_matrix is valid and up to date
    mutable bool d_matrixValid;
    //! tracks viewing distance (this is set up at the same time as d_matrix)
    mutable float d_viewDistance;
};

} // End of  CEGUI namespace section

#if defined(_MSC_VER)
#   pragma warning(pop)
#endif

#endif  // end of guard _CEGUIDirect3D8RenderTarget_h_