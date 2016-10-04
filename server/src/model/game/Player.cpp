/*
 * Player.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include "Player.h"

Player::Player() {
	username = "user";
	sprite = "../../../../client/view/sprites/player/marco.png";
	x = 1;
	y = 1;
	speed = 0;
}

Player::~Player() {
}

void movePlayer(EventCode movimiento){
	switch(movimiento) {
	    case EventCode::CLIENT_DISCONNECT:
	    	// TODO: aca hay que hacer que el personaje aparezca grisado, y se permita
	  		// arrastarlo por la pantalla
	        break;

	    case EventCode::SDL_KEYUP:
	        
	        break;

	    case EventCode::SDL_KEYDOWN:

	        break;

	    case EventCode::SDL_KEYLEFT:
	        
	        break;

	    case EventCode::SDL_KEYRIGHT:

	        break;

	    default:
	        break;
    }

}

struct event Player::playerState(){
	struct event estado;
	struct event_ext eventExt;

    eventExt.code = EventCode::PLAYER_STATUS;
    eventExt.id = Entity::MARCO;  // Hardcodeo el nombre de la entidad
    eventExt.x = 3;
    eventExt.y = 5;
    eventExt.h = 1;  // asumo que en h mando la velocidad

	estado.completion = EventCompletion::FINAL_MSG;
	estado.data = eventExt;

	return estado;
}
