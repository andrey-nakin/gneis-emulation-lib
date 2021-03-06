#ifndef isnp_generator_SpallationMessenger_hh
#define isnp_generator_SpallationMessenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcommand.hh>
#include <G4UIcmdWithAString.hh>

#include "isnp/generator/Spallation.hh"

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

namespace isnp {

namespace generator {

class SpallationMessenger: public G4UImessenger {
public:

	SpallationMessenger(Spallation& spallation);
	~SpallationMessenger();

	G4String GetCurrentValue(G4UIcommand*) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	Spallation& spallation;
	std::unique_ptr<G4UIdirectory> const directory;
	std::unique_ptr<G4UIcmdWithADoubleAndUnit> const diameterCmd, xWidthCmd,
			yWidthCmd, positionXCmd, positionYCmd;
	std::unique_ptr<G4UIcmdWithAnInteger> const verboseCmd;
	std::unique_ptr<G4UIcmdWithAString> const modeCmd;

	static G4String ModeToString(Spallation::Mode mode);
	static Spallation::Mode StringToMode(G4String const& mode);

};

}

}

#endif	//	isnp_generator_SpallationMessenger_hh
