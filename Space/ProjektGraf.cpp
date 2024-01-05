/**
 * @file main.cpp
 * @brief Główny plik programu Space Intruders.
 */

#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "SpriteObject.h"
#include <SDL_ttf.h>
#include <string>
using namespace std;
#define predkosc_pocisku 10 ///< Prędkość poruszania się pocisku.
#define rozmiar_pocisku 20 ///< Rozmiar pocisku.
int AniFrame = 0; ///< Aktualna klatka animacji.
/**
 * @class Alien
 * @brief Klasa reprezentująca obcego statku kosmicznego.
 */
class Alien {
public:
    int x, y, width, height;  ///< Współrzędne, szerokość i wysokość obcego statku.
    SDL_Rect rect;  ///< Prostokąt reprezentujący obcego statku.
    int alive; ///< Flaga określająca, czy statek jest żywy.
    int lives; ///< Ilość żyć obcego statku.
    int type; ///< Typ obcego statku.
    /**
 * @brief Konstruktor klasy Alien.
 */
    Alien()
    {
        this->x = 10;
        this->y = 10;
        this->width = 30;
        this->height = 30;
        this->rect = { x,y,width,height };
        this->alive = 1;
        this->lives = 1;
    }
    /**
 * @brief Metoda ustawiająca nowe współrzędne obcego statku.
 * @param nx Nowa współrzędna x.
 * @param ny Nowa współrzędna y.
 */
    void MoveCoordinates(int nx, int ny)
    {
        this->x = nx;
        this->y = ny;
        this->rect = { x,y,width,height };
    }
};
/**
 * @class Enemies
 * @brief Klasa reprezentująca grupę obcych statków kosmicznych.
 */
class Enemies {
public:
    Alien tab[40];
    int x, y; ///< Współrzędne grupy obcych statków.
    int direction = 1; ///< Kierunek poruszania się grupy obcych statków.
    int dead; ///< Licznik zniszczonych obcych statków.
    int currentSpeed; ///< Aktualna prędkość poruszania się grupy obcych statków.
    int wave=1; ///< Aktualna fala obcych statków.
    /**
 * @brief Konstruktor klasy Enemies.
 */
    Enemies()
    {
        this->x = 10;
        this->y = 10;
        this->currentSpeed = 5;
    }
    /**
 * @brief Metoda ustawiająca bazowe pozycje grupy obcych statków.
 */
    void BasePosition()
    {
        this->x = 10;
        this->y = 10;
    }
    /**
 * @brief Metoda inicjalizująca grupę obcych statków.
 */
    void IntEnemies()
    {
        int i = 0;
        this->dead = 0;
        currentSpeed = 5;
        for (int j = 0; j < (sizeof(tab) / sizeof(tab[0])); j++)
        {
            tab[j].MoveCoordinates(x, y);
            tab[j].alive = 1;
            switch (wave)
            {
            case 1:
                tab[j].type = 1;
                break;
            case 2:
                tab[j].type = 2;
                break;
            case 3:
                tab[j].type = 3;
                break;
            case 4:
                tab[j].type = 4;
                break;
            case 5:
                tab[j].type = 5;
                break;
            case 6:
                tab[j].type = 6;
                break;
                
            }
            
            switch (tab[j].type) {
            case 1:
                tab[j].lives = 1;
                break;
            case 2:
                tab[j].lives = 2;
                break;
            case 3:
                tab[j].lives = 3;
                break;
            case 4:
                tab[j].lives = 4;
                break;
            case 5:
                tab[j].lives = 5;
                break;
            case 6:
                tab[j].lives = 6;
                break;
            }
            x = x + 40;
            i++;
            if (i == 10) {
                y += 40;
                x = 10;
                i = 0;
            }
        }
    }
    /**
 * @brief Metoda odpowiedzialna za ruch grupy obcych statków.
 */
    void Move()
    {
        int change = 0;
        int speed = currentSpeed;
        int alien_maxX = 0;
        int alien_maxY = 0;
        int alien_minX = 10000;
        int alien_minY = 10000;
        for (int i = 0; i < (sizeof(tab) / sizeof(tab[0])); i++)
        {
            if (tab[i].alive)
            {
                int IndexX = i % 10;
                int IndexY = i % 4;//Height
                if (IndexX > alien_maxX)alien_maxX = IndexX;
                if (IndexX < alien_minX)alien_minX = IndexX;
                if (IndexY > alien_maxY)alien_maxY = IndexY;
                if (IndexY < alien_minY)alien_minY = IndexY;
            }
        }
        if (tab[alien_maxX].x + tab[alien_maxX].width >= 800)
        {
            direction = -1;
            change = 1;
            currentSpeed += 1;
        }
        if (tab[alien_minX].x <= 0)
        {
            direction = 1;
            change = 1;

        }
        for (int j = 0; j < (sizeof(tab) / sizeof(tab[0])); j++)
        {
            tab[j].x = tab[j].x + (direction * speed);
            if (change == 1)
                tab[j].y += tab[j].height;
            tab[j].MoveCoordinates(tab[j].x, tab[j].y);
        }
    }
};
/**
 * @class Bullet
 * @brief Klasa reprezentująca pocisk gracza.
 */
class Bullet {
public:
    int x, y, width, height; ///< Współrzędne, szerokość i wysokość pocisku.
    SDL_Rect rect; ///< Prostokąt reprezentujący pocisk.
    bool active; ///< Flaga określająca, czy pocisk jest aktywny.
    SDL_Texture* Texture; ///< Tekstura pocisku.
    /**
 * @brief Konstruktor klasy Bullet.
 */
    Bullet() {
        width = rozmiar_pocisku;
        height = rozmiar_pocisku;
        rect = { x, y, width, height };
        active = false;

    }
    /**
 * @brief Metoda odpowiadająca za strzał pocisku.
 * @param playerX Współrzędna x gracza.
 * @param playerY Współrzędna y gracza.
 */
    void Shoot(int playerX, int playerY) {
        x = (playerX + (width / 2)) - 5; // pocisk na środku naszego pleyera
        y = playerY;
        rect = { x, y, width, height };
        active = true;
    }
    /**
 * @brief Metoda odpowiadająca za ruch pocisku.
 */
    void Move() {
        if (active) {
            y -= predkosc_pocisku;
            rect = { x, y, width, height };
        }
    }
    /**
 * @brief Metoda odpowiadająca za rysowanie pocisku.
 * @param renderer Renderer SDL.
 * @param bulletTexture Tekstura pocisku.
 */
    void Draw(SDL_Renderer* renderer, SDL_Texture* bulletTexture) {
        if (active) {
            // Use renderer and bulletTexture to draw the bullet
            SDL_RenderCopy(renderer, bulletTexture, NULL, &rect);
        }
    }
};

/**
 * @class Player
 * @brief Klasa reprezentująca gracza.
 */
class Player {
public:
    int x, y, width, height; ///< Współrzędne, szerokość i wysokość gracza.
    int score; ///< Wynik gracza.
    SDL_Rect rect; ///< Prostokąt reprezentujący gracza.
    vector<Bullet> bullets; ///< Wektor przechowujący pociski gracza.
    int currentBullet; ///< Indeks aktualnego pocisku.
    Uint32 lastWeaponFire; ///< Czas ostatniego strzału gracza.

    /**
 * @brief Konstruktor klasy Player.
 */
    Player()
    {
        this->x = 10;
        this->y = 10;
        this->width = 30;
        this->height = 30;
        this->rect = { x,y,width,height };
        this->score = 0;
        lastWeaponFire = SDL_GetTicks();
    }
    /**
 * @brief Metoda ustawiająca nowe współrzędne gracza.
 * @param nx Nowa współrzędna x.
 * @param ny Nowa współrzędna y.
 */
    void MoveCoordinates(int nx, int ny)
    {
        this->x = nx;
        this->y = ny;
        this->rect = { x,y,width,height };
    }
    /**
 * @brief Metoda odpowiadająca za ruch gracza w lewo.
 */
    void MoveLeft()
    {
        if (x > 0)
            x = x - 10;
        this->rect = { x,y,width,height };
    }
    /**
 * @brief Metoda odpowiadająca za ruch gracza w prawo.
 */
    void MoveRight()
    {
        if (x + width < 800)
            x = x + 10;
        this->rect = { x,y,width,height };
    }
    /**
 * @brief Metoda odpowiadająca za strzał gracza.
 */
    void Shoot() {
        Bullet newBullet;
        newBullet.Shoot(x, y);
        bullets.push_back(newBullet);
    }
};
/**
 * @class Engine
 * @brief Klasa reprezentująca silnik gry.
 */
class Engine {
public:
    SDL_Window* window; ///< Okno gry.
    SDL_Renderer* renderer;///< Renderer SDL.
    SDL_Event event; ///< Zdarzenia SDL.
    int Width, Height; ///< Szerokość i wysokość okna gry.
    enum GameStateType { PAUSE, RUN, GAMEOVER, START }; ///< Enumeracja stanów gry.
    GameStateType GameState = START; ///< Aktualny stan gry.
    Player p1; ///< Obiekt gracza.
    Enemies e1; ///< Obiekt grupy obcych statków.
    BitmapHandler bh1 = BitmapHandler(); ///< Obiekt do obsługi bitmap.
    SDL_Texture* Tex1; ///< Tekstura1
    SDL_Texture* Tex2; ///< Tekstura2
    SDL_Texture* Tex3; ///< Tekstura3
    SDL_Texture* Tex4; ///< Tekstura4
    SDL_Texture* spodek; ///< Tekstura5
    SDL_Texture* xeno; ///< Tekstura6
    SDL_Texture* mario; ///< Tekstura7
    SDL_Texture* Pause; ///< Tekstura8
    SDL_Texture* GameOver; ///< Tekstura9
    SDL_Texture* Start; ///< Tekstura10
    SDL_Texture* Background1; ///< Tekstura11
    SDL_Texture* Background2; ///< Tekstura12
    AnimatedObject a1 = AnimatedObject(); ///< Animowany obiekt.
    BitmapObject b1 = BitmapObject(); ///< Obiekt bitmapowy.
    SpriteObject s1 = SpriteObject(); ///< Obiekt sprite'a.
    SDL_Texture** Animation2; ///< Animacja 2.
    SDL_Texture* BulletTexture; ///< Tekstura dla pocisku.

    /////////////////////
    //fpsy od
    const int FPS = 30;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    float old_time = SDL_GetTicks();
    // fps do oraz w while
    bool isRunning = true;
    /**
 * @brief Konstruktor klasy Engine.
 * @param x Szerokość okna gry.
 * @param y Wysokość okna gry.
 */
    Engine(int x, int y) {
        this->Width = x;
        this->Height = y;
        p1.MoveCoordinates(this->Width / 2, this->Height - (p1.height + 5));
        e1.IntEnemies();
        // inicjalizacja biblioteki od
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            exit(1); // Wyjœcie z programu w przypadku b³êdu inicjalizacji.
        } // do
        //Tworzenie okna
        window = SDL_CreateWindow("Space Intruders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!window) {
            exit(1); // Wyjœcie z programu w przypadku b³êdu tworzenia okna.
        }
        BulletTexture = bh1.LoadTexture("Textury/pocisk.png", renderer);
    }
    /**
     * @brief Metoda sprawdzająca kolizje między pociskiem a obcym statkiem.
     */
    void CheckCollisions() {
        for (int i = 0; i < p1.bullets.size(); i++) {
            if (p1.bullets[i].active) {
                for (int j = 0; j < sizeof(e1.tab) / sizeof(e1.tab[0]); j++) {
                    if (e1.tab[j].alive) {
                        if (CheckCollision(p1.bullets[i], e1.tab[j])) {
                            // Kolizja między pociskiem a obcym statkiem kosmicznym.
                            p1.bullets[i].active = false;
                            e1.tab[j].lives--;

                            if (e1.tab[j].lives <= 0) {
                                e1.tab[j].alive = false;
                                e1.dead++;
                            }
                        }
                    }
                }
            }
        }
    }

    bool CheckCollision(const Bullet& bullet, const Alien& alien) {
        // sprawdza nachodzenie sie pocisku z pojedynczym kwadratem z tych tam kilku w ocb
        if (bullet.x < alien.x + alien.width &&
            bullet.x + bullet.width > alien.x &&
            bullet.y < alien.y + alien.height &&
            bullet.y + bullet.height > alien.y) {
            p1.score++;
            return true; // Kolizja.
        }
        return false; // Brak kolizji.
    }

    /**
     * @brief Metoda sprawdzająca kolizje między graczem a obcymi statkami.
     * @param player Referencja do obiektu gracza.
     */
    void CheckCollisions(const Player& player) {
        for (int j = 0; j < sizeof(e1.tab) / sizeof(e1.tab[0]); j++) {
            if (e1.tab[j].alive) {
                if (player.x < e1.tab[j].x + e1.tab[j].width &&
                    player.x + player.width > e1.tab[j].x &&
                    player.y < e1.tab[j].y + e1.tab[j].height &&
                    player.y + player.height > e1.tab[j].y) {
                    
                    GameState = { GAMEOVER };
                    //gameover
                }
            }
        }
    }

    /**
 * @brief Metoda wzmocnienia obcych statków po zniszczeniu grupy.
 */
    void AlienReinforcement()
    {
        if (e1.dead == (sizeof(e1.tab) / sizeof(e1.tab[0])))
        {
            e1.BasePosition();
            e1.wave++;
            if (e1.wave >= 6)
                e1.wave = 6;
            e1.IntEnemies();

        }
    }


    //Pętla główna gry, wyświetlanie okna
        /**
     * @brief Metoda uruchamiająca główną pętlę gry.
     */
    void Run() {
        Background1 = bh1.LoadTexture("Textury/Background1.png", renderer);
        Start = bh1.LoadTexture("Textury/Start.png", renderer);
        Pause = bh1.LoadTexture("Textury/Pause.png", renderer);
        GameOver = bh1.LoadTexture("Textury/GameOver.png", renderer);
        Background2 = bh1.LoadTexture("Textury/Background2.png", renderer);
        Tex1 = bh1.LoadTexture("Textury/alien1.png", renderer);
        Tex2 = bh1.LoadTexture("Textury/alien2.png", renderer);
        Tex3 = bh1.LoadTexture("Textury/pocisk.png", renderer);
        Tex4 = bh1.LoadTexture("Textury/alien3.png", renderer);
        spodek = bh1.LoadTexture("Textury/alien5.png", renderer);
        xeno = bh1.LoadTexture("Textury/alien4.png", renderer);
        mario = bh1.LoadTexture("Textury/mario.png", renderer);

        Animation2 = bh1.LoadAnimation("Animacja1/move%d.png", renderer, 6);
        
        while (isRunning) {

            switch (GameState) {
            case START: {
                SDL_Rect back = { 0,0,Width,Height };
                SDL_Rect tmp = { 300,100,200,300 };
                SDL_RenderCopy(renderer, Background1, NULL, &back);
                SDL_RenderCopy(renderer, Start, NULL, &tmp);
                if (SDLK_TAB == event.key.keysym.sym)
                    GameState = RUN;
                break;
            }
            case PAUSE: {
                SDL_Rect back = { 0,0,Width,Height };
                SDL_Rect tmp = { 100,100,50,50 };
                Draw();
                RenderScore();
                SDL_RenderCopy(renderer, Pause, NULL, &tmp);
                if (SDLK_TAB == event.key.keysym.sym)
                    GameState = RUN;
                break;
            }
            case RUN: {
                frameStart = SDL_GetTicks();
                MovementHandle();
                e1.Move();

                DrawBullets();
                UpdateBullets();
                Draw();
                RenderScore();
                CheckCollisions();
                CheckCollisions(p1);
                AlienReinforcement();
                if (SDLK_ESCAPE == event.key.keysym.sym)
                    GameState = PAUSE;
                break;
            }
            case GAMEOVER:
            {
                Draw();
                RenderScore();
                SDL_Rect tmp = { 300,100,200,300 };
                SDL_RenderCopy(renderer, GameOver, NULL, &tmp);
                if (SDLK_TAB == event.key.keysym.sym) {
                    e1.BasePosition();
                    e1.wave = 1;
                    e1.IntEnemies();
                    p1.score = 0;
                    p1.bullets.clear();
                    GameState = RUN;
                    
                }
                break;
            }
            }

            //time function od
            frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            } // do
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            DrawBullets();
        }

    }
    /**
 * @brief Metoda aktualizująca pozycję i stan wszystkich pocisków gracza.
 */
    void UpdateBullets() {
        for (int i = 0; i < p1.bullets.size(); i++) {
            p1.bullets[i].Move();
            if (p1.bullets[i].y < 0) {
                p1.bullets.erase(p1.bullets.begin() + i); // Usunięcie obiektu ze vectora
            }
        }
    }

    /**
 * @brief Metoda rysująca wszystkie pociski gracza na ekranie.
 */
    void DrawBullets() {
        for (int i = 0; i < p1.bullets.size(); i++) {
            if (p1.bullets[i].active) {
                p1.bullets[i].Draw(renderer, BulletTexture);
            }
        }
    }

    /**
 * @brief Metoda rysująca elementy gry na ekranie.
 */
    void Draw()
    {
        SDL_Rect back = { 0,0,Width,Height };
        SDL_RenderCopy(renderer, Background2, NULL, &back);
        DrawBullets();
        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
        a1.animate(renderer, Animation2, p1.rect, AniFrame);

        for (int i = 0; i < (sizeof(e1.tab) / sizeof(e1.tab[0])); i++)
        {
            
            if (e1.tab[i].alive == 1) 
            { 
                switch (e1.tab[i].type) {
                case 1:  SDL_RenderCopy(renderer, Tex1, NULL, &e1.tab[i].rect);
                    break;
                case 2:  SDL_RenderCopy(renderer, Tex2, NULL, &e1.tab[i].rect);
                    break;
                case 3:  SDL_RenderCopy(renderer, Tex4, NULL, &e1.tab[i].rect);
                    break;
                case 4:  SDL_RenderCopy(renderer, xeno, NULL, &e1.tab[i].rect);
                    break;
                case 5:  SDL_RenderCopy(renderer, spodek, NULL, &e1.tab[i].rect);
                    break;
                case 6:  SDL_RenderCopy(renderer, mario, NULL, &e1.tab[i].rect);
                    break;

                }
            }
        }


    }
    /**
 * @brief Metoda obsługująca ruch gracza i strzały.
 */
    void MovementHandle()
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_LEFT])
        {
            p1.MoveLeft();
            if (AniFrame == 5) //index tablicy do animacji
            {
                AniFrame = 0;
            }
            else AniFrame++;
        }
        else {};

        if (state[SDL_SCANCODE_RIGHT])
        {
            p1.MoveRight();
            if (AniFrame == 5) //index tablicy do animacji
            {
                AniFrame = 0;
            }
            else AniFrame++;
        }
        else {};

        // Dodaj obsługę innych klawiszy według potrzeb.
        if (state[SDL_SCANCODE_SPACE] && SDL_GetTicks() > p1.lastWeaponFire + 100) { ///to 500 to opóżnienie w ms
            p1.Shoot();
            p1.lastWeaponFire = SDL_GetTicks();
        }


    }
    /**
 * @brief Metoda rysująca aktualny wynik gracza na ekranie.
 */
    void RenderScore() {
        TTF_Font* font = TTF_OpenFont("C:/Labolatorium_grafika/Space/Space/arial.ttf", 24);
        if (!font) {
            cerr << "Failed to load font: " << TTF_GetError() << endl;
            return;
        }
        if (TTF_Init() == -1) {
            cerr << "SDL_ttf could not be initialized! SDL_ttf Error: " << TTF_GetError() << endl;
            // Handle the error or exit the program.
        }

        SDL_Color textColor = { 255, 255, 255 }; // White color

        // Convert the score to a string
        string scoreText = "Score: " + to_string(p1.score);

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
        if (!textSurface) {
            cerr << "Failed to render text surface: " << TTF_GetError() << endl;
            TTF_CloseFont(font);
            return;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!scoreTexture) {
            cerr << "Failed to create texture from surface: " << SDL_GetError() << endl;
            SDL_FreeSurface(textSurface);
            TTF_CloseFont(font);
            return;
        }

        SDL_Rect textRect = { 10, 10, textSurface->w, textSurface->h }; // Adjust the position as needed
        SDL_RenderCopy(renderer, scoreTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(scoreTexture);
        TTF_CloseFont(font);
    }

    /**
     * @brief Destruktor klasy Engine.
     */
    ~Engine() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }


};
/**
 * @brief Główna funkcja programu.
 * @param argc Liczba argumentów wiersza poleceń.
 * @param argv Tablica zawierająca argumenty wiersza poleceń.
 * @return Kod zakończenia programu.
 */
int main(int argc, char* argv[]) {
    if (TTF_Init() == -1) {
        cerr << "SDL_ttf could not be initialized! SDL_ttf Error: " << TTF_GetError() << endl;
        // Obsłuż błąd lub zakończ program.
        return 1;
    }
    Engine game(800, 600); // Tworzenie instancji klasy Engine.
    game.Run();
    TTF_Quit();
    return 0; // Zakoñczenie programu.

}