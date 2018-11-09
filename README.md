# Hayvan Tahmini

- [Hayvan Tahmini nedir?](#hayvan tahmini nedir?)  
- [Nasil Çalışıyor](##Nasıl Çalışıyor)  
- [Nasıl Denerim](##Nasıl Denerim)  
- [Güncellemeler](##Güncellemeler)  
- [Referanslar](#Referanslar)

## Hayvan Tahmini nedir?

Hayvan Tahmini oyunu bilgisayar tarihindeki ilk yapay zeka denemelerinden biridir.

Bilgisayar ve insanın olarak karşılıklı yazıştığı ilk program olarak Joseph Weizenbaum'un 60'larda yazdığı *Eliza*'dır. Hayvan tahmin programı ise Eliza'dan biraz daha akıllıdır çünkü hatalarından öğrenerek bilgisini arttırabilir.

Hayvan tahmin programının en ünlü versiyonu John Walker'ın 1975'de UNIVAC için yazdığı *ANIMAL* olsa da ben en eski versiyon olarak Arthur Luehrmann'ın 1970'lerde yazdığı *JACKASS*'e ulaşabildim.

## Nasıl Çalışıyor

Program hayvan bilgisini binary tree yapısı üzerinde tutuyor.

Klasic binary tree yapısına ek olarak is_leaf ve parent bilgisini de ilave ettim.

    extern struct Node 			
	{
		bool is_leaf;
		uchar data[40];
		uchar left;
		uchar right;
		uchar parent;
	}

Doğru cevapta `left`, yanlış cevapta `right` node'a gidiliyor. Ağın sonuna geldiğimi de `is_leaf` bilgisine bakarak anlıyorum.

                             Suda mi yaşar?
                              /         \ 
                             /           \
                  Memeli midir?           Uçar mı?
                 /    \                    /             \
                /      \                  /               \
       Balık ağına   Dokungaçları      Gececi midir?   Evcilleştirilebilir mi?
       takılır mı?    var mıdır:          /    \            /    \
        /      \        /     \          /      \          /      \
      Yunus  Balina  Ahtapot  Köpek   Yarasa  Papağan   Köpek    Aslan
                              Balığı 


## Nasıl Denerim

Derlenmiş programı disk.d64 imajını kullanarak açabilirsiniz. Programı sadece C64 üzerinde denedim ancak 128'de de çalışması gerekir.

makefile OSX El Capitan üzerinde cc65 v2.17 ile denenmiştir. 

   
## Güncellemeler
*9.11.2014*   
string.h kütüphanesi kaldırıldı.
strcpy ve strcat fonksiyonları yerine char_cpy ve concat fonksiyonları yazıldı.

stdlib.h kütüphanesi kaldırıldı.
malloc ve itoa fonksiyonlarının kullandığı yerler yeniden düzenlendi.

Bu aşamada programın boyutu 10KB'a indi.

## Referanslar
[The Animal Episode](http://www.fourmilab.ch/documents/univac/animal.html)

[GUESS THE ANIMAL - A DECISION-TREE IN YOUR ATARI] (https://www.atarimagazines.com/v4n12/Animal.html)

[AI Animals / perlMonks ](https://www.perlmonks.org/?node_id=195991)  


