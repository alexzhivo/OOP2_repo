# - Fonts
configure_file ("fonts/arcadefont.ttf" ${CMAKE_BINARY_DIR} COPYONLY)

# - Levels
configure_file ("levels/level_1.txt" ${CMAKE_BINARY_DIR} COPYONLY)
#configure_file ("levels/level_2.txt" ${CMAKE_BINARY_DIR} COPYONLY)
#configure_file ("levels/level_3.txt" ${CMAKE_BINARY_DIR} COPYONLY)

# - Wallpaper
configure_file ("media/images/wallpaper.png" ${CMAKE_BINARY_DIR} COPYONLY)

# - Game Objects
configure_file ("media/images/ball.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/bar_grey.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/brick_blue.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/brick_green.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/brick_red.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/heart_blue.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/heart_red.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/platform_long.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/platform_mid.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/platform_sm.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/power_upscore.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/images/power_lowscore.png" ${CMAKE_BINARY_DIR} COPYONLY)

# - Sounds (MP3)
configure_file ("media/sounds/stardust_music.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/game_music.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/collect_pts.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/game_start.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/not_break.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/select_sound.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/game_lose.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/lose_ball.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/pop_once.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
# - (WAV)
configure_file ("media/sounds/game_win.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/hover_sound.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("media/sounds/level_up.wav" ${CMAKE_BINARY_DIR} COPYONLY)



