
Scene1 = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] = { type="texture", id = "player-texture", file = "../../assets/character-spritesheets/monsterspritesheet.png" },
        [1] = { type="texture", id = "background", file = "../../assets/backgrounds/twotiles.png" },
        [2] = { type="texture", id = "nums", file = "../../assets/backgrounds/nums.png" },

    },
    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    map = {
        textureAssetId = "nums",
        file = "../../assets/mapfiles/nums.map",
        scale = 2,
        tileSize = 32,
        mapSizeX = 80,
        mapSizeY = 50,
        scroll = 4
    },
    ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {
        [0] = {
            name = "player",
            layer = 2,
            isActive = true,
            components = {
                transform = {
                    position = {
                        x = 100,
                        y = 100
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 96,
                    height = 64,
                    scale = 1,
                    centered = false
                },
                sprite = {
                    textureAssetId = "player-texture",
                    animated = true,
                    animatedWhileNotMoving = false,
                    frameCount = 2,
                    animationSpeed = 90,
                    hasDirections = true,
                    fixed = false
                },
                input = {
                    keyboard = {
                        up = "w",
                        left = "a",
                        down = "s",
                        right = "d",
                        shoot = "space"
                    }
                },
                collider = { tag = "PLAYER" }
            }
            --end of components
        }
        -- end of this particular entity
    }
    --end of entities
}
