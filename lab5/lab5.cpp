#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

struct arrow_class
{
	int x, y;
	int dir, speed;
	int color;

} arrow;

#define MAXSPEED 3

void create_arrow_bitmap(ALLEGRO_BITMAP* arrow_bmp[], ALLEGRO_DISPLAY* display);
void erase_arrow();
void move_arrow();
void up();
void down();
void right();
void left();

int main(void)
{

	ALLEGRO_BITMAP* arrow_bmp[4] = { NULL,NULL,NULL,NULL };
	//variables
	int width = 640;
	int height = 480;
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	create_arrow_bitmap(arrow_bmp, display);


	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		
		al_draw_rotated_bitmap(arrow_bmp[0], 32, 32, 200, 400, 3.14159, 0);
		al_draw_rotated_bitmap(arrow_bmp[1], 32, 32, 350, 400, 3.14159, 0);
		al_draw_bitmap(arrow_bmp[2], width / 2, 100, 0);
		al_draw_bitmap(arrow_bmp[3], width / 2, 200, 0);
		al_draw_bitmap(arrow_bmp[4], 100, 100, 0);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	for (int i = 0; i < 5; i++)
	{
		al_destroy_bitmap(arrow_bmp[i]);
	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}

void create_arrow_bitmap(ALLEGRO_BITMAP* arrow_bmp[], ALLEGRO_DISPLAY* display)
{
	for (int i = 0;i < 5; i++)
	{
		arrow_bmp[i] = al_create_bitmap(64, 64);
		if (!arrow_bmp[i]) {
			exit(1);
			al_destroy_display(display);

		}

		al_set_target_bitmap(arrow_bmp[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		switch (i)
		{
		case 0: //
			al_draw_filled_ellipse(20, 20, 15, 15, al_map_rgb(255, 25, 25)); //round body bottom
			al_draw_filled_rectangle(5, 20, 15, 55, al_map_rgb(255, 25, 25)); //main left
			al_draw_filled_rectangle(25, 20, 35, 55, al_map_rgb(255, 25, 25));//main right
			al_draw_filled_rectangle(8, 20, 12, 55, al_map_rgb(45, 45, 45));//thin middle left
			al_draw_filled_rectangle(28, 20, 32, 55, al_map_rgb(45, 45, 45));//thin middle right
			al_draw_filled_ellipse(20, 20, 13, 13, al_map_rgb(45, 35, 45)); //round body top
			break;

		case 1://Right
			al_draw_filled_ellipse( 20, 20, 15, 15, al_map_rgb(255, 25, 25)); //body bottom
			al_draw_filled_rectangle( 5, 20, 15, 55, al_map_rgb(255, 25, 25)); //main left
			al_draw_filled_rectangle( 25, 20, 35, 55, al_map_rgb(255, 25, 25));//main right
			al_draw_filled_rectangle( 8, 20, 12, 55, al_map_rgb(45, 45, 45));//thin middle left
			al_draw_filled_rectangle( 28, 20, 32, 55, al_map_rgb(45, 45, 45));//thin middle right
			al_draw_filled_ellipse( 20, 20, 13, 13, al_map_rgb(45, 35, 45)); //body top

			break;
		case 2://Down
			al_draw_filled_triangle( 20, 20, 25, 5, 30, 20, al_map_rgb(25, 80, 75));//ear l
			al_draw_filled_triangle( 34, 20, 39, 5, 44, 20, al_map_rgb(25, 80, 75));//ear r

			al_draw_filled_ellipse( 32, 32, 20, 15, al_map_rgb(25, 80, 75)); //body bottom
			al_draw_filled_ellipse( 25, 29, 3, 3, al_map_rgb(128, 128, 128)); //left eye bottom
			al_draw_filled_ellipse( 25, 29, 1.5, 3, al_map_rgb(255, 15, 0)); //left eye top
			al_draw_filled_ellipse( 40, 29, 3, 3, al_map_rgb(128, 128, 128)); //right eye bottom
			al_draw_filled_ellipse( 40, 29, 1.5, 3, al_map_rgb(255, 15, 0)); //right eye top
			al_draw_line( 31, 29, 31, 37, al_map_rgb(255, 255, 255), 1);//top nose l
			al_draw_line( 35, 29, 35, 37, al_map_rgb(255, 255, 255), 1);//top nose r

			al_draw_line( 31, 37, 28, 40, al_map_rgb(255, 255, 255), 1);//mid nose l
			al_draw_line( 35, 37, 38, 40, al_map_rgb(255, 255, 255), 1);// mid nose r

			al_draw_line( 28, 40, 32, 43, al_map_rgb(255, 255, 255), 1);// bottom nose 1
			al_draw_line( 38, 40, 32, 43, al_map_rgb(255, 255, 255), 1);// bottom nose r

			al_draw_line( 29, 37, 12, 32, al_map_rgb(255, 255, 255), 1);// wisker top l
			al_draw_line( 29, 38, 12, 38, al_map_rgb(255, 255, 255), 1);// wisker middle l
			al_draw_line( 29, 39, 12, 44, al_map_rgb(255, 255, 255), 1);// wisker bottom l

			al_draw_line( 39, 37, 56, 32, al_map_rgb(255, 255, 255), 1);// wisker top r
			al_draw_line( 39, 38, 56, 38, al_map_rgb(255, 255, 255), 1);// wisker middle r
			al_draw_line( 39, 39, 56, 44, al_map_rgb(255, 255, 255), 1);// wisker bottom r

			al_draw_line( 32, 41, 25, 44, al_map_rgb(255, 255, 255), 1);// mouth l
			al_draw_line( 32, 41, 39, 44, al_map_rgb(255, 255, 255), 1);// mouth r

			break;
		case 3: //Left
			al_draw_filled_triangle( 20, 20, 25, 5, 30, 20, al_map_rgb(25, 80, 75));//ear l
			al_draw_filled_triangle( 34, 20, 39, 5, 44, 20, al_map_rgb(25, 80, 75));//ear r

			al_draw_filled_ellipse( 32, 32, 20, 15, al_map_rgb(25, 80, 75)); //body bottom
			al_draw_filled_ellipse( 25, 29, 3, 3, al_map_rgb(128, 128, 128)); //left eye bottom
			al_draw_filled_ellipse( 25, 29, 1.5, 3, al_map_rgb(255, 15, 0)); //left eye top
			al_draw_filled_ellipse( 40, 29, 3, 3, al_map_rgb(128, 128, 128)); //right eye bottom
			al_draw_filled_ellipse( 40, 29, 1.5, 3, al_map_rgb(255, 15, 0)); //right eye top
			al_draw_line( 31, 29, 31, 37, al_map_rgb(255, 255, 255), 1);//top nose l
			al_draw_line( 35, 29, 35, 37, al_map_rgb(255, 255, 255), 1);//top nose r

			al_draw_line( 31, 37, 28, 40, al_map_rgb(255, 255, 255), 1);//mid nose l
			al_draw_line( 35, 37, 38, 40, al_map_rgb(255, 255, 255), 1);// mid nose r

			al_draw_line( 28, 40, 32, 43, al_map_rgb(255, 255, 255), 1);// bottom nose 1
			al_draw_line( 38, 40, 32, 43, al_map_rgb(255, 255, 255), 1);// bottom nose r

			al_draw_line( 29, 37, 12, 32, al_map_rgb(255, 255, 255), 1);// wisker top l
			al_draw_line( 29, 38, 12, 38, al_map_rgb(255, 255, 255), 1);// wisker middle l
			al_draw_line( 29, 39, 12, 44, al_map_rgb(255, 255, 255), 1);// wisker bottom l

			al_draw_line( 39, 37, 56, 32, al_map_rgb(255, 255, 255), 1);// wisker top r
			al_draw_line( 39, 38, 56, 38, al_map_rgb(255, 255, 255), 1);// wisker middle r
			al_draw_line( 39, 39, 56, 44, al_map_rgb(255, 255, 255), 1);// wisker bottom r

			al_draw_line( 32, 41, 25, 44, al_map_rgb(255, 255, 255), 1);// mouth l
			al_draw_line( 32, 41, 39, 44, al_map_rgb(255, 255, 255), 1);// mouth r

			break;
		case 4:
			al_draw_filled_ellipse( 32, 32, 10, 20, al_map_rgb(0, 128, 255)); //body
			al_draw_filled_triangle( 24, 54, 40, 54, 32, 40, al_map_rgb(0, 100, 200));//tail fin
			al_draw_filled_triangle( 18, 34, 24, 28, 24, 40,al_map_rgb(0, 100, 200));//left fin
			al_draw_filled_triangle( 46, 34, 40, 28, 40, 40,al_map_rgb(0, 100, 200));//right fin
			al_draw_filled_ellipse( 30, 20, 2, 2, al_map_rgb(255, 255, 255));//under eye
			al_draw_filled_ellipse( 30, 20, 1, 1, al_map_rgb(0, 0, 0));//top eye
			break;
		}
	}
}

