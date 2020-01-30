//========================================================================================================
/// ClimberHold.h
//========================================================================================================
///
/// File Description:
///     This controls the "hold" function of the climber
///
//========================================================================================================

#include <subsys/IMechanism.h>
#include <controllers/IState.h>

class ClimberHold : public IState
{
    public:

    ClimberHold();
    ~ClimberHold() = default;

    void Init() override;
    void Run()  override;
    bool AtTarget() const override;

    private:

    IMechanism* m_climber;

};