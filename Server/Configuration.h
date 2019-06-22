#ifndef PORTAL_CONFIGURATION_H
#define PORTAL_CONFIGURATION_H

#include <mutex>

// Configuracion almacenada en archivo yaml
class Configuration {
private:
    float _gravity_x;
    float _gravity_y;
    float _FPS;
    float _velocity_iterations;
    float _position_iterations;
    float _move_force;
    float _jump_force;
    
    float _block_half_len;
    
    float _chell_half_width;
    float _chell_half_height;
    float _chell_density;
    float _chell_gravity_scale;
    
    float _rock_half_len;
    float _rock_density;
    
    float _acid_half_height;
    
    float _button_half_width;
    float _button_half_height;
    
    float _gate_half_width;
    float _gate_half_height;

    float _enrg_block_half_len;
    float _time_to_release_enrg_ball;

    float _energy_ball_radius;
    float _energy_ball_density;
    float _energy_ball_force;
    float _energy_ball_lifetime;

    float _barrier_half_len;
    float _barrier_half_width;

    float _cake_half_len;

    float _portal_half_width;
    float _portal_half_height;

    float _pintool_half_width;
    float _pintool_half_height;
    float _pintool_lifetime;

public:
    Configuration();

    float getGravityX() const;

    float getGravityY() const;

    float getFps() const;

    float getVelocityIterations() const;

    float getPositionIterations() const;

    float getMoveForce() const;

    float getJumpForce() const;

    float getBlockHalfLen() const;

    float getChellHalfWidth() const;

    float getChellHalfHeight() const;

    float getChellDensity() const;

    float getChellGravityScale() const;

    float getRockHalfLen() const;

    float getRockDensity() const;

    float getAcidHalfHeight() const;

    float getButtonHalfWidth() const;

    float getButtonHalfHeight() const;

    float getGateHalfWidth() const;

    float getGateHalfHeight() const;

    float getEnergyBlockHalfLen() const;

    float getTimeToReleaseEnrgBall() const;

    float getEnergyBallRadius() const;

    float getEnergyBallDensity() const;

    float getEnergyBallForce() const;

    float getEnergyBallLifetime() const;

    float getBarrierHalfLen() const;

    float getBarrierHalfWidth() const;

    float getCakeHalfLen() const;

    float getPortalHalfWidth() const;

    float getPortalHalfHeight() const;

    float getPintoolHalfWidth() const;

    float getPintoolHalfHeight() const;

    float getPintoolLifetime() const;
};


#endif //PORTAL_CONFIGURATION_H
