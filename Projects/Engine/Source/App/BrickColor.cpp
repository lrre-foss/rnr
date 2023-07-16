#include <App/BrickColor.hpp>
#include <OGRE/RTShaderSystem/OgreShaderGenerator.h>

namespace RNR
{
    static BrickColor brickcolors[] = {
        { -1, std::string("Placeholder"), Ogre::Vector3(255.0/255.0,0.0/255.0,255.0/255.0) },

        { 1, std::string("White"), Ogre::Vector3(242.0/255.0,243.0/255.0,243.0/255.0) },
        { 2, std::string("Grey"), Ogre::Vector3(161.0/255.0,165.0/255.0,162.0/255.0) },
        { 3, std::string("Light yellow"), Ogre::Vector3(249.0/255.0,233.0/255.0,153.0/255.0) },

        { 5, std::string("Brick yellow"), Ogre::Vector3(215.0/255.0,197.0/255.0,154.0/255.0) },
        { 6, std::string("Light green"), Ogre::Vector3(194.0/255.0,218.0/255.0,184.0/255.0) },

        { 9, std::string("Light reddish violet"), Ogre::Vector3(232.0/255.0,186.0/255.0,200.0/255.0) },

        { 11, std::string("Pastel Blue"), Ogre::Vector3(128.0/255.0,187.0/255.0,219.0/255.0) },
        { 12, std::string("Light orange brown"), Ogre::Vector3(203.0/255.0,132.0/255.0,66.0/255.0) },

        { 18, std::string("Nougat"), Ogre::Vector3(204.0/255.0,142.0/255.0,105.0/255.0) },

        { 21, std::string("Bright red"), Ogre::Vector3(196.0/255.0,40.0/255.0,28.0/255.0) },
        { 22, std::string("Med. reddish violet"), Ogre::Vector3(196.0/255.0,112.0/255.0,160.0/255.0) },
        { 23, std::string("Bright blue"), Ogre::Vector3(13.0/255.0,105.0/255.0,172.0/255.0) },
        { 24, std::string("Bright yellow"), Ogre::Vector3(245.0/255.0,205.0/255.0,48.0/255.0) },
        { 25, std::string("Earth orange"), Ogre::Vector3(98.0/255.0,71.0/255.0,50.0/255.0) },
        { 26, std::string("Black"), Ogre::Vector3(27.0/255.0,42.0/255.0,52.0/255.0) },
        { 27, std::string("Dark grey"), Ogre::Vector3(109.0/255.0,110.0/255.0,108.0/255.0) },
        { 28, std::string("Dark green"), Ogre::Vector3(40.0/255.0,127.0/255.0,71.0/255.0) },
        { 29, std::string("Medium green"), Ogre::Vector3(161.0/255.0,196.0/255.0,140.0/255.0) },
    };

    BrickColor::BrickColor(int color_id, std::string color_name, Ogre::Vector3 color)
    {
        this->color_id = color_id;
        this->color_name = color_name;
        this->color_val = color;
    }

    Ogre::Vector3 BrickColor::color(int brickcolor)
    {
        for(int i = 0; i < sizeof(brickcolors) / sizeof(BrickColor); i++)
        {
            if(brickcolors[i].color_id == brickcolor)
            {
                return brickcolors[i].color_val;
            }
        }
        return brickcolors[0].color_val;
    }

    Ogre::MaterialPtr BrickColor::material(int brickcolor)
    {
        for(int i = 0; i < sizeof(brickcolors) / sizeof(BrickColor); i++)
        {
            if(brickcolors[i].color_id == brickcolor)
            {
                if(!brickcolors[i].color_material)
                {
                    brickcolors[i].color_material = Ogre::MaterialManager::getSingletonPtr()->getByName("materials/partinstanced");
                    brickcolors[i].color_material = brickcolors[i].color_material->clone(Ogre::String("tmp_part/") + Ogre::StringConverter::toString(brickcolor));
                    Ogre::Technique* mat_tech = brickcolors[i].color_material->getTechnique(0);
                    Ogre::Pass* mat_pass = mat_tech->getPass(0);
                    Ogre::TextureUnitState* part_texunit = mat_pass->getTextureUnitState(0);
                    part_texunit->setColourOperationEx(Ogre::LayerBlendOperationEx::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, Ogre::ColourValue(brickcolors[i].color_val.x, brickcolors[i].color_val.y, brickcolors[i].color_val.z));
                }
                return brickcolors[i].color_material;
            }
        }
        if(!brickcolors[0].color_material)
        {
            brickcolors[0].color_material = Ogre::MaterialManager::getSingletonPtr()->getByName("materials/partinstanced");
            brickcolors[0].color_material = brickcolors[0].color_material->clone(Ogre::String("tmp_part/") + Ogre::StringConverter::toString(brickcolor));
            Ogre::Technique* mat_tech = brickcolors[0].color_material->getTechnique(0);
            Ogre::Pass* mat_pass = mat_tech->getPass(0);
            Ogre::TextureUnitState* part_texunit = mat_pass->getTextureUnitState(0);
            part_texunit->setColourOperationEx(Ogre::LayerBlendOperationEx::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, Ogre::ColourValue(brickcolors[0].color_val.x, brickcolors[0].color_val.y, brickcolors[0].color_val.z));
        }
        return brickcolors[0].color_material;
    }

    bool BrickColor::valid(int brickcolor)
    {
        for(int i = 0; i < sizeof(brickcolors) / sizeof(BrickColor); i++)
        {
            if(brickcolors[i].color_id == brickcolor)
            {
                return true;
            }
        }
        return false;
    }
}