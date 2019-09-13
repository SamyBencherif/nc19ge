
typedef enum {unchoosen, friendly, swift, frugal, courageous, 
    enchanting, wise} skill;

typedef enum {gun, cursed_pendant, grappling_hook, magical_spectacles,
    broom} gift_item;

typedef struct {
    
    int time = 0;
    scene scene_present = title;
    
    coord2 cursor;
    skill player_skill = unchoosen;

    int cheat_sequence_index = 0;
    /* Type this sequence into the title screen */
    char* cheat_sequence_wisdom = "ppp[*"; 
    bool cheat_wisdom_active = false;

} gamestate;
