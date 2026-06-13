/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Dagim Abeje; Milena-Aika Fujita; Victoria Kilgore; Serena Mili
 * adagi; aikafuji; kilgorev; smili
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>


char intToChar(int num) {
    return static_cast<char>(num + '0');
}

//Make the code run getAIPickUpList if pickUpList is true
string getAIMoveString(const BuildingState& buildingState) {
    int greatestNumPeopleF = 0;
    int servicedFloor = 0;
    string floor = "";
    string elevator = "";
    string move = "";
    
    
    for (int i = 0; i < NUM_ELEVATORS; i++){   
        if (buildingState.elevators[i].isServicing){
            servicedFloor = buildingState.elevators[i].targetFloor;
        }
        
        if (!(buildingState.elevators[i].isServicing)){
            elevator = intToChar(i);
            
            for (int j = 0; j < NUM_FLOORS; j++){
                if (buildingState.floors[j].numPeople 
                    > greatestNumPeopleF && j != servicedFloor) {
                    greatestNumPeopleF = j;
                    
                    if (buildingState.elevators[i].currentFloor == j) {
                        return "e" + elevator + "p";
                    }
                }
            }
            
            if (greatestNumPeopleF == 0) {
                return "";
            }
            
            floor = intToChar(greatestNumPeopleF);
            
            return "e" + elevator + "f" + floor;
        }
    }
    
    return "";
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
                       const Floor& floorToPickup) { 
    int goUp = 0;
    int goDown = 0;
    string peopleDown;
    string peopleUp;
    
    for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
        if (floorToPickup.getPersonByIndex(i).getCurrentFloor() 
            > floorToPickup.getPersonByIndex(i).getTargetFloor()) {
            goDown += 1;
            peopleDown += intToChar(i);
            
        } else {
            goUp += 1;
            peopleUp += intToChar(i);
            
        }
    }

    if (floorToPickup.getHasUpRequest() 
        && floorToPickup.getHasDownRequest()) {
        if (goUp > goDown) {
            return peopleUp;
        
        } else {
            return peopleDown;
        
        }
    }
    
    if (floorToPickup.getHasUpRequest()) {
        return peopleUp;
    
    } else if (floorToPickup.getHasDownRequest()) {
        return peopleDown;
    
    }
    
    return "";
}
