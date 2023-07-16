#pragma once

#include <OGRE/Ogre.h>

namespace RNR
{
    class BrickColor
    {
    private:
        int color_id;
        std::string color_name;
        Ogre::Vector3 color_val;

        Ogre::MaterialPtr color_material;
    public:
        BrickColor(int color_id, std::string name, Ogre::Vector3 color);
        static Ogre::Vector3 color(int brickcolor);
        static bool valid(int brickcolor);
        static Ogre::MaterialPtr material(int brickcolor);
    };
}