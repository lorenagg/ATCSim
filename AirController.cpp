/*
 * AirController.cpp
 *
 *  Created on: 21/07/2014
 *      Author: paco
 *
 *  Copyright 2014 Francisco Martín
 *
 *  This file is part of ATCSim.
 *
 *  ATCSim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ATCSim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ATCSim.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include "AirController.h"
#include "Airport.h"
#include "Flight.h"
#include "Position.h"
#include <list>

int N = 3;
Route ruta1[3];
Route ruta2[3]; // el numero de dentro del corchete sera el num de puntos que tendra la ruta
Route espera1[3];
Route espera2[3];

AirController::AirController() {
	// TODO Auto-generated constructor stub
	//aqui me tengo que añadir los puntos de la ruta

	ruta1[0].pos = Position(500.0, -500.0, 100.0);
	ruta1[0].speed = 500.0;
	ruta1[1].pos = Position(-750.0, -500.0, 30.0);
	ruta1[1].speed = 200.0;
	ruta1[2].pos = Position(-750.0, 0.0, 25.0); // aqui me he declarado los puntos de una ruta
	ruta1[2].speed= 20.0;

	ruta2[0].pos= Position(-900.0, -500.0, 100.0);
	ruta2[1].pos = Position(-750.0, -500.0, 30.0);
	ruta2[2].pos = Position(-750.0, 0.0, 25.0);
	ruta2[0].speed = 500.0;
	ruta2[1].speed = 200.0;
	ruta2[2].speed= 20.0;

	//hago lo mismo para definirme las esperas

	espera1[0].pos = Position(-950.0, -950.0,150.0);
	espera1[0].speed = 500.0 ;
	espera1[1].pos = Position(500.0, -950.0, 150.0);
	espera1[1].speed = 500.0;
	espera1[2].pos = Position(-850.0, -600.0, 150.0);
	espera1[2].speed = 500.0;

	espera2[0].pos = Position(-950.0, 950.0,150.0);
	espera2[0].speed = 500.0 ;
	espera2[1].pos = Position(500.0, 950.0, 150.0);
	espera2[1].speed = 500.0;
	espera2[2].pos = Position(-850.0, 600.0, 150.0);
	espera2[0].speed = 500.0;

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void añadirRuta(Flight* avion, Route* ruta) {
	for (int i = 0; i < N; i++) {
		avion->getRoute()->push_back(ruta[i]);
	}
}

void eligirRutaPista(Flight* avion) {
	float distancia1, distancia2;
	distancia1 = avion->getPosition().distance(ruta1[0].pos);
	distancia2 = avion->getPosition().distance(ruta2[0].pos);

	if (distancia1 <= distancia2) {
		añadirRuta(avion, ruta1);
	} else {
		añadirRuta(avion, ruta2);
	}
}

int eslamayor(float* dis, int maximo) {
	float mayor = -999.0;
	int resultado = 0;
	for (int i = 0; i < maximo; i++) {
		if (mayor < dis[i]) {
			mayor = dis[i];
			resultado = i;
		}
	}
	return resultado;
}

void elegirRutaEspera(Flight* avion) {
	float distancia[4];
	int entrada;
	//esto pertenece al circuito de espera 1
	distancia[0] = avion->getPosition().distance(espera1[0].pos);
	distancia[1] = avion->getPosition().distance(espera1[1].pos);
	// y esto pertenece al circuito de espera 2
	distancia[2] = avion->getPosition().distance(espera2[0].pos);
	distancia[3] = avion->getPosition().distance(espera2[1].pos);
	entrada = eslamayor(distancia, 4);
	std::cout << "el avion " <<avion->getId()<<" elige "<<entrada<< std::endl;
	switch (entrada) {
	case 0: //circuito de espera 1
		avion->getRoute()->push_back(espera1[0]);
	case 1:
		avion->getRoute()->push_back(espera1[1]);
		avion->getRoute()->push_back(espera1[2]);
		break;
	case 2: //circuito de espera 2
		avion->getRoute()->push_back(espera2[0]);
	case 3:
		avion->getRoute()->push_back(espera2[1]);
		avion->getRoute()->push_back(espera2[2]);
		break;
	default:
		;
	}
}

void AirController::doWork() {
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	std::list<Flight*>::iterator it;
	Position pos1(500.0, 0.0, 100.0);
	Position pos2(0.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 25.0);
	bool liberarPista = true;
	Route r1, r2, r3;

	r1.pos = pos1;
	r1.speed = 500.0;
	r2.pos = pos2;
	r2.speed = 19.0;
	r3.pos = pos3;
	r3.speed = 15.0;

	for (it = flights.begin(); it != flights.end(); ++it) {
		if (pistaAsignada == "") {
			pistaAsignada= (*it)->getId();
			eligirRutaPista(*it);

		} else {
			if ((*it)->getRoute()->empty())
				elegirRutaEspera(*it);
		}
	}

	for (it = flights.begin(); it != flights.end(); ++it) {
		if (pistaAsignada == (*it)->getId()) {
			liberarPista = false;
			break;
		}
	}
	if (liberarPista) {
		pistaAsignada ="";
	}

}
