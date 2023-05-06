#include "Texture.h"
#include "Engine.h"
#include "Vector2d.h"
#include "Camera.h"

Texture* Texture::s_Instance = nullptr;
void Texture::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load( filename.c_str() );
    if(surface == nullptr ) {
        SDL_Log( "failed to load texture: %s, %s", filename.c_str(), SDL_GetError() );
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( Engine::GetInstance()->GetRenderer(), surface );
    if( texture == nullptr ){
        SDL_Log( "failed to create texture from surface: %s",  SDL_GetError() );
    }
    m_TextureMap[id] = texture;
}

void Texture::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect dstRect = { x, y, width, height };
    SDL_RenderCopyEx( Engine::GetInstance()->GetRenderer(),m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip );
}

void Texture::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { width*frame, height*row, width, height };
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = { (x - cam.X), (y - cam.Y), width, height };
    SDL_RenderCopyEx( Engine::GetInstance()->GetRenderer(),m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip );
}

void Texture::DrawText(std::string id, std::string text, int x, int y, float s) {
    SDL_Color color = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(Engine::GetInstance()->GetFont(), text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    m_TextureMap[id] = texture;

    SDL_Rect dstRect = {x, y, surface->w*s, surface->h*s};
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], nullptr, &dstRect);
}

void Texture::DrawButton(std::string id, int x, int y, int width, int height,int row, int column, float s, SDL_RendererFlip flip) {
    SDL_Rect srcRect = { width*column, height*row, width, height };
    SDL_Rect dstRect = { x, y, s*width, s*height };
    SDL_RenderCopyEx( Engine::GetInstance()->GetRenderer(),m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip );
}

void Texture::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { tileSize*frame, tileSize*row, tileSize, tileSize };
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = { x-cam.X, y-cam.Y, tileSize, tileSize };
    SDL_RenderCopyEx( Engine::GetInstance()->GetRenderer(),m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip );
}

void Texture::QueryText(std::string id, int width, int height) {
    SDL_QueryTexture(m_TextureMap[id], nullptr, nullptr, &width, &height);
}

void Texture::Drop(std::string id)
{
    SDL_DestroyTexture( m_TextureMap[id] );
    m_TextureMap.erase(id);
}

void Texture::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for( it = m_TextureMap.begin(); it != m_TextureMap.end(); it++ )
        SDL_DestroyTexture( it->second );
    m_TextureMap.clear();
    SDL_Log("texture map cleaned");
}
