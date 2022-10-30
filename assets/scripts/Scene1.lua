
Scene1 = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] = { type="texture", id = "landscape-texture", file = "../../assets/test-landscape.png" },
        [1] = { type="texture", id = "player-texture", file = "../../assets/monsterspritesheet.png" },
        [2] = { type="texture", id = "spotty-dog", file = "../../assets/spottydog.png" },
        [3] = { type="texture", id = "bw-landscape", file = "../../assets/blackandwhitelandscape.png" },
        [4] = { type="texture", id = "house", file = "../../assets/house.png" },
        [5] = { type="texture", id = "hello", file = "../../assets/hello.png" }

    },
    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    map = {
        textureAssetId = "bw-landscape",
        file = "../../assets/landscape.map",
        scale = 4,
        tileSize = 32,
        mapSizeX = 20,
        mapSizeY = 10,
        scroll = 2
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
        },
        -- end of this particular entity
        [1] = {
            name = "dog",
            layer = 3,
            isActive = true,
            components = {
                transform = {
                    position = {
                        x = 500,
                        y = 500
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 48,
                    height = 32,
                    scale = 4,
                    centered = false
                },
                sprite = {
                    textureAssetId = "spotty-dog",
                    animated = true,
                    animatedWhileNotMoving = true,
                    frameCount = 2,
                    animationSpeed = 500,
                    hasDirections = true,
                    fixed = false
                },
                movementschedule = {
                        destinations = {
                                            [0] = { x = 500, y = 500},
                                            [1] = { x = 1000, y = 1000},
                                            [2] = { x = 100, y = 1000},
                                            [3] = { x = 100, y = 100},
                                            [4] = { x = 500, y = 100}
                                        },
                        timeAtDestination = 10
                },
                interaction = {
                                interactiontype = "speak",
                                info = "hello"
                            }
            }
            --end of components
        },
        -- end of this particular entity
        [2] = {
                    name = "house",
                    layer = 1,
                    isActive = true,
                    components = {
                        transform = {
                            position = {
                                x = 1664,
                                y = 256
                            },
                            velocity = {
                                x = 0,
                                y = 0
                            },
                            width = 96,
                            height = 96,
                            scale = 4,
                            centered = false
                        },
                        sprite = {
                            textureAssetId = "house",
                            animated = false,
                            animatedWhileNotMoving = false,
                            frameCount = 1,
                            animationSpeed = 1,
                            hasDirections = false,
                            fixed = true
                        },
                        collider = { tag = "OBSTACLE" },
                        interaction = {
                            interactiontype = "loadscene",
                            info = "2"
                        }
                    }
                    --end of components
                },
                -- end of this particular entity
        [3] = {
                    name = "hello",
                    layer = 4,
                    isActive = false,
                    components = {
                        transform = {
                            position = {
                                x = 500,
                                y = 500
                            },
                            velocity = {
                                x = 0,
                                y = 0
                            },
                            width = 600,
                            height = 300,
                            scale = 1,
                            centered = true
                        },
                        sprite = {
                            textureAssetId = "hello",
                            animated = false,
                            animatedWhileNotMoving = false,
                            frameCount = 1,
                            animationSpeed = 90,
                            hasDirections = false,
                            fixed = true
                        },
                        interaction = {
                                        interactiontype = "deactivate",
                                        info = "hello",
                                        rect = {
                                                x = 0,
                                                y = 0,
                                                width = 1280,
                                                height = 640
                                        }

                                    }

                    }
                    --end of components
                },
                -- end of this particular entity
    }
    --end of entities
}
