#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <SDL.h>
#include <SDL_ttf.h>
#include<fstream>

using namespace std;

void renderPlayer(SDL_Renderer* renderer, SDL_Rect player, int x, int y, int scale, vector<int> tailX, vector<int> tailY, int tailLength) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	player.w = scale;
	player.h = scale;

	for (int i = 0; i < tailLength; i++) {
		player.x = tailX[i];
		player.y = tailY[i];
		SDL_RenderFillRect(renderer, &player);
	}

	player.x = x;
	player.y = y;

	SDL_RenderFillRect(renderer, &player);
}

void renderFood(SDL_Renderer* renderer, SDL_Rect food) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &food);
}

void renderScore(SDL_Renderer* renderer, int tailLength, int hscore , int spnumber) {
	SDL_Color Black = { 0, 0, 0 };

	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * (6-spnumber))).c_str(), Black);
	SDL_Surface* highscore = TTF_RenderText_Solid(font, (string("High Score: ") + to_string(hscore )).c_str(), Black);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Texture* highscoreMessage = SDL_CreateTextureFromSurface(renderer, highscore);
	SDL_Rect scoreRect;
	SDL_Rect highscoreRect;
	highscoreRect.w = 100;
	highscoreRect.h = 40;
	highscoreRect.x = 350;
	highscoreRect.y = 0;
	scoreRect.w = 100;
	scoreRect.h = 40;
	scoreRect.x = 150;
	scoreRect.y = 0;

	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);
	SDL_RenderCopy(renderer, highscoreMessage, NULL, &highscoreRect);

	TTF_CloseFont(font);
}

bool checkCollision(int foodx, int foody, int playerx, int playery) {

	if (playerx == foodx && playery == foody){
		return true;
	}

	return false;
}

pair<int, int> getFoodSpawn(vector<int> tailX, vector<int> tailY, int playerX, int playerY, int scale, int wScale, int tailLength) {
	bool valid = false;
	int x = 0;
	int y = 0;
	srand(time(0));
	x = scale * (rand() % wScale);
	y = scale * (rand() % wScale);
	valid = true;
	for (int i = 0; i < tailLength; i++) {

		if ((x == tailX[i] && y == tailY[i]) || (x == playerX && y == playerY)) {
			valid = false;
		}

	}

	if (!valid) {
		pair<int, int> foodLoc;
		foodLoc = make_pair(-100, -100);
		return foodLoc;
	}

	pair<int, int> foodLoc;
	foodLoc = make_pair(x, y);

	return foodLoc;
}

void gameOver(SDL_Renderer* renderer, SDL_Event event,int tailLength,int spnumber) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "Game Over", Red);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to retry", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * (6-spnumber))).c_str(), Black);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = 225;
	gameoverRect.y = 200;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = 175;
	retryRect.y = 350;
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = 275;
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}

}

void youWin(SDL_Renderer* renderer, SDL_Event event, int tailLength,int spnumber) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Yellow = { 255, 255, 0 };
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "You won!", Yellow);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to play again", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * (6-spnumber))).c_str(), Black);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = 225;
	gameoverRect.y = 200;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = 175;
	retryRect.y = 350;
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = 275;
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}
        }

	}

}


void setting(SDL_Renderer* renderer,SDL_Event event,int &number){
     SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Yellow = { 255, 255, 0 };
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;

		return;
	}

        SDL_Surface* classic = TTF_RenderText_Solid(font, "1.Classic", White);
        SDL_Surface* modern = TTF_RenderText_Solid(font, "2.Modern", White);
        SDL_Surface* snake = TTF_RenderText_Solid(font, "Snake Game", Yellow);
        SDL_Texture* classicMessage = SDL_CreateTextureFromSurface(renderer, classic);
        SDL_Texture* modernMessage = SDL_CreateTextureFromSurface(renderer, modern);
        SDL_Texture* snakeMessage = SDL_CreateTextureFromSurface(renderer, snake);


        SDL_Rect snakeRect;
        SDL_Rect classicRect;
        SDL_Rect modernRect;
        SDL_Rect mouse;
        classicRect.w = 100;
	    classicRect.h = 50;
	    classicRect.x = 278;
	    classicRect.y = 300;
        modernRect.w = 100;
        modernRect.h = 50;
	    modernRect.x = 278;
	    modernRect.y = 400;
	    snakeRect.w = 200;
	    snakeRect.h = 100;
	    snakeRect.x = 238;
	    snakeRect.y = 100;


    SDL_RenderCopy(renderer, snakeMessage, NULL, &snakeRect);
	SDL_RenderCopy(renderer, classicMessage, NULL, &classicRect);
	SDL_RenderCopy(renderer, modernMessage, NULL, &modernRect);

    TTF_CloseFont(font);

while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_1) {
                number=1;
				return;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_2) {
                number=2;
				return;
			}

		}

	}

}

void speed(SDL_Renderer* renderer,SDL_Event event,int &spnumber){
    SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Yellow = { 255, 255, 0 };

	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;

		return;
	}

        SDL_Surface* speed = TTF_RenderText_Solid(font, "Speed    1.A     2.S     3.D     4.F     5.G", White);
        SDL_Texture* speedMessage = SDL_CreateTextureFromSurface(renderer, speed);

        SDL_Rect speedRect;
        speedRect.w = 400;
	    speedRect.h = 150;
	    speedRect.x = 125;
	    speedRect.y = 225;


	    SDL_RenderCopy(renderer, speedMessage, NULL, &speedRect);

	     TTF_CloseFont(font);


	    while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                spnumber=1;
				return;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                spnumber=2;
				return;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                spnumber=3;
				return;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                spnumber=4;
				return;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_G) {
                spnumber=5;
				return;
			}

		}

	}
}
int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);

	if (TTF_Init() < 0) {
		cout << "Error: " << TTF_GetError() << endl;
	}
    int number;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_Event event2;
	SDL_Event event3;

	SDL_Rect player;
	player.x = 0;
	player.y = 0;
	player.h = 0;
	player.w = 0;

	int tailLength = 0;


	vector<int> tailX;
	vector<int> tailY;


	int scale = 25;
	int wScale = 25;


	int x = 0;
	int y = 0;
	int prevX = 0;
	int prevY = 0;

	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	bool inputThisFrame = false;
	bool redo = false;

	SDL_Rect food;
	food.w = scale;
	food.h = scale;
	food.x = 0;
	food.y = 0;

    int highscore1,highscore2;
	ifstream sfile("highscore.txt");
	if (!sfile) {
                   cout << "Error: cannot open file\n";
    }
    else {
              sfile >> highscore1 >> highscore2;

 }
	pair<int, int> foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
	food.x = foodLoc.first;
	food.y = foodLoc.second;

	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scale*wScale+1, scale*wScale+1, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	float time = SDL_GetTicks() / 1000;


	setting(renderer, event2, number);
	int spnumber;
	SDL_RenderClear(renderer);
    speed(renderer, event3, spnumber);
    int  spnumber1=spnumber*75;

if (number==1){

while (true) {

		float newTime = SDL_GetTicks() / spnumber1;
		float delta = newTime - time;
		time = newTime;

		inputThisFrame = false;
		if (tailLength >= 15) {
			youWin(renderer, event, tailLength,spnumber);
			x = 0;
			y = 0;
			up = false;
			left = false;
			right = false;
			down = false;
			tailX.clear();
			tailY.clear();
			tailLength = 0;
			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

			food.x = foodLoc.first;
			food.y = foodLoc.second;
		}
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				exit(0);
			}
			if (event.type == SDL_KEYDOWN && inputThisFrame == false) {
				if (down == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
					up = true;
					left = false;
					right = false;
					down = false;
					inputThisFrame = true;
				}
				else if (right == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					up = false;
					left = true;
					right = false;
					down = false;
					inputThisFrame = true;
				}
				else if (up == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					up = false;
					left = false;
					right = false;
					down = true;
					inputThisFrame = true;
				}
				else if (left == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					up = false;
					left = false;
					right = true;
					down = false;
					inputThisFrame = true;
				}

			}

		}

		prevX = x;
		prevY = y;

		if (up) {

            y -= delta * scale;
		}
		else if (left) {

			x -= delta * scale;
		}
		else if (right) {

			x += delta * scale;
		}
		else if (down) {

			y += delta * scale;
		}

		if (redo == true) {

			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

		}

		if (checkCollision(food.x, food.y, x, y)){
            foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

			tailLength++;
		}

		if (delta * scale == 25) {

			if (tailX.size() != tailLength) {
				tailX.push_back(prevX);
				tailY.push_back(prevY);
			}

			for (int i = 0; i < tailLength; i++) {

				if (i > 0) {
					tailX[i - 1] = tailX[i];
					tailY[i - 1] = tailY[i];
				}

			}

			if (tailLength > 0) {
				tailX[tailLength - 1] = prevX;
				tailY[tailLength - 1] = prevY;
			}

		}
		for (int i = 0; i < tailLength; i++) {

			if (x == tailX[i] && y == tailY[i]) {
				gameOver(renderer, event, tailLength,spnumber);
				x = 0;
				y = 0;
				up = false;
				left = false;
				right = false;
				down = false;
				tailX.clear();
				tailY.clear();
				tailLength = 0;
				redo = false;

				foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
				if (food.x == -100 && food.y == -100) {
					redo = true;
				}

				food.x = foodLoc.first;
				food.y = foodLoc.second;
			}

		}

		if (x < 0 || y < 0 || x > scale * wScale - scale || y > scale * wScale - scale) {
			gameOver(renderer, event, tailLength,spnumber);
			x = 0;
			y = 0;
			up = false;
			left = false;
			right = false;
			down = false;
			tailX.clear();
			tailY.clear();
			tailLength = 0;
			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

		}
        if (highscore1<  (tailLength* (6-spnumber) ) ) {
                highscore1=tailLength*(6-spnumber);

               ofstream sfileout("highscore.txt");
	           sfileout << highscore1 << " "  <<highscore2;

        }

		renderFood(renderer, food);
		renderPlayer(renderer, player, x, y, scale, tailX, tailY, tailLength);
		renderScore(renderer, tailLength,highscore1,spnumber);
		SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
		SDL_RenderClear(renderer);
	}

}


if (number==2){
    while (true) {

		float newTime = SDL_GetTicks() / spnumber1;
		float delta = newTime - time;
		time = newTime;

		inputThisFrame = false;

		if (tailLength >= 15) {
			youWin(renderer, event, tailLength,spnumber);
			x = 0;
			y = 0;
			up = false;
			left = false;
			right = false;
			down = false;
			tailX.clear();
			tailY.clear();
			tailLength = 0;
			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

			food.x = foodLoc.first;
			food.y = foodLoc.second;
		}

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.type == SDL_KEYDOWN && inputThisFrame == false) {

				if (down == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
					up = true;
					left = false;
					right = false;
					down = false;
					inputThisFrame = true;
				}
				else if (right == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					up = false;
					left = true;
					right = false;
					down = false;
					inputThisFrame = true;
				}
				else if (up == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					up = false;
					left = false;
					right = false;
					down = true;
					inputThisFrame = true;
				}
				else if (left == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					up = false;
					left = false;
					right = true;
					down = false;
					inputThisFrame = true;
				}

			}

		}
		prevX = x;
		prevY = y;


		if (up) {
            if (y<0) y += 625;
			y -= delta * scale;
		}
		else if (left) {
		    if (x<0) x=x+625;
			x -= delta * scale;
		}
		else if (right) {
            if (x>600) x=x-625;
			x += delta * scale;

		}
		else if (down) {
		    if (y>600) y=y-625;
			y += delta * scale;
		}

		if (redo == true) {

			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

		}
		if (checkCollision(food.x, food.y, x, y)) {
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

			tailLength++;
		}
		if (delta * scale == 25) {
			if (tailX.size() != tailLength) {
				tailX.push_back(prevX);
				tailY.push_back(prevY);
			}
			for (int i = 0; i < tailLength; i++) {

				if (i > 0) {
					tailX[i - 1] = tailX[i];
					tailY[i - 1] = tailY[i];
				}

			}

			if (tailLength > 0) {
				tailX[tailLength - 1] = prevX;
				tailY[tailLength - 1] = prevY;
			}

		}

		for (int i = 0; i < tailLength; i++) {

			if (x == tailX[i] && y == tailY[i]) {
				gameOver(renderer, event, tailLength,spnumber);
				x = 0;
				y = 0;
				up = false;
				left = false;
				right = false;
				down = false;
				tailX.clear();
				tailY.clear();
				tailLength = 0;
				redo = false;

				foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
				if (food.x == -100 && food.y == -100) {
					redo = true;
				}

				food.x = foodLoc.first;
				food.y = foodLoc.second;
			}

		}
		if (highscore2<  (tailLength* (6-spnumber) ) ) {
                highscore2=tailLength*(6-spnumber);

               ofstream sfileout("highscore.txt");
	           sfileout << highscore1 << " "  <<highscore2;

		}
		renderFood(renderer, food);
		renderPlayer(renderer, player, x, y, scale, tailX, tailY, tailLength);
		renderScore(renderer, tailLength,highscore2, spnumber);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
		SDL_RenderClear(renderer);
	}


}


	SDL_DestroyWindow(window);

	TTF_Quit();

	SDL_Quit();


	return 0;

}
