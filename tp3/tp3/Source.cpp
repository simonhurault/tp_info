// Created by Alain Redlinger on 03/10/2016.
// Copyright © 2016 Alain Redlinger. All rights reserved.
//
// Cet exemple de code initialise un tableau avec des valeurs aléatoires
// approximativement équiprobables et comprises dans un intervalle [-MAXVAL, +MAXVAL[
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
// Dimension des tableaux de test
#define N 10
// Limite des valeurs des éléments des tableaux afin de faciliter le débogage
// ou bien de produire des données de test spécifiques
#define MAXVAL 7


//Cette fonction repond a l'exercice 1 du TP
// Param : un tableau, taille du tableau, 2 pointeur vers un entier 
void minMax(int* arr, int size, int* iMax, int* iMin)
{
	int i; //variable de boucle 
	*iMax = 0;
	*iMin = 0; // On initialise ces indices comme étant celle du premier élément du tableau
	for (i = 1; i < size; i++)
	{
		if (arr[i] > arr[*iMax])
		{
			*iMax = i;
		}
		else if (arr[i] < arr[*iMin])
		{
			*iMin = i;
		}
	}
}


// Cette fonction repond a l'exercice 2 du TP
// Param : un tableau et sa taille
void sort(int* arr, int size)
{
	int iMin, iMax; // Variable stockant l'indice du min et max du tableau
	int begining; // Variable stockant l'indice du debut du tableau considere
	int stock; // Variable permettant l'echange de 2 valeur
	begining = 0;
	while(size - begining >= 1)
	{
		minMax(arr + begining, size - begining, &iMax, &iMin); // On utilise minMax en passant en parametre l'adresse du tableau a partir du debut considere
																	 // On definit la taille comme etant l'indice de fin au quel on soustrait l'indice de debut
		iMin += begining;
		iMax += begining; // La fonction minMax considere l'indice begining comme etant 0 on ajoute donc la valeur de begining

		// On place le minimum au debut du tableau 
		stock = arr[iMin];
		arr[iMin] = arr[begining];
		arr[begining] = stock;

		// Dans le cas ou iMax etait la premiere valeur du tableau
		if (iMax == begining)
		{
			iMax = iMin; // On met a jour son nouvel indice
		}


		// On place le maximum à la fin du tableau 
		stock = arr[iMax];
		arr[iMax] = arr[size - 1];
		arr[size - 1] = stock;

		size--;
		begining++;
	}
}


// Cette fonction repond a l'exercice 3 du TP
// Param : un tableau et sa taille
int countDuplication(int* arr, int size)
{
	int i;
	int cpt; // compteur de doublon
	cpt = 1;
	for (i = 0; i < size - 1; i++)
	{
		if (arr[i] != arr[i + 1])
		{
			cpt++;
		}
	}
	return cpt;
}


// Cette fonction repond a l'exercice 4 du TP
// Param : le tableau initial, le tableau ou l'on souhaite mettre les valeur et la taille des tableaux qui est la meme
void arrWithoutDuplication(int* arr, int* newArr, int size)
{
	int i;
	int cpt; // compteur permettant de stocker le prochain indice ou l'on mettra une valeur dans le nouveau tableau
	int nbrOfValue = countDuplication(arr, size); // nombre de valeur differente dans le tableau
	cpt = 0; 

	// On rempli le nouveau tableau sans les doublons que jusqu'a l'avant dernier element pour ne pas sortir de l'indice max du tableau
	for (i = 0; i < size - 1; i++)
	{
		if (arr[i] != arr[i + 1])
		{
			newArr[cpt] = arr[i];
			cpt++;
		}
	}

	// Si on a pas fini de mettre toute les valeur c'est qu'il faut egalement mettre la derniere du tableau initial
	if(nbrOfValue >= cpt)
		newArr[cpt] = arr[size - 1];

	// On rempli le reste du tableau avec la valeur de INT_MIN
	for (i = cpt + 1; i < size; i++)
		newArr[i] = INT_MIN;
}


void removeDuplications(int* arr, int size)
{
	int i;
	int stock; // variable de stockage pour echanger des valeurs
	int cpt; // compteur stockant l'endroit actuel du tableau ou l'on met les valeurs
	cpt = 0;
	for (i = 0; i < size - 1; i++)
	{
		if (arr[i] != arr[cpt + 1])
		{
			arr[i] = INT_MIN;
		}
		else
		{
			stock = arr[cpt];
			arr[cpt] = arr[i];
			arr[i] = stock;
			cpt++;
		}
		printf("\n \n tableau pour i = %d et cpt = %d \n", i, cpt);
		for (int j = 0; j < N; ++i)
			printf("%d ", arr[i]);
	}
}

int main()
{
	int t1[N]; // Tableau de N nbr entiers
	int i; // Indice de parcours de tableau

		   // Initialisation du générateur aléatoire
		   // (une nouvelle série de valeurs à chaque exécution)
	unsigned int seed = (unsigned int)time(0) % 10000;
	// On peut forcer une valeur précédente pour retrouver les mêmes nombres
	// seed = 3756;
	srand(seed);
	printf("RAND_MAX=%d\n", RAND_MAX);
	// On initialise le tableau avec des valeurs aléatoires comprises
	// dans l'intervalle ]-MAXVAL, +MAXVAL[
	for (i = 0; i < N; ++i)
		t1[i] = (rand() % 2 ? (rand() % MAXVAL) : -(rand() % MAXVAL));
	// On affiche le tableau, volontairement dans une boucle séparée
	printf("\nTableau t1:\n");
	for (i = 0; i < N; ++i)
		printf("%d ", t1[i]);
	printf("\n%d element(s).\n", N);

	// Exercice 1
	int iMax, iMin; // Variable stockant l'indice du min et max du tableau
	minMax(t1, N, &iMax, &iMin);
	printf("\n Exercice 1 : \n L'indice du minimum est %d, sa valeur est %d", iMin, t1[iMin]);
	printf("\n L'indice du maximum est %d, sa valeur est %d \n", iMax, t1[iMax]);

	// Auto verification de l'exercice
	for (i = 0; i < N; i++)
	{
		assert(t1[i] <= t1[iMax]);
		assert(t1[i] >= t1[iMin]);
	}

	// Exercice 2
	sort(t1, N);
	printf("\n Exercice 2 : \n Une fois trie le tableau t1 vaut : \n");
	for (i = 0; i < N; ++i)
		printf("%d ", t1[i]);

	// Auto verification de l'exercice
	for (i = 0; i < N - 1; i++)
	{
		assert(t1[i] <= t1[i + 1]);
	}

	// Exercice 3
	int duplications; // Variable stockant le nombre de doublon dans le tableau 
	duplications = countDuplication(t1, N);
	printf("\n \n Exercice 3 : \n Il y a %d valeurs differente dans le tableau \n", duplications);

	// Exercice 4 
	int newArr[N];
	arrWithoutDuplication(t1, newArr, N);
	printf("\n Exercice 4 : \n Le nouveau tableau sans les doublons est : \n");
	for (i = 0; i < N; ++i)
		printf("%d ", newArr[i]);

	// Auto verification
	for (i = 0; i < duplications - 1; i++)
	{
		assert(newArr[i] < newArr[i + 1]);
	}

	// Exercice 5

	printf("\n \n Exercice 5 : \n L'ancien tableau sans les doublons est : \n");
	removeDuplications(t1, N);
	/*for (i = 0; i < N; ++i)
		printf("%d ", t1[i]);
		*/
	return 0;
}