#ifndef SRC_CORE_SCENE_HPP_
#define SRC_CORE_SCENE_HPP_

#include <vector>
#include <variant>
#include <memory>
#include <cmath>
#include <glm/glm.hpp>

namespace krayon::core {

/**
 * @class Scene
 * @brief Manages a scene with drawable objects and transformation commands.
 *
 * Uses the Command pattern with std::variant to handle different types of
 * drawing and transformation operations in a unified manner.
 */
class Scene {
 public:
  /**
   * @struct PlotCommand
   * @brief Command to plot a point at specified coordinates.
   */
  struct PlotCommand {
    float x;
    float y;
    float z = 0.0f;
    
    PlotCommand(float x, float y, float z = 0.0f)
        : x(x), y(y), z(z) {}
  };

  /**
   * @struct RotateCommand
   * @brief Command to rotate objects around an axis.
   */
  struct RotateCommand {
    float angle_radians;  ///< Rotation angle in radians
    glm::vec3 axis;       ///< Rotation axis (x, y, z)
    
    RotateCommand(float angle, const glm::vec3& axis = glm::vec3(0.0f, 0.0f, 1.0f))
        : angle_radians(angle), axis(glm::normalize(axis)) {}
    
    RotateCommand(float angle, float ax, float ay, float az)
        : angle_radians(angle), axis(glm::normalize(glm::vec3(ax, ay, az))) {}
  };

  /**
   * @brief Type alias for command variant supporting Plot and Rotate commands.
   */
  using Command = std::variant<PlotCommand, RotateCommand>;

  /**
   * @brief Constructor - initializes an empty scene.
   */
  Scene() = default;

  /**
   * @brief Destructor
   */
  ~Scene() = default;

  /**
   * @brief Plot a point in the scene.
   *
   * @param x X-coordinate
   * @param y Y-coordinate
   * @param z Z-coordinate (default: 0.0f)
   */
  void plot(float x, float y, float z = 0.0f);

  /**
   * @brief Plot a point using glm::vec3.
   *
   * @param position The 3D position to plot
   */
  void plot(const glm::vec3& position);

  /**
   * @brief Rotate the scene around a specified axis.
   *
   * @param angle_radians Rotation angle in radians
   * @param axis Rotation axis as glm::vec3 (default: Z-axis)
   */
  void rotate(float angle_radians, const glm::vec3& axis = glm::vec3(0.0f, 0.0f, 1.0f));

  /**
   * @brief Rotate the scene around a specified axis.
   *
   * @param angle_radians Rotation angle in radians
   * @param ax X component of rotation axis
   * @param ay Y component of rotation axis
   * @param az Z component of rotation axis
   */
  void rotate(float angle_radians, float ax, float ay, float az);

  /**
   * @brief Execute a command on the scene.
   *
   * @param command The command to execute
   */
  void execute_command(const Command& command);

  /**
   * @brief Get all recorded commands.
   *
   * @return const reference to the command history
   */
  const std::vector<Command>& get_commands() const;

  /**
   * @brief Clear all commands from the scene.
   */
  void clear_commands();

  /**
   * @brief Get the current transformation matrix.
   *
   * @return The cumulative transformation matrix
   */
  const glm::mat4& get_transformation_matrix() const;

  /**
   * @brief Reset the transformation matrix to identity.
   */
  void reset_transformation();

  /**
   * @brief Get the number of recorded commands.
   *
   * @return Number of commands in history
   */
  size_t command_count() const;

 private:
  std::vector<Command> commands_;       ///< Command history
  glm::mat4 transformation_matrix_;     ///< Current transformation matrix

  /**
   * @brief Apply a PlotCommand to the scene.
   *
   * @param plot_cmd The plot command to apply
   */
  void apply_plot(const PlotCommand& plot_cmd);

  /**
   * @brief Apply a RotateCommand to the scene.
   *
   * @param rotate_cmd The rotate command to apply
   */
  void apply_rotate(const RotateCommand& rotate_cmd);
};

}  // namespace krayon::core

#endif  // SRC_CORE_SCENE_HPP_
