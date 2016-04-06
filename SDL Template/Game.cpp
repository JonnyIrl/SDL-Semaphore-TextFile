#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "SDL_thread.h"
#include <string>

#undef main
#include "Renderer.h"
#include "Sprite.h"
#include "InputHandler.h"
#include <list>
using namespace std;

void Init();
void DrawGame();

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


Sprite* backGroundImage;
InputHandler inputHandler = InputHandler();


int nr = 0; //num of readers

//Data access semaphore
SDL_sem* gDataLock = NULL;
SDL_sem* mutexR = NULL;

int ReaderThread(void * data);
int WriterThread(void * data);

bool work = true;

int main()
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;



	list<SDL_Thread*> readers;
	list<SDL_Thread*> writers;

	//Initialize semaphore
	gDataLock = SDL_CreateSemaphore(1);
	mutexR = SDL_CreateSemaphore(1);

	for (int i = 0; i < 5; i++)
	{
		readers.push_back(SDL_CreateThread(ReaderThread, "reader Thread", NULL));
		writers.push_back(SDL_CreateThread(WriterThread, "writer Thread", &i));
	}

	work = false;

	std::cin.get();
	system("PAUSE");


}

void Init()
{
	backGroundImage = new Sprite();
	SDL_Rect destination = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect Source = { 0, 0, 1240, 720 };
	SDL_Rect destination1 = { 0, -200, SCREEN_WIDTH, SCREEN_HEIGHT };
	backGroundImage->Init("Assets/menu.png", destination1, Source);

}

void DrawGame()
{
	Renderer::GetInstance()->ClearRenderer();

	backGroundImage->Draw();

	Renderer::GetInstance()->RenderScreen();
}

int ReaderThread(void * data)
{
	while (work)
	{
		SDL_SemWait(mutexR);

		//Number of readers
		nr++;

		//If its first, then get the lock to let you read the text file.
		if (nr == 1)
		{
			SDL_SemWait(gDataLock);
		}
		SDL_SemPost(mutexR);

		//read the text file;
		cout << "reading the text file" << endl;

		ifstream myfile("text.txt");
		string line;
		//Open text file
		if (myfile.is_open())
		{
			int count = 1;
			//Go through each line and output to console...
			while (getline(myfile, line))
			{
				cout << "Reading line no. " << count << " It says: " << line << endl;
				count++;
			}
			myfile.close();
		}

		SDL_SemWait(mutexR);

		//Reduce No. of readers
		nr--;

		if (nr == 0)
		{
			SDL_SemPost(gDataLock);
		}


		//If its the last, then release the lock
		SDL_SemPost(mutexR);

		//Wait randomly to give writers a chance to acquire lock
		SDL_Delay(15 + rand() % 600);
	}
	return 0;
}


int WriterThread(void * data)
{
	int i = *(int *)data;
	while (work)
	{
		SDL_SemWait(gDataLock);
		//Write to the text file;
		cout << "Writing to text file" << endl;

		ofstream myfile;
								//Used to append lines
		myfile.open("text.txt", std::ios_base::app);

		//Just write Thead and the current thread to the text file..
		myfile << "Thread: " << i << endl;
		myfile.close();

		SDL_SemPost(gDataLock);

		//Wait randomly to give writers a chance to acquire lock
		SDL_Delay(15 + rand() % 600);
	}
	return 0;
}