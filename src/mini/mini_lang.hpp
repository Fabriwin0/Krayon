#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <variant>
#include <optional>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace krayon::mini {

/**
 * @file mini_lang.hpp
 * @brief Mini language DSL implementation for scene commands in Krayon
 * 
 * This header defines a lightweight domain-specific language for describing
 * and executing scene commands. The DSL supports:
 * - Command definitions and execution
 * - Parameter binding and validation
 * - Scene manipulation operations
 * - Extensible command registry
 */

// Forward declarations
class SceneCommand;
class CommandContext;
class MiniLangParser;

/**
 * @brief Represents a value in the mini language
 * Can be a number, string, boolean, or null
 */
using MiniValue = std::variant<
    std::monostate,  // null
    double,
    std::string,
    bool
>;

/**
 * @brief Parameter definition for scene commands
 */
struct Parameter {
    std::string name;
    std::string type;  // "number", "string", "bool", "any"
    bool required = true;
    MiniValue default_value;
    std::string description;
};

/**
 * @brief Result of command execution
 */
struct CommandResult {
    bool success = true;
    std::string message;
    MiniValue return_value;
    
    CommandResult() = default;
    
    CommandResult(bool success, const std::string& msg = "", 
                  const MiniValue& value = std::monostate())
        : success(success), message(msg), return_value(value) {}
};

/**
 * @brief Context for command execution
 */
class CommandContext {
public:
    CommandContext() = default;
    
    /**
     * @brief Set a variable in the context
     */
    void set_variable(const std::string& name, const MiniValue& value) {
        variables[name] = value;
    }
    
    /**
     * @brief Get a variable from the context
     */
    std::optional<MiniValue> get_variable(const std::string& name) const {
        auto it = variables.find(name);
        if (it != variables.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    /**
     * @brief Check if a variable exists
     */
    bool has_variable(const std::string& name) const {
        return variables.find(name) != variables.end();
    }
    
    /**
     * @brief Clear all variables
     */
    void clear_variables() {
        variables.clear();
    }
    
    /**
     * @brief Get the current scene id (if available)
     */
    std::optional<std::string> get_scene_id() const {
        return scene_id;
    }
    
    /**
     * @brief Set the current scene id
     */
    void set_scene_id(const std::string& id) {
        scene_id = id;
    }

private:
    std::map<std::string, MiniValue> variables;
    std::optional<std::string> scene_id;
};

/**
 * @brief Base class for scene commands
 */
class SceneCommand {
public:
    virtual ~SceneCommand() = default;
    
    /**
     * @brief Get the command name
     */
    virtual std::string get_name() const = 0;
    
    /**
     * @brief Get command description
     */
    virtual std::string get_description() const = 0;
    
    /**
     * @brief Get parameter definitions
     */
    virtual std::vector<Parameter> get_parameters() const = 0;
    
    /**
     * @brief Execute the command with given parameters
     */
    virtual CommandResult execute(const std::map<std::string, MiniValue>& params,
                                  CommandContext& context) = 0;
    
    /**
     * @brief Validate parameters
     */
    virtual CommandResult validate_parameters(
        const std::map<std::string, MiniValue>& params) const;
};

/**
 * @brief Tokenizer for mini language
 */
class Tokenizer {
public:
    enum class TokenType {
        End,
        Identifier,
        Number,
        String,
        OpenParen,
        CloseParen,
        OpenBrace,
        CloseBrace,
        Comma,
        Colon,
        Equals,
        Semicolon,
        Arrow,
        Plus,
        Minus,
        Multiply,
        Divide,
        Keyword
    };
    
    struct Token {
        TokenType type;
        std::string value;
        size_t position = 0;
    };
    
    /**
     * @brief Tokenize input string
     */
    static std::vector<Token> tokenize(const std::string& input);
    
private:
    static bool is_identifier_char(char c);
    static bool is_digit(char c);
    static TokenType get_keyword_type(const std::string& value);
};

/**
 * @brief Parser for mini language
 */
class MiniLangParser {
public:
    /**
     * @brief Parse a command string
     * @param input The command string to parse
     * @return Parsed command with parameters, or empty if parse failed
     */
    struct ParsedCommand {
        std::string command_name;
        std::map<std::string, MiniValue> parameters;
        bool valid = false;
    };
    
    explicit MiniLangParser() = default;
    
    /**
     * @brief Parse a single command line
     */
    ParsedCommand parse_command(const std::string& input);
    
    /**
     * @brief Parse multiple commands from input
     */
    std::vector<ParsedCommand> parse_commands(const std::string& input);
    
private:
    std::vector<Tokenizer::Token> tokens;
    size_t current = 0;
    
    Tokenizer::Token peek() const;
    Tokenizer::Token advance();
    bool match(Tokenizer::TokenType type);
    bool check(Tokenizer::TokenType type) const;
    
    MiniValue parse_value();
    std::string parse_identifier();
    double parse_number();
    std::string parse_string();
};

/**
 * @brief Registry for scene commands
 */
class CommandRegistry {
public:
    /**
     * @brief Register a command
     */
    void register_command(std::shared_ptr<SceneCommand> command) {
        commands[command->get_name()] = command;
    }
    
    /**
     * @brief Get a command by name
     */
    std::shared_ptr<SceneCommand> get_command(const std::string& name) const {
        auto it = commands.find(name);
        if (it != commands.end()) {
            return it->second;
        }
        return nullptr;
    }
    
    /**
     * @brief Check if a command exists
     */
    bool has_command(const std::string& name) const {
        return commands.find(name) != commands.end();
    }
    
    /**
     * @brief Get all registered commands
     */
    std::vector<std::string> get_all_commands() const {
        std::vector<std::string> names;
        for (const auto& pair : commands) {
            names.push_back(pair.first);
        }
        return names;
    }
    
    /**
     * @brief Clear all commands
     */
    void clear() {
        commands.clear();
    }

private:
    std::map<std::string, std::shared_ptr<SceneCommand>> commands;
};

/**
 * @brief Mini language executor
 */
class MiniLangExecutor {
public:
    explicit MiniLangExecutor(std::shared_ptr<CommandRegistry> registry)
        : registry(registry) {}
    
    /**
     * @brief Execute a command string
     */
    CommandResult execute(const std::string& input, CommandContext& context);
    
    /**
     * @brief Execute multiple commands
     */
    std::vector<CommandResult> execute_batch(const std::string& input,
                                             CommandContext& context);
    
    /**
     * @brief Execute a parsed command
     */
    CommandResult execute_parsed(const MiniLangParser::ParsedCommand& parsed,
                                CommandContext& context);

private:
    std::shared_ptr<CommandRegistry> registry;
    MiniLangParser parser;
};

/**
 * @brief Helper class for converting MiniValue
 */
class ValueConverter {
public:
    /**
     * @brief Convert MiniValue to string
     */
    static std::string to_string(const MiniValue& value);
    
    /**
     * @brief Convert MiniValue to number
     */
    static std::optional<double> to_number(const MiniValue& value);
    
    /**
     * @brief Convert MiniValue to bool
     */
    static std::optional<bool> to_bool(const MiniValue& value);
    
    /**
     * @brief Create MiniValue from string
     */
    static MiniValue from_string(const std::string& value);
    
    /**
     * @brief Create MiniValue from double
     */
    static MiniValue from_number(double value);
    
    /**
     * @brief Create MiniValue from bool
     */
    static MiniValue from_bool(bool value);
    
    /**
     * @brief Get type name of MiniValue
     */
    static std::string get_type_name(const MiniValue& value);
    
    /**
     * @brief Check if value matches expected type
     */
    static bool matches_type(const MiniValue& value, const std::string& type);
};

/**
 * @brief Built-in scene commands
 */
namespace builtin_commands {

/**
 * @brief Command to create a new scene element
 */
class CreateElementCommand : public SceneCommand {
public:
    std::string get_name() const override { return "create_element"; }
    
    std::string get_description() const override {
        return "Create a new scene element";
    }
    
    std::vector<Parameter> get_parameters() const override {
        return {
            {"type", "string", true, std::monostate(), "Element type"},
            {"name", "string", true, std::monostate(), "Element name"},
            {"x", "number", false, 0.0, "X coordinate"},
            {"y", "number", false, 0.0, "Y coordinate"}
        };
    }
    
    CommandResult execute(const std::map<std::string, MiniValue>& params,
                         CommandContext& context) override;
};

/**
 * @brief Command to delete a scene element
 */
class DeleteElementCommand : public SceneCommand {
public:
    std::string get_name() const override { return "delete_element"; }
    
    std::string get_description() const override {
        return "Delete a scene element";
    }
    
    std::vector<Parameter> get_parameters() const override {
        return {
            {"id", "string", true, std::monostate(), "Element ID"}
        };
    }
    
    CommandResult execute(const std::map<std::string, MiniValue>& params,
                         CommandContext& context) override;
};

/**
 * @brief Command to modify element properties
 */
class SetPropertyCommand : public SceneCommand {
public:
    std::string get_name() const override { return "set_property"; }
    
    std::string get_description() const override {
        return "Set a property of a scene element";
    }
    
    std::vector<Parameter> get_parameters() const override {
        return {
            {"id", "string", true, std::monostate(), "Element ID"},
            {"property", "string", true, std::monostate(), "Property name"},
            {"value", "any", true, std::monostate(), "Property value"}
        };
    }
    
    CommandResult execute(const std::map<std::string, MiniValue>& params,
                         CommandContext& context) override;
};

/**
 * @brief Command to query element properties
 */
class GetPropertyCommand : public SceneCommand {
public:
    std::string get_name() const override { return "get_property"; }
    
    std::string get_description() const override {
        return "Get a property of a scene element";
    }
    
    std::vector<Parameter> get_parameters() const override {
        return {
            {"id", "string", true, std::monostate(), "Element ID"},
            {"property", "string", true, std::monostate(), "Property name"}
        };
    }
    
    CommandResult execute(const std::map<std::string, MiniValue>& params,
                         CommandContext& context) override;
};

/**
 * @brief Command to apply a transformation
 */
class TransformCommand : public SceneCommand {
public:
    std::string get_name() const override { return "transform"; }
    
    std::string get_description() const override {
        return "Apply transformation to an element";
    }
    
    std::vector<Parameter> get_parameters() const override {
        return {
            {"id", "string", true, std::monostate(), "Element ID"},
            {"operation", "string", true, std::monostate(), "Transform operation (move, rotate, scale)"},
            {"x", "number", false, 0.0, "X parameter"},
            {"y", "number", false, 0.0, "Y parameter"},
            {"z", "number", false, 0.0, "Z parameter"}
        };
    }
    
    CommandResult execute(const std::map<std::string, MiniValue>& params,
                         CommandContext& context) override;
};

}  // namespace builtin_commands

}  // namespace krayon::mini
