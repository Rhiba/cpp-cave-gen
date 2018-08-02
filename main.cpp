
#include <vector>
#include <iostream>
#include <time.h>


typedef std::vector<std::pair<int,int> > TArea;

class TMap
{
public:
    TMap(int width,int height) {m_data.resize(height*width);Width = width;Height=height;};
    ~TMap(){};
    int* operator[](int i) {return &m_data[i*Width];};
    int Width,Height;
private:
    std::vector<int> m_data;
};


TMap initialiseMap(int width, int height, int chanceToStartAlive);//function initialisation, returns a 2d array, takes a 2d array
TMap simStep(TMap& oldMap); //"game of life" style simulation
int countAliveNeighbours(TMap& map, int x, int y); //checks how many of the squares around a certain square are walls

void printMap(TMap& map);

int main()
{
    //allows you to change size of map
    int mapXSize = 70;
    int mapYSize = 30;
    int simSteps = 4;
    int chanceToStartAlive = 41; //percentage of being a wall tile at start

    srand(time(NULL));
    TMap map = initialiseMap(mapXSize,mapYSize,chanceToStartAlive); //setting up the map grid
    for (int k=0; k<=simSteps; k++) //run sim a few times to smooth out map
    {
        //printMap(map);
        map = simStep(map);
    }

    //prints out ascii representation
    printMap(map);

    return 0;
}

TMap initialiseMap(int width, int height,int chanceToStartAlive) //returns a 2d array of bools
{
    TMap map(width,height); //create map to return

    for (int h=0; h<height; h++)
    {
        for (int w=0; w<width; w++) //initialising values here
        {
            if (rand()%100+1 < chanceToStartAlive) //it has a chance of being a wall or not
            {
                map[h][w] = 1;
            }
            else
            {
                map[h][w] = 0;
            }
        }
    }
    //return our new map
    return map;
}

TMap simStep(TMap& oldMap) //this is the magic "game of life" thingy, google it
{

    int width = oldMap.Width;
    int height = oldMap.Height;
    TMap newMap(width,height);

    int birthLimit = 4;
    int deathLimit = 3;

    //iterates through every tile in the map and decides if needs to be born, die, or remain unchanged
    for (int h=0; h<height; h++)
    {
        for (int w=0; w<width; w++)
        {
            int newVal = countAliveNeighbours(oldMap,w,h);
            if (oldMap[h][w])
            {
                if (newVal<deathLimit)
                {
                    newMap[h][w] = 0;
                }
                else
                {
                    newMap[h][w] = 1;
                }
            }
            else
            {
                if (newVal>birthLimit)
                {
                    newMap[h][w] = 1;
                }
                else
                {
                    newMap[h][w] = 0;
                }
            }
        }
    }
    return newMap;
}
//counts the number of "alive" cells around the target cell, given a current map and a target x and y coord
int countAliveNeighbours(TMap& map, int x, int y)
{
    int count = 0;
    for (int i=-1; i<2; i++)
    {
        for (int j=-1; j<2; j++)
        {
            int neighbour_x = x+i;
            int neighbour_y = y+j;

            if (i==0&&j==0)
            {
                //do nothing as its our target cell
            }
            //if out of bounds, obviously don't check it, but add one anyway as it counts as an alive neighbour
            else if (neighbour_x<0||neighbour_y<0||neighbour_x>=map.Width||neighbour_y>=map.Height)
            {
                count +=1;
            }
            else if (map[neighbour_y][neighbour_x]==1)
            {
                count +=1;
            }
        }
    }
    return count;
}


void printMap(TMap& map)
{
    //return;
    std::cout << std::endl;
    for (int y=0; y<map.Height; y++)
    {
        for (int x=0; x<map.Width; x++)
        {
            if (map[y][x]==1) std::cout << "X";
            else if (map[y][x]==0) std::cout << " ";
            else std::cout << map[y][x];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

