#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
void malenaduze(char* klucz)//zamiana malych liter na duze
{
	for (int i = 0; i < strlen(klucz); i++)
	{
		if (islower(klucz[i]))
			klucz[i] = toupper(klucz[i]);
	}
}
void jnai(char* klucz)//zamiana "J" na "I"
{
	for (int i = 0; i < strlen(klucz); i++)
	{
		if (klucz[i] == 'J')
			klucz[i] = 'I';
	}
}
void usunznaki(char* klucz)
{
	int p = -1, q = 0;
	while (klucz[++p] != '\0')
		if (klucz[p] != ' ' && klucz[p] != '.' && klucz[p] != ',' && klucz[p] != '!' && klucz[p] != '?' && klucz[p] != ':')
			klucz[q++] = klucz[p];
	klucz[q] = '\0';
}
void macierz(char* klucz, char play[5][5]) //funkcja która tworzy macierz z kluczem i alfabetem
{
	const char* alfabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	strcat(klucz, alfabet);//laczenie dwoch tablic w jedna
	int roz, k, x;
	char macierz[25];
	roz = strlen(klucz);
	macierz[0] = klucz[0];
	k = 1;
	//petla ktora usuwa powtarzajace sie znaki
	for (int l = 1; l < roz; l++)
	{
		x = 0;
		for (int j = 0; j < k; j++)
		{
			if (klucz[l] == macierz[j])
				x = 1;
		}
		if (x == 0)
		{
			macierz[k] = klucz[l];
			k++;
		}
	}
	int h = 0;
	//wype³nienie macierzy
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			play[i][j] = macierz[i + j + h];
		}
		h = h + 4;
	}
}
void szyfrowanie(char play[5][5], char* tekst, char* szyfrogram)
{
	int w1, w2, k1, k2;
	for (int i = 0; i < strlen(tekst); i = i + 2)
	{
		w1 = w2 = k1 = k2 = 0;
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (tekst[i] == play[j][k])
				{
					w1 = j;
					k1 = k;
				}
				if (tekst[i + 1] == play[j][k])
				{
					w2 = j;
					k2 = k;
				}
			}
		}
		if (w1 == w2 && k1 != k2)
		{
			if (k1 == 4)
			{
				szyfrogram[i] = play[w1][0];
				szyfrogram[i + 1] = play[w2][k2 + 1];
			}
			else if (k2 == 4)
			{
				szyfrogram[i] = play[w1][k1 + 1];
				szyfrogram[i + 1] = play[w2][0];
			}
			else
			{
				szyfrogram[i] = play[w1][k1 + 1];
				szyfrogram[i + 1] = play[w2][k2 + 1];
			}
		}
		else if (k1 == k2 && w1 != w2)
		{
			if (w1 == 4)
			{
				szyfrogram[i] = play[0][k1];
				szyfrogram[i + 1] = play[w2 + 1][k2];
			}
			else if (w2 == 4)
			{
				szyfrogram[i] = play[w1 + 1][k1];
				szyfrogram[i + 1] = play[0][k2];
			}
			else
			{
				szyfrogram[i] = play[w1 + 1][k1];
				szyfrogram[i + 1] = play[w2 + 1][k2];
			}
		}
		else
		{
			szyfrogram[i] = play[w1][k2];
			szyfrogram[i + 1] = play[w2][k1];
		}
	}
}
void deszyfrowanie(char play[5][5], char* tekst, char* tekstjawny)
{
	int w1, w2, k1, k2;
	for (int i = 0; i < strlen(tekst); i = i + 2)
	{
		w1 = w2 = k1 = k2 = 0;
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (tekst[i] == play[j][k])
				{
					w1 = j;
					k1 = k;
				}
				if (tekst[i + 1] == play[j][k])
				{
					w2 = j;
					k2 = k;
				}
			}
		}
		if (w1 == w2 && k1 != k2)
		{
			if (k1 == 0)
			{
				tekstjawny[i] = play[w1][4];
				tekstjawny[i + 1] = play[w2][k2 - 1];
			}
			else if (k2 == 0)
			{
				tekstjawny[i] = play[w1][k1 - 1];
				tekstjawny[i + 1] = play[w2][4];
			}
			else
			{
				tekstjawny[i] = play[w1][k1 - 1];
				tekstjawny[i + 1] = play[w2][k2 - 1];
			}
		}
		else if (k1 == k2 && w1 != w2)
		{
			if (w1 == 0)
			{
				tekstjawny[i] = play[4][k1];
				tekstjawny[i + 1] = play[w2 - 1][k2];
			}
			else if (w2 == 0)
			{
				tekstjawny[i] = play[w1 - 1][k1];
				tekstjawny[i + 1] = play[4][k2];
			}
			else
			{
				tekstjawny[i] = play[w1 - 1][k1];
				tekstjawny[i + 1] = play[w2 - 1][k2];
			}
		}
		else
		{
			tekstjawny[i] = play[w1][k2];
			tekstjawny[i + 1] = play[w2][k1];
		}
	}
}
int main()
{
	FILE* PK, * KP;
	char teks[2000];
	char  playfair[5][5];
	char t[50];
	char szyfr[2000];
	const char* iks = "X";
	int il = 0, wybor;
	printf("Witaj w programie 'Kalkulator Szyfru Playfaira', podaj klucz:\n");
	gets(t);
	usunznaki(t);
	malenaduze(t);
	jnai(t);
	printf("Wybierz: \n1.Szyfracja\n2.Deszyfracja\nPrzed przystapieniem do pracy z programem upewnij sie, ze masz w folderze z kodem zrodlowym plik 'tekst.txt'\n");
	do
	{
		scanf_s("%d", &wybor);
		switch (wybor)
		{
		case 1:
			macierz(t, playfair);
			printf("Oto utworzona macierz:\n");
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
					printf("%c	", playfair[i][j]);
				printf("\n");
			}
			if ((PK = fopen("tekst.txt", "r")) == NULL)
			{
				printf("Nie moge otworzyc pliku tekst.txt do zapisu!\n");
				exit(1);
			}
			fgets(teks, 2000, PK);
			usunznaki(teks);
			if (strlen(teks) % 2 != 0)
				strcat(teks, iks);
			malenaduze(teks);
			jnai(teks);
			szyfrowanie(playfair, teks, szyfr);
			if ((KP = fopen("rezultat.txt", "w")) == NULL)
			{
				printf("Nie moge otworzyc pliku rezultat.txt do zapisu!\n");
				exit(1);
			}
			for (int i = 0; i < strlen(teks); i++)
				fprintf(KP, "%c", szyfr[i]);
			printf("Szyfracja ukonczona, sprawdz plik 'rezultat.txt' \n");
			fclose(KP);
			fclose(PK);
			break;
		case 2:
			macierz(t, playfair);
			printf("Oto utworzona macierz:\n");
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
					printf("%c	", playfair[i][j]);
				printf("\n");
			}
			if ((PK = fopen("tekst.txt", "r")) == NULL)
			{
				printf("Nie moge otworzyc pliku tekst.txt do zapisu!\n");
				exit(1);
			}
			fgets(teks, 2000, PK);
			usunznaki(teks);
			if (strlen(teks) % 2 != 0)
				strcat(teks, iks);
			malenaduze(teks);
			jnai(teks);
			deszyfrowanie(playfair, teks, szyfr);
			if ((KP = fopen("rezultat.txt", "w")) == NULL)
			{
				printf("Nie moge otworzyc pliku rezultat.txt do zapisu!\n");
				exit(1);
			}
			for (int i = 0; i < strlen(teks); i++)
				fprintf(KP, "%c", szyfr[i]);
			printf("Deszyfracja ukonczona, sprawdz plik 'rezultat.txt' \n");
			fclose(KP);
			fclose(PK);
			break;
		default:
			printf("Zly wybor!! Sprobuj ponownie:\n");
			continue;
		}
	} while (wybor != 1 && wybor != 2);
	return 0;
}