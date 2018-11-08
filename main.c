/* ===================================================== *
   C64 Hayvan Tahmin Programi                                   
                                                    
   Environment: cc65 v2.17                           
   Date: Ekim - Kasım 2018                           
 * ===================================================== */

#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "functions.h"

/*** Global Değişkenler ***/
uchar buffer[40];
uchar ch;
struct Node node[TREE_SIZE];
uchar current_node = 0;
uchar num_of_nodes = 0;
uchar num_of_animals = 0;
enum cflag menu_command = null;

/*** Fonksiyon Prototipleri ***/

void new_data_dialog(void);

/*
 * Main
 */

void main(void)
	{
		// Ağaç yapısını hazırla
		reset_screen();
		read_tree(0);
		//debug_test_input();
		//debug_print_tree();

		reset_screen();
		cprintf("\n\r");
		cprintf("Merhaba. Hayvan Tanimlama Programina ho$");
		cprintf("geldin. Bana tarif ettigin hayvani bul- ");
		cprintf("mayi deneyecegim. Bir hayvan du$un.     ");
		cprintf("Hazir olunca baslayalim.\n\r");
		cprintf("\n<DEVAM>\n\r");
		cgetc();

		reset_screen();

		current_node = 0;

		// Ana döngü
		while(1)
		{
			cursor(1);

			// Standart Node
			if(!node[current_node].is_leaf)
			{
				if (wherey()>20)
					reset_screen();

				cprintf("\n\r%s",&node[current_node].data[0]);
				cprintf("\n\rE/H>");
				get_closed_answer();
				
				if (ch==1)
					current_node = node[current_node].left;
				else if (ch==2)
					current_node = node[current_node].right;
			}
			
			// Leaf Node
			else 
			{
				reset_screen();
				cprintf("\n\rBu hayvan bir %s olmali.\n\r", &node[current_node].data[0]);
				cprintf("Bildim mi?");
				cprintf("\n\rE/H>");
				get_closed_answer();
				
				if (ch==1)
				{
					// Doğru cevap başa don
					cprintf("\nI$te yine bildim.!\n\r");
					cprintf("Hadi tekrar ba$layalim.\n\r");
					cprintf("\n<DEVAM>");
					cursor(0);
					cgetc();
					current_node = 0;
					menu_command = reset;
					reset_screen();
					cprintf("I$te yine ba$liyoruz.\n\r");
				}
				else if (ch==2)
					new_data_dialog();
			}
		}
	}

void new_data_dialog(void)
	// Yeni hayvan öğren
	{
		uchar n,p;
		uchar data[40];
		uchar animal[40];
		bool is_left;
		
		cprintf("\n\rTamam. Pes ediyorum. ");

		enter_new_animal:
		cputs("\n\rHangi hayvani dusunmustun?\n\r");
		cprintf(">");
		get_input(animal);
		cprintf("\n\n\r%s ile %s farkini"
			, animal, node[current_node].data);
		cprintf("\n\rbelirten bir evet/hayir sorusu yazar    ");
		cprintf("misin?\n\r>");
		get_input(data);

		cprintf("\n\n\r%s icin dogru cevap hangisi?", animal);
		cprintf("\n\rE/H>");
		get_closed_answer();

		if (ch==1)
			is_left = 1;
		else
			is_left = 0;

		// Son Kontrol
		reset_screen();
		cprintf("\n\r%s:\n\r", animal);
		if (is_left)
			cprintf(" %s > EVET\n\r", data);
		else
			cprintf(" %s > HAYIR\n\r", data);

		n = current_node;
		do {
			p = node[n].parent;
			if(node[p].left == n)
				cprintf(" %s > EVET\n\r", node[p].data);
			else
				cprintf(" %s > HAYIR\n\r", node[p].data);
			n = p;
		} while(n);

		cputs("\n\rDogru anlamis miyim?\n\r");
		cprintf("E/H>");
		get_closed_answer();

		if (ch==1)
		{
			add_node(data, animal, is_left);
			cputs("\n\rSaniyorum ogrendim.");
			cgetc();
			// Reset game
			current_node = 0;
			reset_screen();
		}
		else if (ch==2)
		{
			cursor(0);
			cputs("\n\r<TEKRAR DENE>");
			cgetc();
			
			reset_screen();
			goto enter_new_animal;
		}
	}
