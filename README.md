# RNR
RNR (**R**NR's **N**ot **R**oblox) is a project that aims to recreate the look and feel of classic Roblox while bringing in new features at the same time as well as remaining fully compatible with clients from that era.

Interested in contributing? [Feel free to make a pull request!](https://github.com/kiseki-lol/RNR/pulls)

# Objectives
There are several goals that RNR seeks to achieve, those being;
- Full native x64 support on Windows and Linux
- Efficient and powerful renderer built from scratch (with only OpenGL support for the time being)
- Easy-to-use (simple CLI options to launch and host games, as well as a level editor with a modern UI)
- Fully compatible with Roblox versions up to 0.3.744.0 (dated April 2008) in areas such as hosting, joining, level file serialization, etc.
- Incorporates all the various facets of the Roblox engine, with a little bit extra (e.g. a network replication whitelist, fancy shader support, etc.)
- Made with clean-room reverse engineering
- As free and open-source as is possible (with client code being licensed under the GPL and the engine itself released into the public domain, void of any copyright)
- Patches all the security vulnerabilities and bugs that legacy Roblox clients contained

# License
RNR is licensed under two separate licenses:
- The bulk of the code (which includes the player, studio, and server projects) are all licensed under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.txt) license.
- The engine that RNR runs on is licensed under the [Creative Commons Zero v1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/legalcode.txt) license.

Copies of both licenses have been bundled with RNR.