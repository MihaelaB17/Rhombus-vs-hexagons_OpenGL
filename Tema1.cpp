#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <random>
#include <string.h>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;

bool press, pressS;
float radians, scaleX = 1, scaleY = 1, sum = 1, signT = 0.6, hexagon_size = 1;
bool FINAL = false;
std::vector<int> lines;
std::vector<glm::mat3> hexagonVector;
std::vector<glm::mat3> starVector;
std::vector<glm::mat3> stele;
std::vector<glm::mat3> rombVector;
std::vector<glm::mat3> sus;
std::vector<int> culoareHex;
std::vector<int> culoareStea;
std::vector<int> culoareRomb;
std::vector<int> linieStea;
std::vector<int> steleLinie;
std::vector<int> steleColoana;
std::vector<float> hex_size;
std::vector<int> steleAfisare;
int afisare[100], creste[100];
int appLine[4], apasareRomb[4], releaseRomb[4], linieR[4], coloanaR[4];

std::vector<int> pozitie;
std::vector<int> releaseColor;
int coliziune[100][100], intersectieStele[100];
int disparut[100];
std::vector<glm::mat3> temporarRomb;
int appTempLinieRomb[4][4], clrrmb[4][4];
std::vector<int>appTempCuloareRomb;
int poz = 740, nr = 5, contorPoz[20];
int vizibilRomb[1000], culoareLiniiHexa[3][4];
std::vector<float>romb_size;

//int incercareCulHexLinia1[4], incercareCulHexLinia2[4], incercareCulHexLinia3[4];
int incercareLiniiHexa[3][4];
int inc1[4], inc2[4], inc3[4];
int dec1[4], dec2[4], dec3[4];
int final1 = 3;
int murit, contorMurit[1000];
std::vector<int> vedereRomb;
int dispareRomb[1000];
int clickdr[4][4];
std::vector<int> click;
///int click[1000];

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            clrrmb[i][j] = -1;

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0.5, 0.5, 1), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(1, 1, 1));
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide - 10, glm::vec3(1, 0.5, 1), true);
    AddMeshToList(square3);

    Mesh* rectangle = object2D::CreateRectangular("rectangle", corner, 70, 350, glm::vec3(0.5, 1, 0.5), true);
    AddMeshToList(rectangle);

    Mesh* romb1 = object2D::CreateRomb("romb1", corner, 30, 30, glm::vec3(0, 1, 1), true);
    AddMeshToList(romb1);

    Mesh* star1 = object2D::CreateStar("star1", corner, 30, glm::vec3(0, 1, 1), true);
    AddMeshToList(star1);

    Mesh* romb2 = object2D::CreateRomb("romb2", corner, 30, 30, glm::vec3(1, 1, 0), true);
    AddMeshToList(romb2);

    Mesh* star2 = object2D::CreateStar("star2", corner, 30, glm::vec3(1, 1, 0), true);
    AddMeshToList(star2);

    Mesh* romb3 = object2D::CreateRomb("romb3", corner, 30, 30, glm::vec3(1, 0, 1), true);
    AddMeshToList(romb3);

    Mesh* star3 = object2D::CreateStar("star3", corner, 30, glm::vec3(1, 0, 1), true);
    AddMeshToList(star3);

    Mesh* romb4 = object2D::CreateRomb("romb4", corner, 30, 30, glm::vec3(1, 0.5, 0.5), true);
    AddMeshToList(romb4);

    Mesh* star4 = object2D::CreateStar("star4", corner, 30, glm::vec3(1, 0.5, 0.5), true);
    AddMeshToList(star4);

    Mesh* star = object2D::CreateStar("star", corner, 30, glm::vec3(1, 1, 1), true);
    AddMeshToList(star);

    Mesh* star5 = object2D::CreateStar("star5", corner, 30, glm::vec3(0.5, 0.5, 0.5), true);
    AddMeshToList(star5);

    Mesh* hexagon1 = object2D::CreateHexagon("hexagon1", corner, 30, glm::vec3(0, 1, 1), glm::vec3(0, 0.5, 0), true);
    AddMeshToList(hexagon1);

    Mesh* hexagon2 = object2D::CreateHexagon("hexagon2", corner, 30, glm::vec3(1, 1, 0), glm::vec3(0, 0.5, 0), true);
    AddMeshToList(hexagon2);

    Mesh* hexagon3 = object2D::CreateHexagon("hexagon3", corner, 30, glm::vec3(1, 0, 1), glm::vec3(0, 0.5, 0), true);
    AddMeshToList(hexagon3);

    Mesh* hexagon4 = object2D::CreateHexagon("hexagon4", corner, 30, glm::vec3(1, 0.5, 0.5), glm::vec3(0, 0.5, 0), true);
    AddMeshToList(hexagon4);

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    if (FINAL == false) {
        glm::ivec2 resolution = window->GetResolution();
        glm::vec3 corner = glm::vec3(0, 0, 0);
        ///dreptunghi
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(10, 10);
        RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
        ///

        //prima coloana de patrate
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100, 260);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100, 135);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100, 10);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        ///

        //a doua coloana de patrate
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(220, 260);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(220, 135);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(220, 10);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        ///

        //a treia coloana de patrate
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(340, 260);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(340, 135);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(340, 10);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        ///

        //partate sus
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(30, 600);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(200, 600);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(370, 600);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(540, 600);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        ///

        ///patrate dreapta
        if (final1 == 3) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(760, 610);
            RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(920, 610);
            RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1080, 610);
            RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
        }
        if (final1 == 2) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(760, 610);
            RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(920, 610);
            RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
        }
        if (final1 == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(760, 610);
            RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
        }
        if(final1 == 0 )
            FINAL = true;
        ///

        ///stele sub patrate dreapta
        for (int i = 0; i < 20; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(poz, 580);
            sus.push_back(modelMatrix);
            if (contorPoz[i] == 0) {
                poz = poz + 40;
                contorPoz[i] = 1;
            }
        }

        float current_time2 = (float)clock() / CLOCKS_PER_SEC;
        static float last_time_star2 = current_time2;
        float timeStar2 = current_time2 - last_time_star2;
        int TTL3 = 5.0f;
        int randomX, randomY;

        if (timeStar2 > TTL3) {
            last_time_star2 = current_time2;

            for (int i = 0; i < 3; i++) {
                randomX = rand() % 1280;
                randomY = rand() % 720;
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(randomX, randomY);

                stele.push_back(modelMatrix);
                steleLinie.push_back(randomX);
                steleColoana.push_back(randomY);
                steleAfisare.push_back(1);
            }
        }

        for (int i = 0; i < stele.size(); i++)
            if (steleAfisare[i] == 1)
                RenderMesh2D(meshes["star5"], shaders["VertexColor"], stele[i]);
            else {
                if (creste[i] == 0) {
                    poz = poz + 40;
                    creste[i] = 1;
                    nr++;
                }
            }

        for (int i = 0; i < nr; i++)
            RenderMesh2D(meshes["star"], shaders["VertexColor"], sus[i]);


        ///romburi
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(50, 650);
        RenderMesh2D(meshes["romb1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(220, 650);
        RenderMesh2D(meshes["romb2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(390, 650);
        RenderMesh2D(meshes["romb3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(560, 650);
        RenderMesh2D(meshes["romb4"], shaders["VertexColor"], modelMatrix);
        ///

        //stele
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(20, 580);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
        ///
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(190, 580);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(230, 580);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
        ///
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(360, 580);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(400, 580);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
        ///
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(540, 580);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(580, 580);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(620, 580);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
        ///

        //hexagoane
        for (int i = 0; i < 4; i++) {
            if (press == true) {
                if (i == 0 && apasareRomb[i] == 1) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(window->GetCursorPosition().x, 720 - window->GetCursorPosition().y);
                    RenderMesh2D(meshes["romb1"], shaders["VertexColor"], modelMatrix);
                }
                if (i == 1 && apasareRomb[i] == 1) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(window->GetCursorPosition().x, 720 - window->GetCursorPosition().y);
                    RenderMesh2D(meshes["romb2"], shaders["VertexColor"], modelMatrix);
                }
                if (i == 2 && apasareRomb[i] == 1) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(window->GetCursorPosition().x, 720 - window->GetCursorPosition().y);
                    RenderMesh2D(meshes["romb3"], shaders["VertexColor"], modelMatrix);
                }
                if (i == 3 && apasareRomb[i] == 1) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(window->GetCursorPosition().x, 720 - window->GetCursorPosition().y);
                    RenderMesh2D(meshes["romb4"], shaders["VertexColor"], modelMatrix);
                }
            }
        }

        for (int i = 0; i < pozitie.size(); i = i + 2) {
            if (pozitie[i] == 0 && pozitie[i + 1] == 0 && clrrmb[0][0] != 5) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(115, 310);
                romb_size.push_back(1);

                temporarRomb.push_back(modelMatrix);
                appTempCuloareRomb.push_back(releaseColor[i / 2]);
                appTempLinieRomb[0][0] = 1;
                clrrmb[0][0] = releaseColor[i / 2];
                vedereRomb.push_back(0);
                romb_size.push_back(1);
                click.push_back(0);
            }
            if (pozitie[i] == 1 && pozitie[i + 1] == 0 && clrrmb[1][0] != 5) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(115, 185);
                romb_size.push_back(1);

                temporarRomb.push_back(modelMatrix);
                appTempCuloareRomb.push_back(releaseColor[i / 2]);
                appTempLinieRomb[1][0] = 1;
                clrrmb[1][0] = releaseColor[i / 2];
                vedereRomb.push_back(0);
                romb_size.push_back(1);
                click.push_back(0);
            }
            if (pozitie[i] == 2 && pozitie[i + 1] == 0 && clrrmb[2][0] != 5) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(115, 60);
                romb_size.push_back(1);

                temporarRomb.push_back(modelMatrix);
                appTempCuloareRomb.push_back(releaseColor[i / 2]);
                appTempLinieRomb[2][0] = 1;
                clrrmb[2][0] = releaseColor[i / 2];
                vedereRomb.push_back(0);
                romb_size.push_back(1);
                click.push_back(0);
            }
            if (pozitie[i] == 0 && pozitie[i + 1] == 1 && clrrmb[0][1] != 5) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(240, 310);
                romb_size.push_back(1);

                temporarRomb.push_back(modelMatrix);
                appTempCuloareRomb.push_back(releaseColor[i / 2]);
                appTempLinieRomb[0][1] = 1;
                clrrmb[0][1] = releaseColor[i / 2];
                vedereRomb.push_back(0);
                romb_size.push_back(1);
                click.push_back(0);
            }
            if (pozitie[i] == 1 && pozitie[i + 1] == 1 && clrrmb[1][1] != 5) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(240, 185);
                romb_size.push_back(1);

                temporarRomb.push_back(modelMatrix);
                appTempCuloareRomb.push_back(releaseColor[i / 2]);
                appTempLinieRomb[1][1] = 1;
                clrrmb[1][1] = releaseColor[i / 2];
                vedereRomb.push_back(0);
                click.push_back(0);
            }
            if (pozitie[i] == 2 && pozitie[i + 1] == 1 && clrrmb[2][1] != 5) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(240, 60);
                romb_size.push_back(1);

                temporarRomb.push_back(modelMatrix);
                appTempCuloareRomb.push_back(releaseColor[i / 2]);
                appTempLinieRomb[2][1] = 1;
                clrrmb[2][1] = releaseColor[i / 2];
                vedereRomb.push_back(0);
                romb_size.push_back(1);
                click.push_back(0);
            }
            if (pozitie[i] == 0 && pozitie[i + 1] == 2 && clrrmb[0][2] != 5) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(365, 310);
                romb_size.push_back(1);

                temporarRomb.push_back(modelMatrix);
                appTempCuloareRomb.push_back(releaseColor[i / 2]);
                appTempLinieRomb[0][2] = 1;
                clrrmb[0][2] = releaseColor[i / 2];
                vedereRomb.push_back(0);
                romb_size.push_back(1);
                click.push_back(0);
            }
            if (pozitie[i] == 1 && pozitie[i + 1] == 2 && clrrmb[1][2] != 5) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(365, 185);
                romb_size.push_back(1);

                temporarRomb.push_back(modelMatrix);
                appTempCuloareRomb.push_back(releaseColor[i / 2]);
                appTempLinieRomb[1][2] = 1;
                clrrmb[1][2] = releaseColor[i / 2];
                vedereRomb.push_back(0);
                romb_size.push_back(1);
                click.push_back(0);
            }
            if (pozitie[i] == 2 && pozitie[i + 1] == 2 && clrrmb[2][2] != 5) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(365, 60);
                romb_size.push_back(1);

                temporarRomb.push_back(modelMatrix);
                appTempCuloareRomb.push_back(releaseColor[i / 2]);
                appTempLinieRomb[2][2] = 1;
                clrrmb[2][2] = releaseColor[i / 2];
                vedereRomb.push_back(0);
                romb_size.push_back(1);
                click.push_back(0);
            }
        }

        float current_time = (float)clock() / CLOCKS_PER_SEC;
        static float last_time_hex = current_time;
        static float last_time_star = current_time;
        float timeHex = current_time - last_time_hex;
        float timeStar = current_time - last_time_star;

        float TTL1 = 7.0f + rand() % 3;
        float TTL2 = 2.0f;

        float radiusStar = 30;
        float radiusHexagon = 30;
        float radiusRomb = 30;

        int culoarehex = rand() % 4;

        if (timeHex > TTL1) {
            last_time_hex = current_time;

            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<int> distribution(0, 2);
            int values[] = { 60, 185, 320 };
            int line = values[distribution(generator)];

            lines.push_back(line);
            if (line == 60) {
                appLine[0] = 1;
                if (culoarehex == 0) {
                    if (inc1[0] == 0) {
                        incercareLiniiHexa[0][0]++;
                        inc1[0] = 1;
                    }
                }
                if (culoarehex == 1) {
                    if (inc1[1] == 0) {
                        incercareLiniiHexa[0][1]++;
                        inc1[1] = 1;
                    }
                }
                if (culoarehex == 2) {
                    if (inc1[2] == 0) {
                        incercareLiniiHexa[0][2]++;
                        inc1[2] = 1;
                    }
                }
                if (culoarehex == 3) {
                    if (inc1[3] == 0) {
                        incercareLiniiHexa[0][3]++;
                        inc1[3] = 1;
                    }
                }
            }
            if (line == 185) {
                appLine[1] = 1;
                if (culoarehex == 0) {
                    if (inc2[0] == 0) {
                        incercareLiniiHexa[1][0]++;
                        inc2[0] = 1;
                    }
                }
                if (culoarehex == 1) {
                    if (inc2[1] == 0) {
                        incercareLiniiHexa[1][1]++;
                        inc2[1] = 1;
                    }
                }
                if (culoarehex == 2) {
                    if (inc2[2] == 0) {
                        incercareLiniiHexa[1][2]++;
                        inc2[2] = 1;
                    }
                }
                if (culoarehex == 3) {
                    if (inc2[3] == 0) {
                        incercareLiniiHexa[1][3]++;
                        inc2[3] = 1;
                    }
                }
            }
            if (line == 320) {
                appLine[2] = 1;
                if (culoarehex == 0) {
                    if (inc3[0] == 0) {
                        incercareLiniiHexa[2][0]++;
                        inc3[0] = 1;
                    }
                }
                if (culoarehex == 1) {
                    if (inc3[1] == 0) {
                        incercareLiniiHexa[2][1]++;
                        inc3[1] = 1;
                    }
                }
                if (culoarehex == 2) {
                    if (inc3[2] == 0) {
                        incercareLiniiHexa[2][2]++;
                        inc3[2] = 1;
                    }
                }
                if (culoarehex == 3) {
                    if (inc3[3] == 0) {
                        incercareLiniiHexa[2][3]++;
                        inc3[3] = 1;
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                inc1[i] = 0;
                inc2[i] = 0;
                inc3[i] = 0;
                dec1[i] = 0;
                dec2[i] = 0;
                dec3[i] = 0;
            }

            culoareHex.push_back(culoarehex);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1280, line);
            hexagonVector.push_back(modelMatrix);
            hex_size.push_back(1);
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (timeStar > TTL2 && appLine[2 - i] == 1 && appTempLinieRomb[i][j] == 1 && incercareLiniiHexa[2 - i][clrrmb[i][j]] > 0 && clrrmb[i][j] != -1 && clrrmb[i][j] != 5 && clickdr[i][j] == 0) {
                    last_time_star = current_time;
                    int ll, cc;
                    if (i == 0 && j == 0) {
                        cc = 123;
                        ll = 320;
                    }
                    if (i == 1 && j == 0) {
                        cc = 123;
                        ll = 195;
                    }
                    if (i == 2 && j == 0) {
                        cc = 123;
                        ll = 70;
                    }
                    if (i == 0 && j == 1) {
                        cc = 248;
                        ll = 320;
                    }
                    if (i == 1 && j == 1) {
                        cc = 248;
                        ll = 195;
                    }
                    if (i == 2 && j == 1) {
                        cc = 248;
                        ll = 70;
                    }
                    if (i == 0 && j == 2) {
                        cc = 373;
                        ll = 320;
                    }
                    if (i == 1 && j == 2) {
                        cc = 373;
                        ll = 195;
                    }
                    if (i == 2 && j == 2) {
                        cc = 373;
                        ll = 70;
                    }

                    if (clrrmb[i][j] == 0)
                        culoareStea.push_back(0);
                    if (clrrmb[i][j] == 1)
                        culoareStea.push_back(1);
                    if (clrrmb[i][j] == 2)
                        culoareStea.push_back(2);
                    if (clrrmb[i][j] == 3)
                        culoareStea.push_back(3);

                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(cc, ll);

                    starVector.push_back(modelMatrix);
                    linieStea.push_back(ll);
                }
            }
        }

        for (int i = 0; i < hexagonVector.size(); i++)
            for (int j = 0; j < starVector.size(); j++) {
                float distance = glm::distance(hexagonVector[i][2], starVector[j][2]);
                if (distance < radiusStar + radiusHexagon && culoareHex[i] == culoareStea[j] && disparut[i] == 0 && afisare[j] == 0) {
                    afisare[j] = 1;
                    if (coliziune[i][j] == 0) {
                        intersectieStele[i]++;
                        coliziune[i][j] = 1;
                    }
                }
            }

        for (int i = 0; i < hexagonVector.size(); i++) {
            char cul[10];
            if (culoareHex[i] == 0)
                strcpy(cul, "hexagon1");
            if (culoareHex[i] == 1)
                strcpy(cul, "hexagon2");
            if (culoareHex[i] == 2)
                strcpy(cul, "hexagon3");
            if (culoareHex[i] == 3)
                strcpy(cul, "hexagon4");

            if (intersectieStele[i] == 3) {
                if (hexagonVector[i][2].y == 60) {
                    appLine[0] = 0;
                    if (culoareHex[i] == 0 && dec1[0] == 0) {
                        incercareLiniiHexa[0][0]--;
                        dec1[0] = 1;
                    }
                    if (culoareHex[i] == 1 && dec1[1] == 0) {
                        incercareLiniiHexa[0][1]--;
                        dec1[1] = 1;
                    }
                    if (culoareHex[i] == 2 && dec1[2] == 0) {
                        incercareLiniiHexa[0][2]--;
                        dec1[2] = 1;

                    }
                    if (culoareHex[i] == 3 && dec1[3] == 0) {
                        incercareLiniiHexa[0][3]--;
                        dec1[3] = 1;
                    }
                }
                if (hexagonVector[i][2].y == 185) {
                    appLine[1] = 0;
                    if (culoareHex[i] == 0 && dec2[0] == 0) {
                        incercareLiniiHexa[1][0]--;
                        dec2[0] = 1;
                    }
                    if (culoareHex[i] == 1 && dec2[1] == 0) {
                        incercareLiniiHexa[1][1]--;
                        dec2[1] = 1;
                    }
                    if (culoareHex[i] == 2 && dec2[2] == 0) {
                        incercareLiniiHexa[1][2]--;
                        dec2[2] = 1;
                    }
                    if (culoareHex[i] == 3 && dec2[3] == 0) {
                        incercareLiniiHexa[1][3]--;
                        dec2[3] = 1;
                    }

                }
                if (hexagonVector[i][2].y == 320) {
                    appLine[2] = 0;
                    if (culoareHex[i] == 0 && dec3[0] == 0) {
                        incercareLiniiHexa[2][0]--;
                        dec3[0] = 1;
                    }
                    if (culoareHex[i] == 1 && dec3[1] == 0) {
                        incercareLiniiHexa[2][1]--;
                        dec3[1] = 1;
                    }
                    if (culoareHex[i] == 2 && dec3[2] == 0) {
                        incercareLiniiHexa[2][2]--;
                        dec3[2] = 1;
                    }
                    if (culoareHex[i] == 3 && dec3[3] == 0) {
                        incercareLiniiHexa[2][3]--;
                        dec3[3] = 1;
                    }

                }

                if (hex_size[i] <= 0)
                    intersectieStele[i] = 4;

                hex_size[i] -= deltaTimeSeconds;
                hexagonVector[i] *= transform2D::Scale(hex_size[i], hex_size[i]);
                RenderMesh2D(meshes[cul], shaders["VertexColor"], hexagonVector[i]);
                disparut[i] = 1;

            }

            if (intersectieStele[i] < 3) {
                if (hexagonVector[i][2].x < 100) {
                    if (contorMurit[i] == 0) {
                        contorMurit[i] = 1;
                        final1--;
                    }
                    if (hexagonVector[i][2].y == 60) {
                        appLine[0] = 0;
                        if (culoareHex[i] == 0 && dec1[0] == 0) {
                            incercareLiniiHexa[0][0]--;
                            dec1[0] = 1;
                        }
                        if (culoareHex[i] == 1 && dec1[1] == 0) {
                            incercareLiniiHexa[0][1]--;
                            dec1[1] = 1;
                        }
                        if (culoareHex[i] == 2 && dec1[2] == 0) {
                            incercareLiniiHexa[0][2]--;
                            dec1[2] = 1;

                        }
                        if (culoareHex[i] == 3 && dec1[3] == 0) {
                            incercareLiniiHexa[0][3]--;
                            dec1[3] = 1;
                        }
                    }
                    if (hexagonVector[i][2].y == 185) {
                        appLine[1] = 0;
                        if (culoareHex[i] == 0 && dec2[0] == 0) {
                            incercareLiniiHexa[1][0]--;
                            dec2[0] = 1;
                        }
                        if (culoareHex[i] == 1 && dec2[1] == 0) {
                            incercareLiniiHexa[1][1]--;
                            dec2[1] = 1;
                        }
                        if (culoareHex[i] == 2 && dec2[2] == 0) {
                            incercareLiniiHexa[1][2]--;
                            dec2[2] = 1;
                        }
                        if (culoareHex[i] == 3 && dec2[3] == 0) {
                            incercareLiniiHexa[1][3]--;
                            dec2[3] = 1;
                        }

                    }
                    if (hexagonVector[i][2].y == 320) {
                        appLine[2] = 0;
                        if (culoareHex[i] == 0 && dec3[0] == 0) {
                            incercareLiniiHexa[2][0]--;
                            dec3[0] = 1;
                        }
                        if (culoareHex[i] == 1 && dec3[1] == 0) {
                            incercareLiniiHexa[2][1]--;
                            dec3[1] = 1;
                        }
                        if (culoareHex[i] == 2 && dec3[2] == 0) {
                            incercareLiniiHexa[2][2]--;
                            dec3[2] = 1;
                        }
                        if (culoareHex[i] == 3 && dec3[3] == 0) {
                            incercareLiniiHexa[2][3]--;
                            dec3[3] = 1;
                        }

                    }
                    disparut[i] = 1;
                }
                if (hexagonVector[i][2].x > 100) {
                    if (hexagonVector[i][2].y == 60)
                        appLine[0] = 1;
                    if (hexagonVector[i][2].y == 185)
                        appLine[1] = 1;
                    if (hexagonVector[i][2].y == 320)
                        appLine[2] = 1;

                    translateX = signT * deltaTimeSeconds * 200;
                    hexagonVector[i] *= transform2D::Translate(-translateX, 0);

                    RenderMesh2D(meshes[cul], shaders["VertexColor"], hexagonVector[i]);
                }
            }
        }

        for (int i = 0; i < temporarRomb.size(); i++)
            for (int j = 0; j < hexagonVector.size(); j++) {
                float distance = glm::distance(hexagonVector[j][2], temporarRomb[i][2]);
                if (distance < radiusRomb + radiusHexagon  && dispareRomb[i] == 0 && disparut[j] == 0) {
                    dispareRomb[i] = 1;
                }
            }

        for (int i = 0; i < temporarRomb.size(); i++) {
            if (temporarRomb[i][2].y == 310) {
                if (temporarRomb[i][2].x == 115) {
                    if(clickdr[0][0]  == 1)
                        click[i] = 1;
                }
                if (temporarRomb[i][2].x == 240) {
                   if(clickdr[0][1]  == 1)
                        click[i] = 1;
                }
                if (temporarRomb[i][2].x == 365) {
                    if (clickdr[0][2] == 1)
                        click[i] = 1;
                }
            }
            if (temporarRomb[i][2].y == 185) {
                if (temporarRomb[i][2].x == 115) {
                    if (clickdr[1][0] == 1)
                        click[i] = 1;
                }
                if (temporarRomb[i][2].x == 240) {
                    if (clickdr[1][1] == 1)
                        click[i] = 1;
                }
                if (temporarRomb[i][2].x == 365) {
                    if (clickdr[1][2] == 1)
                        click[i] = 1;
                }
            }
            if (temporarRomb[i][2].y == 60) {
                if (temporarRomb[i][2].x == 115) {
                    if (clickdr[2][0] == 1)
                        click[i] = 1;
                }
                if (temporarRomb[i][2].x == 240) {
                    if (clickdr[2][1] == 1)
                        click[i] = 1;
                }
                if (temporarRomb[i][2].x == 365) {
                    if (clickdr[2][2] == 1)
                        click[i] = 1;
                }
            }
        }

        for (int i = 0; i < temporarRomb.size(); i++) {
            if (dispareRomb[i] == 0 && click[i] == 0) {
                if (appTempCuloareRomb[i] == 0)
                    RenderMesh2D(meshes["romb1"], shaders["VertexColor"], temporarRomb[i]);
                if (appTempCuloareRomb[i] == 1)
                    RenderMesh2D(meshes["romb2"], shaders["VertexColor"], temporarRomb[i]);
                if (appTempCuloareRomb[i] == 2)
                    RenderMesh2D(meshes["romb3"], shaders["VertexColor"], temporarRomb[i]);
                if (appTempCuloareRomb[i] == 3)
                    RenderMesh2D(meshes["romb4"], shaders["VertexColor"], temporarRomb[i]);
            }
            if (dispareRomb[i] == 1) {
                if (temporarRomb[i][2].y == 310) {
                    if (temporarRomb[i][2].x == 115) {
                        appTempLinieRomb[0][0] = 0;
                        clrrmb[0][0] = 5;
                    }
                    if (temporarRomb[i][2].x == 240) {
                        appTempLinieRomb[0][1] = 0;
                        clrrmb[0][1] = 5;
                    }
                    if (temporarRomb[i][2].x == 365) {
                        appTempLinieRomb[0][2] = 0;
                        clrrmb[0][2] = 5;
                    }
                }
                if (temporarRomb[i][2].y == 185) {
                    if (temporarRomb[i][2].x == 115) {
                        appTempLinieRomb[1][0] = 0;
                        clrrmb[1][0] = 5;
                    }
                    if (temporarRomb[i][2].x == 240) {
                        appTempLinieRomb[1][1] = 0;
                        clrrmb[1][1] = 5;
                    }
                    if (temporarRomb[i][2].x == 365) {
                        appTempLinieRomb[1][2] = 0;
                        clrrmb[1][2] = 5;
                    }
                }
                if (temporarRomb[i][2].y == 60) {
                    if (temporarRomb[i][2].x == 115) {
                        appTempLinieRomb[2][0] = 0;
                        clrrmb[2][0] = 5;
                    }
                    if (temporarRomb[i][2].x == 240) {
                        appTempLinieRomb[2][1] = 0;
                        clrrmb[2][1] = 5;
                    }
                    if (temporarRomb[i][2].x == 365) {
                        appTempLinieRomb[2][2] = 0;
                        clrrmb[2][2] = 5;
                    }
                }
                if (romb_size[i] <= 0)
                    dispareRomb[i] = 4;

                romb_size[i] -= deltaTimeSeconds;
                temporarRomb[i] *= transform2D::Scale(romb_size[i], romb_size[i]);
                if(appTempCuloareRomb[i] == 0)
					RenderMesh2D(meshes["romb1"], shaders["VertexColor"], temporarRomb[i]);
                if(appTempCuloareRomb[i] == 1)
                    RenderMesh2D(meshes["romb2"], shaders["VertexColor"], temporarRomb[i]);
                if(appTempCuloareRomb[i] == 2)
                    RenderMesh2D(meshes["romb3"], shaders["VertexColor"], temporarRomb[i]);
                if(appTempCuloareRomb[i] == 3)
                    RenderMesh2D(meshes["romb4"], shaders["VertexColor"], temporarRomb[i]);
            }
        }

        for (int i = 0; i < starVector.size(); i++) {
            if (afisare[i] == 0) {
                if (linieStea[i] == 70) {
                    cx=starVector[i][2].x;
                    cy=starVector[i][2].y;
                    radians = -deltaTimeSeconds;
                    translateX = signT * deltaTimeSeconds * 300;
                    starVector[i] = transform2D::Translate(translateX, 0) * transform2D::Translate(cx, cy) * transform2D::Rotate(radians) * transform2D::Translate(-cx, -cy) * starVector[i];

                    char cul[10];
                    if (culoareStea[i] == 0)
                        strcpy(cul, "star1");
                    if (culoareStea[i] == 1)
                        strcpy(cul, "star2");
                    if (culoareStea[i] == 2)
                        strcpy(cul, "star3");
                    if (culoareStea[i] == 3)
                        strcpy(cul, "star4");
                    RenderMesh2D(meshes[cul], shaders["VertexColor"], starVector[i]);
                }
                if (linieStea[i] == 195) {
                    cx = starVector[i][2].x;
                    cy = starVector[i][2].y;
                    radians = -deltaTimeSeconds;
                    translateX = signT * deltaTimeSeconds * 300;
                    starVector[i] = transform2D::Translate(translateX, 0) * transform2D::Translate(cx, cy) * transform2D::Rotate(radians) * transform2D::Translate(-cx, -cy) * starVector[i];

                    char cul[10];
                    if (culoareStea[i] == 0)
                        strcpy(cul, "star1");
                    if (culoareStea[i] == 1)
                        strcpy(cul, "star2");
                    if (culoareStea[i] == 2)
                        strcpy(cul, "star3");
                    if (culoareStea[i] == 3)
                        strcpy(cul, "star4");
                    RenderMesh2D(meshes[cul], shaders["VertexColor"], starVector[i]);
                }
                if (linieStea[i] == 320) {
                    radians = -deltaTimeSeconds;
                    translateX = signT * deltaTimeSeconds * 300;

                    cx = starVector[i][2].x;
                    cy = starVector[i][2].y;
                    
                    starVector[i] = transform2D::Translate(translateX, 0) * transform2D::Translate(cx, cy) * transform2D::Rotate(radians) * transform2D::Translate(-cx, -cy) * starVector[i];

                    char cul[10];
                    if (culoareStea[i] == 0)
                        strcpy(cul, "star1");
                    if (culoareStea[i] == 1)
                        strcpy(cul, "star2");
                    if (culoareStea[i] == 2)
                        strcpy(cul, "star3");
                    if (culoareStea[i] == 3)
                        strcpy(cul, "star4");
                    RenderMesh2D(meshes[cul], shaders["VertexColor"], starVector[i]);
                }
            }
        }
    }
}

void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event

}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    //press = true;
    mouseY = 720 - mouseY;
    if (button == 1) {
        if (mouseX >= 30 && mouseX <= 140 && mouseY >= 600 && mouseY <= 700 && nr >= 1) {
            apasareRomb[0] = 1;
            nr = nr - 1;
            press = true;
        }

        if (mouseX >= 200 && mouseX <= 310 && mouseY >= 600 && mouseY <= 700 && nr >= 2) {
            apasareRomb[1] = 1;
            nr = nr - 2;
            press = true;
        }

        if (mouseX >= 370 && mouseX <= 480 && mouseY >= 600 && mouseY <= 700 && nr >= 2) {
            apasareRomb[2] = 1;
            nr = nr - 2;
            press = true;
        }

        if (mouseX >= 540 && mouseX <= 650 && mouseY >= 600 && mouseY <= 700 && nr >= 3) {
            apasareRomb[3] = 1;
            nr = nr - 3;
            press = true;
        }

        for (int i = 0; i < steleLinie.size(); i++) {
            if (mouseX >= steleLinie[i] - 30 && mouseX <= steleLinie[i] + 30 && mouseY >= steleColoana[i] - 30 && mouseY <= steleColoana[i] + 30) {
                poz = poz + 40;
                pressS = true;
            }
        }

    }
    if (button == 2) {
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 260 && mouseY <= 340 && appTempLinieRomb[0][0] == 1) {
            cout << " click dreapta" << endl;
            clickdr[0][0] = 1;
        }
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 135 && mouseY <= 215 && appTempLinieRomb[1][0] ==1) {
            cout << " click dreapta" << endl;
            clickdr[1][0] = 1;
        }
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 10 && mouseY <= 90 && appTempLinieRomb[2][0] ==1) {
            cout << " click dreapta" << endl;
            clickdr[2][0] = 1;
        }
        if (mouseX >= 220 && mouseX <= 320 && mouseY >= 260 && mouseY <= 340 && appTempLinieRomb[0][1] ==1) {
            cout << " click dreapta" << endl;
            clickdr[0][1] = 1;
        }
        if (mouseX >= 220 && mouseX <= 320 && mouseY >= 135 && mouseY <= 215 && appTempLinieRomb[1][1] == 1) {
            cout << " click dreapta" << endl;
            clickdr[1][1] = 1;
        }
        if (mouseX >= 220 && mouseX <= 320 && mouseY >= 10 && mouseY <= 90 && appTempLinieRomb[2][1]==1) {
            cout << " click dreapta" << endl;
            clickdr[2][1] = 1;
        }
        if (mouseX >= 340 && mouseX <= 440 && mouseY >= 260 && mouseY <= 340 && appTempLinieRomb[0][2] ==1) {
            cout << " click dreapta" << endl;
            clickdr[0][2] = 1;
        }
        if (mouseX >= 340 && mouseX <= 440 && mouseY >= 135 && mouseY <= 215 && appTempLinieRomb[1][2]==1) {
            cout << " click dreapta" << endl;
            clickdr[1][2] = 1;
        }
        if (mouseX >= 340 && mouseX <= 440 && mouseY >= 10 && mouseY <= 90 && appTempLinieRomb[2][2]==1) {
            cout << " click dreapta" << endl;
            clickdr[2][2] = 1;
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    //press = false;
    int ok = 0;
    mouseY = 720 - mouseY;
    if (button == 1 && press == true) {
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 260 && mouseY <= 340) {
            linieR[0] = 1;
            coloanaR[0] = 1;
            pozitie.push_back(0);
            pozitie.push_back(0);
            press = false;
            ok = 1;
            clrrmb[0][0] = -1;
        }else
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 135 && mouseY <= 215) {
            linieR[1] = 1;
            coloanaR[0] = 1;
            pozitie.push_back(1);
            pozitie.push_back(0);
            press = false;
            ok = 1;
            clrrmb[1][0] = -1;
        }else
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 10 && mouseY <= 90) {
            linieR[2] = 1;
            coloanaR[0] = 1;
            pozitie.push_back(2);
            pozitie.push_back(0);
            press = false;
            ok = 1;
            clrrmb[2][0] = -1;
        }else
        if (mouseX >= 220 && mouseX <= 320 && mouseY >= 260 && mouseY <= 340) {
            linieR[0] = 1;
            coloanaR[1] = 1;
            pozitie.push_back(0);
            pozitie.push_back(1);
            press = false;
            ok = 1;
            clrrmb[0][1] = -1;
        }else
        if (mouseX >= 220 && mouseX <= 320 && mouseY >= 135 && mouseY <= 215) {
            linieR[1] = 1;
            coloanaR[1] = 1;
            pozitie.push_back(1);
            pozitie.push_back(1);
            press = false;
            ok = 1;
            clrrmb[1][1] = -1;
        }else
        if (mouseX >= 220 && mouseX <= 320 && mouseY >= 10 && mouseY <= 90) {
            linieR[2] = 1;
            coloanaR[1] = 1;
            pozitie.push_back(2);
            pozitie.push_back(1);
            press = false;
            ok = 1; 
            clrrmb[2][1] = -1;
        }else
        if (mouseX >= 340 && mouseX <= 440 && mouseY >= 260 && mouseY <= 340) {
            linieR[0] = 1;
            coloanaR[2] = 1;
            pozitie.push_back(0);
            pozitie.push_back(2);
            press = false;
            ok = 1;
            clrrmb[0][2] = -1;
        }else
        if (mouseX >= 340 && mouseX <= 440 && mouseY >= 135 && mouseY <= 215) {
            linieR[1] = 1;
            coloanaR[2] = 1;
            pozitie.push_back(1);
            pozitie.push_back(2);
            press = false;
            ok = 1;
            clrrmb[1][2] = -1;
        }else
        if (mouseX >= 340 && mouseX <= 440 && mouseY >= 10 && mouseY <= 90) {
            linieR[2] = 1;
            coloanaR[2] = 1;
            pozitie.push_back(2);
            pozitie.push_back(2);
            press = false;
            ok = 1;
            clrrmb[2][2] = -1;
        }
        else {
            press = false;
            if (apasareRomb[0] == 1) {
                nr = nr + 1;
                apasareRomb[0] = 0;
            }
            if (apasareRomb[1] == 1) {
				nr = nr + 2;
				apasareRomb[1] = 0;
			}
            if (apasareRomb[2] == 1) {
                nr = nr + 2;
                apasareRomb[2] = 0;
            }
            if (apasareRomb[3] == 1) {
				nr = nr + 3;
				apasareRomb[3] = 0;
            }
        }
        if (ok == 1) {
            for (int i = 0; i < 4; i++)
                if (apasareRomb[i] == 1) {
                    releaseRomb[i] = 1;
                    apasareRomb[i] = 0;
                    releaseColor.push_back(i);
                }
        }
    }

    if (button == 1 && pressS == true) {
        for (int i = 0; i < steleLinie.size(); i++) {
            if (mouseX >= steleLinie[i] - 30 && mouseX <= steleLinie[i] + 30 && mouseY >= steleColoana[i] - 30 && mouseY <= steleColoana[i] + 30 && steleAfisare[i] == 1 && pressS == true) {
                steleAfisare[i] = 0;
                pressS = false;
            }
        }
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
