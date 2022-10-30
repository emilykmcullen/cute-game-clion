
Scene2 = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] = { type="texture", id = "landscape-texture", file = "../../assets/test-landscape.png" },
        [1] = { type="texture", id = "player-texture", file = "../../assets/monsterspritesheet.png" },
        [2] = { type="texture", id = "spotty-dog", file = "../../assets/spottydog.png" },
        [3] = { type="texture", id = "bw-landscape", file = "../../assets/blackandwhitelandscape.png" },
        [4] = { type="texture", id = "school", file = "../../assets/school.png" }

    },
    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    map = {
        textureAssetId = "school",
        file = "../../assets/school.map",
        scale = 1,
        tileSize = 1280,
        mapSizeX = 1,
        mapSizeY = 1,
        scroll = 1
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
                    scale = 2,
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