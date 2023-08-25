#ifndef ATG_ENGINE_SIM_VEHICLE_H
#define ATG_ENGINE_SIM_VEHICLE_H

#include "scs.h"

class Vehicle {
    public:
        struct Parameters {
            double mass;
            double dragCoefficient;
            double crossSectionArea;
            double diffRatio;
            double tireRadius;
            double rollingResistance;
        };

    public:
        Vehicle();
        virtual ~Vehicle();

        virtual void initialize(const Parameters &params);
        virtual void update(double dt);
        virtual void addToSystem(atg_scs::RigidBodySystem *system, atg_scs::RigidBody *rotatingMass);

        virtual double getSpeed() const;
        virtual double linearForceToVirtualTorque(double force) const;

        inline double getMass() const { return m_mass; }
        inline double getRollingResistance() const { return m_rollingResistance; }
        inline double getDragCoefficient() const { return m_dragCoefficient; }
        inline double getCrossSectionArea() const { return m_crossSectionArea; }
        inline double getDiffRatio() const { return m_diffRatio; }
        inline double getTireRadius() const { return m_tireRadius; }
        inline double getTravelledDistance() const { return m_travelledDistance; }
        inline void resetTravelledDistance() { m_travelledDistance = 0; }

    protected:
        atg_scs::RigidBody *m_rotatingMass;

        double m_mass;
        double m_dragCoefficient;
        double m_crossSectionArea;
        double m_diffRatio;
        double m_tireRadius;
        double m_travelledDistance;
        double m_rollingResistance;
};

#endif /* ATG_ENGINE_SIM_VEHICLE_H */
