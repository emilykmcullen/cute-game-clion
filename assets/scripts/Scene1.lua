
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
        [5] = { type="texture", id = "wigglyman", file = "../../assets/character-spritesheets/wigglyman.png" },
        [6] = { type="texture", id = "woman", file = "../../assets/character-spritesheets/womanspritesheet.png" },
        [7] = { type="texture", id = "man", file = "../../assets/character-spritesheets/man.png" },
        [8] = { type="font", id = "charriot-font", file = "../../assets/fonts/charriot.ttf", fontSize = 32 },
        [9] = { type="texture", id = "duck", file = "../../assets/character-spritesheets/duck2.png" },
        [10] = { type="texture", id = "bla", file = "../../assets/character-spritesheets/bla.png" },
        [11] = { type="texture", id = "blank", file = "../../assets/mapfiles/blank.png" },
        [12] = { type="texture", id = "sally1", file = "../../assets/character-spritesheets/sally1.png" },
        [13] = { type="texture", id = "sally2", file = "../../assets/character-spritesheets/sally2.png" },
        [14] = { type="texture", id = "sally3", file = "../../assets/character-spritesheets/sally4.png" },
        [15] = { type="texture", id = "sallylight", file = "../../assets/character-spritesheets/sally5.png" },
        [16] = { type="texture", id = "sallywalkingcolour", file = "../../assets/character-spritesheets/sallywalkingcolour.png" },
        [17] = { type="texture", id = "sallywalkingup", file = "../../assets/character-spritesheets/sallywalkingup.png" },
        [18] = { type="texture", id = "sallysheet", file = "../../assets/character-spritesheets/sally-sheet.png" },
        [19] = { type="texture", id = "house", file = "../../assets/housetest.png" },
        [20] = { type="texture", id = "antiques", file = "../../assets/antiques.png" },
        [21] = { type="texture", id = "extra", file = "../../assets/extrafood.png" },
        [22] = { type="texture", id = "path", file = "../../assets/path.png" },
        [23] = { type="texture", id = "woodenhouse", file = "../../assets/forest/woodenhouse.png" },
        [24] = { type="texture", id = "forestgrass", file = "../../assets/forest/forestmap2.png" },
        [25] = { type="texture", id = "tree", file = "../../assets/forest/tree.png" },








    },
    ----------------------------------------d------------
    -- table to define the map config variables
    ----------------------------------------------------
    map = {
        textureAssetId = "test",
        scale =5,
        tileSize = 32,
        mapSizeX = 40,
        mapSizeY = 25,
        scroll = 4
    },
    ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {
--         [0] = {
--             name = "player",
--             layer = 5,
--             isActive = true,
--             components = {
--                 transform = {
--                     position = {
--                         x = 100,
--                         y = 450
--                     },
--                     velocity = {
--                         x = 0,
--                         y = 0
--                     },
--                     width = 32,
--                     height = 32,
--                     scale = 1,
--                     centered = false,
--                     offscreen = false
--                 },
--                 sprite = {
--                     textureAssetId = "car",
--                     animated = true,
--                     animatedWhileNotMoving = false,
--                     frameCount = 2,
--                     animationSpeed = 90,
--                     hasDirections = true,
--                     fixed = false,
--                     hasCollisionAnim = false
--                 },
--                 input = {
--                     keyboard = {
--                         up = "w",
--                         left = "a",
--                         down = "s",
--                         right = "d",
--                         shoot = "space"
--                     }
--                 },
--                 collider = {
--                         tag = "PLAYER",
--                          specialSize = true,
--                          x = 101,
--                          y = 513,
--                          width = 30,
--                          height = 14,
--                          result = "stopmovement"
--                          }
--             }
--             --end of components
--         },
        -- end of this particular entity
--         [1] = {
--                     name = "shopcollidor",
--                     layer = 1,
--                     isActive = true,
--                     components = {
--                         transform = {
--                             position = {
--                                 x = 0,
--                                 y = 0
--                             },
--                             velocity = {
--                                 x = 0,
--                                 y = 0
--                             },
--                             width = 5120,
--                             height = 512,
--                             scale = 1,
--                             centered = false,
--                             offscreen = false
--                     },
--                         collider = {
--                                         tag = "OBSTACLE",
--                                         specialSize = false,
--                                         result = "stopmovement"
--                                     }
--                 }
--                 --end of components
--             },
            -- end of this particular entity
--             [2] = {
--                     name = "shopcollidor2",
--                     layer = 1,
--                     isActive = true,
--                     components = {
--                         transform = {
--                             position = {
--                                 x = 0,
--                                 y = 896
--                             },
--                             velocity = {
--                                 x = 0,
--                                 y = 0
--                             },
--                             width = 4480,
--                             height = 512,
--                             scale = 1,
--                             centered = false,
--                             offscreen = false
--                         },
--                         collider = {
--                                     tag = "OBSTACLE",
--                                     specialSize = false,
--                                     result = "stopmovement"
--                          }
--                     }
--                     --end of components
--             },
--             -- end of this particular entity
--             [3] = {
--                     name = "greencar",
--                     layer = 1,
--                     isActive = true,
--                     components = {
--                         transform = {
--                             position = {
--                                 x = 1200,
--                                 y = 650
--                             },
--                             velocity = {
--                                 x = 0,
--                                 y = 0
--                             },
--                             width = 32,
--                             height = 32,
--                             scale = 5,
--                             rotation = 0,
--                             centered = false,
--                             offscreen = true
--                         },
--                         sprite = {
--                             textureAssetId = "greencar",
--                             animated = true,
--                             animatedWhileNotMoving = false,
--                             frameCount = 2,
--                             animationSpeed = 500,
--                             hasDirections = true,
--                             fixed = false,
--                             hasCollisionAnim = false
--                         },
--                         movementschedule = {
--                                 destinations = {
--                                                     [0] = { x = -500, y = 650}
--                                                 },
--                                 timeAtDestination = 0
--                         },
--                         collider = { tag = "OBSTACLE",
--                                        specialSize = true,
--                                        x = 1201,
--                                        y = 713,
--                                        width = 30,
--                                        height = 18,
--                                        result = "stopmovement"
--                                        }
--                 }
--                 --end of components
--             },
--             -- end of this particular entity
--             [4] = {
--                     name = "woman",
--                     layer = 4,
--                     isActive = true,
--                     components = {
--                         transform = {
--                             position = {
--                                 x = 500,
--                                 y = 340
--                             },
--                             velocity = {
--                                 x = 0,
--                                 y = 0
--                             },
--                             width = 64,
--                             height = 128,
--                             scale = 1,
--                             centered = false,
--                             offscreen = true
--                         },
--                         sprite = {
--                             textureAssetId = "woman",
--                             animated = true,
--                             animatedWhileNotMoving = true,
--                             frameCount = 4,
--                             animationSpeed = 120,
--                             hasDirections = true,
--                             fixed = false,
--                             hasCollisionAnim = true
--                         },
--                         movementschedule = {
--                                 destinations = {
--                                                     [0] = { x = 500, y = 340},
--                                                     [1] = { x = 1024, y = 340},
--                                                     [2] = { x = 1024, y = 295},
--                                                     [3] = { x = 4992, y = 295},
--                                                     [4] = { x = 4992, y = 700},
--                                                     [5] = { x = 4864, y = 300}
--                                                 },
--                                 timeAtDestination = 5
--                         },
--                         collider = {
--                                     tag = "NPC",
--                                     specialSize = false,
--                                     result = "squash"
--                          }
--                     }
--                     --end of components
--                 },
--                 -- end of this particular entity
--             [5] = {
--                     name = "man",
--                     layer = 4,
--                     isActive = true,
--                     components = {
--                         transform = {
--                             position = {
--                                 x = 800,
--                                 y = 300
--                             },
--                             velocity = {
--                                 x = 0,
--                                 y = 0
--                             },
--                             width = 64,
--                             height = 128,
--                             scale = 1,
--                             centered = false,
--                             offscreen = true
--                         },
--                         sprite = {
--                             textureAssetId = "man",
--                             animated = true,
--                             animatedWhileNotMoving = true,
--                             frameCount = 4,
--                             animationSpeed = 120,
--                             hasDirections = true,
--                             fixed = false,
--                             hasCollisionAnim = true
--                         },
--                         movementschedule = {
--                                                 destinations = {
--                                                                     [0] = { x = 800, y = 300},
--                                                                     [1] = { x = 800, y = 340},
--                                                                     [2] = { x = 500, y = 290},
--                                                                     [3] = { x = 500, y = 500},
--                                                                     [4] = { x = 500, y = 300}
--                                                                 },
--                                                 timeAtDestination = 3
--                                         },
--                         collider = {
--                                     tag = "NPC",
--                                      specialSize = false,
--                                     result = "squash"
--                          }
--                     }
--                     --end of components
--                 },
--                 -- end of this particular entity
--                 [6] = {
--                         name = "farrightpath1",
--                         layer = 1,
--                         isActive = true,
--                         components = {
--                             transform = {
--                                 position = {
--                                     x = 4864,
--                                     y = 512
--                                 },
--                                 velocity = {
--                                     x = 0,
--                                     y = 0
--                                 },
--                                 width = 256,
--                                 height = 1280,
--                                 scale = 1,
--                                 centered = false,
--                                 offscreen = false
--                         },
--                         collider = {
--                                         tag = "OBSTACLE",
--                                         specialSize = false,
--                                         result = "stopmovement"
--                                     }
--                     }
--                         --end of components
--                 },
--                 --end of entity
--                 [7] = {
--                         name = "shopcollidor3",
--                         layer = 1,
--                         isActive = true,
--                         components = {
--                             transform = {
--                                 position = {
--                                     x = 768,
--                                     y = 1792
--                                 },
--                                 velocity = {
--                                     x = 0,
--                                     y = 0
--                                 },
--                                 width = 4480,
--                                 height = 512,
--                                 scale = 1,
--                                 centered = false,
--                                 offscreen = false
--                             },
--                             collider = {
--                                         tag = "OBSTACLE",
--                                         specialSize = false,
--                                         result = "stopmovement"
--                              }
--                         }
--                         --end of components
--                 },
--                 -- end of this particular entity
--                 [8] = {
--                         name = "farrightpath2",
--                         layer = 1,
--                         isActive = true,
--                         components = {
--                             transform = {
--                                 position = {
--                                     x = 0,
--                                     y = 1408
--                                 },
--                                 velocity = {
--                                     x = 0,
--                                     y = 0
--                                 },
--                                 width = 256,
--                                 height = 1280,
--                                 scale = 1,
--                                 centered = false,
--                                 offscreen = false
--                         },
--                         collider = {
--                                         tag = "OBSTACLE",
--                                         specialSize = false,
--                                         result = "stopmovement"
--                                     }
--                     }
--                         --end of components
--                 },
--                 --end of entity
--                 [9] = {
--                         name = "shopcollidor4",
--                         layer = 1,
--                         isActive = true,
--                         components = {
--                             transform = {
--                                 position = {
--                                     x = 0,
--                                     y = 2688
--                                 },
--                                 velocity = {
--                                     x = 0,
--                                     y = 0
--                                 },
--                                 width = 5120,
--                                 height = 512,
--                                 scale = 1,
--                                 centered = false,
--                                 offscreen = false
--                             },
--                             collider = {
--                                         tag = "OBSTACLE",
--                                         specialSize = false,
--                                         result = "stopmovement"
--                              }
--                         }
--                         --end of components
--                 },
--                 -- end of this particular entity
--                 [10] = {
--                         name = "timer",
--                         layer = 6,
--                         isActive = true,
--                         components = {
--                             textlabel =
--                             {
--                                 x = 1028,
--                                 y = 68,
--                                 text = "Time: ",
--                                 font = "charriot-font",
--                                 background = true
--                             }
--                         }
--                         --end of components
--                 },
--                 --end of entity
--                 [11] = {
--                         name = "monster1",
--                         layer = 4,
--                         isActive = true,
--                         components = {
--                             transform = {
--                                 position = {
--                                     x = 500,
--                                     y = 540
--                                 },
--                                 velocity = {
--                                     x = 0,
--                                     y = 0
--                                 },
--                                 width = 128,
--                                 height = 256,
--                                 scale = 1,
--                                 centered = false,
--                                 offscreen = true
--                             },
--                             sprite = {
--                                 textureAssetId = "duck",
--                                 animated = true,
--                                 animatedWhileNotMoving = true,
--                                 frameCount = 4,
--                                 animationSpeed = 120,
--                                 hasDirections = false,
--                                 fixed = false,
--                                 hasCollisionAnim = false
--                             },
--                             collider = {
--                                         tag = "ENEMY",
--                                         specialSize = false,
--                                         result = "pain"
--                              }
--                         }
--                         --end of components
--                     },
                    -- end of this particular entity
                    --end of entity
--                     [1] = {
--                             name = "sally3",
--                             layer = 4,
--                             isActive = true,
--                             components = {
--                                 transform = {
--                                     position = {
--                                         x = 500,
--                                         y = 340
--                                     },
--                                     velocity = {
--                                         x = 0,
--                                         y = 0
--                                     },
--                                     width = 125,
--                                     height = 256,
--                                     scale = 0.6,
--                                     centered = false,
--                                     offscreen = true
--                                 },
--                                 sprite = {
--                                     textureAssetId = "sally3",
--                                     animated = true,
--                                     animatedWhileNotMoving = true,
--                                     frameCount = 8,
--                                     animationSpeed = 120,
--                                     hasDirections = false,
--                                     fixed = false,
--                                     hasCollisionAnim = false
--                                 },
--                                 collider = {
--                                             tag = "ENEMY",
--                                             specialSize = false,
--                                             result = "pain"
--                                  }
--                             }
--                             --end of components
--                         },
--                         -- end of this particular entity
--                         [2] = {
--                                 name = "sallylightoutline",
--                                 layer = 4,
--                                 isActive = true,
--                                 components = {
--                                     transform = {
--                                         position = {
--                                             x = 575,
--                                             y = 340
--                                         },
--                                         velocity = {
--                                             x = 0,
--                                             y = 0
--                                         },
--                                         width = 125,
--                                         height = 256,
--                                         scale = 0.5,
--                                         centered = false,
--                                         offscreen = true
--                                     },
--                                     sprite = {
--                                         textureAssetId = "sally3",
--                                         animated = true,
--                                         animatedWhileNotMoving = true,
--                                         frameCount = 8,
--                                         animationSpeed = 120,
--                                         hasDirections = false,
--                                         fixed = false,
--                                         hasCollisionAnim = false
--                                     },
--                                     collider = {
--                                                 tag = "ENEMY",
--                                                 specialSize = false,
--                                                 result = "pain"
--                                      }
--                                 }
--                                 --end of components
--                             },
--                             -- end of this particular entity
--                             [3] = {
--                                     name = "sallywalking",
--                                     layer = 4,
--                                     isActive = true,
--                                     components = {
--                                         transform = {
--                                             position = {
--                                                 x = 800,
--                                                 y = 340
--                                             },
--                                             velocity = {
--                                                 x = 0,
--                                                 y = 0
--                                             },
--                                             width = 250,
--                                             height = 512,
--                                             scale = 1,
--                                             centered = false,
--                                             offscreen = true
--                                         },
--                                         sprite = {
--                                             textureAssetId = "sallywalkingup",
--                                             animated = true,
--                                             animatedWhileNotMoving = true,
--                                             frameCount = 8,
--                                             animationSpeed = 120,
--                                             hasDirections = false,
--                                             fixed = false,
--                                             hasCollisionAnim = false
--                                         },
--                                         collider = {
--                                                     tag = "ENEMY",
--                                                     specialSize = false,
--                                                     result = "pain"
--                                          }
--                                     }
--                                     --end of components
--                                 },
                    -- end of this particular entity
                    [0] = {
                                name = "player",
                                layer = 5,
                                isActive = true,
                                components = {
                                    transform = {
                                        position = {
                                            x = 100,
                                            y = 340
                                        },
                                        velocity = {
                                            x = 0,
                                            y = 0
                                        },
                                        width = 250,
                                        height = 512,
                                        scale = 0.4,
                                        centered = false,
                                        offscreen = false
                                    },
                                    sprite = {
                                        textureAssetId = "sallysheet",
                                        animated = true,
                                        animatedWhileNotMoving = false,
                                        frameCount = 8,
                                        animationSpeed = 120,
                                        hasDirections = true,
                                        fixed = false,
                                        hasCollisionAnim = false
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
                                             specialSize = false,
                                             result = "stopmovement"
                                             }
                                }
                                --end of components
                            },
-- end of this particular entity
                            [1] = {
                                    name = "wigglyman",
                                    layer = 4,
                                    isActive = true,
                                    components = {
                                        transform = {
                                            position = {
                                                x = 2000,
                                                y = 340
                                            },
                                            velocity = {
                                                x = 0,
                                                y = 0
                                            },
                                            width = 250,
                                            height = 490,
                                            scale = 0.5,
                                            centered = false,
                                            offscreen = true
                                        },
                                        sprite = {
                                            textureAssetId = "wigglyman",
                                            animated = true,
                                            animatedWhileNotMoving = true,
                                            frameCount = 8,
                                            animationSpeed = 120,
                                            hasDirections = false,
                                            fixed = false,
                                            hasCollisionAnim = false
                                        },
                                        collider = {
                                                    tag = "ENEMY",
                                                    specialSize = false,
                                                    result = "pain"
                                         }
                                    }
                                    --end of components
                                },
--                             [2] = {
--                                     name = "antiques",
--                                     layer = 4,
--                                     isActive = true,
--                                     components = {
--                                         transform = {
--                                             position = {
--                                                 x = 2880,
--                                                 y = 115
--                                             },
--                                             velocity = {
--                                                 x = 0,
--                                                 y = 0
--                                             },
--                                             width = 960,
--                                             height = 737,
--                                             scale = 0.5,
--                                             centered = false,
--                                             offscreen = true
--                                         },
--                                         sprite = {
--                                             textureAssetId = "antiques",
--                                             animated = false,
--                                             animatedWhileNotMoving = false,
--                                             frameCount = 1,
--                                             animationSpeed = 120,
--                                             hasDirections = false,
--                                             fixed = false,
--                                             hasCollisionAnim = false
--                                         }
--                                     }
--                                     --end of components
--                                 },
                                [2] = {
                                        name = "woodenhouse",
                                        layer = 4,
                                        isActive = true,
                                        components = {
                                            transform = {
                                                position = {
                                                    x = 800,
                                                    y = 0
                                                },
                                                velocity = {
                                                    x = 0,
                                                    y = 0
                                                },
                                                width = 1920,
                                                height = 2200,
                                                scale = 0.4,
                                                centered = false,
                                                offscreen = true
                                            },
                                            sprite = {
                                                textureAssetId = "woodenhouse",
                                                animated = false,
                                                animatedWhileNotMoving = false,
                                                frameCount = 1,
                                                animationSpeed = 120,
                                                hasDirections = false,
                                                fixed = false,
                                                hasCollisionAnim = false
                                            }
                                        }
                                        --end of components
                                    },
                           [3] = {
                                   name = "forestgrassmap",
                                   layer = 1,
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
                                           width = 5120,
                                           height = 3200,
                                           scale = 0.4,
                                           centered = false,
                                           offscreen = true
                                       },
                                       sprite = {
                                           textureAssetId = "forestgrass",
                                           animated = false,
                                           animatedWhileNotMoving = false,
                                           frameCount = 1,
                                           animationSpeed = 120,
                                           hasDirections = false,
                                           fixed = false,
                                           hasCollisionAnim = false
                                       }
                                   }
                               },
                              [4] = {
                                      name = "tree",
                                      layer = 4,
                                      isActive = true,
                                      components = {
                                          transform = {
                                              position = {
                                                  x = 1600,
                                                  y = 0
                                              },
                                              velocity = {
                                                  x = 0,
                                                  y = 0
                                              },
                                              width = 1739,
                                              height = 2087,
                                              scale = 0.4,
                                              centered = false,
                                              offscreen = true
                                          },
                                          sprite = {
                                              textureAssetId = "tree",
                                              animated = false,
                                              animatedWhileNotMoving = false,
                                              frameCount = 1,
                                              animationSpeed = 120,
                                              hasDirections = false,
                                              fixed = false,
                                              hasCollisionAnim = false
                                          }
                                      }
                                      --end of components
                                  },

                             [5] = {
                                     name = "forestgrassmap2",
                                     layer = 1,
                                     isActive = true,
                                     components = {
                                         transform = {
                                             position = {
                                                 x = 2048,
                                                 y = 0
                                             },
                                             velocity = {
                                                 x = 0,
                                                 y = 0
                                             },
                                             width = 5120,
                                             height = 3200,
                                             scale = 0.4,
                                             centered = false,
                                             offscreen = true
                                         },
                                         sprite = {
                                             textureAssetId = "forestgrass",
                                             animated = false,
                                             animatedWhileNotMoving = false,
                                             frameCount = 1,
                                             animationSpeed = 120,
                                             hasDirections = false,
                                             fixed = false,
                                             hasCollisionAnim = false
                                         }
                                     }
                                 },


    }
    --end of entities
}
