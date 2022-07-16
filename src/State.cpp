#include "State.h"
#include "Face.h"
#include "TileMap.h"
#include "TileSet.h"

#include <cmath>
#include "Sound.h"

State::State() : music("Recursos/audio/stageState.ogg") {

	//Background GameObject creation
	GameObject* backGround;
	Sprite* sprite;

	backGround = new GameObject();
	sprite = new Sprite("Recursos/img/ocean.jpg", *backGround);
	backGround->box.x = 0;
	backGround->box.y = 0;
	backGround->AddComponent(sprite);
	objectArray.emplace_back(backGround);
	
	//TileMap GameObject creation
	GameObject* scenery;
	TileMap* tileMap;
	TileSet* tileSet;

	scenery = new GameObject();
	scenery->box.x = 0;
	scenery->box.y = 0;
	tileSet = new TileSet(64,64,"Recursos/img/tileset.png");
	tileMap = new TileMap(*scenery,"Recursos/map/tileMap.txt",tileSet);
	scenery->AddComponent(tileMap);
	objectArray.emplace_back(scenery);

    quitRequested = false;
    music.Play(-1);

}

State::~State() {

    objectArray.clear();

}

void State::LoadAssets() {

    return;

}

void State::Update(float dt) {

	Input();
	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
	for(int i = 0; i < objectArray.size(); i++) {
	    if (objectArray[i]->IsDead()) {
		   objectArray.erase(objectArray.begin()+i);	
		}
	}

}

void State::Render() {

	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}

    return;

}

void State::AddObject(int mouseX, int mouseY) {

	GameObject* enemy;
	Sprite* sprite;
	Sound* sound;
	Face* face;

	enemy = new GameObject();
	sprite = new Sprite("Recursos/img/penguinface.png", *enemy);
	sound = new Sound(*enemy, "Recursos/audio/boom.wav");
	face = new Face(*enemy);

	//Adjust the coordenades to render the image center on it
	enemy->box.x = mouseX - sprite->GetWidth()/2;
	enemy->box.y = mouseY + sprite->GetHeight()/2;

	enemy->AddComponent(sprite);
	enemy->AddComponent(sound);
	enemy->AddComponent(face);

	objectArray.emplace_back(enemy);

}

bool State::QuitRequested() {

    return quitRequested;

}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.PointInRect( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).RotateVec2( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}