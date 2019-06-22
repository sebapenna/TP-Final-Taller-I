#include <Yaml/include/yaml-cpp/yaml.h>
#include "Configuration.h"

#ifdef DEBUG_MODE
    #define CONFIG_FILE "Config/config.yaml"
#else
    #define CONFIG_FILE "/etc/Pörtal/Server/space.yaml"   // todo IF NOT DEBUF CON TODOS LOS ARCHIVOS
#endif

Configuration::Configuration() {
    auto _config = YAML::LoadFile(CONFIG_FILE);

    _gravity_x = _config["gravity_x"].as<float>();
    _gravity_y = _config["gravity_y"].as<float>();
    _FPS = _config["FPS"].as<float>();
    _velocity_iterations = _config["velocity_iterations"].as<float>();
    _position_iterations = _config["position_iterations"].as<float>();
    _move_force = _config["move_force"].as<float>();
    _jump_force = _config["jump_force"].as<float>();

    _block_half_len = _config["half_block_len"].as<float>();
    
    _chell_half_width = _config["chell_half_width"].as<float>();
    _chell_half_height = _config["chell_half_height"].as<float>();
    _chell_density = _config["chell_density"].as<float>();
    _chell_gravity_scale = _config["chell_gravity_scale"].as<float>();
    
    _rock_half_len  = _config["rock_half_len"].as<float>();
    _rock_density  = _config["rock_density"].as<float>();
    
    _acid_half_height = _config["acid_half_height"].as<float>();

    _button_half_width = _config["button_half_width"].as<float>();
    _button_half_height = _config["button_half_height"].as<float>();
    
    _gate_half_width = _config["gate_half_width"].as<float>();
    _gate_half_height = _config["gate_half_height"].as<float>();
    
    _enrg_block_half_len = _config["enrg_block_half_len"].as<float>();
    _time_to_release_enrg_ball = _config["time_to_release"].as<float>();
    
    _energy_ball_radius = _config["enrg_ball_radius"].as<float>();
    _energy_ball_density = _config["enrg_ball_density"].as<float>();
    _energy_ball_force = _config["enrg_ball_force"].as<float>();
    _energy_ball_lifetime = _config["enrg_ball_lifetime"].as<float>();

    _barrier_half_len  = _config["barrier_half_len"].as<float>();
    _barrier_half_width  = _config["barrier_half_width"].as<float>();

    _cake_half_len  = _config["cake_half_len"].as<float>();

    _portal_half_width = _config["portal_half_width"].as<float>();
    _portal_half_height = _config["portal_half_height"].as<float>();
    
    _pintool_half_width = _config["pintool_half_width"].as<float>();
    _pintool_half_height = _config["pintool_half_height"].as<float>();
    _pintool_lifetime = _config["pintool_lifetime"].as<float>();
}

float Configuration::getGravityX() const {
    return _gravity_x;
}

float Configuration::getGravityY() const {
    return _gravity_y;
}

float Configuration::getFps() const {
    return _FPS;
}

float Configuration::getVelocityIterations() const {
    return _velocity_iterations;
}

float Configuration::getPositionIterations() const {
    return _position_iterations;
}

float Configuration::getMoveForce() const {
    return _move_force;
}

float Configuration::getJumpForce() const {
    return _jump_force;
}

float Configuration::getBlockHalfLen() const {
    return _block_half_len;
}

float Configuration::getChellHalfWidth() const {
    return _chell_half_width;
}

float Configuration::getChellHalfHeight() const {
    return _chell_half_height;
}

float Configuration::getChellDensity() const {
    return _chell_density;
}

float Configuration::getChellGravityScale() const {
    return _chell_gravity_scale;
}

float Configuration::getRockHalfLen() const {
    return _rock_half_len;
}

float Configuration::getRockDensity() const {
    return _rock_density;
}

float Configuration::getAcidHalfHeight() const {
    return _acid_half_height;
}

float Configuration::getButtonHalfWidth() const {
    return _button_half_width;
}

float Configuration::getButtonHalfHeight() const {
    return _button_half_height;
}

float Configuration::getGateHalfWidth() const {
    return _gate_half_width;
}

float Configuration::getGateHalfHeight() const {
    return _gate_half_height;
}

float Configuration::getEnergyBlockHalfLen() const {
    return _enrg_block_half_len;
}

float Configuration::getTimeToReleaseEnrgBall() const {
    return _time_to_release_enrg_ball;
}

float Configuration::getEnergyBallRadius() const {
    return _energy_ball_radius;
}

float Configuration::getEnergyBallDensity() const {
    return _energy_ball_density;
}

float Configuration::getEnergyBallForce() const {
    return _energy_ball_force;
}

float Configuration::getEnergyBallLifetime() const {
    return _energy_ball_lifetime;
}

float Configuration::getBarrierHalfLen() const {
    return _barrier_half_len;
}

float Configuration::getBarrierHalfWidth() const {
    return _barrier_half_width;
}

float Configuration::getCakeHalfLen() const {
    return _cake_half_len;
}

float Configuration::getPortalHalfWidth() const {
    return _portal_half_width;
}

float Configuration::getPortalHalfHeight() const {
    return _portal_half_height;
}

float Configuration::getPintoolHalfWidth() const {
    return _pintool_half_width;
}

float Configuration::getPintoolHalfHeight() const {
    return _pintool_half_height;
}

float Configuration::getPintoolLifetime() const {
    return _pintool_lifetime;
}
