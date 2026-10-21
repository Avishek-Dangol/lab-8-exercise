#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <cassert>
#include <deque>
#include <string>
#include <unordered_map>
#include <utility>

#include "sprite.h"
#include <SFML/Graphics.hpp>

using SpriteID = size_t;

class SpriteManager {
public:
    // registerTexture returns a reference to the texture, so you can pass it directly to
    // createSprite
    sf::Texture& registerTexture(const std::string& filepath) {
        auto found = mTextures.find(filepath);
        if (found != mTextures.end()) {
            return found->second;
        }
        // try_emplace returns a pair of an iterator and a bool indicating whether the insertion
        // took place
        auto [it, inserted] = mTextures.try_emplace(filepath, filepath);
        return it->second;
    }
    // createSprite returns a SpriteID, which you can use to retrieve the sprite later with
    // getSprite
    template <typename... Args>
    SpriteID createSprite(Args&&... args) {
        mSprites.emplace_back(std::forward<Args>(args)...);
        return mSprites.size() - 1;
    }
    Sprite& getSprite(SpriteID id) {
        assert(id < mSprites.size());
        return mSprites[id];
    }

private:
    // same texture can be used for multiple sprites, so we store them in a map from filepath to
    // texture
    std::unordered_map<std::string, sf::Texture> mTextures;
    // keep sprites in a deque so that we can return references to them without worrying about
    // invalidation
    std::deque<Sprite> mSprites;
};

#endif  // SPRITE_MANAGER_H
