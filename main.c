/**
 * @mainpage
 * Strona zawiera dokumentację programu do symulacji struktury <b>drzewa BST</b>
 **/
/**
 * @file main.c
 * @brief Główny plik programu
 **/

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#define globalnyodstep 5 ///< Globalna zmienna służaca do wyswietlania drzewa w oknie konsoli

float proces;           ///< Zmienna globalna przechowujaca czas operacji
int menu();             ///< Deklaracja pustej funkcji, aby wyeliminować ostrzeżenie o wywoływaniu nieistniejącej funkcji
void szukaj_elementu(); ///< Deklaracja pustej funkcji, aby wyeliminować ostrzeżenie o wywoływaniu nieistniejącej funkcji

/** @struct node
 *   @brief Główna struktura drzewa BST
 *   @var data - zmienna przechowująca wartość elementu
 *   @var left_child - wskaźnik na lewy (mniejszy, bądź równy) element
 *   @var right_child - wskaźnik na prawy (większy) element
 **/
struct node
{
    int data;
    struct node *right_child;
    struct node *left_child;
};

/** @struct node
    @struct *search
   @brief struktura przeszukująca drzewo w poszukiwaniu danej wartości
    @see struct node
  @param struct node *root - wskaźnik na pierwszy element struktury
  @param x - szukany element
**/
struct node *search(struct node *root, int x)
{
    if (root == NULL || root->data == x)
        return root;
    else if (x > root->data)
        return search(root->right_child, x);
    else
        return search(root->left_child, x);
}
/** @struct node
    @struct *find_minimum
   @brief struktura przeszukująca drzewo w poszukiwaniu najmniejszej wartości
  @param struct node *root - wskaźnik na pierwszy element struktury
**/
struct node *find_minimum(struct node *root)
{
    if (root == NULL)
        return NULL;
    else if (root->left_child != NULL)
        return find_minimum(root->left_child);
    return root;
}
/** @struct node
    @struct *new_node
    @brief struktura alokująca miejsce w pamięci dla drzewa
    @param x - wstawiany element
    @return p - zwracamy adres pierwszej komórki struktury
**/
struct node *new_node(int x)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = x;
    p->left_child = NULL;
    p->right_child = NULL;
    return p;
}

/** @struct node
    @struct *delete
   @brief struktura usuwająca element z drzewa
    @see struct node
  @param struct node *root - wskaźnik na pierwszy element struktury
  @param x - element do usunięcia
**/
struct node *delete_el(struct node *root, int x)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (x > root->data)
    {
        root->right_child = delete_el(root->right_child, x);
    }
    else if (x < root->data)
    {
        root->left_child = delete_el(root->left_child, x);
    }
    else
    {
        if (root->left_child == NULL && root->right_child == NULL)
        {
            root->data = 0;
            return NULL;
        }
        else if (root->left_child == NULL)
        {
            struct node *temp;
            if (root->left_child == NULL)
            {
                temp = root->right_child;
                root->data = temp->data;
                if (temp->left_child != NULL)
                {
                    root->left_child = delete_el(temp->left_child, temp->data);
                    root->right_child = delete_el(temp->left_child, temp->data);
                }
                if (temp->right_child != NULL)
                {
                    root->right_child = delete_el(temp->right_child, temp->data);
                    root->right_child = delete_el(temp->right_child, temp->data);
                }
                /*if(temp->left_child == NULL){
                root->right_child = delete_el(temp->right_child, temp->data);
                //root->right_child = delete_el(temp->right_child,temp->data);
                }*/
                if (temp->right_child == NULL)
                {
                    root->left_child = delete_el(temp->left_child, temp->data);
                    root->right_child = delete_el(temp->right_child, temp->data);
                }
                return root;
            }
        }
        else if (root->right_child == NULL)
        {
            struct node *temp;
            if (root->right_child == NULL)
            {
                temp = root->left_child;
                root->data = temp->data;
                if (temp->right_child != NULL)
                {
                    root->right_child = delete_el(temp->right_child, temp->data);
                    root->left_child = delete_el(temp->left_child, temp->data);
                }
                else if (temp->left_child != NULL)
                {
                    root->left_child = delete_el(temp->left_child, temp->data);
                    root->left_child = delete_el(temp->left_child, temp->data);
                }
                /*if(temp->right_child == NULL){
                     root->left_child = delete_el(temp->left_child, temp->data);
                     //root->left_child = delete_el(temp->left_child,temp->data);
                }*/
                else if (temp->left_child == NULL)
                {
                    root->right_child = delete_el(temp->right_child, temp->data);
                    root->left_child = delete_el(temp->right_child, temp->data);
                }
                else
                {
                    delete_el(temp->left_child, temp->data);
                }

                return root;
            }
            else
            {
                temp = root->right_child;
                root->data = temp->data;
                root->right_child = delete_el(root->right_child->right_child, temp->data);
                return root;
            }
        }
        else
        {
            struct node *temp = find_minimum(root->right_child);
            root->data = temp->data;
            root->right_child = delete_el(root->right_child, temp->data);
        }
    }

    return root;
}

/** @struct node
    @struct *insert
   @brief struktura dodająca element do drzewa. Jeżeli element będzie pierwszy w strukturze, zostanie wywołana funkcja new_node() z parametrem x.
    @see struct node
    @see struct new_node
  @param struct node *root - wskaźnik na pierwszy element struktury
  @param x - dodawany element
**/
struct node *insert(struct node *root, int x)
{
    if (root == NULL)
        return new_node(x);
    else if (x > root->data)
        if (root->data == 0)
        {
            root->right_child = insert(root->right_child, x);
            int o = 0;
            delete_el(root, o);
            return root;
        }
        else
        {
            root->right_child = insert(root->right_child, x);
        }
    else
        root->left_child = insert(root->left_child, x);
    return root;
}

/**
 * @brief Funkcja obsługująca wyświetlanie struktury w konsoli
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 * @param odstep - zmienna wskazujaca na odstep kolejnych elementów od siebie
 **/
int wyswietlanie(struct node *root, int odstep)
{
    if (root == NULL)
        return NULL;
    odstep += globalnyodstep;
    wyswietlanie(root->right_child, odstep);
    printf("\n");
    int i;
    for (i = globalnyodstep; i < odstep; i++)
    {
        printf(" ");
    }
    printf("%d \n", root->data);
    wyswietlanie(root->left_child, odstep);
    return 1;
}

/**
 * @brief Funkcja rekurencyjna odpowiadająca za rysowanie linii i kolejnych elementów drzewa BST w menu
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 * @param BITMAP *background - bitmapa na którą zostanie naniesione drzewo
 * @param odstep - zmienna określająca pozycję pionową drzewa
 * @param poziom - zmienna określająca pozycję poziomą drzewa
 * @param linia - zmienna określająca kierunek linii (1 = lewo; 2 = prawo)
 **/
void create_line(struct node *root, BITMAP *background, int odstep, int poziom, int linia)
{
    circlefill(background, 400 + (50 * odstep) + 8, 100 + (50 * poziom) + 5, 21, makecol(0, 0, 0));
    circlefill(background, 400 + (50 * odstep) + 8, 100 + (50 * poziom) + 5, 20, makecol(255, 255, 255));
    textprintf_ex(background, font, 400 + (50 * odstep), 100 + (50 * poziom), makecol(0, 0, 0), -1, "%d", root->data);
    if (linia == 1 && odstep == -2 && poziom == 1)
    { // LEWO
        line(background, 400 + (50 * (odstep)), 100 + (50 * poziom), 400, 100, makecol(255, 255, 255));
    }
    if (linia == 2 && odstep == 2 && poziom == 1)
    { // PRAWO
        line(background, 400 + (50 * (odstep)), 100 + (50 * poziom), 400, 100, makecol(255, 255, 255));
    }
    if ((linia == 1 && odstep != -2 && poziom != 1) || (linia == 1 && odstep == -2 && poziom != 1))
    { // LEWO
        line(background, 400 + (50 * (odstep)), 100 + (50 * poziom), 400 + (50 * (odstep + 1)), 100 + (50 * (poziom - 1)), makecol(255, 255, 255));
    }
    if ((linia == 2 && odstep != 2 && poziom != 1) || (linia == 2 && odstep == 2 && poziom != 1))
    { // PRAWO
        line(background, 400 + (50 * (odstep)), 100 + (50 * poziom), 400 + (50 * (odstep - 1)), 100 + (50 * (poziom - 1)), makecol(255, 255, 255));
    }

    if (root->left_child != NULL)
    {
        create_line(root->left_child, background, odstep - 1, poziom + 1, 1);
    }
    if (root->right_child != NULL)
    {
        create_line(root->right_child, background, odstep + 1, poziom + 1, 2);
    }
}

/**
 * @brief Funkcja rekurencyjna odpowiadająca za narysowanie pierwszego elementu drzewa i mierzenie czasu wyświetlania
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 * @param BITMAP *background - bitmapa na którą zostanie naniesione drzewo
 * @param gbs - dodatkowy warunek który pozwala wyświetlać/niewyświetlać pierwszy element drzewa
 **/
int wyswietlanie_w_menu(struct node *root, BITMAP *background, int gbs)
{
    clock_t start = clock();
    signed int odstep = -1;
    signed int poziom = 0;
    if (root == NULL)
        return NULL;

    else if (root != NULL && gbs == 0)
    {
        circlefill(background, 405, 106, 21, makecol(0, 0, 0));
        circlefill(background, 405, 106, 20, makecol(255, 255, 255));
        textprintf_ex(background, font, 400, 100, makecol(0, 0, 0), -1, "%d", root->data);
    }
    if (root->left_child == NULL && root->right_child == NULL)
    {
    }
    else
    {
        if (root->left_child != NULL || root->right_child == NULL)
        {
            create_line(root->left_child, background, odstep - 1, poziom + 1, 1);
        }
        odstep = 1;
        poziom = 0;
        if (root->right_child != NULL || root->left_child == NULL)
        {
            create_line(root->right_child, background, odstep + 1, poziom + 1, 2);
        }
    }
    blit(background, screen, 0, 0, 400, 0, background->w, background->h);
    clock_t end = clock();
    proces = (end - start);
    return 1;
}

/**
 * @brief Funkcja odpowiadająca za eksport drzewa
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 * @param odstep - zmienna określająca pozycję pionową drzewa
 **/
int export(struct node *root, int odstep)
{
    FILE *fp;
    fp = fopen("data.txt", "a");
    if (root == NULL)
        return NULL;
    odstep += globalnyodstep;
    export(root->right_child, odstep);
    fprintf(fp, "\n");
    int i;
    for (i = globalnyodstep; i < odstep; i++)
    {
        fprintf(fp, "  ");
    }
    fprintf(fp, "%d \n", root->data);
    export(root->left_child, odstep);
    fclose(fp);
    return 1;
}

/**
 * @brief Funkcja odpowiadająca za tworzenie przycisku dla wybierania ilości elementów
 * @param x - koordynat początkowy x
 * @param y - koordynat początkowy y
 * @param x2 - koordynat końcowy x
 * @param y2 - koordynat końcowy y
 * @param BITMAP *bufor - bitmapa na którą zostanie naniesiony przycisk
 **/
void przycisk_dodaj(int x, int y, int x2, int y2, BITMAP *bufor)
{
    rect(bufor, x - 2, y - 2, x2 + 2, y2 + 2, makecol(0, 0, 0));
    rectfill(bufor, x, y, x2, y2, makecol(16, 35, 82));
    rectfill(bufor, x - 1, y, x, y2, makecol(255, 255, 255));
    rectfill(bufor, x - 1, y - 1, x2, y, makecol(255, 255, 255));
}

/**
 * @brief Funkcja odpowiadająca za tworzenie przycisku dla menu
 * @param x - koordynat początkowy x
 * @param y - koordynat początkowy y
 * @param x2 - koordynat końcowy x
 * @param y2 - koordynat końcowy y
 * @param BITMAP *bufor - bitmapa na którą zostanie naniesiony przycisk
 **/
void menu_przycisk(int x, int y, int x2, int y2, BITMAP *bufor)
{
    rect(bufor, x - 2, y - 2, x2 + 2, y2 + 2, makecol(255, 255, 255));
    rect(bufor, x - 1, y - 1, x2 + 1, y2 + 1, makecol(255, 255, 255));
    rect(bufor, x, y, x2, y2, makecol(255, 255, 255));
}

/**
 * @brief Funkcja odpowiadająca za wpisywanie elementów do dodania
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 * @param k - ilość zadeklarowanych wcześniej elementów do dodania
 **/
void wprowadz_liczby(int k, struct node *root)
{
    BITMAP *gbs;
    gbs = load_bmp("tlododaj2.bmp", default_palette);
    FONT *czcionka;
    czcionka = load_font("cz1.pcx", default_palette, NULL);

    int i = 0, done = 0;
    textout_ex(gbs, czcionka, "WPISZ TE LICZBY", 330, 50, makecol(255, 255, 255), -1);

    int o = 0, tmp = 1;
    blit(gbs, screen, 0, 0, 0, 0, 1200, 800);
    char klawisz = 0;
    int minus = 0;
    int a = 1;
    while (done == 0)
    {
        textprintf_ex(screen, czcionka, 980, 270, makecol(255, 255, 255), 0, " %d ", o);

        klawisz = readkey();
        if (klawisz == 45) // Zamiana na liczbe ujemną
        {
            if (o != 0)
                o = o * (-1);
        }
        else if (key[KEY_ENTER]) // Zatwierdzenie wpisanej liczby
        {
            if ((i == 0 && root == NULL) || root == 0)
            {
                textprintf_ex(screen, font, 20 + a * 45, 360 + a * 15, makecol(255, 0, 0), 0, " %d  ", o);
                root = new_node(o);
                i++;
                a++;
            }
            else if (i > 0 || (i == 0 && root != NULL))
            {
                textprintf_ex(screen, font, 20 + a * 45, 360 + a * 15, makecol(255, 255, 255), 0, " %d  ", o);
                insert(root, o);
                i++;
                a++;
            }

            if (i == k)
            {
                wyswietlanie(root, 2);
                menu(root);
            }
        }
        else if (key[KEY_BACKSPACE]) // Usunięcie ostatnio wpisanej cyfry
        {
            if (tmp != 1)
            {
                o = o / 10;
                tmp--;
            }
        }
        else if ((klawisz < 48 || klawisz > 57) && klawisz != 13) // Zabezpieczenie przed wpisaniem czegoœ innego niż cyfra.
        {
            continue;
        }
        else if (o == 0 && klawisz == 48) // Zabezpieczenie przed dopisaniem zera do ju¿ istniejącego zera.
        {
            continue;
        }
        else // Wpisanie cyfry
        {
            if (tmp < 4)
            {
                if (o < 0)
                {
                    o = o * (-1);
                    minus = 1;
                }
                o = o * 10 + klawisz - 48;

                tmp++;
                if (minus == 1)
                {
                    o = o * (-1);
                    minus = 0;
                }
            }
            else
                allegro_message("NIE MOŻESZ WPISAĆ WIĘCEJ CYFR !");
        }
        clear_keybuf();
    }
    blit(gbs, screen, 0, 0, 0, 0, 1200, 800);
}

/**
 * @brief Funkcja odpowiadająca za wybranie liczby elementów do dodania
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 * @return k - ilość zadeklarowanych wcześniej elementów do dodania
 * @see wprowadz_liczby
 **/
void dodaj_gbs(struct node *root)
{
    FONT *mojfont;
    mojfont = load_font("c_export.pcx", default_palette, NULL);
    FONT *czcionka;
    czcionka = load_font("cz1.pcx", default_palette, NULL);
    BITMAP *dodaj;
    dodaj = load_bmp("wprowadz.bmp", default_palette);
    BITMAP *gbs;
    gbs = load_bmp("tlododaj2.bmp", default_palette);
    int done = 0;
    int k = 5;

    while (done == 0)
    {
        blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
        textout_ex(dodaj, mojfont, "WPISZ ILE CHCESZ MIEC LICZB W DRZEWKU", 230, 130, makecol(255, 255, 255), -1);
        przycisk_dodaj(400, 260, 800, 410, dodaj);
        przycisk_dodaj(830, 260, 1000, 410, dodaj);
        przycisk_dodaj(200, 260, 370, 410, dodaj);
        przycisk_dodaj(500, 440, 700, 540, dodaj);
        textout_ex(dodaj, czcionka, "+", 895, 285, makecol(255, 255, 255), -1);
        textout_ex(dodaj, czcionka, "-", 275, 285, makecol(255, 255, 255), -1);
        textout_ex(dodaj, czcionka, "OK", 550, 450, makecol(255, 255, 255), -1);
        textprintf_ex(dodaj, czcionka, 570, 290, makecol(255, 255, 255), -1, "%d", k);
        if (mouse_b & 1 && mouse_x >= 830 && mouse_x <= 1000 && mouse_y >= 260 && mouse_y <= 410)
        { // dodawanie wartosci
            przycisk_dodaj(830, 260, 1000, 410, dodaj);
            textout_ex(dodaj, czcionka, "+", 896, 286, makecol(255, 255, 255), -1);
            k++;
            blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
            if (k >= 30)
            {
                k = 30;
            }
            rest(100);
            textprintf_ex(dodaj, czcionka, 570, 340, makecol(255, 255, 255), -1, "%d", k);
        }
        if (mouse_b & 1 && mouse_x >= 200 && mouse_x <= 370 && mouse_y >= 260 && mouse_y <= 410)
        { // odejmowanie wartosci
            przycisk_dodaj(200, 260, 370, 410, dodaj);
            textout_ex(dodaj, czcionka, "-", 276, 286, makecol(255, 255, 255), -1);
            k--;
            blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
            if (k <= 1)
            {
                k = 1;
            }
            rest(100);
            textprintf_ex(dodaj, czcionka, 570, 340, makecol(255, 255, 255), -1, "%d", k);
        }
        if (mouse_b & 1 && mouse_x >= 500 && mouse_x <= 700 && mouse_y >= 440 && mouse_y <= 540)
        {
            przycisk_dodaj(500, 500, 700, 600, dodaj);
            blit(gbs, screen, 0, 0, 0, 0, 1200, 800);
            wprowadz_liczby(k, root);
            done = 1;
        }
    }
    clear_keybuf();
    readkey();
}

/**
 * @brief Funkcja odpowiadająca za wpisywanie elementów do usunięcia
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 **/
void wprowadz_usun(struct node *root)
{
    BITMAP *gbs;
    gbs = load_bmp("usun1.bmp", default_palette);
    FONT *czcionka;
    czcionka = load_font("cz1.pcx", default_palette, NULL);
    textout_ex(gbs, czcionka, "WPISZ LICZBĘ ABY JĄ USUNĄĆ", 120, 70, makecol(255, 255, 255), -1);
    blit(gbs, screen, 0, 0, 0, 0, 1200, 800);
    int o = 0, tmp = 1, done = 0, minus = 0;
    char klawisz = 0;
    while (done == 0)
    {
        textprintf_ex(screen, czcionka, 530, 360, makecol(255, 255, 255), 0, " %d ", o);

        klawisz = readkey();
        if (klawisz == 45) // Zamiana na liczbe ujemną
        {
            if (o != 0)
                o = o * (-1);
        }
        else if (key[KEY_ENTER]) // Zatwierdzenie wpisanej liczby
        {
            delete_el(root, o);
            wyswietlanie(root, 2);
            menu(root);
            done = 1;
        }
        else if (key[KEY_BACKSPACE]) // Usuniêcie ostatnio wpisanej cyfry
        {
            if (tmp != 1)
            {
                o = o / 10;
                tmp--;
            }
        }
        else if ((klawisz < 48 || klawisz > 57) && klawisz != 13) // Zabezpieczenie przed wpisaniem czegoœ innego niż cyfra.
        {
            continue;
        }
        else if (o == 0 && klawisz == 48) // Zabezpieczenie przed dopisaniem zera do już istniejącego zera.
        {
            continue;
        }
        else // Wpisanie cyfry
        {
            if (tmp < 4)
            {
                if (o < 0)
                {
                    o = o * (-1);
                    minus = 1;
                }
                o = o * 10 + klawisz - 48;

                tmp++;
                if (minus == 1)
                {
                    o = o * (-1);
                    minus = 0;
                }
            }
            else
                allegro_message("NIE MOŻESZ WPISAĆ WIĘCEJ CYFR !");
        }
    }

    blit(gbs, screen, 0, 0, 0, 0, 1200, 800);
    clear_keybuf();
    readkey();
}

/**
 * @brief Funkcja odpowiadająca za wybranie elementu, jakiego będziemy szukać w strukturze
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 * @param k - szukana liczba
 * @param BITMAP *background - przekazanie wskaźnika na tło
 **/
void wprowadz_szukaj(int k, struct node *root, BITMAP *background)
{ /// POJAWIA SIE PROBLEM, GDY URUCHAMIAMY FUNKCJE DODAJ PO SZUKANIU
    BITMAP *gbs;
    gbs = load_bmp("usun1.bmp", default_palette);
    FONT *czcionka;
    czcionka = load_font("cz1.pcx", default_palette, NULL);

    textout_ex(gbs, czcionka, "WPISZ LICZBĘ ABY JĄ USUNĄĆ", 120, 70, makecol(255, 255, 255), -1);
    blit(gbs, screen, 0, 0, 0, 0, 1200, 800);
    int o = 0, tmp = 1, done = 0, minus = 0;
    char klawisz = 0;
    while (done == 0)
    {
        textprintf_ex(screen, czcionka, 530, 360, makecol(255, 255, 255), 0, " %d ", o);

        klawisz = readkey();
        if (klawisz == 45) // Zamiana na liczbe ujemną
        {
            if (o != 0)
                o = o * (-1);
        }
        else if (key[KEY_ENTER]) // Zatwierdzenie wpisanej liczby
        {
            szukaj_elementu(root, background, o, 0, 0, 1);
            menu(root);
            done = 1;
        }
        else if (key[KEY_BACKSPACE]) // Usuniêcie ostatnio wpisanej cyfry
        {
            if (tmp != 1)
            {
                o = o / 10;
                tmp--;
            }
        }
        else if ((klawisz < 48 || klawisz > 57) && klawisz != 13) // Zabezpieczenie przed wpisaniem czegoœ innego niż cyfra.
        {
            continue;
        }
        else if (o == 0 && klawisz == 48) // Zabezpieczenie przed dopisaniem zera do ju¿ istniejącego zera.
        {
            continue;
        }
        else // Wpisanie cyfry
        {
            if (tmp < 4)
            {
                if (o < 0)
                {
                    o = o * (-1);
                    minus = 1;
                }
                o = o * 10 + klawisz - 48;

                tmp++;
                if (minus == 1)
                {
                    o = o * (-1);
                    minus = 0;
                }
            }
            else
                allegro_message("NIE MOŻESZ WPISAĆ WIĘCEJ CYFR !");
        }
    }

    blit(gbs, screen, 0, 0, 0, 0, 1200, 800);
}

/**
 * @brief Funkcja odpowiadająca za przeszukiwanie drzewa w menu w celu znalezienia elementu
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 * @param BITMAP *background - wskaźnik na bitmapę, na ktorej będzie wyświetlany proces szukania
 * @param szukana - zmienna przechowująca szukaną wartość
 * @param odstep - zmienna przechowująca pozycje poziomą dla elementu drzewa
 * @param poziom - zmienna przechowująca pozycje pionową dla elementu drzewa
 * @param pierwszy - warunek czy funkcja jest wywołana pierwszy raz
 **/
void szukaj_elementu(struct node *root, BITMAP *background, int szukana, signed int odstep, signed int poziom, int pierwszy)
{
    BITMAP *lewo;
    lewo = load_bitmap("lewo.bmp", default_palette);
    blit(lewo, screen, 0, 0, 0, 0, lewo->w, lewo->h);

    if (root == NULL)
        return NULL;

    if (root->data == szukana && root != NULL)
    {
        if (pierwszy == 1)
        {
            int i;
            for (i = 0; i < 5; i++)
            {
                circle(background, 405 + (50 * odstep), 106 + (50 * poziom), 20, makecol(181, 0, 0));
                circle(background, 405 + (50 * odstep), 106 + (50 * poziom), 21, makecol(181, 0, 0));
                blit(background, screen, 0, 0, 400, 0, background->w, background->h);
                rest(300);
                circle(background, 405 + (50 * odstep), 106 + (50 * poziom), 20, makecol(121, 60, 61));
                circle(background, 405 + (50 * odstep), 106 + (50 * poziom), 21, makecol(121, 60, 61));
                blit(background, screen, 0, 0, 400, 0, background->w, background->h);
                rest(300);
            }
            circle(background, 405 + (50 * odstep), 106 + (50 * poziom), 20, makecol(181, 0, 0));
            circle(background, 405 + (50 * odstep), 106 + (50 * poziom), 21, makecol(181, 0, 0));
            blit(background, screen, 0, 0, 400, 0, background->w, background->h);
            rest(2000);
        }
        else
        {
            int i;
            for (i = 0; i < 5; i++)
            {
                circle(background, 408 + (50 * odstep), 105 + (50 * poziom), 21, makecol(181, 0, 0));
                circle(background, 408 + (50 * odstep), 105 + (50 * poziom), 22, makecol(181, 0, 0));
                blit(background, screen, 0, 0, 400, 0, background->w, background->h);
                rest(300);
                circle(background, 408 + (50 * odstep), 105 + (50 * poziom), 21, makecol(121, 60, 61));
                circle(background, 408 + (50 * odstep), 105 + (50 * poziom), 22, makecol(121, 60, 61));
                blit(background, screen, 0, 0, 400, 0, background->w, background->h);
                rest(300);
            }
            circle(background, 408 + (50 * odstep), 105 + (50 * poziom), 21, makecol(121, 60, 61));
            circle(background, 408 + (50 * odstep), 105 + (50 * poziom), 22, makecol(121, 60, 61));
            blit(background, screen, 0, 0, 400, 0, background->w, background->h);
            rest(2000);
        }
    }
    else if ((root->left_child != NULL || root->right_child != NULL) && szukana <= root->data)
    {
        if (pierwszy == 1)
        {
            circle(background, 405 + (50 * odstep), 107 + (50 * poziom), 21, makecol(200, 66, 66));
            blit(background, screen, 0, 0, 400, 0, background->w, background->h);
            rest(700);
        }
        else
        {
            circle(background, 408 + (50 * odstep), 105 + (50 * poziom), 21, makecol(200, 66, 66));
            blit(background, screen, 0, 0, 400, 0, background->w, background->h);
            rest(700);
        }
        root = root->left_child;
        if (poziom == 0)
        {
            szukaj_elementu(root, background, szukana, odstep - 2, poziom + 1, 0);
        }
        else
        {
            szukaj_elementu(root, background, szukana, odstep - 1, poziom + 1, 0);
        }
    }
    else if ((root->left_child != NULL || root->right_child != NULL) && szukana > root->data)
    {
        if (pierwszy == 1)
        {
            circle(background, 405 + (50 * odstep), 107 + (50 * poziom), 21, makecol(200, 66, 66));
            blit(background, screen, 0, 0, 400, 0, background->w, background->h);
            rest(700);
        }
        else
        {
            circle(background, 408 + (50 * odstep), 105 + (50 * poziom), 21, makecol(200, 66, 66));
            blit(background, screen, 0, 0, 400, 0, background->w, background->h);
            rest(700);
        }
        root = root->right_child;
        if (poziom == 0)
        {
            szukaj_elementu(root, background, szukana, odstep + 2, poziom + 1, 0);
        }
        else
        {
            szukaj_elementu(root, background, szukana, odstep + 1, poziom + 1, 0);
        }
    }
}

/**
 * @brief Funkcja losująca liczby
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 * @param x - ilość zadeklarowanych wcześniej elementów do wylosowania
 **/
void random(int x, struct node *root)
{
    int i, j;
    srand(time(NULL));
    int tab[30];
    for (i = 0; i < x; i++)
    {
        // losowanie bez powtorzen
        for (i = 0; i < x; i++)
        {
            tab[i] = rand() % 49 + 1;
            for (j = 0; j < i; j++)
            {
                if (tab[j] == tab[i])
                {
                    tab[i] = rand() % 49 + 1;
                    j = -1; // bo zaraz j zostanie zinkrementowane
                }
                // o tutaj nastepuje j++ (na koncu petli, bo postinkrementacja)
            }
        }
        for (i = 0; i < x; i++)
        {
            if (root == NULL)
                root = new_node(tab[i]);
            else
                insert(root, tab[i]);
        }
    }
    wyswietlanie(root, 2);
    menu(root);
}

/**
 * @brief Funkcja odpowiadająca za wybranie liczby elementów do wylosowania i dodania
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 **/
void losuj_gbs(struct node *root)
{
    FONT *mojfont;
    mojfont = load_font("c_export.pcx", default_palette, NULL);
    FONT *czcionka;
    czcionka = load_font("cz1.pcx", default_palette, NULL);
    BITMAP *dodaj;
    dodaj = load_bmp("wprowadz.bmp", default_palette);
    int done = 0;
    int k = 5;

    while (done == 0)
    {
        blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
        textout_ex(dodaj, mojfont, "WPISZ ILE LICZB CHCESZ WYLOSOWAĆ", 280, 130, makecol(255, 255, 255), -1);
        przycisk_dodaj(400, 260, 800, 410, dodaj);
        przycisk_dodaj(830, 260, 1000, 410, dodaj);
        przycisk_dodaj(200, 260, 370, 410, dodaj);
        przycisk_dodaj(500, 440, 700, 540, dodaj);
        textout_ex(dodaj, czcionka, "+", 895, 285, makecol(255, 255, 255), -1);
        textout_ex(dodaj, czcionka, "-", 275, 285, makecol(255, 255, 255), -1);
        textout_ex(dodaj, czcionka, "OK", 550, 450, makecol(255, 255, 255), -1);
        textprintf_ex(dodaj, czcionka, 570, 290, makecol(255, 255, 255), -1, "%d", k);
        if (mouse_b & 1 && mouse_x >= 830 && mouse_x <= 1000 && mouse_y >= 260 && mouse_y <= 410)
        { // dodawanie wartosci
            przycisk_dodaj(830, 260, 1000, 410, dodaj);
            textout_ex(dodaj, czcionka, "+", 896, 286, makecol(255, 255, 255), -1);
            k++;
            blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
            if (k >= 30)
            {
                k = 30;
            }
            rest(100);
            textprintf_ex(dodaj, czcionka, 570, 340, makecol(255, 255, 255), -1, "%d", k);
        }

        if (mouse_b & 1 && mouse_x >= 200 && mouse_x <= 370 && mouse_y >= 260 && mouse_y <= 410)
        { // odejmowanie wartosci
            przycisk_dodaj(200, 260, 370, 410, dodaj);
            textout_ex(dodaj, czcionka, "-", 276, 286, makecol(255, 255, 255), -1);
            k--;
            blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
            if (k <= 1)
            {
                k = 1;
            }
            rest(100);
            textprintf_ex(dodaj, czcionka, 570, 340, makecol(255, 255, 255), -1, "%d", k);
        }

        if (mouse_b & 1 && mouse_x >= 500 && mouse_x <= 700 && mouse_y >= 440 && mouse_y <= 540)
        {

            przycisk_dodaj(500, 440, 700, 540, dodaj);
            blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
            random(k, root);
            done = 1;
        }
    }

    readkey();
}

/**
 * @brief Funkcja odpowiadająca za wywołanie odpowiednich przycisków i funkcji wyświetlenia drzewa w menu
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 **/
int menu(struct node *root)
{
    FONT *mojfont;
    mojfont = load_font("czcionka.pcx", default_palette, NULL);
    BITMAP *lewo;
    lewo = load_bitmap("lewo.bmp", default_palette);
    BITMAP *prawo;
    prawo = load_bitmap("prawo.bmp", default_palette);
    BITMAP *dodaj;
    dodaj = load_bmp("wprowadz.bmp", default_palette);
    textout_centre_ex(lewo, mojfont, " DODAJ", 140, 62, makecol(255, 255, 255), -1);
    textout_centre_ex(lewo, mojfont, " USUŃ", 139, 191, makecol(255, 255, 255), -1);
    textout_centre_ex(lewo, mojfont, " LOSUJ", 140, 321, makecol(255, 255, 255), -1);
    textout_centre_ex(lewo, mojfont, " SZUKAJ", 145, 450, makecol(255, 255, 255), -1);
    textout_centre_ex(lewo, mojfont, " EKSPORTUJ DANE", 145, 581, makecol(255, 255, 255), -1);
    textout_centre_ex(lewo, mojfont, " WYGENERUJ CZAS", 145, 711, makecol(255, 255, 255), -1);
    menu_przycisk(50, 35, 250, 115, lewo);
    menu_przycisk(50, 165, 250, 245, lewo);
    menu_przycisk(50, 295, 250, 375, lewo);
    menu_przycisk(50, 425, 250, 505, lewo);
    menu_przycisk(50, 555, 250, 635, lewo);
    menu_przycisk(50, 685, 250, 765, lewo);
    blit(lewo, screen, 0, 0, 0, 0, lewo->w, lewo->h);
znacznik:

    blit(prawo, screen, 0, 0, 400, 0, prawo->w, prawo->h);
    wyswietlanie_w_menu(root, prawo, 0);
    int done = 0;

    while (done == 0)
    {
        if (mouse_b & 1 && mouse_x >= 50 && mouse_x <= 250 && mouse_y >= 35 && mouse_y <= 115)
        {
            done = 1;
            blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
            dodaj_gbs(root);
        }

        if (mouse_b & 1 && mouse_x >= 50 && mouse_x <= 250 && mouse_y >= 165 && mouse_y <= 245)
        {
            done = 1;
            wprowadz_usun(root);
        }

        if (mouse_b & 1 && mouse_x >= 50 && mouse_x <= 250 && mouse_y >= 295 && mouse_y <= 375)
        {
            done = 1;
            blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
            losuj_gbs(root);
        }

        if (mouse_b & 1 && mouse_x >= 50 && mouse_x <= 250 && mouse_y >= 425 && mouse_y <= 505)
        {
            done = 1;
            blit(dodaj, screen, 0, 0, 0, 0, 1200, 800);
            wprowadz_szukaj(1, root, prawo);
        }

        if (mouse_b & 1 && mouse_x >= 50 && mouse_x <= 250 && mouse_y >= 555 && mouse_y <= 635)
        {
            done = 1;
            FILE *fp;
            fp = fopen("data.txt", "w");
            fclose(fp);
            export(root, 2);
            rest(1000);
            set_window_title("Eksportowanie drzewa");
            allegro_message("Dane wyeksportowane.");
            rest(500);
            set_window_title("Drzewo BST");
            menu(root);
        }
        if (mouse_b & 1 && mouse_x >= 50 && mouse_x <= 250 && mouse_y >= 685 && mouse_y <= 765)
        {
            done = 1;
            rest(1000);
            set_window_title("Czas generowania drzewa");
            allegro_message("Generowanie zajeło %.1lf s.", proces);
            rest(500);
            set_window_title("Drzewo BST");
            goto znacznik;
        }
    }
    return 0;
}
/**
 * @brief Główna funkcja programu odpowiadająca za implementację allegro i deklarację początkową elementu root.
 * @param node *root - wskaźnik na korzeń drzewa
 * @see struct node
 **/
int main()
{
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1200, 800, 0, 0);
    set_palette(default_palette);
    clear_to_color(screen, 48);
    install_mouse();
    show_mouse(screen);
    unscare_mouse();
    struct node *root = NULL;
    set_window_title("Drzewo BST");
    menu(root);

    allegro_exit();

    return 0;
}
END_OF_MAIN();
