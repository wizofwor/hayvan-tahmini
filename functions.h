#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "common.h"

void reset_screen(void);
void update_header(void);

void get_closed_answer(void);
	/* Evet/Hayır sorusu 

	Cevap evet ise ch=1,
	Cevap hayır ise ch=2,
	Menü komutu verildiyse ch=0 yapar. */

void get_input(uchar * s);
	/* char array (string) veri girişi:
	
	Enter'a basılana kadar girilen karakterleri
	verilen pointer'a kaydeder. */

bool check_for_menu_command(void);
	/* ch değişkenini menü girişleriyle karşılaştırır.
	eşleşme durumunda menu_command bayrağını set eder */

// --- Temel Fonksiyonlar ---------------------------------

void char_cpy(char * destination, char * source);
	/* char array copy

	null terminating diziler için src'yi dest'e kopyalar. */

void concat(char * destination, char * source);
	/* char array concatanete

	null terminating diziler için src'yi dest'in sonuna ekler.
	Boyut kontrolü yapmaz. */
	

// --- Veri Manipulasyonu ---------------------------------

void add_node(uchar *data, uchar *animal, bool is_left);
	/* Listeye yeni bir soru ve hayvan ve soru ekler.
		
	1) Yeni hayvanı ekler
	2) Geçerli hayvanı yeni bir node'a kopyalar
	3) Gererli hayvanın yerine yeni soruyu kaydeder */

void print_tree(void);
	/* Hafızaki hayvanların listesini basar. */

void do_menu_command(void);
	/* Menu Komutlarını İşle */

// --- Dosya Arayüzü --------------------------------------

void read_tree(uchar *id);

void write_tree(uchar *id);

// --- DEBUG ----------------------------------------------

#ifdef DEBUG

void debug_test_input(void);
void debug_print_tree(void);

#endif



#endif // FUNCTIONS_H
