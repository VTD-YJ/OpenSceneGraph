/**********************************************************************
 *
 *    FILE:            TextureRectangle.cpp
 *
 *    DESCRIPTION:    Read/Write osg::TextureRectangle in binary format to disk.
 *
 *    CREATED BY:        Auto generated by iveGenerated
 *                    and later modified by Rune Schmidt Jensen.
 *
 *    HISTORY:        Created 20.3.2003
 *
 *    Copyright 2003 VR-C
 **********************************************************************/

#include "Exception.h"
#include "TextureRectangle.h"
#include "Texture.h"
#include "Image.h"

using namespace ive;

void TextureRectangle::write(DataOutputStream* out){
    // Write TextureRectangle's identification.
    out->writeInt(IVETEXTURERECTANGLE);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Texture*  tex = dynamic_cast<osg::Texture*>(this);
    if(tex){
        ((ive::Texture*)(tex))->write(out);
    }
    else
        throw Exception("TextureRectangle::write(): Could not cast this osg::TextureRectangle to an osg::Texture.");
    // Write TextureRectangle's properties.
    // Write image.

    // Should we include images date in stream
    IncludeImageMode includeImg = out->getIncludeImageMode();
    out->writeChar(includeImg);

    out->writeImage(includeImg,getImage());
}

void TextureRectangle::read(DataInputStream* in){
    // Read TextureRectangle's identification.
    int id = in->peekInt();
    if(id == IVETEXTURERECTANGLE){
        // Code to read TextureRectangle's properties.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Texture*  tex = dynamic_cast<osg::Texture*>(this);
        if(tex){
            ((ive::Texture*)(tex))->read(in);
        }
        else
            throw Exception("TextureRectangle::read(): Could not cast this osg::TextureRectangle to an osg::Texture.");
        // Read image.
        
        // Should we read image data from stream
        IncludeImageMode includeImg = (IncludeImageMode)in->readChar();

        osg::Image *image = in->readImage(includeImg);
        if(image) {
            setImage(image);
        }
    }
    else{
        throw Exception("TextureRectangle::read(): Expected TextureRectangle identification.");
    }
}
