/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TOMLLoader.cpp
*/

/**
 * @file TOMLLoader.cpp
 *
 * @brief This is the file in charge of containing the functions for the class that will handle the loading and navigation of the TOML language.
 */

#include "TOMLLoader.hpp"

TOMLLoader::TOMLLoader()
{
    _loadNodeTypeEquivalence();
};

TOMLLoader::TOMLLoader(const std::string &tomlPath)
{
    setTOMLPath(tomlPath);
    _loadNodeTypeEquivalence();
};

TOMLLoader::TOMLLoader(const TOMLLoader &tomlInstance)
{
    update(tomlInstance);
};

TOMLLoader::TOMLLoader(const toml::table &tomlTable, const std::string &tomlPath)
{
    _toml = tomlTable;
    _tomlLoaded = true;
    _tomlPath = tomlPath;
    _loadNodeTypeEquivalence();
};

TOMLLoader::TOMLLoader(const toml::array &tomlArray, const std::string &tomlPath)
{
    _tomlLoaded = true;
    update(tomlArray);
    _tomlPath = tomlPath;
    _loadNodeTypeEquivalence();
};

TOMLLoader::TOMLLoader(const toml::array &tomlArray, const std::string &key, const std::string &tomlPath)
{
    _tomlLoaded = true;
    update(tomlArray);
    _tomlPath = tomlPath;
    _loadNodeTypeEquivalence();
};

void TOMLLoader::setTOMLPath(const std::string &tomlPath)
{
    _tomlPath = tomlPath;
    _loadTOML();
};

const bool TOMLLoader::isTOMLLoaded() const
{
    return _tomlLoaded;
};

const std::string TOMLLoader::getTOMLPath() const
{
    return _tomlPath;
};

const std::string TOMLLoader::getTOMLString() const
{
    _ensureLoaded();
    return _tomlString;
};

const toml::table TOMLLoader::getRawTOML() const
{
    _ensureLoaded();
    return _toml;
};

const toml::node_type TOMLLoader::getValueType(const std::string &key) const
{
    _ensureLoaded();
    if (!hasKey(key)) {
        throw CustomExceptions::NoTOMLKey(_tomlPath, key);
    }
    return _toml[key].type();
}

const std::string TOMLLoader::getValueTypeAsString(const std::string &key) const
{
    _ensureLoaded();
    toml::node_type nodeType = getValueType(key);
    auto it = _nodeTypeEquivalence.find(nodeType);
    if (it != _nodeTypeEquivalence.end()) {
        return it->second;
    }
    return "unknown";
}

const std::string TOMLLoader::getTypeAsString(const std::string &key) const
{
    return getValueTypeAsString(key);
}

const std::string TOMLLoader::getTypeAsString(const toml::node_type &type) const
{
    auto it = _nodeTypeEquivalence.find(type);
    if (it != _nodeTypeEquivalence.end()) {
        return it->second;
    }
    return "unknown";
}

const bool TOMLLoader::hasKey(const std::string &key) const
{
    _ensureLoaded();
    return _toml.contains(key);
};

std::vector<std::string> TOMLLoader::getKeys() const
{
    _ensureLoaded();
    std::vector<std::string> keys;
    for (const auto &[key, _] : _toml) {
        keys.push_back(std::string(key));
    }
    return keys;
};

toml::table TOMLLoader::getTable(const std::string &key) const
{
    _ensureLoaded();
    if (auto table = _toml[key].as_table()) {
        return *table;
    }
    throw CustomExceptions::NoTOMLKey(_tomlPath, key);
};

toml::array TOMLLoader::getArray(const std::string &key) const
{
    _ensureLoaded();
    if (auto array = _toml[key].as_array()) {
        return *array;
    }
    throw CustomExceptions::NoTOMLKey(_tomlPath, key);
};

void TOMLLoader::update(const TOMLLoader &copy)
{
    _tomlLoaded = copy.isTOMLLoaded();
    if (!_tomlLoaded) {
        return;
    }
    _tomlPath = copy.getTOMLPath();
    _toml = copy.getRawTOML();
}

void TOMLLoader::update(const toml::table &copy)
{
    _toml = copy;
    _tomlLoaded = true;
}

void TOMLLoader::update(const toml::array &copy)
{
    _toml = toml::table{ {"array", copy} };
    _tomlLoaded = true;
}

void TOMLLoader::update(const toml::array &copy, const std::string &key)
{
    _toml = toml::table{ {key, copy} };
    _tomlLoaded = true;
}

void TOMLLoader::printTOML() const
{
    _ensureLoaded();
    PRETTY_INFO << "TOML Contents:\n" + _tomlString << std::endl;
};

TOMLLoader &TOMLLoader::operator=(const TOMLLoader &copy)
{
    update(copy);
    return *this;
}

TOMLLoader &TOMLLoader::operator=(const toml::table &copy)
{
    update(copy);
    return *this;
}

TOMLLoader &TOMLLoader::operator=(const toml::array &copy)
{
    update(copy);
    return *this;
}

void TOMLLoader::_loadTOML()
{
    _tomlLoaded = false;
    try {
        _toml = toml::parse_file(_tomlPath);
    }
    catch (const toml::parse_error &e) {
        throw CustomExceptions::InvalidTOML(_tomlPath, e.what());
    }
    std::ostringstream oss;
    oss << _toml;
    _tomlString = oss.str();
    _tomlLoaded = true;
};

void TOMLLoader::_ensureLoaded() const
{
    if (!_tomlLoaded) {
        throw CustomExceptions::NoTOML(_tomlPath);
    }
};

void TOMLLoader::_loadNodeTypeEquivalence()
{
    _nodeTypeEquivalence[toml::node_type::none] = "none";
    _nodeTypeEquivalence[toml::node_type::date] = "date";
    _nodeTypeEquivalence[toml::node_type::time] = "time";
    _nodeTypeEquivalence[toml::node_type::table] = "table";
    _nodeTypeEquivalence[toml::node_type::array] = "array";
    _nodeTypeEquivalence[toml::node_type::string] = "string";
    _nodeTypeEquivalence[toml::node_type::integer] = "integer";
    _nodeTypeEquivalence[toml::node_type::boolean] = "boolean";
    _nodeTypeEquivalence[toml::node_type::date_time] = "date_time";
    _nodeTypeEquivalence[toml::node_type::floating_point] = "floating_point";
}

std::ostream &operator<<(std::ostream &os, const TOMLLoader &node)
{
    os << node.getTOMLString();
    return os;
};
