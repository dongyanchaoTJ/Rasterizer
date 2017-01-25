#include "OrthographicCamera.h"
#include <limits>
OrthographicCamera::OrthographicCamera()
  : Camera() {

}

OrthographicCamera::OrthographicCamera(const Point3D& position, const uint32_t image_height, const uint32_t image_width)
  : Camera(position, image_height, image_width) {

}

OrthographicCamera::~OrthographicCamera() {

}

const Point3D OrthographicCamera::viewTransform(const Point3D& point_world) const {
  const Point3D point_camera = {
    point_world.x * m_left.x + point_world.y * m_up.x + point_world.z * m_forward.x + m_position.x,
    point_world.x * m_left.y + point_world.y * m_up.y + point_world.z * m_forward.y + m_position.y,
    point_world.x * m_left.z + point_world.y * m_up.z + point_world.z * m_forward.z + m_position.z
  };
  return point_camera;
}

const Point2D OrthographicCamera::projectTransform(const Point3D& point_camera) const {
  const Point2D point_projected = {
    (float)((point_camera.x )),
    (float)((point_camera.y ))
  };

  const double slopeX = 1.0 / (m_image_width);
  const double slopeY = 1.0 / (m_image_height);

  const Point2D point_ndc = {
    (float) (slopeX * (point_projected.x + m_image_width / 2.0)),
    (float) (slopeY * (point_projected.y + m_image_height / 2.0))
  };
  return point_ndc;
}

const Vector3D OrthographicCamera::viewDirection(const Point3D point) const {
  return m_forward;
}