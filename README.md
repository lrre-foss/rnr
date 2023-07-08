# RNR
[![Star](https://img.shields.io/github/stars/lrre-foss/RNR?style=social)](https://github.com/lrre-foss/RNR/stargazers)

RNR (**R**NR's **N**ot **R**oblox) is a project that aims to recreate the look and feel of classic Roblox with extra features while remaining fully compatible with clients from that era.

Interested in contributing? [Feel free to make a pull request!](https://github.com/lrre-foss/RNR/pulls)

# Goals
There are several goals that RNR seeks to achieve, them being;
- Full native x64 support on Windows and Linux
- Efficient and powerful renderer built from scratch (with only OpenGL support for the time being)
- Easy-to-use (simple CLI options to launch and host games, as well as a level editor with a modern UI)
- Fully compatible with Roblox versions up to 0.3.744.0 (dated April 2008) in areas such as hosting, joining, levels, etc.
- Incorporates all the various facets of the Roblox engine, plus a little bit extra (e.g. a network replication whitelist, fancy shader support, etc.)
- Made with clean-room reverse engineering
- Uses Roblox's [Luau](https://github.com/roblox/luau) as its scripting language while remaining fully compatible with classic Roblox scripts written using Lua 5.1 at the same time
- As free and open-source as is possible (with client code being licensed under the GPL and the engine itself released into the public domain, void of any copyright)
- Patching all the security vulnerabilities and fixing bugs/inefficiencies that legacy Roblox clients had
- Quick build times

# Building
RNR uses [CMake](https://cmake.org/) as its build system and [GCC](https://gcc.gnu.org/) as its compiler. To build RNR, you must first have the following packages installed:
- [Boost](https://www.boost.org/)
- [CGLM](https://github.com/recp/cglm)
- [Qt 6](https://www.qt.io/product/qt6) (if building the player or studio projects)

For Windows:
- If you're *targeting* Windows, [MinGW-w64](https://www.mingw-w64.org/) is the preferred toolset of choice.
- If you're *building on* Windows, you may use a platform such as [MSYS2](https://www.msys2.org/), which provides an all-in-one environment for running MinGW or GCC.

Additionally, you must also acquire the content folder of the Roblox client you would like to use its resources from and place it in the root of the repository. Proprietary Roblox assets are not included with RNR.

Finally, you may run `cmake --build .` in the path of the folder you've cloned the repository to so that you may configure and then finally build RNR.

# License
RNR is licensed under two separate licenses:
- The bulk of RNR (which includes the player, studio, and server projects) are all licensed under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.txt) license.
- The RNR engine itself is licensed under the [Creative Commons Zero v1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/legalcode.txt) license.

Copies of both licenses have been bundled with RNR.