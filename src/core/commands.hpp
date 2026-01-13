#ifndef KRAYON_CORE_COMMANDS_HPP
#define KRAYON_CORE_COMMANDS_HPP

#include <string>
#include <variant>
#include <vector>

namespace krayon::core {

/// Command to plot data
struct CmdPlot {
    std::string dataSource;      ///< Data source identifier
    std::string outputPath;      ///< Output file path for the plot
    std::string plotType;        ///< Type of plot (e.g., "line", "scatter", "bar")
    std::vector<std::string> axes;  ///< Axes labels and configuration
    bool interactive = false;    ///< Whether the plot should be interactive
};

/// Command to animate a sequence
struct CmdAnimate {
    std::string inputSequence;   ///< Input sequence identifier or path
    std::string outputPath;      ///< Output file path for the animation
    double frameRate = 30.0;     ///< Frames per second for animation
    int totalFrames = 0;         ///< Total number of frames (0 = auto-detect)
    std::string animationType;   ///< Type of animation effect
    bool loop = true;            ///< Whether the animation should loop
};

/// Variant type representing all possible commands
using Command = std::variant<CmdPlot, CmdAnimate>;

}  // namespace krayon::core

#endif  // KRAYON_CORE_COMMANDS_HPP
