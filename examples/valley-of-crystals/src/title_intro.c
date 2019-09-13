
void title_init()
{
    title_img_0 = bitmap_create(KBM_VALLEY_TITLE_0_W,
    KBM_VALLEY_TITLE_0_H,
    KBM_VALLEY_TITLE_0);
    title_img_0->transform->translate->x = -KBM_VALLEY_TITLE_0_W/2;
    title_img_0->transform->translate->y = (-KBM_VALLEY_TITLE_0_H/2
                      + 2) * BLOCK_ASPECT;
    component_add(title_img_0);

    title_img_1 = bitmap_create(KBM_VALLEY_TITLE_1_W,
    KBM_VALLEY_TITLE_1_H,
    KBM_VALLEY_TITLE_1);
    title_img_1->transform->translate->x = -KBM_VALLEY_TITLE_1_W/2;
    title_img_1->transform->translate->y = (-KBM_VALLEY_TITLE_1_H/2
                      + 2) * BLOCK_ASPECT;
    title_img_1->visible = false;
    component_add(title_img_1);
}

void title_update()
{
	printc(W/2, H/2 + 6, BLACK, "~ Press Any Key To Begin ~");

	if (t%5 == 0)
	{
		title_img_0->visible = !title_img_0->visible;
		title_img_1->visible = !title_img_1->visible;
	}
}

void title_key()
{
	if ( k == cheat_sequence_wisdom[cheat_index] )
	{
		cheat_index ++;
		if (cheat_index < 5)
			return;

		/* cheat code successful */
		cheat_wisdom_active = true;
		cheat_index = 0;

	} else
	{
		cheat_index = 0;
	}

    /*
     * int modal_selector(char* caption, char* select_fmt,
     * char* unselect_fmt, color select_color, color unselect_color,
     * int choice_count, char** choices);
     */
    
    char** choices = {
        "Friendly",
        "Swift",
        "Frugal",
        "Courageous",
        "Enchanting"
    };
    modal_selector("First, choose your personality.",
            "I am %s.", "%s", BLUE, BLACK, 5, choices);
	init();
}

