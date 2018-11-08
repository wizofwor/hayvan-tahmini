/* ===================================================== *
   C64 Hayvan Tahmin Programi                                    
                                                    
   Globals                                              
 * ===================================================== */

#ifndef GLOB_VARS
#define GLOB_VARS

/*** Makrolar ***/
#define INPUT_SIZE 40		// Lenght of user input array
#define TREE_SIZE 200		// Number of maxiumum nodes

/*** Tip Tanımları ***/
typedef unsigned char uchar;
typedef enum {False, True} bool;


/*** Global Değişkenler ***/
extern struct Node 					// Veri yapısı
	{
		bool is_leaf;
		uchar data[40];
		uchar left;
		uchar right;
		uchar parent;
	} node[TREE_SIZE];

extern uchar current_node;			// Aktif node
extern uchar num_of_nodes; 			// Nodların toplam sayısı
extern uchar num_of_animals;		// Bilinen hayvanların toplam sayısı
extern uchar buffer[40]; 			// Metin girişi için tampon
extern uchar ch; 					// Tek karekter girişi için tampon

extern enum cflags { null, reset, save, list, quit} menu_command;

#endif