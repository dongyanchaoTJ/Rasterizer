#include <iostream>
#include <vector>

#include "World.h"
#include "Renderer.h"
#include "Rasterizer.h"
#include "Camera.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "Constants.h"

GeometryObject* cube = new GeometryObject(Colors::RED, Materials::PLASTIC, 
  std::vector<Point3D> {
    Point3D(50, -50, 1),
    Point3D(50, 50, 1),
    Point3D(100, 50, 1),
    Point3D(100, -50, 1),

    Point3D(50, -50, 20),
    Point3D(50, 50, 20),
    Point3D(100, 50, 20),
    Point3D(100, -50, 20),
  }, 
  std::vector<uint32_t> {
      0, 1, 2,
      2, 3, 0,

      3, 2, 6,
      6, 7, 3,

      //6, 5, 4,
      //4, 7, 6,

      1, 5, 4,
      4, 0, 1,

      //1, 2, 6,
      //6, 5, 1
  });

GeometryObject* ground = new GeometryObject(Colors::GREY, Materials::WALL,
  std::vector<Point3D> {
    Point3D(-350, -450, -10),
    Point3D(350, -450, 50),
    Point3D(350, -450, -10),
    //Point3D(-250, -250, 15),
  },
  std::vector<uint32_t> {
      0, 1, 2,
      //0, 3, 1
  });
const std::vector<GeometryObject*> OBJECTS {
  cube, 
  //ground
};

const std::vector<Light*> LIGHTS {
  new PointLight(RGBColor(1.0f), Point3D(0.0f, 100.0f, -100.0f))
};

Camera * camera;

int main (){
    World * world = new World(OBJECTS, LIGHTS, camera);
    Renderer * renderer = new Rasterizer(world);

#ifdef _ORTHOGRAPHIC
    camera = new OrthographicCamera(CAMERA_POS, IMAGE_HEIGHT, IMAGE_WIDTH, renderer);
#endif 

#ifdef _PERSPECTIVE
    camera = new PerspectiveCamera(CAMERA_POS, IMAGE_HEIGHT, IMAGE_WIDTH, renderer);
#endif 
    world->m_camera = camera;
    camera->render(IMAGE_NAME);
    
    return 0;
}