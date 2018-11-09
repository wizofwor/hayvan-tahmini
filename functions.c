/* ===================================================== *
   C64 Hayvan Tahmin Programi                                    
                                                    
   Fonksiyonlar                                              
 * ===================================================== */

//#define DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "functions.h"

void reset_screen(void)
	{
		clrscr();
		gotoxy(0,0);
		cclear(40);
		cprintf("  **** Hayvan Tanimlama Programi ****   ");
		cclear(80);
		cclear(255);
		// footer
		gotoxy(0,24);
		cprintf("   F1:Reset F3:Liste F5:Kayit STOP:Cikis ");
		gotoxy(0,4);

		update_header();
	}

void update_header(void)
	{
		uchar x, y;
		x = wherex();
		y = wherey();

		gotoxy(0,3);
		cprintf(" Bilinen %d hayvan, ", num_of_animals);
		cprintf("%d serbest dugum", TREE_SIZE-num_of_nodes);

		gotoxy(x,y);
	}

void get_input(uchar * s)
	{
		const uchar k_spc = 32;
		const uchar k_del = 20;
		const uchar k_qm = 63;
		//uchar *pclue = (uchar *)0x0400;
		uchar i = 0;

		cursor(1);

		do 
		{
			ch = cgetc();

			if (check_for_menu_command())
				{
					do_menu_command();
					break;
				}

			if (ch == k_del)
			{
				if(i>0)
				{
					gotox(wherex()-1);
					cputc(k_spc);
					gotox(wherex()-1);
					*s--;
					i--;
				}
			}
			else if (ch == '\n') 
			{
				*s++ = '\0';
				i++;
				break;
			}
			else if (i<INPUT_SIZE &&  ((ch>=65 && ch<=90)
				|| (ch>=193 && ch<=218) || ch==k_spc) || (ch==k_qm))
			{ 
				*s++ = ch;
				i++;
				cputc(ch);
			}
		} while (1);
		
	}

void get_closed_answer(void)
	{
		while(1)
		{
			ch = cgetc();

			if (check_for_menu_command())
			{
				do_menu_command();
				ch = 0;
				return;
			}
			else if (ch=='e')
			{
				cprintf("E\n\r");
				ch = 1;
				return;
			}
			else if (ch=='h')
			{
				cprintf("H\n\r");
				ch = 2;
				return;
			}
		}
	}

bool check_for_menu_command(void)
	{
		const uchar c_f1 = 133;
		const uchar c_f3 = 134;
		const uchar c_f5 = 135;
		const uchar c_esc = 3;

		if (ch==c_f1)
		{
			menu_command = reset;
			return(1);
		}
		else if (ch==c_f3)
		{
			menu_command = list;
			return(1);
		}
		else if (ch==c_f5)
		{
			menu_command = save;
			return(1);
		}
		else if (ch==c_esc)
		{
			menu_command = quit;
			return(1);
		}
		else
			menu_command = null;
			return(0);
	}

void do_menu_command(void)
	{
		if (menu_command == reset)
		{
			reset_screen();
			cprintf("\n\rBasa donmek istedigine emin misin?");
			cprintf("\n\rE/H>");

			get_closed_answer();
			if (ch==1)
			{
				current_node = 0;
				menu_command = null;
				reset_screen();
			}
			else if (ch==2)
			{
				cprintf("\n\rIptal edildi. <DEVAM>\n\r");
				menu_command = null;
				cgetc();
				reset_screen();
			}
		}
		else if (menu_command == save)
		{
			reset_screen();
			cprintf("\n\rOgrendiklerimi diske kaydedeyim mi?\n\r");
			cprintf("\n\rE/H> ");
			get_closed_answer();

			if (ch==1)
			{
				write_tree(0);
				menu_command = null;
				reset_screen();
			}
			else if (ch==0)
			{
				cprintf("\n\rIptal edildi.\n\r");
				cgetc();
				menu_command = null;
				reset_screen();
			}
		}
		else if (menu_command == list)
		{
			cursor(0);
			print_tree();
			//debug_print_tree();
			menu_command = null;
		}
		else if (menu_command == quit)
		{
			reset_screen();
			cprintf("\n\rCikmak istediginden emin misin?");
			cprintf("\n\rE/H> ");
			
			get_closed_answer();

			if (ch==1)
			{
				exit(0);
			}
			else if (ch==2)
			{
				cprintf("\n\rIptal edildi. <DEVAM>\n\r");
				menu_command = null;
				cgetc();
				reset_screen();
			}
		}
		else
			menu_command = null;
	}

// --- Temel Fonksiyonlar ---------------------------------

void char_cpy(char * dest, char * src)
	{
		while(*src)
			*dest++ = *src++;
		*dest = '\0';
	}

void concat(char * dest, char * src)
	{
		char i;
		while(*dest)
			*dest++;
		while(*src)
			*dest++ = *src++;
		*dest = '\0';
	}



// --- Veri Manipulasyonu ---------------------------------

void add_node(uchar *data, uchar *animal, bool is_left)
	{
		int n = num_of_nodes;

		struct Node *ptr_target;
		ptr_target = &node[current_node];

		// add new animal
		node[n].is_leaf=1;
		char_cpy(node[n].data, animal);
		node[n].left=NULL;
		node[n].right=NULL;
		node[n].parent=current_node;

		num_of_animals++;
		num_of_nodes++;

		// copy old animal
		node[n+1] = *ptr_target; //node[current_node];
		node[n+1].parent = current_node;

		num_of_nodes++;

		// update current node with data
		ptr_target->is_leaf=0;
		char_cpy(ptr_target->data, data);
		if(is_left)
			{
			ptr_target->left=n;
			ptr_target->right=n+1;
			}
		else
			{
			ptr_target->left=n+1;
			ptr_target->right=n;
			}

		update_header();
	}								

void print_tree(void)
	{
		uchar i, j;
		const uchar lim = 20; // sayfada gosterilecek kayit
		i = 0;
		j = 0;

		reset_screen();

		cprintf("\n\r");
		cprintf("Bildigim Hayvanlar:\n\r");
		cprintf("===================\n\r");

		for (i=0; i<num_of_nodes; i++)
		{
			if (node[i].is_leaf)
					cprintf("%s, ", &node[i].data);
		}
		cprintf("%s\n\n\r", &node[i+1].data);

		cprintf("<DEVAM>");
		cgetc();
		reset_screen();
	}

// --- Dosya Arayüzü --------------------------------------

void write_tree(uchar *id)
	{
		uchar *buffer;
		uchar *file_name;
		FILE *file;
		uchar i;

		buffer = malloc(1 * sizeof(uchar));
		file_name = malloc(8 * sizeof(uchar));

		// Dosya ismini hesapla
		itoa((uchar)id, buffer, 10);
		char_cpy(file_name,"tdat");
		concat(file_name,buffer);
		
		cprintf("\n\rVeri dosyasi aciliyor...");
		_filetype = 's';
		if(file = fopen(file_name, "w"))
			{
				cprintf("\n\rVeri yaziliyor... ");
				// Nodların sayısı
				fwrite(&num_of_nodes, sizeof(uchar), 1, file);
				fwrite(&num_of_animals, sizeof(uchar), 1, file);
				// Nod verisi
				for(i=0; i<num_of_nodes; i++)
					{
					fwrite(&node[i], sizeof(struct Node), 1, file);
					gotox(wherex()-3);
					cprintf("%%%2d",(100*(i+1)/num_of_nodes));
					}
				if(fwrite == 0)
					cprintf("\n\rVeri yazilirken bir hata olustu.");
				fclose(file);
				cprintf("\n\rOk.");
			}
		else
			{
				cprintf("\n\r'%s' acilirken bir hata olustu.",file_name);
			}
		cgetc();
	}

void read_tree(uchar *id)
	{
		uchar *buffer;
		uchar *file_name;
		FILE *file;
		uchar i;

		buffer = malloc(1 * sizeof(uchar));
		file_name = malloc(8 * sizeof(uchar));

		// Dosya ismini hesapla
		itoa((uchar)id, buffer, 10);
		char_cpy(file_name,"tdat");
		concat(file_name,buffer);

		i=0;
		cprintf("\n\rVeri dosyasi aciliyor...");
		_filetype = 's';
		if(file = fopen(file_name, "r"))
		{
			cprintf("\n\rVeriler aliniyor...    ");
			fread(&num_of_nodes, sizeof(uchar), 1, file);
			fread(&num_of_animals, sizeof(uchar), 1, file);
			for(i=0; i<num_of_nodes; i++)
			{
				fread(&node[i], sizeof(struct Node), 1, file);
				gotox(wherex()-3);
				cprintf("%%%2d",(100*(i+1)/num_of_nodes));
				if(feof(file)) break;
			}
			fclose(file);
			cprintf("\n\rOk.");
		}
		else
		{
			cprintf("\n\rDosya okunamadi.");
			cgetc();
		}
	}

// --- DEBUG ----------------------------------------------

#ifdef DEBUG

void debug_test_input(void)
	{
		// Initialize tree
		node[0].is_leaf=0;
		arr_cpy(node[0].data, "Suda mi yasar?");
		node[0].left=1;
		node[0].right=2;
		node[0].parent=NULL;

		node[1].is_leaf=1;
		arr_cpy(node[1].data, "Kopek Baligi");
		node[1].left=NULL;
		node[1].right=NULL;
		node[1].parent=0;

		node[2].is_leaf=1;
		arr_cpy(node[2].data, "Aslan");
		node[2].left=NULL;
		node[2].right=NULL;
		node[2].parent=0;

		num_of_nodes= 3;
		num_of_animals= 2;

		// Add further nodes
		current_node=1;
		add_node("Memeli midir?","Balina",1);
		current_node=2;
		add_node("Ucar mi?","Papagan",1);
		current_node=3;
		add_node("Balik agina takilabilir mi?","Yunus",1);
		current_node=4;
		add_node("Dokungaclari var midir?","Ahtapot",1);
		current_node=5;
		add_node("Gececi midir?","Yarasa",1);
		current_node=6;
		add_node("Evcillestirilebilir mi?","Kopek",1);
	}

void debug_print_tree(void)
	{
		uchar i, j;
		const uchar lim = 10; // sayfada gosterilecek kayit
		i = 0;
		j = 0;

		reset_screen();

		cprintf("ID                    Data   P   L   R\n\r");
		cprintf("--------------------------------------\n\r");
		for (i=0; i<num_of_nodes; i++)
		{
			if(!node[i].is_leaf)
			{
				cprintf("%2.d %23.23s %3d %3d %3d \n\r",
					i,
				 	node[i].data,
				 	node[i].parent,
				 	node[i].left,
				 	node[i].right
				 	);
				if (j++ == lim)
				{
					cprintf("<MORE>\n\r");
					cgetc();
					reset_screen();
				}
			}
		}
		cputs("\n\rHayvanlar\n\r");
		for (i=0; i<num_of_nodes; i++)
		{
			if(node[i].is_leaf)
			{
				cprintf("%2.d %23.23s %3d %3d %3d \n\r",
					i,
				 	node[i].data,
				 	node[i].parent,
				 	node[i].left,
				 	node[i].right
				 	);
				if (j++ == lim)
				{
					cprintf("<MORE>\n\r");
					cgetc();
					clrscr();
					reset_screen();
				}
			}
		}


		cprintf("<END>\n\r");
		cgetc();
		reset_screen();
	}

#endif