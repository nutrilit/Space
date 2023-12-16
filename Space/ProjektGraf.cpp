#include <SDL.h> // W³¹czamy bibliotekê SDL.
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "SpriteObject.h"
#include <SDL_ttf.h>
#include <string>
using namespace std;
#define predkosc_pocisku 10
#define rozmiar_pocisku 20

class Alien {
public:
    int x, y, width, height;
    SDL_Rect rect;
    int alive;
    Alien()
    {
        this->x = 10;
        this->y = 10;
        this->width = 30;
        this->height = 30;
        this->rect = { x,y,width,height };
        this->alive = 1;
    }

    void MoveCoordinates(int nx, int ny)
    {
        this->x = nx;
        this->y = ny;
        this->rect = { x,y,width,height };
    }
};
class Enemies {
public:
    Alien tab[40];
    int x, y;
    int direction = 1;
    int dead;
    int currentSpeed;
    Enemies()
    {
        this->x = 10;
        this->y = 10;
        this->currentSpeed = 5;
    }
    void BasePosition()
    {
        this->x = 10;
        this->y = 10;
    }
    void IntEnemies()
    {
        int i = 0;
        this->dead = 0;
        for (int j = 0; j < (sizeof(tab) / sizeof(tab[0])); j++)
        {
            tab[j].MoveCoordinates(x, y);
            tab[j].alive = 1;
            x = x + 40; //40
            i++;
            if (i == 10) {
                y += 40;
                x = 10;
                i = 0;
            }
        }
    }
    void Move()
    {
        //int direction = 1;
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
                //alien_alive_amount++;
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

class Bullet {
public:
    int x, y, width, height;
    SDL_Rect rect;
    bool active;
    SDL_Texture* Texture; // Dodaj pole do przechowywania tekstury

    Bullet() {
        width = rozmiar_pocisku;
        height = rozmiar_pocisku;
        rect = { x, y, width, height };
        active = false;
        
    }

    void Shoot(int playerX, int playerY) {
        x = (playerX + (width / 2)) -5; // pocisk na środku naszego pleyera
        y = playerY;
        rect = { x, y, width, height };
        active = true;
    }

    void Move() {
        if (active) {
            y -= predkosc_pocisku;
            rect = { x, y, width, height };
        }
    }
    void Draw(SDL_Renderer* renderer, SDL_Texture* bulletTexture) {
        if (active) {
            // Use renderer and bulletTexture to draw the bullet
            SDL_RenderCopy(renderer, bulletTexture, NULL, &rect);
        }
    }
};


class Player {
public:
    int x, y, width, height;
    int score;
    SDL_Rect rect;
    vector<Bullet> bullets;
    int currentBullet;
    Uint32 lastWeaponFire; ///////////////////////////testy
    Player()
    {
        this->x = 10;
        this->y = 10;
        this->width = 30;
        this->height = 30;
        this->rect = { x,y,width,height };
        this->score = 0;
        lastWeaponFire = SDL_GetTicks(); ///////////////////////////testy
    }
    void MoveCoordinates(int nx, int ny)
    {
        this->x = nx;
        this->y = ny;
        this->rect = { x,y,width,height };
    }
    void MoveLeft()
    {
        if (x > 0)
            x = x - 10;
        this->rect = { x,y,width,height };
    }
    void MoveRight()
    {
        if (x + width < 800) //w przyszlosci dac rozdzielczosc nie sztywna wartosc
            x = x + 10;
        this->rect = { x,y,width,height };
    }

    void Shoot() {
        Bullet newBullet;
        newBullet.Shoot(x, y);
        bullets.push_back(newBullet);
    }
};

class Engine {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int Width, Height;
    enum GameStateType { PAUSE, RUN, GAMEOVER, START };
    GameStateType GameState = START;
    Player p1;
    Enemies e1;
    BitmapHandler bh1 = BitmapHandler();
    SDL_Texture* Tex1; //= bh1.LoadTexture("Textury/alien1.png", renderer);
    SDL_Texture* Tex2; //= bh1.LoadTexture("Textury/alien2.png", renderer);
    SDL_Texture* Tex3;
    SDL_Texture* Pause;
    SDL_Texture* GameOver;
    SDL_Texture* Start;
    SDL_Texture* Background1;
    SDL_Texture* Background2;
    AnimatedObject a1 = AnimatedObject();
    BitmapObject b1 = BitmapObject();
    SpriteObject s1 = SpriteObject();

    SDL_Texture* BulletTexture;
    /////////////////////
    //fpsy od
    const int FPS = 30;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    float old_time = SDL_GetTicks();
    // fps do oraz w while
    bool isRunning = true;
    //SDL_Event event;
    ///////////////////
   /// SDL_Rect Testa;/////////////////////////testy
   // int tmpTime=0;/////////////////////////testy


    Engine(int x, int y) {
       
        //this->Testa= { 10,300,25,25 };/////////////////////////testy
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
    void CheckCollisions() {
        for (int i = 0; i < p1.bullets.size(); i++) {
            if (p1.bullets[i].active) {
                for (int j = 0; j < sizeof(e1.tab) / sizeof(e1.tab[0]); j++) {
                    if (e1.tab[j].alive) {
                        if (CheckCollision(p1.bullets[i], e1.tab[j])) {
                            // Kolizja między pociskiem a obcym statkiem kosmicznym.
                            p1.bullets[i].active = false;
                            e1.tab[j].alive = false;
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
            e1.dead++;
            return true; // Kolizja.
        }
        return false; // Brak kolizji.
    }

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

    void AlienReinforcement()
    {
        if (e1.dead == (sizeof(e1.tab) / sizeof(e1.tab[0])))
        {
            e1.BasePosition();
            e1.IntEnemies();
        }
    }


    //Pętla główna gry, wyświetlanie okna

    void Run() {
        ///// wywalone do góry
        //     ||
        /////  \/
        /*//fpsy od
        const int FPS = 30;
        const int frameDelay = 1000 / FPS;
        Uint32 frameStart;
        int frameTime;
        float old_time = SDL_GetTicks();
        // fps do oraz w while
        bool isRunning = true;
        //SDL_Event event;*/
        Background1 = bh1.LoadTexture("Textury/Background1.png", renderer);
        Start = bh1.LoadTexture("Textury/Start.png", renderer);
        Pause = bh1.LoadTexture("Textury/Pause.png", renderer);
        GameOver = bh1.LoadTexture("Textury/GameOver.png", renderer);
        Background2 = bh1.LoadTexture("Textury/Background2.png", renderer);
        Tex1 = bh1.LoadTexture("Textury/alien1.png", renderer);
        Tex2 = bh1.LoadTexture("Textury/alien2.png", renderer);
        Tex3 = bh1.LoadTexture("Textury/pocisk.png", renderer);


        while (isRunning) {

            switch (GameState) {
            case START: {
                /*Background1 = bh1.LoadTexture("Textury/Background1.png", renderer);
                Start = bh1.LoadTexture("Textury/Start.png", renderer);*/
                SDL_Rect back = { 0,0,Width,Height };
                SDL_Rect tmp = { 300,100,200,300 };
                // SDL_Rect tmp1 = { 200,100,50,50 };
                 // Draw();
                // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                // SDL_RenderFillRect(renderer, &tmp);
                SDL_RenderCopy(renderer, Background1, NULL, &back);
                SDL_RenderCopy(renderer, Start, NULL, &tmp);
                if (SDLK_TAB == event.key.keysym.sym)
                    GameState = RUN;
                break;
            }
            case PAUSE: {
                //Background2 = bh1.LoadTexture("Textury/Background2.png", renderer);
                /*Pause = bh1.LoadTexture("Textury/Pause.png", renderer);*/
                SDL_Rect back = { 0,0,Width,Height };
                SDL_Rect tmp = { 100,100,50,50 };
                Draw();
                //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                //SDL_RenderFillRect(renderer, &tmp);
                //SDL_RenderCopy(renderer, Background2, NULL, &back);
                SDL_RenderCopy(renderer, Pause, NULL, &tmp);
                if (SDLK_TAB == event.key.keysym.sym)
                    GameState = RUN;
                break;
            }
            case RUN: {
                /*Background2 = bh1.LoadTexture("Textury/Background2.png", renderer);
                SDL_Rect back = { 0,0,Width,Height };
                SDL_RenderCopy(renderer, Background2, NULL, &back);*/
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
                /*e1.BasePosition();
                e1.IntEnemies();
                p1.score = 0;*/
                /*GameOver = bh1.LoadTexture("Textury/GameOver.png", renderer);*/
                Draw();
                SDL_Rect tmp = { 300,100,200,300 };
                SDL_RenderCopy(renderer, GameOver, NULL, &tmp);
                // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                 //SDL_RenderFillRect(renderer, &tmp);
                if (SDLK_TAB == event.key.keysym.sym) {
                    e1.BasePosition();
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
                // tmpTime = frameDelay - frameTime;
                SDL_Delay(frameDelay - frameTime);
            } // do
           // Testa.x += 1 * (frameDelay - frameTime);/////////////////////////testy
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

    void UpdateBullets() {
        for (int i = 0; i < p1.bullets.size(); i++) {
            p1.bullets[i].Move();
            if (p1.bullets[i].y < 0) {
                p1.bullets.erase(p1.bullets.begin() + i); // Usunięcie obiektu ze vectora
            }
        }
    }


    void DrawBullets() {
        for (int i = 0; i < p1.bullets.size(); i++) {
            if (p1.bullets[i].active) {
                //SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                //SDL_RenderFillRect(renderer, &p1.bullets[i].rect);
                p1.bullets[i].Draw(renderer, BulletTexture);
                //SDL_RenderCopy(renderer, p1.bullets[i].Texture, NULL, &p1.bullets[i].rect);
            }
        }
    }


    void Draw()
    {
        /*Background2 = bh1.LoadTexture("Textury/Background2.png", renderer);*/
        SDL_Rect back = { 0,0,Width,Height };
        SDL_RenderCopy(renderer, Background2, NULL, &back);
        DrawBullets();
        /*Tex1 = bh1.LoadTexture("Textury/alien1.png", renderer);
        Tex2 = bh1.LoadTexture("Textury/alien2.png", renderer);*/
        //Player p1(this->Width/2,this->Height-25);
        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
        //SDL_RenderCopy(renderer, Tex1, NULL, &p1.rect);
        //s1.Draw(renderer, Tex1, p1.rect);
        //SDL_RenderFillRect(renderer, &p1.rect);
        SDL_RenderCopy(renderer, Tex2, NULL, &p1.rect);
        //SDL_RenderFillRect(renderer, &Testa);/////////////////////////testy
        for (int i = 0; i < (sizeof(e1.tab) / sizeof(e1.tab[0])); i++)
        {
            if (e1.tab[i].alive == 1)
                SDL_RenderCopy(renderer, Tex1, NULL, &e1.tab[i].rect);
            // SDL_RenderFillRect(renderer, &e1.tab[i].rect);
        }


    }
    void MovementHandle()
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_LEFT]) {
            p1.MoveLeft();
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            p1.MoveRight();
        }

        // Dodaj obsługę innych klawiszy według potrzeb.
        if (state[SDL_SCANCODE_SPACE] && SDL_GetTicks() > p1.lastWeaponFire + 500) { ///to 500 to opóżnienie w ms
            p1.Shoot();
            p1.lastWeaponFire = SDL_GetTicks();
        }


    }

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

    // Desktruktor
    ~Engine() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }


};

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
