#include "gameMap.h"

void gameMap::loadMap(string path){
    ifstream file(path);
    if(!file.is_open()) cout <<"load file map khong thanh cong";
    else{
        map arr;
        int length_x, length_y;
        file >> length_x;
        file >> length_y;
        for(int i = 0; i < length_x; i++){
            for(int j = 0; j < length_y; j++){
                file >> arr.arrMap[i][j];
                if(arr.arrMap[i][j] == PLAYER){
                    arr.posPlayerX = i;
                    arr.posPlayerY = j;
                    arr.arrMap[i][j] = FLOOR;
                }
            }
        }
        arr.mapX = length_x;
        arr.mapY = length_y;
        arr.sizeX = (GAME_WIDTH/length_x)/10*10;  
        arr.sizeY = (GAME_HEIGHT/length_y)/10*10; 
        arr.posBoxMoveX = -1;
        arr.posBoxMoveY = -1;
        mainPlayer.setPos( arr.posPlayerX*arr.sizeX ,  arr.posPlayerY*arr.sizeY);
        arr.fileName = path;   
        game_map.push_back(arr);
    }
    file.close();

}

void gameMap::loadTiles(SDL_Renderer* render){
    if(!wall.loadImg("img/block_06.png", render)){
        cout << "load anh wall khong thanh cong" << endl;
    }
    if(!box.loadImg("img/crate_43.png", render)){
        cout << "load anh box khong thanh cong" << endl;
    }
    if(!box_win.loadImg("img/crate_44.png", render)){
        cout << "load anh box_win khong thanh cong" << endl;
    }
    if(!goal.loadImg("img/environment_02.png", render)){
        cout << "load anh goal khong thanh cong" << endl;
    }
    if(!floor.loadImg("img/ground_01.png", render)){
        cout << "load anh floor khong thanh cong" << endl;
    }
    if(!mainPlayer.loadImg("img/player2.png", render)){
        cout << "load anh player khong thanh cong" << endl;
    }
    else mainPlayer.setClips();
}

void gameMap::handelInput(SDL_Event event, SDL_Renderer* render, int& step, animation& animationOj){
    if(animationOj == NONE){
        bool isMove = false;
        boxMove = false;
        map arrTg;
        for(int i = 0; i < game_map[0].mapX; i++){
            for(int j = 0; j < game_map[0].mapY; j++){
                arrTg.arrMap[i][j] = game_map[step].arrMap[i][j]; 
            }
        }
        mainPlayer.handelInput(event, render);
        int wayX = 0;
        int wayY = 0;
        if(event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                animationOj = UP;
                wayX = -1;
                wayY = 0;
                break;
            case SDLK_DOWN:
                animationOj = DOWN;
                wayX = 1;
                wayY = 0;
                break;
            case SDLK_RIGHT:
                animationOj = RIGHT;
                wayY = 1;
                wayX = 0;
                break;
            case SDLK_LEFT:
                animationOj = LEFT;
                wayY = -1;
                wayX = 0;
                break;
            }
            if(arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] == FLOOR || arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] == GOAL){
                arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] = arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] ;
                isMove = true;
                arrTg.posBoxMoveX = -1;
                arrTg.posBoxMoveY = -1;
            }
            else if((arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] == BOX || arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] == BOX_WIN) && 
            (arrTg.arrMap[game_map[step].posPlayerX+wayX*2][game_map[step].posPlayerY+wayY*2] == FLOOR || arrTg.arrMap[game_map[step].posPlayerX+wayX*2][game_map[step].posPlayerY+wayY*2] == GOAL)){
                if(arrTg.arrMap[game_map[step].posPlayerX+wayX*2][game_map[step].posPlayerY+wayY*2] == FLOOR) arrTg.arrMap[game_map[step].posPlayerX+wayX*2][game_map[step].posPlayerY+wayY*2] = BOX;
                if(arrTg.arrMap[game_map[step].posPlayerX+wayX*2][game_map[step].posPlayerY+wayY*2] == GOAL) arrTg.arrMap[game_map[step].posPlayerX+wayX*2][game_map[step].posPlayerY+wayY*2] = BOX_WIN;
                if(arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] == BOX) arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] = FLOOR;
                if(arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] == BOX_WIN) arrTg.arrMap[game_map[step].posPlayerX+wayX][game_map[step].posPlayerY+wayY] = GOAL;
                isMove = true;
                arrTg.posBoxMoveX = game_map[step].posPlayerX + wayX + wayX;
                arrTg.posBoxMoveY = game_map[step].posPlayerY + wayY + wayY;
            }
            else animationOj = NONE;
        }

        if(isMove == true){
            arrTg.sizeX = game_map[step].sizeX;
            arrTg.sizeY = game_map[step].sizeY;
            arrTg.mapX = game_map[step].mapX;
            arrTg.mapY = game_map[step].mapY;
            arrTg.posPlayerX = game_map[step].posPlayerX + wayX;
            arrTg.posPlayerY = game_map[step].posPlayerY + wayY;
            game_map.push_back(arrTg);
            step ++;
        } 
    }
}

void gameMap::drawMap(SDL_Renderer* render, bool& isWin, int& step, animation& animationOj){
    SDL_SetRenderDrawColor(render, 135, 206, 250, 255);
    SDL_Rect rectGame = {0, 0, 960, 960};
    SDL_RenderFillRect(render, &rectGame);
    isWin = true;
    int mapX, mapY;
    mapX = 0;
    boxMove = false;
    for(int i = 5; i < game_map[step].sizeX*game_map[step].mapX + 5; i+= game_map[step].sizeX){
        mapY = 0;
        for(int j = 5; j < game_map[step].sizeY*game_map[step].mapY + 5; j += game_map[step].sizeY){
            switch(game_map[step].arrMap[mapX][mapY])
            {
                case WALL:
                    wall.setRect(j, i, game_map[step].sizeY, game_map[step].sizeX);
                    wall.render(render);
                    break;
                case FLOOR:
                    floor.setRect(j, i, game_map[step].sizeY, game_map[step].sizeX);
                    floor.render(render);
                    break;
                case PLAYER:
                    mainPlayer.setPos(mapX, mapY);
                    floor.setRect(j, i, game_map[step].sizeY, game_map[step].sizeX);
                    floor.render(render);
                    game_map[step].arrMap[mapX][mapY] = FLOOR;
                    break;
                case BOX:
                    if(step > 0 && game_map[step].posBoxMoveX == mapX && game_map[step].posBoxMoveY == mapY && animationOj != NONE){
                       floor.setRect(j, i, game_map[step].sizeY, game_map[step].sizeX);
                        floor.render(render); 
                    }
                    else{
                        floor.setRect(j, i, game_map[step].sizeY, game_map[step].sizeX);
                        floor.render(render);
                        box.setRect(j, i , game_map[step].sizeY, game_map[step].sizeX);
                        box.render(render);
                    }
                        
                    break;
                case GOAL:
                    goal.setRect(j, i, game_map[step].sizeY, game_map[step].sizeX);
                    goal.render(render);
                    isWin = false;
                    break;
                case BOX_WIN:
                    if(step > 0 && game_map[step].posBoxMoveX == mapX && game_map[step].posBoxMoveY == mapY && animationOj != NONE){
                       floor.setRect(j, i, game_map[step].sizeY, game_map[step].sizeX);
                        floor.render(render); 
                    }
                    else{
                        floor.setRect(j, i, game_map[step].sizeY, game_map[step].sizeX);
                        floor.render(render);
                        box_win.setRect(j, i , game_map[step].sizeY, game_map[step].sizeX);
                        box_win.render(render);
                    }
                    break;
            }
            mapY++;
        }
        mapX++;
    }
     if(step > 0 && game_map[step].posBoxMoveX != -1 && game_map[step].posBoxMoveY != -1 && animationOj != NONE){
        switch (animationOj)
        {
        case UP:
            box.setRect(mainPlayer.getPosY() + 5 , mainPlayer.getPosX() + 5 - game_map[step].sizeX , game_map[step].sizeY, game_map[step].sizeX);
            break;
        case DOWN:
            box.setRect(mainPlayer.getPosY() + 5 , mainPlayer.getPosX() + 5 + game_map[step].sizeX, game_map[step].sizeY, game_map[step].sizeX);
            break;
        case LEFT:
            box.setRect(mainPlayer.getPosY() + 5 - game_map[step].sizeY , mainPlayer.getPosX() + 5, game_map[step].sizeY, game_map[step].sizeX);
            break;
        case RIGHT:
            box.setRect(mainPlayer.getPosY() + 5 + game_map[step].sizeY , mainPlayer.getPosX() + 5, game_map[step].sizeY, game_map[step].sizeX);
            break;
        }
        box.render(render);
     }
    switch(animationOj)
    {
        case UP:
            if(mainPlayer.getPosX() > game_map[step].posPlayerX*game_map[step].sizeX ){
                mainPlayer.setPos(mainPlayer.getPosX() - game_map[step].sizeX*1.0/10 ,mainPlayer.getPosY());
            } 
            else animationOj = NONE;
            break;
        case DOWN:
            if(mainPlayer.getPosX() < game_map[step].posPlayerX*game_map[step].sizeX){
                mainPlayer.setPos(mainPlayer.getPosX() + game_map[step].sizeX*1.0/10 ,mainPlayer.getPosY());
            }
            else animationOj = NONE;
            break;
        case LEFT:
            if(mainPlayer.getPosY() > game_map[step].posPlayerY*game_map[step].sizeY){
                mainPlayer.setPos(mainPlayer.getPosX() ,mainPlayer.getPosY() - game_map[step].sizeY*1.0/10);
            } 
            else animationOj = NONE;
            break;
        case RIGHT:
            if(mainPlayer.getPosY() < game_map[step].posPlayerY*game_map[step].sizeY){
                mainPlayer.setPos(mainPlayer.getPosX() ,mainPlayer.getPosY() + game_map[step].sizeY*1.0/10);
            } 
            else animationOj = NONE;
            break;
    }
    mainPlayer.setRect(mainPlayer.getPosY() + 5, mainPlayer.getPosX() + 5, game_map[step].sizeY, game_map[step].sizeX);
    mainPlayer.showPlayer(render, animationOj);

}

void gameMap::go_back(int& step){
    step--;
    game_map.pop_back();
    mainPlayer.setPos(game_map[step].posPlayerX*game_map[step].sizeX, game_map[step].posPlayerY*game_map[step].sizeY);
}

void gameMap::free(){
    wall.free();
    box.free();
    box_win.free();
    floor.free();
    goal.free();
    mainPlayer.free();
}