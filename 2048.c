#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 4

void add_new_number(int mat[SIZE][SIZE], int number)
{
  int i, j, k = 0;
  char fill, fill_2_or_4;
  if (number < 2) // 1 den fazla sayi eklenmesi gerekiyor
  {
    for (i = 0; i < SIZE; i++)
    {
      for (j = 0; j < SIZE; j++)
      {
        if (mat[i][j] == 0 && k < 1)
        {
          fill = rand() % 2;        // dongude dolasilan elemana sayi atayip atamamak
          fill_2_or_4 = rand() % 2; // 2 ya da 4
          if (fill == 1)
          {
            if (fill_2_or_4 == 1)
              mat[i][j] = -4; // - ile veriyoruz cunku yeni atanan sayilarin digerlerinden farkli olmasi icin
            else
              mat[i][j] = -2;
            k++;
          }
        }
      }
    }
  }
  else
  {
    for (i = 0; i < SIZE; i++)
    {
      for (j = 0; j < SIZE; j++)
      {
        if (mat[i][j] == 0 && k < 2)
        {
          fill = rand() % 2;
          if (fill == 1)
          {
            mat[i][j] = -2;
            k++;
          }
        }
      }
    }
  }
}

void print_mat(int mat[SIZE][SIZE], int *score, int *max_score)
{
  // matrisi yazdiriyoruz.
  int i, j;
  printf("\n ");
  for (j = 0; j < SIZE; j++)
  {
    printf("_____");
  }
  printf("  Puaniniz : %d, En Yuksek Puan : %d\n", *score, *max_score);
  for (i = 0; i < SIZE; i++)
  {
    printf("|");
    for (j = 0; j < SIZE; j++)
    {
      if (mat[i][j] == 0)
        printf("    ");
      else if ((mat[i][j] < 0))
      {
        mat[i][j] = -1 * mat[i][j];
        printf("%3d*", mat[i][j]);
      }
      else
        printf("%4d", mat[i][j]);
      printf("|");
    }
    printf("\n ");
    for (j = 0; j < SIZE; j++)
    {
      printf("_____");
    }
    printf("\n");
  }
  printf("\n\n");
}

void fix_minus_numbers(int mat[SIZE][SIZE])
{
  // negatif sayilari pozitif yapiyoruz
  int i, j;

  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      if (mat[i][j] < 0)
        mat[i][j] = -1 * mat[i][j];
    }
  }
}

void rotateMat(int mat[SIZE][SIZE])
{
  // matrisi orijin etrafinda -90 derece donduruyoruz
  int i, j, k, n = SIZE;
  for (i = 0; i < n / 2; i++)
  {
    for (j = i; j < n - i - 1; j++)
    {
      k = mat[i][j];
      mat[i][j] = mat[j][n - i - 1];
      mat[j][n - i - 1] = mat[n - i - 1][n - j - 1];
      mat[n - i - 1][n - j - 1] = mat[n - j - 1][i];
      mat[n - j - 1][i] = k;
    }
  }
}

void shift_numbers(int mat[SIZE][SIZE], int *score)
{
  // sagdan sola sayilari oteleyip eger ayni sayilar denk gelirse topluyoruz
  int i, j;

  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE - 1; j++)
    {
      if (mat[i][j] != 0)
      {
        if (mat[i][j + 1] == 0)
        {
          mat[i][j + 1] = mat[i][j];
          mat[i][j] = 0;
        }
        else if (mat[i][j] == mat[i][j + 1])
        {
          mat[i][j] = 0;
          mat[i][j + 1] = -1 * mat[i][j + 1] * 2;
          *score += -1 * mat[i][j + 1];
        }
      }
    }
  }
}

void shift_numbers_to_L(int mat[SIZE][SIZE], int *score)
{
  rotateMat(mat);
  rotateMat(mat);
  shift_numbers(mat, score);
  rotateMat(mat);
  rotateMat(mat);
}

void shift_numbers_to_R(int mat[SIZE][SIZE], int *score)
{
  shift_numbers(mat, score);
}

void shift_numbers_to_T(int mat[SIZE][SIZE], int *score)
{
  rotateMat(mat);
  rotateMat(mat);
  rotateMat(mat);
  shift_numbers(mat, score);
  rotateMat(mat);
}
void shift_numbers_to_B(int mat[SIZE][SIZE], int *score)
{
  rotateMat(mat);
  shift_numbers(mat, score);
  rotateMat(mat);
  rotateMat(mat);
  rotateMat(mat);
}

void assign_mat_to_prev(int mat[SIZE][SIZE], int prev_mat[SIZE][SIZE])
{
  // matrisin bir onceki durumunu atayan fonksiyon
  int i, j;
  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      prev_mat[i][j] = mat[i][j];
    }
  }
}

void reset_mat(int mat[SIZE][SIZE], int *score, int *max_score)
{
  // matrisi ve skoru sifirliyoruz.
  int i, j;
  *score = 0;
  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      mat[i][j] = 0;
    }
  }
  printf("************\n");
  printf("OYUN SIFIRLANDI!\n");
  printf("************\n");
  add_new_number(mat, 2);
  print_mat(mat, score, max_score);
}

int check_mat(int mat[SIZE][SIZE])
{
  // matristeki herhangi bir eleman 2048 e ulastiysa oyunu bitiriyoruz.
  int i, j, t = 0;
  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      if (mat[i][j] == 2048)
      {
        t += 1;
      }
    }
  }
  return t;
}

void end_game(int mat[SIZE][SIZE], int *max_score, int *play)
{
  // oyunu bitiriyoruz.
  *play = 0;
  printf("************\n");
  printf("OYUNU SONLANDI!\n");
  printf("En Yuksek Puan : %d\n", *max_score);
  printf("Tesekkurler, ismail bayram 2018\n");
  printf("************\n");
}

int main()
{
  srand(time(NULL));
  // tanimlamalar
  char input;
  static int mat[SIZE][SIZE], prev_mat[SIZE][SIZE]; // statik olmasinin sebebi tum elemanlara 0 veriyoruz.
  int *score = malloc(sizeof(int)), *max_score = malloc(sizeof(int)), *play = malloc(sizeof(int)), react_2048 = 0;
  *score = 0;
  *max_score = 0;

  // intro yazilari
  printf("2048'e hosgeldiniz.\n");
  printf("En Yuksek Puan : %d\n", *max_score);
  printf("Tus Bilgileri : \n");
  printf("- Ok tuslari ile sayilari saga, sola, yukariya veya asagiya kaydirabilirsiniz.\n");
  printf("- 'E' tusu ile oyunu bitirip yeni bir oyuna baslayabilirsiniz.\n");
  printf("- 'X' tusu ile en yuksek puani sifirlayip yeni bir oyuna baslayabilirsiniz.\n");
  printf("2018 - ismail bayram\n\n");

  // matrisi baslatiyoruz ve ekrana yazdiriyoruz
  add_new_number(mat, 2);
  print_mat(mat, score, max_score);

  *play = 1;
  while (*play == 1)
  {
    react_2048 = check_mat(mat);
    if (react_2048 > 0) // eger 2048 e ulasildiysa
    {
      printf("TEBRIKLER 2048'e ULASTINIZ!!!!\n");
      end_game(mat, max_score, play);
    }
    input = getchar();
    switch (input)
    {
    case '\033':                         // ok tuslarina ozel karakterleri yakalayip switch case e sokuyoruz
      assign_mat_to_prev(mat, prev_mat); // onceki state i tutan matrise simdiki halini ata
      getchar();
      switch (getchar())
      {
      case 'A':
        shift_numbers_to_T(mat, score);
        break;
      case 'B':
        shift_numbers_to_B(mat, score);
        break;
      case 'C':
        shift_numbers_to_R(mat, score);
        break;
      case 'D':
        shift_numbers_to_L(mat, score);
        break;
      }
      fix_minus_numbers(mat);
      add_new_number(mat, 1);
      if (*score > *max_score)
        *max_score = *score;
      print_mat(mat, score, max_score);
      break;
    case 69: // E
      end_game(mat, max_score, play);
      break;
    case 101: // e
      end_game(mat, max_score, play);
      break;
    case 88: // X
      reset_mat(mat, score, max_score);
      break;
    case 120: // x
      reset_mat(mat, score, max_score);
      break;
    case 114: // r
      print_mat(prev_mat, score, max_score);
      break;
    case 82: // R
      print_mat(prev_mat, score, max_score);
      break;
    default:
      break;
    }
  }
  return 0;
}