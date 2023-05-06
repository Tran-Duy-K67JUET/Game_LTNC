#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>

class Texture
{
    public:
        static Texture* GetInstance() {return s_Instance = (s_Instance != nullptr)? s_Instance : new Texture();}
        void Load(std::string id, std::string file_path);
        void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawButton(std::string id, int x, int y, int width, int height,int row, int column,float s, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawText(std::string id, std::string text, int x, int y, float s);
        void QueryText(std::string id, int width, int height);
        void Drop(std::string id);
        void Clean();

    private:
        static Texture* s_Instance;
        std::map<std::string, SDL_Texture*> m_TextureMap;
        Texture(){}
};

#endif // TEXTURE_H
