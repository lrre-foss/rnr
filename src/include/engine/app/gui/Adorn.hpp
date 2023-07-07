#pragma once

// TODO: add G3D

namespace RBX
{
    // 2d rendering api
    class Adorn
    {
        // weird mystery classes
        class XAlign
        {

        };

        class YAlign
        {

        };

        class Spacing
        {

        };

        virtual void prepareRenderPass() {}; // NOT IN AdornG3D
        virtual void finishRenderPass() {};  // NOT IN AdornG3D
        virtual void sparkles() {}; // NOT IN AdornG3D

        virtual void createTextureProxy(G3D::ReferenceCountedPointer<G3D::GFont> *result, std::string *filename) {};
        virtual void getViewport(G3D::Rect2d *result) {]};
        virtual int getWidth() {};
        virtual int getHeight() {};
        virtual void setTexture(int id, G3D::ReferenceCountedPointer<RBX::TextureProxyBase> texture) {};
        virtual void getTextureSize(G3D::Rect2d *result, G3D::ReferenceCountedPointer<RBX::TextureProxyBase> texture) {};
        virtual void line2d(G3D::Vector2 *p0, G3D::Vector2 *p1, G3D::Color4 *color) {};
        virtual void outlineRect2d(G3D::Rect2d *rect, float thick, G3D::Color4 *color) {};
        virtual void rect2d(G3D::Rect2d *rect, G3D::Color4 *color) {};
        virtual void get2DStringBounds(G3D::Vector2 *result, std::string *s, long double size, RBX::Adorn::Spacing spacing) {};
        virtual void drawFont2D(G3D::Vector2 *result, std::string *s, G3D::Vector2 *po2d, long double size, G3D::Color4 *color, G3D::color4 *outline, RBX::Adorn::XAlign xalign, RBX::Adorn::YAlign yalign, RBX::Adorn::Spacing spacing) {};
        virtual void setObjectToWorldMatrix(G3D::CoordinateFrame *c) {};
        virtual void setColor(G3D::Color4 *color) {};
        virtual void box(G3D::AABox *box, G3D::Color4 *solidColor, G3D::Color4 *wireColor) {};
        virtual void sphere(G3D::sphere* sphere, G3D::Color4 *solidColor, G3D::Color4 *wireColor) {};
        virtual void explosion(G3D::Sphere* sphere, G3D::Color4 *solidColor, G3D::Color4 *wireColor) {};
        virtual void cylinderAlongX(float radius, float length, G3D::Color4 *solidColor, G3D::Color4 *wireColor) {};
        virtual void ray(G3D::Ray* ray, G3D::Color4 *color, float scale) {};
        virtual void lineSegment(G3D::LineSegment *lineSegment, G3D::Color4 *color, float scale) {};
        virtual void axes(G3D::Color4 *xColor, G3D::Color4 *yColor, G3D::Color4 *zColor, float scale) {};
        virtual void quad(G3D::Vector3 *v0, G3D::Vector3 *v1, G3D::Vector3 *v2, G3D::Vector3 *v3, G3D::Color4 *color) {};
    };
}