#include <Network/NetworkReplicator.hpp>
#include <Network/NetworkServer.hpp>
#include <Network/NetworkClient.hpp>
#include <App/V8/Tree/InstanceFactory.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/DataModel.hpp>
#include <Helpers/Strings.hpp>

namespace RNR
{
    NetworkReplicator::NetworkReplicator(ArkNet::ArkPeer* peer) : Instance()
    {
        setName("NetworkReplicator");
        m_peer = peer;
        m_peer->addListener(this);
    }

    NetworkReplicator::~NetworkReplicator()
    {
        // TODO: remove listener (should be done asap actually)
    }

    void NetworkReplicator::sendInstance(Instance* instance)
    {
        DataModel* datamodel = world->getDatamodel();
        std::string guid = datamodel->getGuidByInstance(instance);

        ArkNet::Packets::GamePacket i_packet;
        ArkNet::ArkStream dataStream(i_packet.dataPacket,ArkNet::Packets::GAME_PACKET_MAX_SIZE);
 
        dataStream.write<int>(1);
        dataStream.writeString(guid);
        dataStream.writeString(instance->getClassName());

        i_packet.dataPacketLength = dataStream.size();
        m_peer->sendPacket(&i_packet);
    }

    void NetworkReplicator::onPacketReceiving(ArkNet::ArkPeer* peer, ArkNet::ArkPacket* packet)
    {
        DataModel* datamodel = world->getDatamodel();
        switch(packet->packetId())
        {
        case 0x07:
            {
                ArkNet::Packets::GamePacket* _packet = dynamic_cast<ArkNet::Packets::GamePacket*>(packet);
                ArkNet::ArkStream dataStream(_packet->dataPacket, _packet->dataPacketLength);
                int packet_type = dataStream.read<int>();
                switch(packet_type) // TODO: make this completely accurate
                {
                case 0:         // marker
                    sendInstance(world->getWorkspace()->getCurrentCamera());
                    break;
                case 1:         // new instance
                    {
                        std::string i_guid = dataStream.readString();
                        Instance* newinst;
                        std::string t_type = dataStream.readString();
                        newinst = InstanceFactory::singleton()->build(t_type);
                        if(newinst)
                        {
                            datamodel->registerInstanceByGuid(newinst, dataStream.readString());
                            printf("received %s\n", newinst->getClassName());
                        }
                    }
                case 2:         // del instance
                    {
                        Instance* delinst = datamodel->getInstanceByGuid(dataStream.readString());
                        delinst->setParent(NULL);
                    }
                case 3:         // update instance prop
                    {
                        std::string i_guid = dataStream.readString();
                        Instance* instance = datamodel->getInstanceByGuid(dataStream.readString());
                        std::string p_name = dataStream.readString();
                        ReflectionPropertyType p_type = dataStream.read<ReflectionPropertyType>();
                        std::vector<ReflectionProperty> props = instance->getProperties();
                        ReflectionProperty* prop;
                        for(auto _prop : props)
                            if(_prop.name() == p_name && _prop.type() == p_type)
                                prop = &_prop;
                        if(!prop)
                        {
                            printf("NetworkReplicator::onPacketReceiving: received bad ReflectionProperty '%s' with type '%i'\n", p_name.c_str(), p_type);
                            break;
                        }
                        switch(p_type)
                        {
                        case PROPERTY_BOOL:
                        case PROPERTY_INTEGER:
                            {
                                int v = dataStream.read<int>();
                                prop->rawSetter(&v);
                            }
                            break;
                        case PROPERTY_CFRAME:
                            {
                                CoordinateFrame cframe = dataStream.read<CoordinateFrame>();
                                prop->rawSetter(&cframe);
                            } 
                            break;
                        case PROPERTY_STD_STRING:
                            {
                                std::string string = dataStream.readString();
                                prop->rawSetter(&string);
                            }
                            break;
                        case PROPERTY_VECTOR3:
                            {
                                Ogre::Vector3 vector = dataStream.read<Ogre::Vector3>();
                                prop->rawSetter(&vector);
                            }
                            break;
                        case PROPERTY_INSTANCE:
                            {
                                Instance* inst = datamodel->getInstanceByGuid(dataStream.readString());
                                prop->rawSetter(inst);
                            }
                            break;
                        case PROPERTY_FLOAT:
                            {
                                float v = dataStream.read<float>();
                                prop->rawSetter(&v);
                            }
                            break;
                        default:
                            printf("NetworkReplicator::onPacketReceiving: unknown ReflectionPropertyType %i\n", p_type);
                            break;
                        }
                    }
                    break;
                case 4:         
                    break;
                case 5:         // for now this will be chat message
                    {
                        std::string user = dataStream.readString();
                        std::string msg = dataStream.readString();
                        printf("NetworkReplicator::onPacketReceiving: chat: '%s: %s'\n", user.c_str(), msg.c_str());
                    }
                    break;
                default:
                    printf("NetworkReplicator::onPacketReceiving: received unknown dp id %i\n", packet_type);
                    break;
                }
            }
            break;
        }
    } 

    void NetworkReplicator::sendMarker()
    {
        printf("NetworkReplicator::sendMarker: called\n");
        ArkNet::Packets::GamePacket marker_gp;
        ArkNet::ArkStream stream(marker_gp.dataPacket, ArkNet::Packets::GAME_PACKET_MAX_SIZE);
        stream.write<int>(0); // Marker
        marker_gp.dataPacketLength = stream.size();
        m_peer->sendPacket(&marker_gp);
    }
}