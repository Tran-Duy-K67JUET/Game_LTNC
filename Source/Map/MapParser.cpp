#include "MapParser.h"
#include "SDL2/SDL.h"
#include <iostream>

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
    /*
    if(!Parse("",""))
        return false;
    return true;
    */
    return Parse("map0001","assets/maps/level0001.tmx");
}



bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        std::cerr << "Failed to load map: " << source << std::endl;
        return false;
    }
    TiXmlElement* root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;
    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    m_MapSize[id] = {rowcount, colcount, tilesize};

    // parse tilesets
    TilesetList tilesets;
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }
    }

    // parse layers
    GameMap* gamemap = new GameMap();
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }
    m_MapDict[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    Tileset tileset;

    tileset.Name = xmlTileset->Attribute( "name" );
    xmlTileset->Attribute( "firstgid", &tileset.FirstID );
    //SDL_Log( "map data: \n name = %s", tileset.Name.c_str() );

    xmlTileset->Attribute( "tilecount", &tileset.TileCount );
    tileset.LastID = ( tileset.FirstID + tileset.TileCount) -1;
    //SDL_Log("tilecount = %d", tileset.TileCount );
    //SDL_Log("lastid = %d", tileset.LastID );

    xmlTileset->Attribute( "columns", &tileset.ColCount );
    tileset.RowCount = (tileset.TileCount / tileset.ColCount );
    xmlTileset->Attribute( "tilewidth", &tileset.TileSize );
    //SDL_Log("colcount = %d", tileset.ColCount );
    //SDL_Log("rowcount = %d", tileset.RowCount );
    //SDL_Log("tilesize = %d", tileset.TileSize );

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute( "source" );
    //SDL_Log("tileset = %s", tileset.Source.c_str() );


    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
    TiXmlElement* data;
    for(TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("data") )
        {
            data = e;
            break;
        }
    }

    std::string matrix( data->GetText() );
    std::istringstream iss( matrix );
    std::string id;

    TileMap tilemap( rowcount, std::vector<int>(colcount, 0));
    for(int row = 0; row < rowcount; row++ )
    {
        for(int col = 0; col < colcount; col++ )
        {
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];
            if(!iss.good()) {
                break;
            }
        }
    }
    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}

void MapParser::Clean()
{
    std::map<std::string, GameMap*>::iterator it;
    for(it = m_MapDict.begin(); it != m_MapDict.end(); it++)
        it->second = nullptr;
    m_MapDict.clear();
}
