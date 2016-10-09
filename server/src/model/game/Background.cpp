/*
 * Background.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include "Background.h"

Background::Background(int zindex) {
    x=y=0;
    this->zindex = zindex;
}

Background::~Background() {
}

struct event Background::getState(){
	struct event estado;
	struct event_ext eventExt;

    eventExt.code = EventCode::BACKGROUND_STATUS;
    eventExt.id = Entity::LEVEL1_Z1; // 
    eventExt.x = x;
    eventExt.y = y;

	estado.completion = EventCompletion::FINAL_MSG;
	estado.data = eventExt;

	return estado;
}