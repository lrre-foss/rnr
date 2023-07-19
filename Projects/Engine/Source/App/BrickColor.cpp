#include <App/BrickColor.hpp>
#include <OGRE/RTShaderSystem/OgreShaderGenerator.h>

namespace RNR
{
    static BrickColor brickcolors[] = {
        // Placeholder color, should be replaced with Medium stone grey
        { -1, std::string("Placeholder"), Ogre::Vector3(255.0/255.0,0.0/255.0,255.0/255.0) },

        // Classic colors
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
        { 37, std::string("Bright green"), Ogre::Vector3(75.0/255.0, 151.0/255.0, 75.0/255.0) },
        { 38, std::string("Dark orange"), Ogre::Vector3(160.0/255.0, 95.0/255.0, 53.0/255.0) },
        { 45, std::string("Light blue"), Ogre::Vector3(180.0/255.0, 210.0/255.0, 228.0/255.0) },
        { 101, std::string("Medium red"), Ogre::Vector3(218.0/255.0, 134.0/255.0, 122.0/255.0) },
        { 102, std::string("Medium blue"), Ogre::Vector3(110.0/255.0, 153.0/255.0, 202.0/255.0) },
        { 104, std::string("Bright violet"), Ogre::Vector3(107.0/255.0, 50.0/255.0, 124.0/255.0) },
        { 105, std::string("Br. yellowish orange"), Ogre::Vector3(226.0/255.0, 155.0/255.0, 64.0/255.0) },
        { 106, std::string("Bright orange"), Ogre::Vector3(218.0/255.0, 133.0/255.0, 65.0/255.0) },
        { 107, std::string("Bright bluish green"), Ogre::Vector3(0.0/255.0, 143.0/255.0, 156.0/255.0) },
        { 119, std::string("Br. yellowish green"), Ogre::Vector3(164.0/255.0, 189.0/255.0, 71.0/255.0) },
        { 125, std::string("Light orange"), Ogre::Vector3(234.0/255.0, 184.0/255.0, 146.0/255.0) },
        { 135, std::string("Sand blue"), Ogre::Vector3(116.0/255.0, 134.0/255.0, 157.0/255.0) },
        { 141, std::string("Earth green"), Ogre::Vector3(39.0/255.0, 70.0/255.0, 45.0/255.0) },
        { 151, std::string("Sand green"), Ogre::Vector3(120.0/255.0, 144.0/255.0, 130.0/255.0) },
        { 153, std::string("Sand red"), Ogre::Vector3(149.0/255.0, 121.0/255.0, 119.0/255.0) },
        { 192, std::string("Reddish brown"), Ogre::Vector3(105.0/255.0, 64.0/255.0, 40.0/255.0) },
        { 194, std::string("Medium stone grey"), Ogre::Vector3(163.0/255.0, 162.0/255.0, 165.0/255.0) },
        { 199, std::string("Dark stone grey"), Ogre::Vector3(99.0/255.0, 95.0/255.0, 98.0/255.0) },
        { 208, std::string("Light stone grey"), Ogre::Vector3(229.0/255.0, 228.0/255.0, 223.0/255.0) },
        { 217, std::string("Brown"), Ogre::Vector3(124.0/255.0, 92.0/255.0, 70.0/255.0) },
        { 226, std::string("Cool yellow"), Ogre::Vector3(253.0/255.0, 234.0/255.0, 141.0/255.0) },

        // From here, these are newer colors
        { 1001, std::string("Institutional white"), Ogre::Vector3(248.0/255.0, 248.0/255.0, 248.0/255.0) },
        { 1002, std::string("Mid gray"), Ogre::Vector3(205.0/255.0, 205.0/255.0, 205.0/255.0) },
        { 1003, std::string("Really black"), Ogre::Vector3(17.0/255.0, 17.0/255.0, 17.0/255.0) },
        { 1004, std::string("Really red"), Ogre::Vector3(255.0/255.0, 0.0/255.0, 0.0/255.0) },
        { 1005, std::string("Deep orange"), Ogre::Vector3(255.0/255.0, 176.0/255.0, 0.0/255.0) },
        { 1006, std::string("Alder"), Ogre::Vector3(180.0/255.0, 128.0/255.0, 255.0/255.0) },
        { 1007, std::string("Dusty Rose"), Ogre::Vector3(163.0/255.0, 75.0/255.0, 75.0/255.0) },
        { 1008, std::string("Olive"), Ogre::Vector3(193.0/255.0, 190.0/255.0, 66.0/255.0) },
        { 1009, std::string("New Yeller"), Ogre::Vector3(255.0/255.0, 255.0/255.0, 0.0/255.0) },
        { 1010, std::string("Really blue"), Ogre::Vector3(0/255.0, 0/255.0, 255.0/255.0) },
        { 1011, std::string("Navy blue"), Ogre::Vector3(0.0/255.0, 32.0/255.0, 96.0/255.0) },
        { 1012, std::string("Deep blue"), Ogre::Vector3(33.0/255.0, 84.0/255.0, 185.0/255.0) },
        { 1013, std::string("Cyan"), Ogre::Vector3(4.0/255.0, 175.0/255.0, 236.0/255.0) },
        { 1014, std::string("CGA brown"), Ogre::Vector3(170.0/255.0, 85.0/255.0, 0.0/255.0) },
        { 1015, std::string("Magenta"), Ogre::Vector3(170.0/255.0, 0.0/255.0, 170.0/255.0) },
        { 1016, std::string("Pink"), Ogre::Vector3(255.0/255.0, 102.0/255.0, 204.0/255.0) },
        { 1017, std::string("Deep orange"), Ogre::Vector3(255.0/255.0, 175.0/255.0, 0.0/255.0) },
        { 1018, std::string("Teal"), Ogre::Vector3(18.0/255.0, 238.0/255.0, 212.0/255.0) },
        { 1019, std::string("Toothpaste"), Ogre::Vector3(0.0/255.0, 255.0/255.0, 255.0/255.0) },
        { 1020, std::string("Lime green"), Ogre::Vector3(0.0/255.0, 255.0/255.0, 0.0/255.0) },
        { 1021, std::string("Camo"), Ogre::Vector3(58.0/255.0, 125.0/255.0, 21.0/255.0) },
        { 1022, std::string("Grime"), Ogre::Vector3(127.0/255.0, 142.0/255.0, 100.0/255.0) },
        { 1023, std::string("Lavender"), Ogre::Vector3(140.0/255.0, 91.0/255.0, 159.0/255.0) },
        { 1024, std::string("Pastel light blue"), Ogre::Vector3(175.0/255.0, 221.0/255.0, 255.0/255.0) },
        { 1025, std::string("Pastel orange"), Ogre::Vector3(255.0/255.0, 201.0/255.0, 201.0/255.0) },
        { 1026, std::string("Pastel violet"), Ogre::Vector3(177.0/255.0, 167.0/255.0, 255.0/255.0) },
        { 1027, std::string("Pastel blue-green"), Ogre::Vector3(159.0/255.0, 243.0/255.0, 233.0/255.0) },
        { 1028, std::string("Pastel green"), Ogre::Vector3(204.0/255.0, 255.0/255.0, 204.0/255.0) },
        { 1029, std::string("Pastel yellow"), Ogre::Vector3(255.0/255.0, 255.0/255.0, 204.0/255.0) },
        { 1030, std::string("Pastel brown"), Ogre::Vector3(255.0/255.0, 204.0/255.0, 153.0/255.0) },
        { 1031, std::string("Color"), Ogre::Vector3(98.0/255.0, 37.0/255.0, 209.0/255.0) },
        { 1032, std::string("Hot pink"), Ogre::Vector3(255.0/255.0, 0/255.0, 191.0/255.0) }
    };

    static bool bc_prep = false;

    BrickColor::BrickColor(int color_id, std::string color_name, Ogre::Vector3 color)
    {
        this->color_id = color_id;
        this->color_name = color_name;
        this->color_val = color;
    }

    void BrickColor::buildMaterial()
    {
        if(!bc_prep)
        {
            Ogre::RTShader::ShaderGenerator::getSingletonPtr()->createScheme("rtshader");

            bc_prep = true;
        }
        Ogre::MaterialPtr part_material = Ogre::MaterialManager::getSingletonPtr()->getByName("materials/partinstanced");
        color_material = part_material->clone(Ogre::String("tmp_part/") + Ogre::StringConverter::toString(color_id));
        Ogre::RTShader::ShaderGenerator::getSingletonPtr()->cloneShaderBasedTechniques(*part_material, *color_material);
        Ogre::Technique* mat_tech = color_material->getTechnique(0);
        mat_tech->setLightingEnabled(true);
        mat_tech->setShadingMode(Ogre::ShadeOptions::SO_PHONG);
        Ogre::Pass* mat_pass = mat_tech->getPass(0);
        Ogre::TextureUnitState* part_texunit = mat_pass->getTextureUnitState(0);
        part_texunit->setColourOperationEx(Ogre::LayerBlendOperationEx::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, Ogre::ColourValue(color_val.x, color_val.y, color_val.z));

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
                    brickcolors[i].buildMaterial();
                return brickcolors[i].color_material;
            }
        }
        if(!brickcolors[0].color_material)
            brickcolors[0].buildMaterial();
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

    std::string BrickColor::name(int brickcolor)
    {
        for(int i = 0; i < sizeof(brickcolors) / sizeof(BrickColor); i++)
        {
            if(brickcolors[i].color_id == brickcolor)
            {
                return brickcolors[i].color_name;
            }
        }
        return brickcolors[0].color_name;
    }
}