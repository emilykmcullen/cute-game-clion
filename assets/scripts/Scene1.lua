
Scene1 = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] = { type="texture", id = "pigeon", file = "../../assets/character-spritesheets/pigeon.png" },
        [1] = { type="texture", id = "background", file = "../../assets/backgrounds/twotiles.png" },
        [2] = { type="texture", id = "nums", file = "../../assets/backgrounds/nums.png" },
        [3] = { type="texture", id = "car", file = "../../assets/character-spritesheets/car.png" },
        [4] = { type="texture", id = "test", file = "../../assets/mapfiles/tiledmap.png" },
        [5] = { type="texture", id = "greencar", file = "../../assets/character-spritesheets/greencar.png" },

    },
    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    map = {
        textureAssetId = "test",
        scale = 4,
        tileSize = 32,
        mapSizeX = 40,
        mapSizeY = 25,
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
                        y = 450
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 5,
                    centered = false,
                    offscreen = false
                },
                sprite = {
                    textureAssetId = "car",
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
                collider = {
                        tag = "PLAYER",
                         specialSize = true,
                         x = 101,
                         y = 513,
                         width = 30,
                         height = 14
                         }
            }
            --end of components
        },
        -- end of this particular entity
        [1] = {
                name = "pigeon",
                layer = 4,
                isActive = true,
                components = {
                    transform = {
                        position = {
                            x = 1100,
                            y = 400
                        },
                        velocity = {
                            x = 0,
                            y = 0
                        },
                        width = 96,
                        height = 64,
                        scale = 0.5,
                        centered = false,
                        offscreen = true
                    },
                    sprite = {
                        textureAssetId = "pigeon",
                        animated = true,
                        animatedWhileNotMoving = true,
                        frameCount = 4,
                        animationSpeed = 180,
                        hasDirections = true,
                        fixed = false
                    },
                    movementschedule = {
                                            destinations = {
                                                                [0] = { x = 1100, y = 400},
                                                                [1] = { x = 10, y = 50},
                                                                [2] = { x = 1100, y = 50}
                                                            },
                                            timeAtDestination = 5
                                    }
                }
                --end of components
            },
            -- end of this particular entity
            [2] = {
                        name = "shopcollidor",
                        layer = 2,
                        isActive = true,
                        components = {
                            transform = {
                                position = {
                                    x = 0,
                                    y = 0
                                },
                                velocity = {
                                    x = 0,
                                    y = 0
                                },
                                --width = 5120,
                                --height = 512,
                                width = 1,
                                height = 1,
                                scale = 1,
                                centered = false,
                                offscreen = false
                        },
                            collider = {
                                            tag = "OBSTACLE",
                                            specialSize = false
                                        }
                }
                --end of components
            },
            -- end of this particular entity
            [3] = {
                    name = "shopcollidor2",
                    layer = 2,
                    isActive = true,
                    components = {
                        transform = {
                            position = {
                                x = 0,
                                y = 896
                            },
                            velocity = {
                                x = 0,
                                y = 0
                            },
                            --width = 5120,
                            --height = 448,
                            width = 1,
                            height = 1,
                            scale = 1,
                            centered = false,
                            offscreen = false
                        },
                        collider = {
                                    tag = "OBSTACLE",
                                    specialSize = false
                         }
                    }
                    --end of components
            },
            -- end of this particular entity
            [4] = {
                    name = "greencar",
                    layer = 1,
                    isActive = true,
                    components = {
                        transform = {
                            position = {
                                x = 1200,
                                y = 650
                            },
                            velocity = {
                                x = 0,
                                y = 0
                            },
                            width = 32,
                            height = 32,
                            scale = 5,
                            rotation = 0,
                            centered = false,
                            offscreen = true
                        },
                        sprite = {
                            textureAssetId = "greencar",
                            animated = true,
                            animatedWhileNotMoving = false,
                            frameCount = 2,
                            animationSpeed = 500,
                            hasDirections = true,
                            fixed = false
                        },
                        movementschedule = {
                                destinations = {
                                                    [0] = { x = -500, y = 650}
                                                },
                                timeAtDestination = 0
                        },
                        collider = { tag = "OBSTACLE",
                                       specialSize = true,
                                       x = 1201,
                                       y = 713,
                                       width = 30,
                                       height = 18
                                       }
                }
                --end of components
            },
            -- end of this particular entity


    }
    --end of entities
}
