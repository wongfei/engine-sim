#ifndef ATG_ENGINE_SIM_DYNAMOMETER_H
#define ATG_ENGINE_SIM_DYNAMOMETER_H

#include "scs.h"

#include "crankshaft.h"

class Dynamometer : public atg_scs::Constraint {
    public:
        Dynamometer();
        virtual ~Dynamometer();

        virtual void connectCrankshaft(Crankshaft *crankshaft);
        virtual void calculate(Output *output, atg_scs::SystemState *state);
        virtual double getTorque() const;

        double m_rotationSpeed;
        double m_ks;
        double m_kd;
        double m_maxTorque;

        bool m_hold;
        bool m_enabled;
};

#endif /* ATG_ENGINE_SIM_DYNAMOMETER_H */
