#include "SDLRunningGame.h"

void SDLRunningGame::audioInitialization () {
    //Audio Initialization
    SDLRunningGame::music = new Music(gameMusicPath);
    music->play();
}

SDL_Texture* SDLRunningGame::createTransparentTexture(SDL_Renderer *renderer){
    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(backgroundTransparentPath);

    if(loadingSurface == NULL)
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;

    else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
        if(backgroundTexture == NULL){
            cout<<"Error creating background layer: "<<SDL_GetError()<<endl;

        }

        SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
        return backgroundTexture;
    }
    return backgroundTexture;
}

void SDLRunningGame::layersBuilding (){
    //Layers Building
    SDLRunningGame::backgroundLayer0 = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::backgroundLayer1 = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::playersLayer = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
}

void SDLRunningGame::spritesBuilding () {
    //Sprites Building
    SDLRunningGame::backgroundSprite0 = new BackgroundSprite(SDLRunningGame::backgroundLayer0,
                                                         SDLRunningGame::mainRenderer,window_width,window_height);
    SDLRunningGame::backgroundSprite0->setUpImage("sprites/backgrounds/backgroundMetal1.png");

    SDLRunningGame::backgroundPlayersSprite = new BackgroundSprite(SDLRunningGame::backgroundLayer1,
                                                         SDLRunningGame::mainRenderer,window_width,window_height);
    backgroundPlayersSprite->setUpImage("sprites/backgrounds/backgroundMetal2.png");
    backgroundPlayersSprite->set_position(0, window_height / 2);
    backgroundPlayersSprite->setHeight(window_height / 2);

    SDLRunningGame::marcoSprite = new Marco(SDLRunningGame::playersLayer, SDLRunningGame::mainRenderer);
}

SDLRunningGame::SDLRunningGame (SDL_Window *mainWindow, SDL_Renderer *mainRenderer) {
    SDLRunningGame::mainWindow = mainWindow;
    SDL_GetWindowSize(mainWindow, &window_width, &window_height);

    SDLRunningGame::mainRenderer = mainRenderer;
//_______________________________________________________________________________________
   SDLRunningGame::layersBuilding();
//_______________________________________________________________________________________
    SDLRunningGame::spritesBuilding();
//_______________________________________________________________________________________
    SDLRunningGame::audioInitialization();
//____________________________________________________________________________________________
    SDLRunningGame::handleLeftKey = SDLRunningGame::handleRightKey = 0;
}

struct event SDLRunningGame::eventsHandler(SDL_Event* sdlEvent) {
    struct event nuevoEvento;

    if (sdlEvent->type == SDL_KEYDOWN){  //si aprieto tal tecla:
        switch (sdlEvent->key.keysym.sym){
        case SDLK_LEFT:
            printf("aprieto flecha izquierda");
            //handleLeftKey != 0 no volver a enviarlo al servidor
            if(handleLeftKey>0){
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
                return nuevoEvento;
            }
            else{
                nuevoEvento.data.code = EventCode::SDL_KEYLEFT_PRESSED;
                handleLeftKey = 1;
                return nuevoEvento;
            }
        case SDLK_RIGHT:
            printf("aprieto flecha derecha");
            if(handleRightKey>0){
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
                return nuevoEvento;
            }
            else{
                nuevoEvento.data.code = EventCode::SDL_KEYRIGHT_PRESSED;
                handleRightKey = 1;
                return nuevoEvento;
            }
        case SDLK_UP:
            printf("aprieto flecha arriba");
            if(handleUpKey>0){
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
                return nuevoEvento;
            }
            else{
                nuevoEvento.data.code = EventCode::SDL_KEYUP_PRESSED;
                handleUpKey = 1;
                return nuevoEvento;
            }
        case SDLK_DOWN:
            printf("aprieto flecha abajo");
            if(handleDownKey>0){
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
                return nuevoEvento;
            }
            else{
                nuevoEvento.data.code = EventCode::SDL_KEYDOWN_PRESSED;
                handleDownKey = 1;
                return nuevoEvento;
            }
        default:
            nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            return nuevoEvento;
        }
    }

    else if(sdlEvent->type == SDL_KEYUP){   //si dejo de apretar una tecla
        switch (sdlEvent->key.keysym.sym){
        case SDLK_LEFT:
            nuevoEvento.data.code = EventCode::SDL_KEYLEFT_RELEASED;
            handleLeftKey = 0;
            return nuevoEvento;
        case SDLK_RIGHT:
            cout<<"solte la flecha der"<<endl;
            nuevoEvento.data.code = EventCode::SDL_KEYRIGHT_RELEASED;
            handleRightKey = 0;
            return nuevoEvento;
        case SDLK_UP:
            cout<<"solte la flecha arriba"<<endl;
            nuevoEvento.data.code = EventCode::SDL_KEYUP_RELEASED;
            handleRightKey = 0;
            return nuevoEvento;
        case SDLK_DOWN:
            cout<<"solte la flecha abajo"<<endl;
            nuevoEvento.data.code = EventCode::SDL_KEYDOWN_RELEASED;
            handleRightKey = 0;
            return nuevoEvento;
        default:
            nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            return nuevoEvento;

        }
    }
    nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
    return nuevoEvento;

//    SDL_Delay(100); //antes de procesar otro evento esta pausando 2 milisegundos
}

void SDLRunningGame::handleModelState(vector <event> model_state) {
    for (auto event : model_state) {
        cout << "X: " << event.data.x << endl << "Y: " << event.data.y << endl << "H: " << event.data.h << endl;
    }

//TODO: manejar la actualizacion todos los sprites existentes.
    for (auto nuevoEvento : model_state){
        switch(nuevoEvento.data.id){
            case Entity::MARCO:
                this->marcoSprite->handle( nuevoEvento);
            case Entity::TARMA:
                this->tarmaSprite->handle(nuevoEvento);
//            case FIO:
//            case ERI:
//            case ENEMY_NORMAL:
            case Entity::BACKGROUND_Z0:
                this->backgroundSprite0->handle(nuevoEvento);
            case Entity::BACKGROUND_Z1:
                this->backgroundPlayersSprite->handle(nuevoEvento);
            case Entity::BACKGROUND_Z2:
                this->backgroundSprite2->handle(nuevoEvento);

        }
    }

    this->updateWindowSprites();
}

void SDLRunningGame::updateWindowSprites () {
    SDL_RenderClear(SDLRunningGame::mainRenderer);

    SDLRunningGame::backgroundSprite0->actualizarDibujo();
    SDLRunningGame::backgroundPlayersSprite->actualizarDibujo();
    SDLRunningGame::marcoSprite->actualizarDibujo();
    SDLRunningGame::backgroundSprite2->actualizarDibujo();

    SDL_RenderPresent(SDLRunningGame::mainRenderer);
}

//DESTRUCTOR
SDLRunningGame::~SDLRunningGame () {
//____________________________________________________________________________________________
    //Liberar todo

    SDL_DestroyTexture(backgroundLayer0);
    SDL_DestroyTexture(SDLRunningGame::backgroundLayer1);
    SDL_DestroyTexture(SDLRunningGame::playersLayer);
    SDL_DestroyRenderer(SDLRunningGame::mainRenderer);
//    closeMixer();   //ESTA EN EL DESTRUCTOR DE MUSIC
//____________________________________________________________________________________________
    SDL_DestroyWindow(SDLRunningGame::mainWindow);
    SDL_Quit();
}
