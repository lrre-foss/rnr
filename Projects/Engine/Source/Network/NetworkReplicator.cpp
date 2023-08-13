#include <Network/NetworkReplicator.hpp>
#include <Network/NetworkServer.hpp>
#include <Network/NetworkClient.hpp>
#include <Network/Marker.hpp>
#include <App/V8/Tree/InstanceFactory.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/DataModel.hpp>
#include <Helpers/Strings.hpp>

namespace RNR
{
    NetworkReplicator::NetworkReplicator(ArkNet::ArkPeer* peer, bool serverReplicator) : Instance()
    {
        setName("NetworkReplicator");
        m_peer = peer;
        m_serverReplicator = serverReplicator;
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

        sendInstanceProps(instance);
    }

    void NetworkReplicator::sendReflectionProperty(ReflectionProperty prop)
    {
        Instance* instance = (Instance*)prop.object();
        if(instance)
        {
            DataModel* datamodel = world->getDatamodel();
            std::string guid = datamodel->getGuidByInstance(instance);

            ArkNet::Packets::GamePacket i_packet;
            ArkNet::ArkStream dataStream(i_packet.dataPacket,ArkNet::Packets::GAME_PACKET_MAX_SIZE);
    
            dataStream.write<int>(3);
            dataStream.writeString(guid);
            dataStream.writeString(prop.name());
            dataStream.write(prop.type());

            switch(prop.type())
            {
            case PROPERTY_STD_STRING:
                dataStream.writeString(*(std::string*)prop.rawGetter());
                break;
            case PROPERTY_BOOL:
            case PROPERTY_BRICKCOLOR:
            case PROPERTY_INTEGER:
                dataStream.write(*(int*)prop.rawGetter());
                break;
            case PROPERTY_VECTOR3:
                dataStream.write(*(Ogre::Vector3*)prop.rawGetter());
                break;
            case PROPERTY_INSTANCE:
                {
                    Instance* i = (Instance*)prop.rawGetter();
                    dataStream.writeString(datamodel->getGuidByInstance(i));
                }
                break;
            case PROPERTY_CFRAME:
                dataStream.write(*(CoordinateFrame*)prop.rawGetter());
                break;
            case PROPERTY_FLOAT:
                dataStream.write(*(float*)prop.rawGetter());
                break;
            default:
                break;
            }

            i_packet.dataPacketLength = dataStream.size();
            m_peer->sendPacket(&i_packet);
        }
    }

    void NetworkReplicator::sendInstanceProps(Instance* instance)
    {
        std::vector<ReflectionProperty> props = instance->getProperties();
        for(auto prop : props)
            sendReflectionProperty(prop);
    }

    void NetworkReplicator::readDataPacket(ArkNet::ArkPeer* peer, ArkNet::ArkPacket* packet)
    {        
        DataModel* datamodel = world->getDatamodel();
        std::vector<ReflectionProperty> props;
        ArkNet::Packets::GamePacket* _packet = dynamic_cast<ArkNet::Packets::GamePacket*>(packet);
        ArkNet::ArkStream dataStream(_packet->dataPacket + sizeof(int), _packet->dataPacketLength - sizeof(int)); // we need to skip the onPacketReceiving type
        bool done = false;
        do {
            int packet_type = dataStream.read<int>();
            switch(packet_type) // TODO: make this completely accurate
            {
            case 0:         // stop
                done = true;
                break;
            case 1:         // del instance
                {
                    Instance* delinst = datamodel->getInstanceByGuid(dataStream.readString());
                    if(delinst)
                        delinst->setParent(NULL);
                }
                break;
            case 2:         // new instance
                {
                    std::string i_guid = dataStream.readString();
                    Instance* newinst;
                    std::string t_type = dataStream.readString();
                    Instance* existinst = datamodel->findFirstChildOfType(t_type);
                    if(existinst)
                    {
                        printf("NetworkReplicator::readDataPacket: reregistering %s guid\n", existinst->getName().c_str());
                        datamodel->removeInstanceByGuid(datamodel->getGuidByInstance(existinst));
                        newinst = existinst;
                    }
                    else
                    {
                        newinst = InstanceFactory::singleton()->build(t_type);
                        if(!newinst)
                        {
                            printf("NetworkReplicator::readDataPacket: newinst == NULL\n");
                            break;
                        }
                    }
                    datamodel->registerInstanceByGuid(newinst, i_guid);
                }
                break;
            case 3:         // update instance prop
                {
                    std::string i_guid = dataStream.readString();
                    Instance* instance = datamodel->getInstanceByGuid(i_guid);
                    if(!instance)
                    {
                        printf("NetworkReplicator::readDataPacket: received bad Instance GUID '%s'\n", i_guid.c_str());
                        break;
                    }
                    std::string p_name = dataStream.readString();
                    ReflectionPropertyType p_type = dataStream.read<ReflectionPropertyType>();
                    props = instance->getProperties();
                    ReflectionProperty* prop;
                    for(auto& _prop : props)
                        if(_prop.name() == p_name && _prop.type() == p_type)
                            prop = &_prop;
                    if(!prop)
                    {
                        printf("NetworkReplicator::readDataPacket: received bad ReflectionProperty '%s' with type '%i'\n", p_name.c_str(), p_type);
                        break;
                    }
                    switch(p_type)
                    {
                    case PROPERTY_BOOL:
                    case PROPERTY_BRICKCOLOR:
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
                        printf("NetworkReplicator::readDataPacket: unknown ReflectionPropertyType %i\n", p_type);
                        break;
                    }
                }
                break;
            case 4:
                processMarker(dataStream.read<int>());
                break;
            default:
                printf("NetworkReplicator::readDataPacket: received unknown dp id %i\n", packet_type);
                break;
            }
        } while(!done);
    }

    void NetworkReplicator::onPacketReceiving(ArkNet::ArkPeer* peer, ArkNet::ArkPacket* packet)
    {
        switch(packet->packetId())
        {
        case 0x07:
            {
                ArkNet::Packets::GamePacket* _packet = dynamic_cast<ArkNet::Packets::GamePacket*>(packet);
                ArkNet::ArkStream dataStream(_packet->dataPacket + sizeof(int), _packet->dataPacketLength - sizeof(int)); // we need to skip the onPacketReceiving type
                switch(dataStream.read<int>())
                {
                case 0x59: // Data
                    readDataPacket(peer, packet);
                    break;
                }
            }
            break;        
        }
    } 

    Network::Marker* NetworkReplicator::sendMarker()
    {
        printf("NetworkReplicator::sendMarker: called\n");
        Network::Marker* marker = new Network::Marker();
        ArkNet::Packets::GamePacket marker_gp;
        ArkNet::ArkStream stream(marker_gp.dataPacket, ArkNet::Packets::GAME_PACKET_MAX_SIZE);
        stream.write<int>(0); // Marker
        stream.write(marker->getId());
        marker_gp.dataPacketLength = stream.size();
        m_peer->sendPacket(&marker_gp);
        m_incomingMarkers.push_back(marker);
        return marker;
    }

    void NetworkReplicator::processMarker(int id)
    {
        if(m_incomingMarkers.size() > 0)
            if(id == m_incomingMarkers.back()->getId())
            {
                m_incomingMarkers.front()->fireReturned();
                m_incomingMarkers.pop_back();
            }
            else
                printf("NetworkReplicator::processMarker: rejected marker %i, not back incoming marker\n", id);
        else
            printf("NetworkReplicator::processMarker: rejected marker %i, m_incomingMarkers has no markers\n", id);
    }
}