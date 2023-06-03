#include "TextureManager.h"
#include "../Core/Engine.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }
    m_TextureMap[id] = texture;
    return true;
    AllID.push_back(id);
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);
    m_TextureMap.clear();
}

void TextureManager::Draw(std::string id, int x, int y, int width, int heigth, double compresion, SDL_RendererFlip flip, double angel)
{
    SDL_Rect srcRect = { 0, 0, width, heigth };
    SDL_Rect dstRect = { x, y, width / compresion, heigth / compresion };//суда можно добавить коэффицент сжатия
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, angel, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect dstRect = { x ,y ,tilesize,tilesize };
    SDL_Rect srcRect = { tilesize * frame,tilesize * row,tilesize,tilesize };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int heigth, double compression, int row, int frame, SDL_RendererFlip flip, double angel) {
    SDL_Rect srcRect = { width * frame, heigth * row, width, heigth };
    SDL_Rect dstRect = { x, y, width / compression, heigth / compression };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, angel, nullptr, flip);
}
